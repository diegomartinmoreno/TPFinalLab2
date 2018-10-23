#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

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



#endif // HEADERS_H_INCLUDED
