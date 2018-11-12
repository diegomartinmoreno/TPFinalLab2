#include "headers.h"
/// *** Funciones por si se puede ingresar una entrada de historial de fechas anteriores, ordenandola antes de las ultimas entradas.
/*
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
*/

tiempo leerFechaActual(){
    tiempo aux;
    time_t tiempoSeed=time(NULL);;
    struct tm * tiempoLocal;
    tiempoLocal=localtime(&tiempoSeed);
    aux.ano=tiempoLocal->tm_year+1900;
    aux.dia=tiempoLocal->tm_mday;
    aux.hora=tiempoLocal->tm_hour;
    aux.mes=tiempoLocal->tm_mon+1;
    aux.minuto=tiempoLocal->tm_min;
    aux.segundo=tiempoLocal->tm_sec;
    return aux;
}

void ingresarNuevaAlerta(int IDCamara){
    int IDh;
    imprimirHeader("    Ingresar alerta    ");
    printf("Se ingresara una alerta en la camara ID %i\n", IDCamara);
    historial aux;
    aux.IDcamara=IDCamara;
    aux.fecha=leerFechaActual();
    puts("Ingrese una descripcion de la alerta:");
    fflush(stdin);
    gets(aux.descripcion);
    aux.activo=1;
    aux.tiempoRespuesta=-1;
    aux.siguiente=0;
    FILE *fp=fopen(rutaHistorialAlertas, "ab");
    fseek(fp,0,SEEK_END);
    IDh=ftell(fp);
    IDh=IDh/sizeof(historial);
    IDh++;
    aux.IDregistro=IDh;
    fwrite(&aux, sizeof(historial), 1, fp);
    fclose(fp);
}

void ingresarNuevaAveria(int IDCamara){
    int IDh;
    imprimirHeader("    Ingresar Averia    ");
    printf("Se ingresara una averia en la camara ID %i\n", IDCamara);
    historial aux;
    aux.IDcamara=IDCamara;
    aux.fecha=leerFechaActual();
    puts("Ingrese una descripcion de la averia:");
    fflush(stdin);
    gets(aux.descripcion);
    aux.activo=1;
    aux.tiempoRespuesta=-1;
    aux.siguiente=0;
    FILE *fp=fopen(rutaHistorialAverias, "ab");
    fseek(fp,0,SEEK_END);
    IDh=ftell(fp);
    IDh=IDh/sizeof(historial);
    IDh++;
    aux.IDregistro=IDh;
    fwrite(&aux, sizeof(historial), 1, fp);
    fclose(fp);
}

char cicloDeControl (celda camaras[], int actual){
    time_t delay;
    time_t start;
    char rta=0;
    int i=0, dibujo=1;
    while ((rta!='1'||rta!='2'||rta!='3')&&i<7){
        fflush(stdin);
        system("cls");
        imprimirHeader("    Modo Supervision   ");
        printf ("Actualmente en supervision de la camara: %i\n", camaras[actual].IDcamara);
        mostrarUnaCamara(camaras[actual]);
        puts ("Cambiando de camara en 7 segundos.");
        puts ("<<<<------------------------------------------>>>>");
        dibujo++;
        if(dibujo==5){
            dibujo=1;
        }
        imprimirDibujo(dibujo);
        textcolor(10);
        printf("\n\t1.- ");
        textcolor(15);
        printf("Reportar Alerta.");
        textcolor(10);
        printf("\n\t2.- ");
        textcolor(15);
        printf("Reportar Averia.");
        textcolor(10);
        printf("\n\t3.- ");
        textcolor(15);
        printf("Salir del modo supervision.");
        delay = 1;
        start = time(NULL);
        do
        {
            if (_kbhit())
                rta=getch();
        }
        while (time(NULL) - start < delay);
        i++;
    }
    return rta;
}

void Supervision (celda camaras[], int i, int dimL){
    int prioridad=1;
    char control='0';
    do{
        system("cls");
        imprimirHeader("    Modo Supervision   ");
        if (i<dimL){
            control=cicloDeControl(camaras, i);
            if (control=='1'){
                system("cls");
                ingresarNuevaAlerta(camaras[i].IDcamara);
                printf("Se ha ingresado una alerta. ");
                system("pause");
            }else{
                if (control =='2'){
                    system("cls");
                    ingresarNuevaAveria(camaras[i].IDcamara);
                    printf("Se ha ingresado una averia. ");
                    system("pause");
                }
            }
            i++;
        } else {
            puts("Vigilancia finalizada. Iniciando nueva ronda en 5 segundos.");
            i=0;
            Sleep(5000);
        }
    } while (control!='3');
}


int generarArregloCamaras (celda camaras[], int dimL, int dimF, char usuario[]){
    int cantCamaras=cantidadRegistrosEnFile();
    celda aux;
    FILE *fp=fopen(rutaCamaras, "rb");
    int i=0, j=0;
    for (i=0; i<cantCamaras; i++){
        fread(&aux, sizeof(celda), 1, fp);
        if(strcmp(aux.supervisor.nomUsuario, usuario)==0){
            camaras[j]=aux;
            j++;
        }
    }
    fclose(fp);
    return j;
}


void procesamientoSupervision (char usuario[]) {
    celda camaras[100];
    int dimL=0, dimF=50, i=0;
    char control;
    dimL=generarArregloCamaras(camaras, dimL, dimF, usuario);
    while (control!='s'&&control!='S'){
        Supervision(camaras, i, dimL);
        system("cls");
        imprimirHeader("         Salir         ");
        puts("Desea volver al menu principal? S/N");
        fflush(stdin);
        control=getch();
    }
}


int contarUsuariosCreados (){
    int cant;
    FILE *dataUsuarios=fopen(rutaSupervisores, "r");
    fseek(dataUsuarios, 0, SEEK_END);
    cant = ftell(dataUsuarios);
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

int inicioSesionSup (char user[]){
    actualizarArchivoSupervisores();
    int aprobado=0, i=0;
    char pass,enmascarado[20];
    usuario aux;
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
    aprobado=confirmarUsuario(aux);
    if(aprobado!=1){
        puts("\nDatos incorrectos.");
        system("Pause");
    }
    strcpy(user, aux.nomUsuario);
    return aprobado;
}
