#include <iostream>
#include <fstream>

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

void cargarEquipos();
void cargarUsuarios();
void consultarEstadoOperativo();
void programarSesionUso();
void registrarCierreSesion();
void generarInformeUso();
void rankingUsuarios();


int main () {
    int menu;

    cout << "Bienvenido al menu"; 
    cout << "Oprima '1' para cargar equipos desde un archivo" << endl;
    cout << "Oprima '2' para cargar usuarios desde un archivo" << endl;
    cout << "Oprima '3' para consultar el estado operativo de un laboratorio" << endl;
    cout << "Oprima '4' para programar una sesion de uso" << endl; 
    cout << "Oprima '5' para registrar cierre de sesion y observaciones" << endl;
    cout << "Oprima '6' para generar un informe de uso intensivo de equipos" << endl;
    cout << "Oprima '7' para generar un ranking de usuarios criticos" << endl;
    cout << "Oprima '8' para salir" << endl;
    cout << "Ingrese su elección: ";
    cin >> menu;


    do {
        switch(menu) {

            case 1:
            cargarEquipos();
            break;

            case 2:
            cargarUsuarios();
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
            break

            case 8:
            cout << "Saliendo del programa...";
            break;

            default:
            cout << "Valor ingresado no valido, intente nuevamente: ";
            cin >> menu;
        }

    } while (menu != 8);
    return 0;
}

void cargarEquipos() {

    char nombre[30];

    cout << "Ingrese el nombre del archivo que le gustaria cargar: ";
    cin.ignore();
    cin.getline(nombre, 30);

    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "El archivo de equipos no ha cargado correctamente";
        return;
    }

    cout << "El archivo de equipos ha cargado correctamente!";
}

void cargarUsuarios() {

    char nombre[30];

    cout << "Ingrese el nombre del archivo que le gustaria cargar: ";
    cin.ignore();
    cin.getline(nombre, 30);

    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "El archivo de usuarios no ha cargado correctamente";
        return;
    }

    cout << "El archivo de usuarios ha cargado correctamente!";
}