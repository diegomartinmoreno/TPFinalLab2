#include "headers.h"

void imprimirCamaraEncontrada (celda cam){
    if (!cam.eliminada){
        printf("|---------------------------------->>>\n");
        printf("ID de camara: %i\n",cam.IDcamara);
        printf("Nombre y Apellido de supervisor: %s\n",cam.supervisor);
        if(cam.estado == 0)
            printf("Estado: OFFLINE\n");
        if(cam.estado == 1)
            printf("Estado: ONLINE\n");
        if(cam.estado == 2)
            printf("Estado: EN REPARACION\n");
        printf("Prioridad de Camara: %i",cam.prioridad);
        printf("\n|-------------------------------------------------------------------->>>\n");
    }else{
        puts("Error! Intenta mostrar una camara eliminada!");
}
}

void mostrarUnaCamara (celda cam, int modo, char cliente[]){ /// MODO= 1 muestra activas // 2 muestra inactivas // 3 imprime IDS. /// 4 imprime camaras del lugar CLIENTE.
    if (cam.eliminada==0){
        switch(modo){
            case 2:
                if (cam.estado == 2||cam.estado == 0){
                    printf("|---------------------------------->>>\n");
                    printf("| ID de camara: %i /// ",cam.IDcamara);
                    printf("Supervisor: %s\n",cam.supervisor);
                    printf("| Cliente: %s /// ", cam.ubicacion.nombre);
                    if(cam.estado == 0)
                        printf("Estado: OFFLINE");
                    if(cam.estado == 2)
                        printf("Estado: EN REPARACION");
                    printf(" /// Prioridad de Camara: %i",cam.prioridad);
                    printf("\n|-------------------------------------------------------------------->>>\n");
                }
                break;
            case 1:
                if (cam.estado == 1){
                    printf("|---------------------------------->>>\n");
                    printf("| ID de camara: %i /// ",cam.IDcamara);
                    printf("Supervisor: %s\n",cam.supervisor);
                    printf("| Cliente: %s /// ", cam.ubicacion.nombre);
                    printf("Estado: ONLINE");;
                    printf(" /// Prioridad de Camara: %i",cam.prioridad);
                    printf("\n|-------------------------------------------------------------------->>>\n");
                }
                break;
            case 3:
                printf("| %i |", cam.IDcamara);
                break;
            case 4:
                if (strcmp(cam.ubicacion.nombre, cliente)==0){
                    printf("| %i |", cam.IDcamara);
                }
                break;
        }

    }
}




void textcolor (int color) // Gracias por tanto StackOverflow.
{
    static int __BACKGROUND;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}


void mostrarUnUsuario(usuario aux){
    printf("--------------------------------------\n");
    printf("Nombre de usuario: %s\n",aux.nomUsuario);
    printf("Contrase%ca: %s\n",164,aux.contrasena);
    printf("--------------------------------------\n");
};


//PARA QUEDAR CENTRADO DEBE RECIBIR UN STRING DE 22 CARACTERES.
void imprimirHeader(char titulo[]){
    int i;
    textcolor(2);
    printf("\n%c", 201);
    printf("%c", 205);
    for (i=0; i<19; i++){
        printf("%c", 174);
    }
    textcolor(10);
    for (i=0; i<22; i++){
        printf("%c", 205);
    }
    textcolor(2);
    for (i=0; i<19; i++){
        printf("%c", 175);
    }
    printf("%c", 205);
    printf("%c\n", 187);
    printf("%c%42s%21c\n", 186, " ", 186);
    printf("%c", 186);
    textcolor(15);
    printf("%42s", titulo);
    textcolor(2);
    printf("%21c\n", 186);
    printf("%c%42s%21c\n", 186, " ", 186);
    printf("%c", 200);
    printf("%c", 205);
    for (i=0; i<19; i++){
        printf("%c", 174);
    }
    textcolor(10);
    for (i=0; i<22; i++){
        printf("%c", 205);
    }
    textcolor(2);
    for (i=0; i<19; i++){
        printf("%c", 175);
    }
    printf("%c", 205);
    printf("%c\n\n", 188);
    textcolor(15);
};


void imprimirPrimerMenu(){
    int opc;

    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Ingresar como Supervisor.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Ingresar como Administrador.");
    textcolor(12);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Salir del sistema.");


    printf("\nIngrese opcion para continuar: ");
    fflush(stdin);
    scanf("%i",&opc);

    primerMenuSwt(opc);
}


void imprimirHeadSupervisor (){
    imprimirHeader("   Menu  Supervisor   ");
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Comenzar Supervision.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Reportar Averia.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Reportar Alerta.");
}


void imprimirMenuHalcon(){

    int opc;
    imprimirHeadSupervisor();
    textcolor(12);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Salir del sistema.");

    printf("\nIngrese una opcion para continuar: ");
    fflush(stdin);
    scanf("%i",&opc);

    menuHalconSwt(opc);

};


void imprimirMenuAdmin(){
    int opc;
    system("cls");
    imprimirHeader("  Menu Administrador  ");
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Estadisticas de alertas.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Estadisticas de averias.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Listar y modificar camaras.");
    textcolor(10);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Personal en nomina y estadisticas.");
    textcolor(10);
    printf("\n\t5.- ");
    textcolor(15);
    printf("Agregar Administrador.");//agregado
    textcolor(10);
    printf("\n\t6.- ");
    textcolor(15);
    printf("Listar Administradores."); //agregado
    textcolor(12);
    printf("\n\t7.- ");
    textcolor(15);
    printf("Salir del sistema.");
    printf("\nIngrese una opcion para continuar: ");
    fflush(stdin);
    scanf("%i",&opc);
    menuAdminSwt(opc);
}

void imprimirMenuCamaras (){
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Buscar camara.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Listar camaras activas.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Listar camaras en reparacion.");
    textcolor(10);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Cargar nueva camara.");
    textcolor(10);
    printf("\n\t5.- ");
    textcolor(15);
    printf("Eliminar una camara.");
    textcolor(12);
    printf("\n\t6.- ");
    textcolor(15);
    printf("Volver al menu anterior.\n");
}
