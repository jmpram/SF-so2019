/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 */
/*
 * funcionesEstacion.c 
 */
#include "tren.h"
#include "estacion.h"
#include "comunicaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 80

void inicializar (int v[],int n){     
    for (int i = 0; i < n; i++){   
        v[i] = 0;
    }
}
void inicializarcola (ST_TREN v[],int n){     
    for (int i = 0; i < n; i++){   
        v[i].combustible=0;
        memset(v[i].estacionDestino,'\0',strlen(v[i].estacionDestino));
        memset(v[i].estacionOrigen,'\0',strlen(v[i].estacionOrigen));
        memset(v[i].estado,'\0',strlen(v[i].estado));
        memset(v[i].idTren,'\0',strlen(v[i].idTren));
        memset(v[i].motivo,'\0',strlen(v[i].motivo));
        memset(v[i].pasajeros,'\0',strlen(v[i].pasajeros));
        v[i].tViaje=0;
    }
}
void balanceo(ST_TREN v[],int vsock[],int n){
    int aux1=0;
    ST_TREN aux2;
    for (int i=0; i<(n-1); i++){

        for(int j=0; j<(n-1-i);j++){
            if (((vsock[j]==0) && (vsock[j+1]!=0)) || (v[j].tViaje > v[j+1].tViaje)){
                aux2=v[j];
                aux1=vsock[j];
                v[j]=v[j+1];
                vsock[j]=vsock[j+1];
                v[j+1]=aux2;
                vsock[j+1]=aux1;
            }
        }
    }
}

char identificarEntidad(char * buffer){
    char tipoEnt;   
    int i=0;
    char c= ',';
    char *token;
    token = strtok(buffer, &c);
    if(*token=='T' ||*token=='E'){
        tipoEnt=*token;  
    }
    return tipoEnt;
}

 void decodificarTren (char *buffer, ST_TREN * tren){
    int i=0;
    int indice=0;
    char * palabra=(char*)malloc(sizeof(char)*MAX);

    while( *buffer!='\0' ) {
    indice=0;
    memset(palabra,'\0',MAX);
    obtenerPalabra(buffer,palabra,&indice);

    if(i==1){
    	strcpy(tren->idTren,palabra);
        
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
    buffer=buffer+indice; 

  }
  free(palabra);

}

void escribirRegTrenes(ST_TREN tren){
    FILE * archTrenes=NULL;
    archTrenes=fopen("registros.txt","a");

    if(archTrenes==NULL){
        exit(EXIT_FAILURE);
    }
    fprintf(archTrenes, "Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                tren.idTren ,tren.combustible,tren.estado,tren.pasajeros,
                tren.tViaje,tren.estacionOrigen ,tren.estacionDestino , tren.motivo);
    fclose(archTrenes);
}

void printEstacion(ST_TREN anden , ST_TREN v[], int n, int usoanden,int socktren){
    printf("ESTADO DE LA ESTACIÓN: \n");
    if (usoanden==1){
        printf("Anden \n");
        printf("Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                anden.idTren ,anden.combustible,anden.estado,anden.pasajeros,
                anden.tViaje,anden.estacionOrigen ,anden.estacionDestino , anden.motivo);
    } else{
        printf("No hay trenes en el anden \n");
    }
    
    printf("Trenes en cola de espera: \n");
    if (socktren==0){
        printf("No hay trenes en espera del anden \n");
    }else{
        for (int i=0;i<n;i++){

            if(v[i].idTren!=0){

                printf("Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                v[i].idTren ,v[i].combustible,v[i].estado,v[i].pasajeros,
                v[i].tViaje,v[i].estacionOrigen ,v[i].estacionDestino , v[i].motivo);
            }
        
        }
    }
}   

ST_TREN enviarAnden (ST_TREN v[],int socktren[], int n, int *usoanden){
    
    ST_TREN aux;
    *usoanden=1;
    aux=v[0];
    socktren[0]=0;
    v[0].tViaje=0;
    balanceo(v,socktren,n);
    return aux;
}


