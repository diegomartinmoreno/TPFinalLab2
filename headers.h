#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <sys/stat.h>


#define rutaSupervisores "./bases/Supervisores.bin" /// Guarda bloques de 100 caracteres, 50 para un usuario seguido de 50 para una contraseña.
#define rutaAdministradores "./bases/Administradores.bin" /// Guarda bloques de 100 caracteres, 50 para un usuario seguido de 50 para una contraseña.
#define rutaCamaras "./bases/Camaras.bin"
#define rutaPersonal "./bases/Personal.bin"
#define rutaTecnicos "./bases/Tecnicos.bin"
#define rutaHistorialAverias "./bases/Averias.bin"
#define rutaHistorialAlertas "./bases/Alertas.bin"

#define sizeNom 50

typedef struct lugar
{
    char nombre[sizeNom];
    char ciudad[sizeNom];
    char calle[sizeNom];
    int altura;
    char piso;
    char departamento;
} lugar;

typedef struct historial
{
    int IDregistro; /// INDIVIDUAL de cada camara.
    int activo; /// 1 si todavia no fue reparada la averia o gestionada la alerta, 0 si ya fue hecho.
    time_t fecha;
    float tiempoRespuesta; /// En horas, tiempo que tardo el tecnico o la seguridad en arribar a la incidencia.
    char descripcion[150];
} historial;

typedef struct usuario{
    char nomUsuario[sizeNom];
    char contrasena[sizeNom];
} usuario;

typedef struct celda{
    int IDcamara;
    int estado; /// 1=online; 2=en reparacion;
    time_t fechaInstalacion;
    lugar ubicacion;
    usuario supervisor;
    int prioridad; // 0 <= prioridad < 10
    /// Maximo de 50 averias/alertas almacenadas por camara.
    int dimAverias;
    historial averias[50];
    int dimAlertas;
    historial alertas[50];
} celda;

typedef struct arbolCamara
{
    celda C;
    struct arbolCamara *derecha;
    struct arbolCamara *izquierda;
} arbolCamara;

///Estructuras Personal

typedef struct nodoSupervisor{
    usuario sup;
    struct nodoSupervisor * sig;
} nodoSupervisor;

typedef struct nodo2Supervisor{
    usuario sup;
    struct nodo2Supervisor * ante;
    struct nodo2Supervisor * sig;
} nodo2Supervisor;


/// >>>>  PROTOTIPADO <<<<<



/// impresiones.c
void textcolor (int color);
void imprimirPrimerMenu();
void imprimirHeader(char titulo[]);
void mostrarUnUsuario(usuario aux);
void imprimirMenuHalcon();
void imprimirHeadSupervisor ();
void imprimirMenuAdmin();


/// procesamientoMenues.c
void inicioSistema();
void menuHalconSwt(int opc);
void menuAdminSwt(int opc);
void primerMenuSwt(int opc);


/// sistemaDeAcceso.c
void mostrarArchivoAdministrador();
void crearArchivo();
usuario registro();
int buscarExistente(usuario *aux, char ruta[], int modo);
int cantReg();
void cargarUsuariosAdm();
int identificarse();


/// funcionesSupervisor.c



/// funcionesPersonal.c



/// funcionesEstadisticas.c



/// funcionesCamaras.c


/// funcionesHistoriales.c
historial ingresarNuevoHistorial(int IDRegistro);


/// generadorRandom.c
time_t generarFecha ();
lugar generarUbicacion (int ID);
void generarCamara (int ID);
void generarBaseCamaras();
void inicializarCamaras ();
historial generarAveriaRandom(int IDh);
historial generarAlertaRandom(int IDh);


#endif // HEADERS_H_INCLUDED
