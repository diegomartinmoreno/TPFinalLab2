#include "headers.h"

char cicloDeControl (int camaras[], int actual){
    time_t delay;
    time_t start;
    char rta=0;
    int i=0, dibujo=1;
    while ((rta!='1'||rta!='2'||rta!='3')&&i<7){
        fflush(stdin);
        system("cls");
        imprimirHeader("    Modo Supervision   ");
        printf ("Actualmente en supervision de la camara: %i\n", camaras[actual]);
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

void Supervision (arbolCamara *arbol, int camaras[], int i, int dimL){
    int aux=0;
    arbolCamara *actual;
    char control='0';
    do{
        system("cls");
        imprimirHeader("    Modo Supervision   ");
        if (i<dimL){
            control=cicloDeControl(camaras, i);
            if (control=='1'){
                printf("\n\nSe ingresara una alerta en la camara ID %i\n", camaras[i]);
                buscarCamaraXID(arbol, &actual, camaras[i]);
                actual->C.dimAlertas++;
                Sleep(3000);
                system("cls");
                aux=(actual->C.dimAlertas)-1;
                actual->C.alertas[aux]=ingresarNuevoHistorial(aux);
                printf("Se ha ingresado una alerta. ");
                system("pause");
            }else{
                if (control =='2'){
                    printf("Se ingresara una averia en la camara ID %i\n", camaras[i]);
                    buscarCamaraXID(arbol, &actual, camaras[i]);
                    actual->C.dimAverias++;
                    Sleep(3000);
                    system("cls");
                    aux=(actual->C.dimAverias)-1;
                    actual->C.averias[aux]=ingresarNuevoHistorial(aux);
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


void procesamientoSupervision (arbolCamara *arbol, char usuario[]) {
    int IDS[100];
    int i=0, dimL=0;
    char control;
    dimL=obtenerIDS(arbol, dimL, IDS, usuario);
    while (control!='s'&&control!='S'){
        Supervision(arbol, IDS, i, dimL);
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
        if(pass==8){ ///si lee backspace
            i--;
            printf("\b");
            printf(" ");
            printf("\b");

        }
        if(pass==13){ ///si lee retorno de carro
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
