#include "headers.h"


void inicioSistema(){
    inicializarCamaras();
    inicializarHistAlertas();
    inicializarHistAverias();
    crearArchivo();
    system("Pause");
    system("cls");
    imprimirHeader("    Menu Principal    ");
    imprimirPrimerMenu();
};


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
