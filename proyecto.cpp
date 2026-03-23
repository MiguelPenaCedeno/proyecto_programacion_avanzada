#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Equipo {
    int codigo;
    char nombre[50];
    char laboratorio[50];
    char tipo[30];
    char estado[20];
    int costo_estimado;
    int semestre_minimo;
    char descripcion[100];
};

struct Usuario {
    int codigo_institucional;
    char nombre[50];
    char programa_academico[50];
    int semestre;
};

struct SesionUso {
    int codigo_sesion;
    int codigo_equipo;
    int codigo_usuario;
    char fecha[20];
    int duracion_programada;
    int duracion_real;
    char observaciones[100];
    double penalizacion;
    bool cerrada;
};

void cargarEquipos(Equipo*& equipos, int& num_equipos);
void cargarUsuarios(Usuario*& usuarios, int& num_usuarios);
void consultarEstadoOperativo(Equipo* equipos, int num_equipos);
void programarSesionUso(Equipo* equipos, int num_equipos, Usuario* usuarios, int num_usuarios, int& siguiente_sesion);
void registrarCierreSesion(Equipo* equipos, int num_equipos);
void generarInformeUso(Equipo* equipos, int num_equipos);
void generarRankingUsuarios(Usuario* usuarios, int num_usuarios);

int main() {
    Equipo* equipos = nullptr;
    int num_equipos = 0;

    Usuario* usuarios = nullptr;
    int num_usuarios = 0;

    int siguiente_sesion = 1;
    int menu;

    ifstream archivo_inicio("sesiones.dat", ios::binary);
    if (archivo_inicio) {
        SesionUso sesion_temp;
        while (archivo_inicio.read(reinterpret_cast<char*>(&sesion_temp), sizeof(SesionUso))) {
            if (sesion_temp.codigo_sesion >= siguiente_sesion) {
                siguiente_sesion = sesion_temp.codigo_sesion + 1;
            }
        }
        archivo_inicio.close();
    }

    cout << "Bienvenido al sistema de gestion de equipos de laboratorio" << endl;

    do {
        cout << "\n1. Cargar equipos desde archivo de texto" << endl;
        cout << "2. Cargar usuarios desde archivo de texto" << endl;
        cout << "3. Consultar estado operativo del laboratorio" << endl;
        cout << "4. Programar una sesion de uso de equipo" << endl;
        cout << "5. Registrar cierre de sesion y observaciones" << endl;
        cout << "6. Generar informe de uso intensivo de equipos" << endl;
        cout << "7. Generar ranking de usuarios criticos" << endl;
        cout << "8. Salir" << endl;

        char entrada[10];
        menu = 0;
        while (menu < 1 || menu > 8) {
            cout << "Ingrese su eleccion: ";
            cin.getline(entrada, 10);
            menu = atoi(entrada);
            if (menu < 1 || menu > 8) {
                cout << "Opcion no valida, intente nuevamente." << endl;
            }
        }

        switch (menu) {
            case 1:
                cargarEquipos(equipos, num_equipos);
                break;
            case 2:
                cargarUsuarios(usuarios, num_usuarios);
                break;
            case 3:
                consultarEstadoOperativo(equipos, num_equipos);
                break;
            case 4:
                programarSesionUso(equipos, num_equipos, usuarios, num_usuarios, siguiente_sesion);
                break;
            case 5:
                registrarCierreSesion(equipos, num_equipos);
                break;
            case 6:
                generarInformeUso(equipos, num_equipos);
                break;
            case 7:
                generarRankingUsuarios(usuarios, num_usuarios);
                break;
            case 8:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida, intente nuevamente." << endl;
        }
    } while (menu != 8);

    if (equipos != nullptr) {
        delete[] equipos;
    }
    if (usuarios != nullptr) {
        delete[] usuarios;
    }

    return 0;
}

