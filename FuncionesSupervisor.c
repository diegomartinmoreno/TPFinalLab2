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


void Supervision (celda camaras[], int i, int dimL){
    int prioridad=1;
    char control='0';
    do{
        system("cls");
        if (i<dimL){
            imprimirHeader("    Modo Supervision   ");
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


void procesamientoSupervision (char usuario[]) {
    celda camaras[50];
    int dimL, dimF=50, i=0;
    char control;
    arbolCamara *arbol;
    FILE *fp=fopen(rutaCamaras, "rb");
    arbol=fileToArbol(arbol);
    fclose(fp);
    dimL=generarArregloCamaras(arbol, camaras, dimL, dimF, usuario);
    while (control!='s'&&control!='S'){
        Supervision(camaras, i, dimL);
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

int confirmarUsuario (usuario user){
    int cantUsers=contarUsuariosCreados(), i=0, encontrado=0, aprobado=0;
    usuario aux;
    FILE *dataUsuarios=fopen(rutaSupervisores, "rb");
    while (i<cantUsers && !encontrado){
        i++;
        fread(&aux, sizeof(usuario), 1, dataUsuarios);
        if (strcmp(user.nomUsuario, aux.nomUsuario)==0){
            encontrado=1;
            if (strcmp(user.contrasena, aux.contrasena)==0){
                aprobado=1;
            }
            else{
                puts("Contraseña incorrecta");
            }
        }
    }
    return aprobado;
}

void inicioSesionSup (arbolCamara *arbol){
    int aprobado=0;
    char pass,enmascarado[20];
    usuario aux;

    int i=0,ingreso=0,encontrado=0;

    strcpy(enmascarado,"**********");
    imprimirHeader("    Inicio de Sesion   ");
    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(aux.nomUsuario);
    printf("\nIngrese contrasena: ",164);
    do{
        pass=getch();
        if(pass != 13 && pass != 8){
            printf("%c",enmascarado[i]);
            aux.contrasena[i]=pass;
            i++;
        }
        if(pass==8){ //si lee backspace
            i--;
            printf("\b");
            printf(" ");
            printf("\b");

        }
        if(pass==13){ //si lee retorno de carro
            aux.contrasena[i]='\0';
        }
    }while(i<20&&pass!=13);
    encontrado=confirmarUsuario(aux);
    if(encontrado==1){
        ingreso=1;
    }else{
        puts("\nDatos incorrectos.");
        system("Pause");
    }
    return ingreso;
}
