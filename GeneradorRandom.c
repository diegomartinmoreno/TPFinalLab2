#include "headers.h"

tiempo generarFecha (){
    tiempo aux;
    aux.ano=(rand()%10)+2008;
    aux.dia=rand()%30;
    aux.hora=rand()%24;
    aux.mes=rand()%13;
    aux.minuto=rand()%60;
    aux.segundo=rand()%60;
    return aux;
}


lugar generarUbicacion (int ID){
    lugar aux;
    int IDlugar=ID/100;
    char nombre[][sizeNom]={{"Grido"},{"Italia"},{"San Marino"},{"Reggio"},{"Ischia"},{"Freddo"},{"Giannelli"},{"Arlequin"}};
    char calle [][sizeNom]={{"A. Edison"},{"Alem"},{"Constitucion"},{"Av Libertad"},{"Luro"},{"Rawson"},{"Luro"},{"Luro"}};
    int altura[8]={ 1411, 3618, 4018, 4326, 4004, 1313, 3358, 7198};
    aux.altura=altura[IDlugar];
    strcpy(aux.nombre, nombre[IDlugar]);
    strcpy(aux.calle, calle[IDlugar]);
    aux.piso=0;
    aux.departamento=0;
    strcpy(aux.ciudad, "Mar del Plata");
    return aux;
}

void generarCamara (int ID){
    celda camara;
    int i;
    char supervisores[][sizeNom]={{"Domingo"},{"Nestor"},{"Mauri"},{"Sergio"},{"Gaby"},{"Mariu"},{"Lilita"},{"Cristina"}};
    char contrasenas[][sizeNom]={{"peron"},{"kirchner"},{"macri"},{"massa"},{"michetti"},{"vidal"},{"carrio"},{"kirchner"}};
    i=rand()%7;
    strcpy(camara.supervisor.nomUsuario, supervisores[i]);
    strcpy(camara.supervisor.contrasena, contrasenas[i]);
    camara.fechaInstalacion=generarFecha();
    camara.histAlertas=0;
    camara.histAlertas=0;
    i=rand()%100;
    if (i>80){
        camara.estado=2;
    }
    if (i>70&&i<=80){
        camara.estado=0;
    }
    if (i<=70){
        camara.estado=0;
    }
    camara.estado=rand()%3;
    camara.IDcamara=ID;
    camara.ubicacion=generarUbicacion(ID);
    camara.prioridad=rand()%10;
    camara.eliminada=0;
    FILE *fp=fopen(rutaCamaras, "ab");
    if (fp){
        fwrite(&camara, sizeof(celda), 1, fp);
    }
    fclose(fp);
}

void generarBaseCamaras(){
    int i, j, ID;
    for (i=1; i<8; i++){
        for (j=0;j<6; j++){
            ID=(i*100)+j;
            generarCamara(ID);
        }
    }
}

void inicializarCamaras (){

    FILE *fp=fopen(rutaCamaras, "rb");
    if (!fp){
        generarBaseCamaras();
        puts("Se creo una nueva base de datos de Camaras aleatorias.");
    }
    else
        puts("Base de datos de Camaras disponible.");
    fclose(fp);
}

/// >>>>>> Generador de historiales.

historial generarAveriaRandom(int IDc, int IDh){
    historial aux;
    char descripciones[][150]={{"Camara con mal funcionamiento."},{"Camara no brinda imagen."},{"Camara destruida por un meteorito."},{"Camara con lente obstruido"},{"Camara necesita reemplazo."}};
    strcpy(aux.descripcion, descripciones[rand()%5]);
    aux.tiempoRespuesta=rand()%48;
    aux.tiempoRespuesta+=(rand()%60)/100;
    aux.fecha=generarFecha();
    aux.activo=0;
    aux.IDcamara=IDc;
    aux.IDregistro=IDh;
    aux.siguiente=0;
    return aux;
}


void generarHistAverias(){
    FILE *fp = fopen(rutaCamaras, "rb");
    celda aux;
    historial guardar;
    int *IDS, i, j, cant, cantAverias, IDh=1;
    fseek(fp, 0, SEEK_END);
    cant=ftell(fp);
    cant=cant/sizeof(celda);
    IDS=(int *)malloc(sizeof(int)*cant);
    fseek(fp, 0, SEEK_SET);
    for (i=0; i<cant; i++){
        fread(&aux, sizeof(celda), 1, fp);
        IDS[i]=aux.IDcamara;
    }
    fclose(fp);
    fp=fopen(rutaHistorialAverias, "ab");
    for (i=0; i<cant; i++){
        cantAverias=rand()%5;
        for (j=0; j<cantAverias; j++){
            guardar=generarAveriaRandom(IDS[i], IDh);
            fwrite(&guardar, sizeof(historial), 1, fp);
            IDh++;
        }
    }
    fclose(fp);
}


historial generarAlertaRandom(int IDc, int IDh){
    historial aux;
    char descripciones[][150]={{"Se estan tirando con detodo."},{"Jovenes consumiendo charuto en la puerta."},{"Barras bravas rompiendo el local."},{"Asalto con arma de grueso calibre."},{"Se rompio el aire acondicionado."}};
    strcpy(aux.descripcion, descripciones[rand()%5]);
    aux.tiempoRespuesta=rand()%3;
    aux.tiempoRespuesta+=(rand()%60)/100;
    aux.fecha=generarFecha();
    aux.IDcamara=IDc;
    aux.IDregistro=IDh;
    aux.activo=0;
    aux.siguiente=0;
    return aux;
}


void generarHistAlertas(){
    FILE *fp = fopen(rutaCamaras, "rb");
    celda aux;
    historial guardar;
    int *IDS, i, j, cant, cantAlertas, IDh=1;
    fseek(fp, 0, SEEK_END);
    cant=ftell(fp);
    cant=cant/sizeof(celda);
    IDS=(int *)malloc(sizeof(int)*cant);
    fseek(fp, 0, SEEK_SET);
    for (i=0; i<cant; i++){
        fread(&aux, sizeof(celda), 1, fp);
        IDS[i]=aux.IDcamara;
    }
    fclose(fp);
    fp=fopen(rutaHistorialAlertas, "ab");
    for (i=0; i<cant; i++){
        cantAlertas=rand()%7;
        for (j=0; j<cantAlertas; j++){
            guardar=generarAlertaRandom(IDS[i], IDh);
            fwrite(&guardar, sizeof(historial), 1, fp);
            IDh++;
        }
    }
    fclose(fp);
}


void inicializarHistAverias(){
    FILE *fp=fopen(rutaHistorialAverias, "rb");
    if (!fp){
        fclose(fp);
        generarHistAverias();
        puts("Se ha generado un nuevo historial de averias aleatorias.");
    }else{
        fclose(fp);
        puts("Carga de base de datos del historial de averias exitosa.");
    }
}


void inicializarHistAlertas(){
    FILE *fp=fopen(rutaHistorialAlertas, "rb");
    if (!fp){
        fclose(fp);
        generarHistAlertas();
        puts("Se ha generado un nuevo historial de alertas aleatorias.");
    }else{
        fclose(fp);
        puts("Carga de base de datos del historial de alertas exitosa.");
    }
}