void cargarEquipos(Equipo*& equipos, int& num_equipos) {
    char nombre_archivo[100];
    cout << "Ingrese el nombre del archivo de equipos: ";
    cin.getline(nombre_archivo, 100);

    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "Error: no se pudo abrir el archivo" << endl;
        return;
    }

    int n = 0;
    char linea[500];
    while (archivo.getline(linea, 500)) {
        if (strlen(linea) > 0) {
            n++;
        }
    }
    archivo.close();

    if (equipos != nullptr) {
        delete[] equipos;
    }

    equipos = new Equipo[n];
    num_equipos = n;

    archivo.open(nombre_archivo);
    Equipo* ptr = equipos;
    char campo[100];
    char* inicio;
    char* fin;

    while (archivo.getline(campo, 100, '*')) {
        ptr->codigo = atoi(campo);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->nombre, inicio);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->laboratorio, inicio);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->tipo, inicio);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->estado, inicio);

        archivo.getline(campo, 100, '*');
        ptr->costo_estimado = atoi(campo);

        archivo.getline(campo, 100, '*');
        ptr->semestre_minimo = atoi(campo);

        archivo.getline(campo, 100);
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->descripcion, inicio);

        ptr++;
    }
    archivo.close();

    cout << "Se cargaron " << num_equipos << " equipos" << endl;
    ptr = equipos;
    for (int i = 0; i < num_equipos; i++) {
        cout << (ptr + i)->codigo << " - " << (ptr + i)->nombre
             << ", " << (ptr + i)->laboratorio
             << ", " << (ptr + i)->estado << endl;
    }
}

void cargarUsuarios(Usuario*& usuarios, int& num_usuarios) {
    char nombre_archivo[100];
    cout << "Ingrese el nombre del archivo de usuarios: ";
    cin.getline(nombre_archivo, 100);

    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "Error: no se pudo abrir el archivo" << endl;
        return;
    }

    int n = 0;
    char linea[500];
    while (archivo.getline(linea, 500)) {
        if (strlen(linea) > 0) {
            n++;
        }
    }
    archivo.close();

    if (usuarios != nullptr) {
        delete[] usuarios;
    }

    usuarios = new Usuario[n];
    num_usuarios = n;

    archivo.open(nombre_archivo);
    Usuario* ptr = usuarios;
    char campo[100];
    char* inicio;
    char* fin;

    while (archivo.getline(campo, 100, '*')) {
        ptr->codigo_institucional = atoi(campo);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->nombre, inicio);

        archivo.getline(campo, 100, '*');
        inicio = campo;
        while (*inicio == ' ') inicio++;
        fin = campo + strlen(campo) - 1;
        while (fin >= campo && *fin == ' ') {
            *fin = '\0';
            fin--;
        }
        strcpy(ptr->programa_academico, inicio);

        archivo.getline(campo, 100);
        ptr->semestre = atoi(campo);

        ptr++;
    }
    archivo.close();

    cout << "Se cargaron " << num_usuarios << " usuarios" << endl;
    ptr = usuarios;
    for (int i = 0; i < num_usuarios; i++) {
        cout << (ptr + i)->codigo_institucional << " - " << (ptr + i)->nombre
             << ", " << (ptr + i)->programa_academico
             << ", semestre " << (ptr + i)->semestre << endl;
    }
}

