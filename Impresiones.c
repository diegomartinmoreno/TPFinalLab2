#include "headers.h"

void imprimirDibujo(int op){
    switch (op){
    case 1:
        textcolor(11);
        printf("                      {}\n");
        printf("     ,   A            {}\n");
        printf("    / \\, | ,         .--.\n");
        printf("   |  =|= >         /.--.\\\n");
        printf("    \\ /` | `        |====|\n");
        printf("      `   |         |`::`|\n");
        printf("          |     .-;`\\..../`;_.-^-._\n");
        printf("         /\\\\/ /  |...::..|`   :    `|\n");
        printf("         |:'\\ |   /''::''|   .:.    |\n");
        printf("          \\ /\\;-,/\\  ::  |..   ..   |\n");
        printf("          |\\ <` >  >._::_| ':   :'  |\n");
        printf("          | `""`_/ ^^/>/>  |   ':'    |\n");
        printf("          |       |       \\    :    /\n");
        printf("          |       |        \\   :   /\n");
        printf("          |       |___/\\___|`-.:.-`\n");
        printf("          |        \\_ || _/    `\n");
        printf("          |        <_ >< _>\n");
        printf("          |        |  ||  |\n");
        printf("          |       _\\.:||:./_\n");
        printf("          |      /____/\\____\\\n");
        textcolor(10);
        printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:\n");
        textcolor(15);
        break;
    case 2:
        textcolor(11);
        printf("                     {}\n");
        printf("    ,   A             {}\n");
        printf("   / \\, | ,          .--.\n");
        printf("  |  =|= >          /.--.\\\n");
        printf("   \\ /` | `         |====|\n");
        printf("     `   |          |`::`|\n");
        printf("          |     .-;`\\..../`;_.-^-._\n");
        printf("         /\\\\/ /  |...::..|`   :    `|\n");
        printf("         |:'\\ |   /''::''|   .:.    |\n");
        printf("          \\ /\\;-,/\\  ::  |..   ..   |\n");
        printf("          |\\ <` >  >._::_| ':   :'  |\n");
        printf("          | `""`_/ ^^/>/>  |   ':'    |\n");
        printf("           |      |       \\    :    /\n");
        printf("           |      |        \\   :   /\n");
        printf("           |      |___/\\___|`-.:.-`\n");
        printf("           |       \\_ || _/    `\n");
        printf("           |       <_ >< _>\n");
        printf("            |      |  ||  |\n");
        printf("            |     _\\.:||:./_\n");
        printf("            |    /____/\\____\\\n");
        textcolor(10);
        printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*\n");
        textcolor(15);
        break;
    case 3:
        textcolor(11);
        printf("                      {}\n");
        printf("     ,   A            {}\n");
        printf("    / \\, | ,         .--.\n");
        printf("   |  =|= >         /.--.\\\n");
        printf("    \\ /` | `        |====|\n");
        printf("      `   |         |`::`|\n");
        printf("          |     .-;`\\..../`;_.-^-._\n");
        printf("         /\\\\/ /  |...::..|`   :    `|\n");
        printf("         |:'\\ |   /''::''|   .:.    |\n");
        printf("          \\ /\\;-,/\\  ::  |..   ..   |\n");
        printf("          |\\ <` >  >._::_| ':   :'  |\n");
        printf("          | `""`_/ ^^/>/>  |   ':'    |\n");
        printf("          |       |       \\    :    /\n");
        printf("          |       |        \\   :   /\n");
        printf("          |       |___/\\___|`-.:.-`\n");
        printf("          |        \\_ || _/    `\n");
        printf("          |        <_ >< _>\n");
        printf("          |        |  ||  |\n");
        printf("          |       _\\.:||:./_\n");
        printf("          |      /____/\\____\\\n");
        textcolor(10);
        printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:\n");
        textcolor(15);
        break;
    case 4:
        textcolor(11);
        printf("                       {}\n");
        printf("      ,   A           {}\n");
        printf("     / \\, | ,        .--.\n");
        printf("    |  =|= >        /.--.\\\n");
        printf("     \\ /` |         |====|\n");
        printf("       `   |        |`::`|\n");
        printf("          |     .-;`\\..../`;_.-^-._\n");
        printf("         /\\\\/ /  |...::..|`   :    `|\n");
        printf("         |:'\\ |   /''::''|   .:.    |\n");
        printf("          \\ /\\;-,/\\  ::  |..   ..   |\n");
        printf("          |\\ <` >  >._::_| ':   :'  |\n");
        printf("          | `""`_/ ^^/>/>  |   ':'    |\n");
        printf("         |        |       \\    :    /\n");
        printf("         |        |        \\   :   /\n");
        printf("         |        |___/\\___|`-.:.-`\n");
        printf("         |         \\_ || _/    `\n");
        printf("         |         <_ >< _>\n");
        printf("        |          |  ||  |\n");
        printf("        |         _\\.:||:./_\n");
        printf("        |        /____/\\____\\\n");
        textcolor(10);
        printf(".:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*\n");
        textcolor(15);
        break;
    }
}

