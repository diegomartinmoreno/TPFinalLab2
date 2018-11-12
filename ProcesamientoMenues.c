#include "headers.h"


void inicioSistema(){
    puts("Bienvenidos al trabajo final de Laboratorio 2 de los alumnos Toledo y Moreno.\n");
    inicializarCamaras();
    inicializarHistAlertas();
    inicializarHistAverias();
    crearArchivoAdministradores();
    crearArchivoSupervisores();
    system("Pause");
    SwitchMenuPrincipal();
};

void iniciarMenuCamaras(){
    char op='n', input, confirmacion;
    arbolCamara *arbol=0, *aux=0;
    arbol=fileToArbol(arbol);
    do{
        system("cls");
        imprimirHeader("    Menu de Camaras   ");
        imprimirMenuCamaras();
        fflush(stdin);
        input=getch();
        switch (input){
            case '1':
                aux=buscarCamara(arbol);
                system("cls");
                imprimirHeader("    Datos de camara   ");
                puts("");
                imprimirCamaraEncontrada (aux->C);
                system("Pause");
                break;
            case '2':
                mostrarArbolCamaras(arbol, 1, 30, 0);
                puts("");
                system("Pause");
                break;
            case '3':
                mostrarArbolCamaras(arbol, 2, 30, 0);
                puts("");
                system("Pause");
                break;
            case '4':
                system("cls");
                imprimirHeader("  Cargar nueva camara  ");
                arbol=cargarCamaras(arbol);
                break;
            case '5':
                aux=buscarCamara(arbol);
                if (aux!=NULL){
                    system("cls");
                    imprimirHeader("    Datos de camara   ");
                    puts("");
                    imprimirCamaraEncontrada (aux->C);
                    puts("Eliminar la camara de la base de datos? S/N");
                    fflush(stdin);
                    confirmacion=getch();
                    if (confirmacion=='s'||confirmacion=='S'){
                        aux->C.eliminada=1;
                        puts("La camara ha sido eliminada.");
                    }else{
                        puts("La camara no ha sido eliminada.");
                    }
                }
                system("Pause");
                break;
            case '6':
                op=control();
                break;
            default:
                printf("Opcion invalida!\n");
                break;
        }
    }while (op!='s'&&op!='s');
    arbolToFile(arbol);
}

void menuSup(char usuario[]){
    system("cls");
    char flag='n';
    int op;
    do{
        system("cls");
        imprimirHeader("   Menu  Supervisor   ");
        imprimirMenuSupervisor();
        puts("");
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                procesamientoSupervision(usuario);
                system("cls");
            break;
            case 2:
                system("cls");
            break;
            case 3:
                puts("\nDesea salir del sistema? S/N");
                fflush(stdin);
                flag=getch();
                system("cls");
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while(flag!='s'&&flag!='S');
}

void menuAdmin(){
    char control='n', opchar;
    int op;
    do{
        system("cls");
        imprimirHeader("   Menu Administrador  ");
        imprimirMenuAdmin();
        puts("");
        fflush(stdin);
        opchar=getch();
        op=atoi(&opchar);
        switch(op){
            case 1:
                system("cls");
                ///iniciarMenuEstadisticasAverias();
            break;
            case 2:
                system("cls");
                ///iniciarMenuEstadisticasAlertas();
            break;
            case 3:
                system("cls");
                iniciarMenuCamaras();
            break;
            case 4:
                system("cls");
                system("pause");
            break;
            case 5:
                system("cls");
                cargarUsuariosAdm();
                imprimirMenuAdmin();
            break;
            case 6:
                mostrarArchivoAdministrador();
                getch();
                imprimirMenuAdmin();
            break;
            case 7:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                control=getch();
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while (control!='s'&&control!='S');
}

void SwitchMenuPrincipal(){
    crearArchivoAdministradores();
    char flag='n', user[sizeNom], opchar;
    int op, acceso=0;
    do{
        system("cls");
        imprimirHeader(" Bienvenido al sistema ");
        imprimirPrimerMenu();
        puts("");
        fflush(stdin);
        opchar=getch();
        op=atoi(&opchar);
        switch(op){
            case 1:
                system("cls");
                inicioSesionSup();
            break;
            case 2:
                system("cls");
                acceso=identificarse();
                if (acceso){
                    menuAdmin();
                }
            break;
            case 3:
                puts("\nDesea salir del sistema? S/N");
                fflush(stdin);
                flag=getch();
                system("cls");
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while(flag!='s'&&flag!='S');
}
