/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 */

#include "estacion.h"
#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80

void itoa(int valor, char *linea){
    sprintf(linea,"%d",valor); 
}

char identificarEntidad(const * char buffer){
    char tipoEnt;
    int i=0;
    char c[2] = ",";
    char *token;
    token = strtok(str, c);
    tipoEnt=token;
    return tipoEnt;
}

ST_TREN * decodificarTren(const * char buffer){
    ST_TREN *tren=(ST_TREN*)malloc(sizeof(ST_TREN));
    int i=0;
    char c[2] = ",";
    char *token;
    token = strtok(str, c);
    
    while( token != NULL ) {
    
    if(i==1){
        strcpy(tren->idTren,token);
    }

    if(i==2){
        strcpy(tren->estacionOrigen,palabra);
    }

    if(i==3){
        strcpy(tren->estacionDestino,palabra);
    }

    if(i==4){
        strcpy(tren->pasajeros,palabra);
    }

    if(i==5){
        tren->combustible=atoi(palabra);
    }

    if(i==6){
        tren->tViaje=atoi(palabra);
    }

    if(i==7){
        strcpy(tren->estado,palabra);
    }
    if(i==8){
        strcpy(tren->motivo,palabra);
    }
    i++;

    token = strtok(NULL, c);
  }

}

void escribirRegTrenes(ST_TREN tren){
    FILE * archTrenes=NULL;

    archTrenes=fopen("registros.txt","a");

    if(archTrenes==NULL){
        exit(EXIT_FAILURE);
    }

    fprintf(archTrenes,"Id Tren:%s.Estacion Origen:%s. Estacion Destino:%s
    Motivo:%s.",tren.idTren,tren.estacionOrigen,tren.estacionDestino,tren.motivo);

    fclose(archTrenes);
}
void create(ST_LISTA **list){
    *list=NULL;
    return;
}
ST_LISTA * crearnodo(ST_TREN dato){
    ST_LISTA *nodo=(ST_LISTA*) malloc (sizeof(ST_LISTA));
    nodo->data=dato;
    nodo->ste=NULL;
    return nodo;
}
/*
 *Inserta un nodo y lo ordena por tiempo de viaje #FALTA CREAR CONDICION PARA 
 * EVITAR STARVATION#
 */

ST_LISTA * instordlistaesp (ST_LISTA **list, ST_TREN dato){
    ST_LISTA *nodo=crearnodo (dato);
    ST_LISTA *listaux=*list;
    ST_LISTA *nodoant=NULL;
    while (listaux!=NULL && dato.tViaje>listaux->data->tViaje){
        nodoant=listaux;
        listaux=listaux->ste;
        
    }
    if(nodoant==NULL){
        *list=nodo;
    }
    else{
        nodoant->nodo;
    }
    nodo->ste=listaux;
    return nodo;
}