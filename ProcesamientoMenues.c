#include "headers.h"


void inicioSistema(){
    puts("Bienvenidos al trabajo final de Laboratorio 2 de los alumnos Toledo y Moreno.\n");
    mkdir("./bases");
    inicializarCamaras();
    crearArchivoAdministradores();
    actualizarArchivoSupervisores();
    system("Pause");
    SwitchMenuPrincipal();
};

void iniciarMenuEstadisticas(){
    historial historiales[50];
    int i=0, IDcamara, IDScliente[30], dimLClientes, dimLIDS;
    float impresionOutput;
    char clientes[30][sizeNom];
    arbolCamara *arbol=0, *aux;
    arbol=fileToArbol(arbol);
    dimLClientes=obtenerClientes(arbol, clientes, 0);
    char control='n', op;
    while (control!='s'&&control!='S'){
        system("cls");
        imprimirHeader("     Estadisticas     ");
        puts(">>> Estadisticas del sistema: \n");
        impresionOutput=promedioAlertasXDiaSistema(arbol);
        printf("| Promedio de alertas por dia: %.2f\n", impresionOutput);
        impresionOutput=0;
        tiempoRespuestaAlertaSistema(arbol, &impresionOutput);
        printf("| Tiempo medio de respuesta a las alertas: %.3f horas\n\n", impresionOutput);
        impresionOutput=promedioAveriasXDiaSistema(arbol);
        printf("| Promedio de averias por dia: %.2f\n", impresionOutput);
        impresionOutput=0;
        tiempoRespuestaAveriaSistema(arbol, &impresionOutput);
        printf("| Tiempo medio de respuesta a las averias: %.3f horas\n\n", impresionOutput);
        textcolor(10);
        puts("\n********************************************");
        textcolor(15);
        imprimirMenuEstadisticas();
        fflush(stdin);
        op=getch();
        switch(op){
        case '1':
            system("cls");
            imprimirHeader("   Historial Averias  ");
            histAverias(arbol);
            system("pause");
            break;
        case '2':
            system("cls");
            imprimirHeader("   Historial Alertas  ");
            histAlertas(arbol);
            system("pause");
            break;
        case '3':
            system("cls");
            imprimirHeader("Estadisticas de Camara");
            aux=buscarCamara(arbol);
            system("cls");
            imprimirHeader("Estadisticas de Camara");
            printf("Estadisticas de la camara ID = %i\n\n", aux->C.IDcamara);
            impresionOutput=promedioAlertasXDiaXCamara(arbol, aux->C.IDcamara);
            printf(">> Esta camara tiene un promedio de %.2f alertas por dia.\n", impresionOutput);
            impresionOutput=tiempoRespuestaCamaraAlerta(arbol, aux->C.IDcamara);
            printf("| El tiempo de respuesta medio a las alertas en esta camara es de %.3f horas.\n\n\n", impresionOutput);
            impresionOutput=promedioAveriasXDiaXCamara(arbol, aux->C.IDcamara);
            printf(">> Esta camara tiene un promedio de %.2f averias por dia.\n", impresionOutput);
            impresionOutput=tiempoRespuestaCamaraAveria(arbol, aux->C.IDcamara);
            printf("| El tiempo de respuesta medio a las averias en esta camara es de %.3f horas.\n\n", impresionOutput);

            system("Pause");
            break;
        case '4':
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
    fileToArbol(arbol);
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
                mostrarArbolCamarasMenu(arbol, 1, 0, 0);
                puts("");
                system("Pause");
                break;
            case '3':
                mostrarArbolCamarasMenu(arbol, 2, 0, 0);
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
                        eliminarCamara(&arbol, aux->C);
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
        opchar='0';
        system("cls");
        imprimirHeader("   Menu  Supervisor   ");
        imprimirMenuSupervisor();
        puts("");
        fflush(stdin);
        opchar=getch();
        fflush(stdin);
        op=atoi(&opchar);
        switch(op){
            case 1:
                procesamientoSupervision(arbol, usuario);
                system("cls");
            break;
            case 2:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                aux->C.dimAverias++;
                system("cls");
                aux->C.averias[(aux->C.dimAverias)-1]=ingresarNuevoHistorial((aux->C.dimAverias)-1);
                printf("Se ha ingresado una averia. \n");
                system("pause");
                fflush(stdin);
            break;
            case 3:
                aux=buscarCamara(arbol);
                IDCamara=aux->C.IDcamara;
                aux->C.dimAlertas++;
                system("cls");
                aux->C.alertas[(aux->C.dimAlertas)-1]=ingresarNuevoHistorial((aux->C.dimAlertas-1));
                printf("Se ha ingresado una averia. \n");
                system("pause");
                fflush(stdin);
            break;
            case 4:
                system("cls");
                imprimirHeader("    Reportar Averia  \n");
                aux=buscarCamara(arbol);
                reportarGestion(aux, 1);
                system("pause");
                fflush(stdin);
            break;
            case 5:
                system("cls");
                imprimirHeader("    Reportar Alerta   ");
                aux=buscarCamara(arbol);
                reportarGestion(aux, 2);
                system("pause");
                fflush(stdin);
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
    arbolToFile(arbol);
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
