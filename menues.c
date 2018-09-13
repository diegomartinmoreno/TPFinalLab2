#include "headers.h"

char procesarMenuPrincipal(int op)
{
    char control='n';
    switch (op)
    {
    case 1:
        puts("\n\n---> Alertas y estadisticas.");
        system("pause");
        break;
    case 2:
        puts("\n\n---> Averias y estadisticas.");
        system("pause");
        break;
    case 3:
        puts("\n\n---> Listar y modificar camaras.");
        system("pause");
        break;
    case 4:
        puts("\n\n---> Personal en nomina y estadisticas.");
        system("pause");
        break;
    case 5:
        puts("\n\n---> Seguro desea salir? S/N");
        fflush(stdin);
        control=getch();
        break;
    default:
        puts("\n\n---> Ha ingresado una opcion invalida!");
        system("pause");
    }
    return control;
}

void menuPrincipal()
{
    char control='n', input;
    int op;
    while (control!='s'&&control!='S')
    {
        system("cls");
        imprimirHeader("    Menu Principal    ");
        imprimirMenuPrincipal();
        fflush(stdin);
        input=getch();
        op=atoi(&input);
        fflush(stdin);
        control=procesarMenuPrincipal(op);
    }
}