void imprimirUnHistorial(historial hist){
    puts(" <<<----------------------------->>>");
    printf("Ingresada en ");
    imprimirFecha(hist.fecha);
    puts("");
    if(hist.activo==0){
        printf("La entrada ha sido gestionada en: %.2f horas\n", hist.tiempoRespuesta);
    }
    else{
        puts("La entrada se encuentra pendiente para ser gestionada.");
    }
    printf("Descripcion: %s\n", hist.descripcion);
    puts("<<<--------------------------------->>>");
}

void imprimirFecha(time_t aux){
    struct tm *fecha;
    if (aux!=-1){
        fecha=localtime(&aux);
        printf("Hora: %i:%i:%i del %i/%i/%i", fecha->tm_hour, fecha->tm_min, fecha->tm_sec, fecha->tm_mday, fecha->tm_mon, fecha->tm_year);
    }else{
        printf("(FECHA ALEATORIA)");
    }
}

void imprimirCamaraEncontrada (celda cam){
    printf("|-------------------------------->>>\n");
    printf(" ID de camara: %i\n",cam.IDcamara);
    printf(" Nombre y Apellido de supervisor: %s\n",cam.supervisor.nomUsuario);
    printf("| Cliente: %s /// Desde ", cam.ubicacion.nombre);
    imprimirFecha(cam.fechaInstalacion);
    if(cam.estado == 1)
        printf("\n| Estado: ONLINE\n");
    if(cam.estado == 2)
        printf("\n| Estado: EN REPARACION\n");
    printf(" Prioridad de Camara: %i",cam.prioridad);
    printf("\n|------------------------------------------------------------>>>\n");
}

void mostrarUnaCamara (celda cam, int modo, char cliente[]){ /// MODO= 1 muestra activas // 2 muestra inactivas // 3 imprime IDS. /// 4 imprime camaras del lugar CLIENTE. /// 5 todas.
    switch(modo){
        case 2:
            if (cam.estado == 2||cam.estado == 0){
                printf("|---------------------------------->>>\n");
                printf("| ID de camara: %i /// ",cam.IDcamara);
                printf("Supervisor: %s\n",cam.supervisor.nomUsuario);
                printf("| Cliente: %s /// Desde ", cam.ubicacion.nombre);
                imprimirFecha(cam.fechaInstalacion);
                if(cam.estado == 0)
                    printf("\n| Estado: OFFLINE");
                if(cam.estado == 2)
                    printf("\n| Estado: EN REPARACION");
                printf(" /// Prioridad de Camara: %i",cam.prioridad);
                printf("\n|------------------------------------------------------------>>>\n");
            }
            break;
        case 1:
            if (cam.estado == 1){
                printf("|---------------------------------->>>\n");
                printf("| ID de camara: %i /// ",cam.IDcamara);
                printf("Supervisor: %s\n",cam.supervisor.nomUsuario);
                printf("| Cliente: %s /// Desde ", cam.ubicacion.nombre);
                imprimirFecha(cam.fechaInstalacion);
                printf("\n| Estado: ONLINE");;
                printf(" /// Prioridad de Camara: %i",cam.prioridad);
                printf("\n|------------------------------------------------------------>>>\n");
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
        case 5:
            printf("|---------------------------------->>>\n");
            printf("| ID de camara: %i /// ",cam.IDcamara);
            printf("Supervisor: %s\n",cam.supervisor.nomUsuario);
            printf("| Cliente: %s /// Desde ", cam.ubicacion.nombre);
            imprimirFecha(cam.fechaInstalacion);
            if(cam.estado == 0)
                printf("\n| Estado: OFFLINE");
            if(cam.estado == 1)
                printf("\n| Estado: ONLINE");
            if(cam.estado == 2)
                printf("\n| Estado: EN REPARACION");
            printf(" /// Prioridad de Camara: %i",cam.prioridad);
            printf("\n|------------------------------------------------------------>>>\n");
            break;
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
    printf("Salir del sistema.\n\n");
}

void imprimirMenuEstadisticas (){
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Historico de averias por camara.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Historico de alertas por cliente.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Estadisticas por camara.");
    textcolor(12);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Salir al menu anterior.\n\n");
}

void imprimirMenuSupervisor (){
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
    textcolor(10);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Reportar solucionada una averia.");
    textcolor(10);
    printf("\n\t5.- ");
    textcolor(15);
    printf("Reportar gestionada una alerta.");
    textcolor(12);
    printf("\n\t6.- ");
    textcolor(15);
    printf("Salir al menu principal.\n\n");
}


void imprimirMenuAdmin(){
    textcolor(10);
    printf("\n\t1.- ");
    textcolor(15);
    printf("Estadisticas del sistema.");
    textcolor(10);
    printf("\n\t2.- ");
    textcolor(15);
    printf("Listar y modificar camaras.");
    textcolor(10);
    printf("\n\t3.- ");
    textcolor(15);
    printf("Administracion de supervisores.");
    textcolor(10);
    printf("\n\t4.- ");
    textcolor(15);
    printf("Agregar Administrador.");//agregado
    textcolor(10);
    printf("\n\t5.- ");
    textcolor(15);
    printf("Listar Administradores."); //agregado
    textcolor(12);
    printf("\n\t6.- ");
    textcolor(15);
    printf("Salir del sistema.\n\n");
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
    printf("Volver al menu anterior.\n\n");
}
