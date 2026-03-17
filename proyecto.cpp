#include <iostream>
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
}

struct 

int main () {

    int* ptr_equipo = &codigo_equipo;
    int* ptr_institucional = &codigo_institucional;

    do {
        switch(menu) {

            case 1:

            break;

            case 2:

            break;

            case 3:

            break;

        }

    } while (menu != 0);
}