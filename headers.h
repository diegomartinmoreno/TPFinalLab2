#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define rutaSupervisores "./Sup.txt" /// Guarda bloques de 100 caracteres, 50 para un usuario seguido de 50 para una contraseña.
#define rutaAdministradores "./Adm.bin" /// Guarda bloques de 100 caracteres, 50 para un usuario seguido de 50 para una contraseña.
#define rutaCamaras "./Cam.bin"
#define rutaPersonal "./Personal.bin"
#define rutaTecnicos "./Tecnicos.bin"
#define rutaHistorialAverias "./Averias.bin"
#define rutaHistorialAlertas "./Alertas.bin"

#define sizeNom 50

typedef struct
{
    char ciudad[50];
    char calle[50];
    int altura;
    char piso;
    char departamento;
} lugar;

typedef struct
{
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
} tiempo;
//
typedef struct
{
    int IDcamara;
    tiempo fecha;
    float tiempoRespuesta; /// En horas, tiempo que tardo el tecnico o la seguridad en arribar a la incidencia.
    char descripcion[150];
    struct historial *siguiente;
} historial;
///LOS PRIMEROS 4 BYTES DEL HISTORIAL, UNA VEZ GUARDADO EN FILE, SERÁ INDICADOR DE LA CANTIDAD DE REGISTROS INGRESADOS PARA ESA CAMARA.

typedef struct  {
    int IDcamara;
    int estado; /// 0=offline; 1=online; 2=en reparacion;
    tiempo fechaInstalacion;
    lugar ubicacion;
    char supervisor[50];
    int prioridad; // 0 <= prioridad <= 10
    historial *histAverias;
    historial *histAlertas;
} celda;

typedef struct
{
    celda C;
    struct arbolCamara *derecha;
    struct arbolCamara *izquierda;
} arbolCamara;

///Estructuras Personal
typedef struct{
    int idSupervisor;
    char nomYApe[30];
    int cantReportes;
}supervisor;

typedef struct{
    supervisor sup;
    struct nodoSupervisor * sig;
}nodoSupervisor;

typedef struct{
    supervisor sup;
    struct nodo2Supervisor * ante;
    struct nodo2Supervisor * sig;
}nodo2Supervisor;

typedef struct{
    char nomUsuario[sizeNom];
    char contrasena[sizeNom];
}usuario;


#endif // HEADERS_H_INCLUDED
