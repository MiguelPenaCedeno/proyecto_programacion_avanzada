#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct equipo {
    int codigo_equipo;
    char nombre[30];
    char laboratorio[40];
    int tipo;
    bool estado_operativo;
    int costo_estimado;
    int semestre_minimo;
    char descripcion_tecnica[100];
};

struct usuario {
    int codigo_institucional;
    char nombre[40];
    char programa_academico[40];
    int semestre;
};

struct sesion {
    int codigo_sesion;
    equipo* ptr_equipo;
    usuario* ptr_institucional;
    char fecha[20];
    int duracion;
    char observaciones[100];
    bool penalizacion;
};

void cargarEquipos(char[]);
void cargarUsuarios(char[]);
void consultarEstadoOperativo();
void programarSesionUso();
void registrarCierreSesion();
void generarInformeUso();
void generarRankingUsuarios();

int main() {
    int menu;
    char nombre[30];

    cout << "Bienvenido al menu" << endl; 
    cout << "Oprima '1' para cargar equipos desde un archivo" << endl;
    cout << "Oprima '2' para cargar usuarios desde un archivo" << endl;
    cout << "Oprima '3' para consultar el estado operativo de un laboratorio" << endl;
    cout << "Oprima '4' para programar una sesion de uso" << endl;
    cout << "Oprima '5' para registrar cierre de sesion y observaciones" << endl;
    cout << "Oprima '6' para generar un informe de uso intensivo de equipos" << endl;
    cout << "Oprima '7' para generar un ranking de usuarios criticos" << endl;
    cout << "Oprima '8' para salir" << endl;
    cout << "Ingrese su eleccion: ";
    cin >> menu;

    do {
        switch (menu) {
            case 1:
                cout << "Ingrese el nombre del archivo que le gustaria cargar: ";
                cin.ignore();
                cin.getline(nombre, 30);
                cargarEquipos(nombre);
                break;

            case 2:
                cout << "Ingrese el nombre del archivo que le gustaria cargar: ";
                cin.ignore();
                cin.getline(nombre, 30);
                cargarUsuarios(nombre);
                break;

            case 3:
                consultarEstadoOperativo();
                break;

            case 4:
                programarSesionUso();
                break;

            case 5:
                registrarCierreSesion();
                break;

            case 6:
                generarInformeUso();
                break;

            case 7:
                generarRankingUsuarios();
                break;

            case 8:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Valor ingresado no valido, intente nuevamente." << endl;
        }

        if (menu != 8) {
            cout << "Bienvenido de vuelta al menu\n";
            cout << "Oprima '1' para cargar equipos desde un archivo" << endl;
            cout << "Oprima '2' para cargar usuarios desde un archivo" << endl;
            cout << "Oprima '3' para consultar el estado operativo de un laboratorio" << endl;
            cout << "Oprima '4' para programar una sesion de uso" << endl;
            cout << "Oprima '5' para registrar cierre de sesion y observaciones" << endl;
            cout << "Oprima '6' para generar un informe de uso intensivo de equipos" << endl;
            cout << "Oprima '7' para generar un ranking de usuarios criticos" << endl;
            cout << "Oprima '8' para salir" << endl;
            cout << "Ingrese su eleccion: ";
            cin >> menu;
        }
    } while (menu != 8);

    return 0;
}

void cargarEquipos(char nombre[]) {

    bool eleccion;

    ifstream archivo(nombre);
    if (!archivo) {
        cout << "El archivo de equipos no ha cargado correctamente" << endl;
        return;
    }
    cout << "El archivo de equipos ha cargado correctamente!" << endl;

    // la funcion hasta aqui es lo que pide el enunciado
    // lo que sigue abajo es opcional y seguramente no lo dejemos en la entrega final ya que el enunciado del taller no lo pide
    // es solamente para ver que en efecto las cosas cargan bien

    cout << "Le gustaria imprimir los primeros dos registros del archivo?" << endl;
    cout << "Ingrese 1 para si, 0 para no: ";

    cin >> eleccion;

    if (eleccion) {
    
    equipo e;
    int contador = 0;

    while (contador < 2) {
        archivo >> e.codigo_equipo;
        archivo.ignore();
        archivo.getline(e.nombre, 30);
        archivo.getline(e.laboratorio, 40);
        archivo >> e.tipo >> e.estado_operativo >> e.costo_estimado >> e.semestre_minimo;
        archivo.ignore();
        archivo.getline(e.descripcion_tecnica, 100);

        cout << "--- Equipo " << contador + 1 << " ---" << endl;
        cout << "Codigo: "      << e.codigo_equipo       << endl;
        cout << "Nombre: "      << e.nombre              << endl;
        cout << "Laboratorio: " << e.laboratorio         << endl;
        cout << "Tipo: "        << e.tipo                << endl;
        cout << "Operativo: "   << e.estado_operativo    << endl;
        cout << "Costo: "       << e.costo_estimado      << endl;
        cout << "Semestre min: "<< e.semestre_minimo     << endl;
        cout << "Descripcion: " << e.descripcion_tecnica << endl;

        contador++;
        }
    } else {
        
    }
}


void cargarUsuarios(char nombre[]) {
    bool eleccion;

    ifstream archivo(nombre);
    if (!archivo) {
        cout << "El archivo de usuarios no ha cargado correctamente" << endl;
        return;
    }
    cout << "El archivo de usuarios ha cargado correctamente!" << endl;


    // la funcion hasta aqui es lo que pide el enunciado
    // lo que sigue abajo es opcional y seguramente no lo dejemos en la entrega final ya que el enunciado del taller no lo pide
    // es solamente para ver que en efecto las cosas cargan bien
    
    cout << "Le gustaria imprimir los primeros dos registros del archivo?" << endl;
    cout << "Ingrese 1 para si, 0 para no: ";

    cin >> eleccion;

    if (eleccion) {
    usuario u;
    int contador = 0;

    while (contador < 2) {
        archivo >> u.codigo_institucional;
        archivo.ignore();
        archivo.getline(u.nombre, 40);
        archivo.getline(u.programa_academico, 40);
        archivo >> u.semestre;

        cout << "--- Usuario " << contador + 1 << " ---" << endl;
        cout << "Codigo: "   << u.codigo_institucional << endl;
        cout << "Nombre: "   << u.nombre               << endl;
        cout << "Programa: " << u.programa_academico   << endl;
        cout << "Semestre: " << u.semestre             << endl;

        contador++;
        }
    } else {
        
    }
}


void consultarEstadoOperativo() {
    cout << "Funcion consultar estado operativo - por implementar" << endl;
}

void programarSesionUso() {
    cout << "Funcion programar sesion de uso - por implementar" << endl;
}

void registrarCierreSesion() {
    cout << "Funcion registrar cierre de sesion - por implementar" << endl;
}

void generarInformeUso() {
    cout << "Funcion generar informe de uso - por implementar" << endl;
}

void generarRankingUsuarios() {
    cout << "Funcion generar ranking de usuarios - por implementar" << endl;
}
