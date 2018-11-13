#include "headers.h"


void inicioSistema(){
    puts("Bienvenidos al trabajo final de Laboratorio 2 de los alumnos Toledo y Moreno.\n");
    mkdir("./bases");
    inicializarCamaras();
    inicializarHistAlertas();
    inicializarHistAverias();
    crearArchivoAdministradores();
    actualizarArchivoSupervisores();
    system("Pause");
    SwitchMenuPrincipal();
};

void iniciarMenuEstadisticas(){
    historial historiales[50];
    int i=0, IDcamara, IDScliente[30], dimLClientes, dimLIDS;
    char clientes[30][sizeNom];
    arbolCamara *arbol=0, *aux;
    arbol=fileToArbol(arbol);
    dimLClientes=obtenerClientes(arbol, clientes, 0);
    char control='n', op;
    while (control!='s'&&control!='S'){
        system("cls");
        imprimirHeader("     Estadisticas     ");
        imprimirMenuEstadisticas();
        fflush(stdin);
        op=getch();
        switch(op){
        case '1':
            aux=buscarCamara(arbol);
            system("cls");
            IDcamara=aux->C.IDcamara;
            imprimirHeader("   Historial Averias  ");
            obtenerArrayAA(historiales, IDcamara, 2, rutaHistorialAverias);
            system("pause");
            break;
        case '2':
            dimLIDS=obtenerIDSCliente(IDScliente, dimLClientes, clientes);
            system("cls");
            imprimirHeader("   Historial Alertas  ");
            for(i=0; i<dimLIDS; i++){
                printf("\n|||---- Entradas vinculadas a la camara ID %i ----|||\n\n", IDScliente[i]);
                obtenerArrayAA(historiales, IDScliente[i], 2, rutaHistorialAlertas);
            }
            system("pause");
            break;
        case '3':
            //promInactividad();
            break;
        case '4':
            //promSupervisor();
            break;
        case '5':
            //promPeriodo();
            break;
        case '6':
            //promRespuesta();
            break;
        case '7':
            puts("\nDesea volver al menu anterior? S/N");
            fflush(stdin);
            control=getch();
            system("cls");
            break;
        default:
            puts("OPCION INCORRECTA.");
            Sleep(500);
            break;
        }
    }
}

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
                ///arbol=cargarCamaras(arbol);
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
                puts("OPCION INCORRECTA.");
                Sleep(500);
        }
    }while (op!='s'&&op!='s');
    arbolToFile(arbol);
}

void menuSup(char usuario[]){
    system("cls");
    char flag='n', opchar;
    int op, IDCamara;
    arbolCamara *arbol=0, *aux=0;
    arbol=fileToArbol(arbol);
    do{
        system("cls");
        imprimirHeader("   Menu  Supervisor   ");
        imprimirMenuSupervisor();
        puts("");
        fflush(stdin);
        opchar=getch();
        op=atoi(&opchar);
        switch(op){
            case 1:
                procesamientoSupervision(usuario);
                system("cls");
            break;
            case 2:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                system("cls");
                ingresarNuevaAveria(IDCamara);
                printf("Se ha ingresado una averia. ");
                system("pause");
            break;
            case 3:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                system("cls");
                ingresarNuevaAlerta(IDCamara);
                printf("Se ha ingresado una alerta. ");
                system("pause");
            break;
            case 4:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                system("cls");
                atenderAA(IDCamara, 1, rutaHistorialAverias);
            break;
            case 5:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                system("cls");
                atenderAA(IDCamara, 1, rutaHistorialAlertas);
            break;
            case 6:
                puts("\nDesea cerrar sesion de supervisor? S/N");
                fflush(stdin);
                flag=getch();
                system("cls");
            break;
            default:
                puts("OPCION INCORRECTA.");
                Sleep(500);
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
                iniciarMenuEstadisticas();
            break;
            case 2:
                system("cls");
                iniciarMenuCamaras();
            break;
            case 3:
                system("cls");
                listarPersonal();
            break;
            case 4:
                system("cls");
                cargarUsuariosAdm();
            break;
            case 5:
                mostrarArchivoAdministrador();
                getch();
            break;
            case 6:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                control=getch();
            break;
            default:
                puts("OPCION INCORRECTA.");
                Sleep(500);
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
                acceso=inicioSesionSup(user);
                if (acceso==1){
                    menuSup(user);
                }
            break;
            case 2:
                system("cls");
                acceso=identificarse();
                if (acceso==1){
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
                Sleep(500);
            break;
        }
    }while(flag!='s'&&flag!='S');
}
