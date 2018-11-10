#include "headers.h"


void inicioSistema(){
    crearArchivo();
    imprimirHeader("    Menu Principal    ");
    imprimirPrimerMenu();


};

void textcolor (int color) // Gracias por tanto StackOverflow.
{
    static int __BACKGROUND;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}
char control(){
    char opc;
    puts("Desea continuar? S/N .");
    fflush(stdin);
    opc=getch();
    return opc;
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

///funciones con switch
void menuHalconSwt(int opc){ ///alertar reportar listar salir

    system("cls");
    switch (opc) {
        case 1:
            printf("CREAR ALERTA");
            break;
        case 2:
            printf("REPORTAR AVERIA");
            break;
        case 3:
            printf("LISTAR CAMARAS");
            break;
        case 4:
            inicioSistema();
            break;
        default:
            printf("Ingrese una opcion valida!\n");
            break;
    }
};
void mostrarUnUsuario(usuario aux){
    printf("--------------------------------------\n");
    printf("Nombre de usuario: %s\n",aux.nomUsuario);
    printf("Contrase%ca: %s\n",164,aux.contrasena);
    printf("--------------------------------------\n");
};
void mostrarArchivoAdministrador(){
    FILE * admin=fopen(rutaAdministradores,"rb");
    usuario in;

    if(admin){
        while(fread(&in,sizeof(usuario),1,admin)>0){
            mostrarUnUsuario(in);
        }

        fclose(admin);
    }
};
void menuAdminSwt(int opc){ ///alertas y estad. / averias y estad. / listar y modif. cams / Personal en nomina y estad.

    system("cls");
    switch (opc) {
        case 1:
            printf("Estadisticas de alertas.\n");
            break;
        case 2:
            printf("AVERIAS Y ESTADISTICAS\n");
            break;
        case 3:
            printf("LISTAR Y MODIFICAR CAMARAS\n");
            break;
        case 4:
            printf("LISTAR PERSONAL EN NOMINA Y ESTADISTICA\n");
            break;
        case 5:
            cargarUsuariosAdm();
            imprimirMenuAdmin();
            break;
        case 6:
            mostrarArchivoAdministrador();
            getch();
            imprimirMenuAdmin();
            break;
        case 7:
            inicioSistema();
            break;
        default:
            printf("Ingrese una opcion valida!\n");
            break;
    }
};
void primerMenuSwt(int opc){

    crearArchivo();
    system("cls");
    switch (opc) {
        case 1:
            imprimirMenuHalcon();
            break;
        case 2:
            identificarse();
            break;
        case 3:
            printf("Cerrando sistema...\n");
            system("pause");
            break;
        default:
            printf("Ingrese opcion valida.");
            system("pause");
            system("cls");
            inicioSistema();
            break;
    }
};

///Funciones de menues.
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
    imprimirHeadSupervisor;
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
