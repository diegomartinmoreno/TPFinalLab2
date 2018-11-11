#include "headers.h"
/// *** Funciones por si se puede ingresar una entrada de historial de fechas anteriores, ordenandola antes de las ultimas entradas.

int compararFechas (tiempo t1, tiempo t2){ /// 1 si son iguales, -1 si tienen mismo dia distinta hora. 2 si t1 es mayor y -2 si t2 es mayor.
    int rta=-2;
    if (t1.ano==t2.ano && t1.mes==t2.mes && t1.dia==t2.dia){ /// Compara fecha
        rta=-1;
    }
    if (t1.hora==t2.hora && t1.minuto==t2.minuto && t1.segundo==t2.segundo){ /// Comprara hora
        rta=1;
    }
    if (t1.ano>t2.ano){
        rta=2;
    }else {
        if (t1.mes>t2.mes){
            rta=2;
        }else {
            if (t1.dia>t2.dia){
                rta=2;
            }else {
                if (t1.hora>t2.hora){
                    rta=2;
                }else{
                    if (t1.minuto>t2.minuto){
                        rta=2;
                    }
                    else{
                        if (t1.segundo>t2.segundo)
                            rta=2;
                    }
                }
            }
        }
    }
    return rta;
}


historial *insertarOrdenardoAA (historial *lista, historial *nuevo){
    historial *seg=lista, *anterior=lista;
    if (lista){
        if (compararFechas(seg->fecha, nuevo->fecha)==-2){
            while (seg->siguiente && compararFechas(seg->fecha, nuevo->fecha)==2){
                anterior=seg;
                seg=seg->siguiente;
            }
            anterior->siguiente=nuevo;
            nuevo->siguiente=seg;
        }else{
            nuevo->siguiente=lista;
            lista=nuevo;
        }
    }else{
        lista=nuevo;
    }
    return lista;
}

///****************************************

int realocarArreglo (celda camaras[], int dimF){
    camaras=realloc(camaras, sizeof(celda)+10);
    if (!camaras)
        perror("No se encontro espacio suficiente para realocar arreglo de camaras.");
    return dimF;
}


int generarArregloCamaras (arbolCamara *arbol, celda camaras[], int dimL, int dimF, char usuario[]){
    if (arbol){
        if (strcmp(usuario, arbol->C.supervisor)==0){
           if (dimL+1>dimF){
                dimF=realocarArreglo(camaras, dimF);
           }
           camaras[dimL]=arbol->C;
           dimL++;
        }
        dimL=generarArregloCamaras(arbol->izquierda, camaras, dimL, dimF, usuario);
        dimL=generarArregloCamaras(arbol->derecha, camaras, dimL, dimF, usuario);
    }
    return dimL;
}


char cicloDeControl (){
    char rta=0;
    int i=0;
    while (i<14 && rta==0){
        fflush(stdin);
        Sleep(500);
        if (!feof(stdin)){
            rta=getch();
        }
    }
    return rta;
}


void inicSupervision (celda camaras[], int i, int dimL){
    int prioridad=1;
    char control='0';
    do{
        system("cls");
        if (i<dimL){
            imprimirHeadSupervisor();
            printf ("Comienza supervision de la camara: %i", camaras[i].IDcamara);
            mostrarUnaCamara(camaras[i]);
            puts ("<<<<---------------------------------------------------->>>>");
            puts ("Cambiando de camara en 7 segundos.");
            control=cicloDeControl();
            if (control=='1'){
                ///ingresarAlarma(camaras[i]);
            }else{
                if (control =='2'){
                    ///ingresarAveria(camaras[i]);
                }
            }
        } else {
            puts("Vigilancia finalizada. Iniciando nueva ronda en 5 segundos.");
            i=0;
            Sleep(5000);
        }
    } while (control!='3');
}


void procesamientoSupervision (arbolCamara *arbol, char usuario[]) {
    celda camaras[50];
    int dimL, dimF=50, i=0;
    char control;
    dimL=generarArregloCamaras(arbol, camaras, dimL, dimF, usuario);
    while (control!='s'&&control!='S'){
        inicSupervision(camaras, i, dimL);
        puts("Desea cerrar sesion en este usuario?");
        puts("S para salir.");
        puts("N para reanudar vigilancia.");
        fflush(stdin);
        control=getch();
    }
}


int contarUsuariosCreados (){
    int cant;
    FILE *dataUsuarios=fopen(rutaSupervisores, "r");
    cant = fseek(dataUsuarios, 0, SEEK_END);
    cant = cant/(sizeof(char)*sizeNom*2);
    fclose(dataUsuarios);
    return cant;
}


int confirmarUsuario (char usuario[]){
    int cantUsers=contarUsuariosCreados(), i=0, encontrado=0, aprobado=0;
    char contrasena[sizeNom], aux[sizeNom];
    puts("Ingrese su nombre de usuario de Supervisor:");
    fflush(stdin);
    gets(usuario);
    puts("Ingrese su contraseña:");
    fflush(stdin);
    gets(contrasena);
    FILE *dataUsuarios=fopen(rutaSupervisores, "r");
    while (i<cantUsers && !encontrado){
        i++;
        fread(aux, sizeof(char), sizeNom, dataUsuarios);
        if (strcmp(usuario, aux)==0){
            encontrado=1;
            fread(aux, sizeof(char), 50, dataUsuarios);
            if (strcmp(contrasena, aux)==0){
                aprobado=1;
            }
            else{
                puts("Contraseña incorrecta");
            }
        }
    }
    return aprobado;
}


void inicioSesion (arbolCamara *arbol){
    char usuario[sizeNom];
    int aprobado=0;
    while (aprobado==0){
        system("cls");
        imprimirHeader("   Inicio de Sesion   ");
        aprobado=confirmarUsuario(usuario);
        if (aprobado){
            procesamientoSupervision(arbol, usuario);
        }
    }
}
