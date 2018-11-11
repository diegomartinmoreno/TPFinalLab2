#include "headers.h"

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