void consultarEstadoOperativo(Equipo* equipos, int num_equipos) {
    if (equipos == nullptr || num_equipos == 0) {
        cout << "No hay equipos cargados, use la opcion 1 primero" << endl;
        return;
    }

    char lab[50];
    cout << "Ingrese el nombre del laboratorio: ";
    cin.getline(lab, 50);

    Equipo* ptr = equipos;

    bool encontrado = false;
    for (int i = 0; i < num_equipos; i++) {
        if (strcmp((ptr + i)->laboratorio, lab) == 0) {
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron equipos en ese laboratorio" << endl;
        return;
    }

    cout << "\nEquipos operativos:" << endl;
    for (int i = 0; i < num_equipos; i++) {
        if (strcmp((ptr + i)->laboratorio, lab) == 0 &&
            strcmp((ptr + i)->estado, "operativo") == 0) {
            cout << (ptr + i)->codigo << " - " << (ptr + i)->nombre
                 << ", semestre minimo: " << (ptr + i)->semestre_minimo << endl;
        }
    }

    cout << "\nEquipos en mantenimiento:" << endl;
    for (int i = 0; i < num_equipos; i++) {
        if (strcmp((ptr + i)->laboratorio, lab) == 0 &&
            strcmp((ptr + i)->estado, "en mantenimiento") == 0) {
            cout << (ptr + i)->codigo << " - " << (ptr + i)->nombre << endl;
        }
    }

    cout << "\nEquipos con restriccion por semestre:" << endl;
    for (int i = 0; i < num_equipos; i++) {
        if (strcmp((ptr + i)->laboratorio, lab) == 0 &&
            (ptr + i)->semestre_minimo >= 4) {
            cout << (ptr + i)->codigo << " - " << (ptr + i)->nombre
            << ", requiere semestre " << (ptr + i)->semestre_minimo << endl;
        }
    }
}

void programarSesionUso(Equipo* equipos, int num_equipos, Usuario* usuarios, int num_usuarios, int& siguiente_sesion) {
    if (equipos == nullptr || usuarios == nullptr) {
        cout << "Debe cargar equipos y usuarios primero (opciones 1 y 2)" << endl;
        return;
    }

    int cod_usuario, cod_equipo, duracion;
    char fecha[20];

    char entrada[20];

    cod_usuario = 0;
    while (cod_usuario <= 0) {
        cout << "Ingrese codigo del usuario: ";
        cin.getline(entrada, 20);
        cod_usuario = atoi(entrada);
        if (cod_usuario <= 0) {
            cout << "Entrada no valida, intente nuevamente" << endl;
        }
    }

    Usuario* usuario_encontrado = nullptr;
    Usuario* uptr = usuarios;
    for (int i = 0; i < num_usuarios; i++) {
        if ((uptr + i)->codigo_institucional == cod_usuario) {
            usuario_encontrado = uptr + i;
            break;
        }
    }
    if (usuario_encontrado == nullptr) {
        cout << "Usuario no encontrado" << endl;
        return;
    }

    cod_equipo = 0;
    while (cod_equipo <= 0) {
        cout << "Ingrese codigo del equipo: ";
        cin.getline(entrada, 20);
        cod_equipo = atoi(entrada);
        if (cod_equipo <= 0) {
            cout << "Entrada no valida, intente nuevamente" << endl;
        }
    }

    Equipo* equipo_encontrado = nullptr;
    Equipo* eptr = equipos;
    for (int i = 0; i < num_equipos; i++) {
        if ((eptr + i)->codigo == cod_equipo) {
            equipo_encontrado = eptr + i;
            break;
        }
    }
    if (equipo_encontrado == nullptr) {
        cout << "Equipo no encontrado." << endl;
        return;
    }

    if (strcmp(equipo_encontrado->estado, "operativo") != 0) {
        cout << "El equipo no esta operativo (estado actual: " << equipo_encontrado->estado << ")" << endl;
        return;
    }

    if (usuario_encontrado->semestre < equipo_encontrado->semestre_minimo) {
        cout << "El usuario esta en semestre " << usuario_encontrado->semestre
             << " pero el equipo requiere semestre "
             << equipo_encontrado->semestre_minimo << " minimo" << endl;
        return;
    }

    duracion = 0;
    while (duracion <= 0) {
        cout << "Ingrese duracion estimada (horas): ";
        cin.getline(entrada, 20);
        duracion = atoi(entrada);
        if (duracion <= 0) {
            cout << "La duracion debe ser mayor a 0" << endl;
        }
    }

    cout << "Ingrese fecha (DD/MM/AAAA): ";
    cin.getline(fecha, 20);

    SesionUso sesion;
    sesion.codigo_sesion = siguiente_sesion++;
    sesion.codigo_equipo = equipo_encontrado->codigo;
    sesion.codigo_usuario = usuario_encontrado->codigo_institucional;
    strcpy(sesion.fecha, fecha);
    sesion.duracion_programada = duracion;
    sesion.duracion_real = 0;
    strcpy(sesion.observaciones, "");
    sesion.penalizacion = 0.0;
    sesion.cerrada = false;

    ofstream archivo_binario("sesiones.dat", ios::binary | ios::app);
    if (!archivo_binario) {
        cout << "Error al abrir archivo binario de sesiones." << endl;
        return;
    }
    archivo_binario.write(reinterpret_cast<char*>(&sesion), sizeof(SesionUso));
    archivo_binario.close();

    cout << "\nSesion registrada con codigo " << sesion.codigo_sesion << endl;
    cout << "Equipo: " << equipo_encontrado->nombre << endl;
    cout << "Usuario: " << usuario_encontrado->nombre << endl;
    cout << "Fecha: " << sesion.fecha << endl;
    cout << "Duracion programada: " << sesion.duracion_programada << " horas" << endl;
}

void registrarCierreSesion(Equipo* equipos, int num_equipos) {
    ifstream lectura("sesiones.dat", ios::binary);
    if (!lectura) {
        cout << "No hay sesiones registradas aun" << endl;
        return;
    }

    cout << "\nSesiones abiertas:" << endl;
    SesionUso temp;
    bool hay_abiertas = false;
    while (lectura.read(reinterpret_cast<char*>(&temp), sizeof(SesionUso))) {
        if (!temp.cerrada) {
            cout << "Codigo: " << temp.codigo_sesion
                 << ", equipo: " << temp.codigo_equipo
                 << ", usuario: " << temp.codigo_usuario
                 << ", fecha: " << temp.fecha
                 << ", duracion: " << temp.duracion_programada << "h" << endl;
            hay_abiertas = true;
        }
    }
    lectura.close();

    if (!hay_abiertas) {
        cout << "No hay sesiones abiertas." << endl;
        return;
    }

    char entrada[20];
    int cod_sesion = 0;
    while (cod_sesion <= 0) {
        cout << "Ingrese el codigo de la sesion a cerrar: ";
        cin.getline(entrada, 20);
        cod_sesion = atoi(entrada);
        if (cod_sesion <= 0) {
            cout << "Entrada no valida, intente nuevamente" << endl;
        }
    }

    fstream archivo_binario("sesiones.dat", ios::binary | ios::in | ios::out);

    SesionUso sesion;
    bool encontrada = false;
    long posicion = 0;

    while (archivo_binario.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))) {
        if (sesion.codigo_sesion == cod_sesion) {
            encontrada = true;
            posicion = archivo_binario.tellg();
            posicion -= sizeof(SesionUso);
            break;
        }
    }

    if (!encontrada) {
        cout << "Sesion con codigo " << cod_sesion << " no encontrada" << endl;
        archivo_binario.close();
        return;
    }

    if (sesion.cerrada) {
        cout << "Esta sesion ya fue cerrada anteriormente" << endl;
        archivo_binario.close();
        return;
    }

    int duracion_real = 0;
    cout << "Duracion programada fue: " << sesion.duracion_programada << " horas" << endl;
    while (duracion_real <= 0) {
        cout << "Ingrese duracion real (horas): ";
        cin.getline(entrada, 20);
        duracion_real = atoi(entrada);
        if (duracion_real <= 0) {
            cout << "La duracion debe ser mayor a 0" << endl;
        }
    }

    cout << "Ingrese observaciones tecnicas: ";
    cin.getline(sesion.observaciones, 100);

    sesion.duracion_real = duracion_real;
    sesion.cerrada = true;

    if (duracion_real > sesion.duracion_programada) {
        int horas_extra = duracion_real - sesion.duracion_programada;
        Equipo* eptr = equipos;
        int costo = 0;
        for (int i = 0; i < num_equipos; i++) {
            if ((eptr + i)->codigo == sesion.codigo_equipo) {
                costo = (eptr + i)->costo_estimado;
                break;
            }
        }
        sesion.penalizacion = horas_extra * 0.03 * costo;
        cout << "Penalizacion: " << horas_extra << " hora(s) extra $"
             << sesion.penalizacion << endl;
    }

    char reporta_dano[10];
    cout << "Se reporta daño en el equipo? (s/n): ";
    cin.getline(reporta_dano, 10);

    if (reporta_dano[0] == 's' || reporta_dano[0] == 'S') {
        Equipo* eptr = equipos;
        for (int i = 0; i < num_equipos; i++) {
            if ((eptr + i)->codigo == sesion.codigo_equipo) {
                strcpy((eptr + i)->estado, "en mantenimiento");
                cout << "Equipo " << (eptr + i)->nombre
                     << " marcado como en mantenimiento" << endl;
                break;
            }
        }
    }

    archivo_binario.seekp(posicion);
    archivo_binario.write(reinterpret_cast<char*>(&sesion), sizeof(SesionUso));
    archivo_binario.close();

    cout << "Sesion " << cod_sesion << " cerrada." << endl;
}

void generarInformeUso(Equipo* equipos, int num_equipos) {
    if (equipos == nullptr || num_equipos == 0) {
        cout << "No hay equipos cargados." << endl;
        return;
    }

    ifstream archivo_binario("sesiones.dat", ios::binary);
    if (!archivo_binario) {
        cout << "No hay sesiones registradas." << endl;
        return;
    }

    int* horas_por_equipo = new int[num_equipos];
    Equipo* eptr = equipos;
    for (int i = 0; i < num_equipos; i++) {
        *(horas_por_equipo + i) = 0;
    }

    SesionUso sesion;
    while (archivo_binario.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))) {
        if (sesion.cerrada) {
            for (int i = 0; i < num_equipos; i++) {
                if ((eptr + i)->codigo == sesion.codigo_equipo) {
                    *(horas_por_equipo + i) += sesion.duracion_real;
                    break;
                }
            }
        }
    }
    archivo_binario.close();

    cout << "\nInforme de uso intensivo por laboratorio:" << endl;

    bool* procesado = new bool[num_equipos];
    for (int i = 0; i < num_equipos; i++) {
        *(procesado + i) = false;
    }

    for (int i = 0; i < num_equipos; i++) {
        if (*(procesado + i)) {
            continue;
        }

        char* lab_actual = (eptr + i)->laboratorio;
        int mayor_horas = -1;
        int posicion_mayor = -1;

        for (int j = i; j < num_equipos; j++) {
            if (strcmp((eptr + j)->laboratorio, lab_actual) == 0) {
                *(procesado + j) = true;
                if (*(horas_por_equipo + j) > mayor_horas) {
                    mayor_horas = *(horas_por_equipo + j);
                    posicion_mayor = j;
                }
            }
        }

        if (posicion_mayor >= 0) {
            cout << "--" << lab_actual << ": " << (eptr + posicion_mayor)->nombre
            << " (" << mayor_horas << " horas)" << endl;
        }
    }

    delete[] horas_por_equipo;
    delete[] procesado;
}

void generarRankingUsuarios(Usuario* usuarios, int num_usuarios) {
    if (usuarios == nullptr || num_usuarios == 0) {
        cout << "No hay usuarios cargados." << endl;
        return;
    }

    ifstream archivo_binario("sesiones.dat", ios::binary);
    if (!archivo_binario) {
        cout << "No hay sesiones registradas." << endl;
        return;
    }

    double* penalizacion_acumulada = new double[num_usuarios];
    int* cantidad_sesiones = new int[num_usuarios];

    for (int i = 0; i < num_usuarios; i++) {
        *(penalizacion_acumulada + i) = 0.0;
        *(cantidad_sesiones + i) = 0;
    }

    SesionUso sesion;
    Usuario* uptr = usuarios;

    while (archivo_binario.read(reinterpret_cast<char*>(&sesion), sizeof(SesionUso))) {
        for (int i = 0; i < num_usuarios; i++) {
            if ((uptr + i)->codigo_institucional == sesion.codigo_usuario) {
                *(cantidad_sesiones + i) += 1;
                *(penalizacion_acumulada + i) += sesion.penalizacion;
                break;
            }
        }
    }
    archivo_binario.close();

    cout << "\nRanking de usuarios criticos:" << endl;

    bool* ya_mostrado = new bool[num_usuarios];
    for (int i = 0; i < num_usuarios; i++) {
        *(ya_mostrado + i) = false;
    }

    int mostrados = 0;
    while (mostrados < 3 && mostrados < num_usuarios) {
        double mayor_indice = -1.0;
        int posicion_mayor = -1;

        for (int i = 0; i < num_usuarios; i++) {
            if (*(ya_mostrado + i)) {
                continue;
            }
            if (*(cantidad_sesiones + i) == 0) {
                continue;
            }

            double indice = *(penalizacion_acumulada + i) / *(cantidad_sesiones + i);
            if (indice > mayor_indice) {
                mayor_indice = indice;
                posicion_mayor = i;
            }
        }

        if (posicion_mayor == -1) {
            break;
        }

        *(ya_mostrado + posicion_mayor) = true;
        mostrados++;

        cout << mostrados << ". " << (uptr + posicion_mayor)->nombre
             << ", " << (uptr + posicion_mayor)->programa_academico << endl;
        cout << "   Sesiones: " << *(cantidad_sesiones + posicion_mayor)
             << " / Penalizacion: $" << *(penalizacion_acumulada + posicion_mayor)
             << " / Indice: " << mayor_indice << endl;
    }

    if (mostrados == 0) {
        cout << "No hay usuarios con sesiones registradas" << endl;
    }

    delete[] penalizacion_acumulada;
    delete[] cantidad_sesiones;
    delete[] ya_mostrado;
}
