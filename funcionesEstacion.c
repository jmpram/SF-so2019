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
        v[i].estacionDestino[0]='\0';
        v[i].estacionOrigen[0]='\0';
        v[i].estado[0]='\0';
        v[i].idTren[0]='\0';
        v[i].motivo[0]='\0';
        v[i].pasajeros[0]='\0';
        v[i].tViaje=0;
    }
}
void balanceo(ST_TREN v[],int vsock[],int n){
    int aux1=0;
    ST_TREN aux2;
    for (int i=0; i<(n-1); i++){
        for(int j=0; j<(n-1-i);j++){
            if (((vsock[j]==0)&&(vsock[j+1]!=0))||(v[j].tViaje>v[j+1].tViaje)){
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

/*void itoa( char *linea,int valor){
    sprintf(linea,"%d",valor); 
}*/
void enviarTrenE(ST_TREN * tren, int sockTren){

    char * mensaje=(char*)malloc(sizeof(char)*MAX);
	codificarMsj(mensaje,tren);
    send(sockTren, mensaje, sizeof(mensaje),0); 
    free(mensaje);
}
char identificarEntidad(char * buffer){
    char tipoEnt;   
    int i=0;
    char c[2] = ",";
    char *token;
    token = strtok(buffer, c);
    if(*token=='T' ||*token=='E'){
        tipoEnt=*token;  
    }
    printf("valor del token:%c",*token);
    
    return tipoEnt;
}

 void decodificarTren (char * buffer,ST_TREN * tren){
    int i=0;
    char c[2] = ",";
    char *token;
    token = strtok(buffer, c);
    
    while( token != NULL ) {
    
    if(i==1){
        strcpy(tren->idTren,token);
    }

    if(i==2){
        strcpy(tren->estacionOrigen,token);
    }

    if(i==3){
        strcpy(tren->estacionDestino,token);
    }

    if(i==4){
        strcpy(tren->pasajeros,token);
    }

    if(i==5){
        tren->combustible=atoi(token);
    }

    if(i==6){
        tren->tViaje=atoi(token);
    }

    if(i==7){
        strcpy(tren->estado,token);
    }
    if(i==8){
        strcpy(tren->motivo,token);
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
    fprintf(archTrenes, "Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                tren.idTren ,tren.combustible,tren.estado,tren.pasajeros,
                tren.tViaje,tren.estacionOrigen ,tren.estacionDestino , tren.motivo);
    fclose(archTrenes);
}

void printestacion(ST_TREN anden , ST_TREN v[], int n, int usoanden){
    printf("ESTADO DE LA ESTACIÓN");
    if (usoanden==1){
        printf("Anden \n");
        printf("Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                anden.idTren ,anden.combustible,anden.estado,anden.pasajeros,
                anden.tViaje,anden.estacionOrigen ,anden.estacionDestino , anden.motivo);
    } else{
        printf("No hay trenes en el anden");
    }
    
    printf("Trenes en cola de espera: \n");
    for (int i=0;i<n;i++){
        printf("Id Tren: %s Combustible: %d Estado: %s Pasajeros %s Tiempo de Viaje %d"
                " Estacion Origen: %s Estacion Destino: %s Motivo: %s\n",
                v[i].idTren ,v[i].combustible,v[i].estado,v[i].pasajeros,
                v[i].tViaje,v[i].estacionOrigen ,v[i].estacionDestino , v[i].motivo);
    }   
}   

ST_TREN enviarAnden (ST_TREN v[],int socktren[], int n, int usoanden){
    
    ST_TREN aux;
    usoanden=1;
    aux=v[0];
    socktren[0]=0;
    v[0].tViaje=0;
    balanceo(v,socktren,n);
    return aux;
}
void escribirMensajeEst(ST_TREN anden,ST_TREN v[],int n,int u,int socktren[]) { 
    char mensaje[MAX]; 
    int i; 
    for (;;) { 
        bzero(mensaje, sizeof(mensaje)); 
        printf(" \n Ingrese el mensaje: \n"); 
        i = 0; 
        while ((mensaje[i++] = getchar()) != '\n'); 
        
            if ((strncmp(mensaje, "info", 4)) == 0) { 
                printestacion(anden,v,n,&u);
            } 
            if ((strncmp(mensaje, "enviar tren", 4)) == 0) { 
                printf("El tren se  esta poniendo en marcha.\n"); 
                enviarTrenE(&anden, socktren[1]);

            break; 
            }
            if((strncmp(mensaje, "enviar anden", 4)) == 0){
                if (u==0){
                    anden=enviarAnden(v,socktren,n,&u);
                }else{
                    printf("el anden está siendo utilizado");
                }
            }
            if ((strncmp(mensaje, "exit", 4)) == 0) { 
            printf("te desconectaste.\n"); 
            break; 
        } else{
        
            send(socktren, mensaje, sizeof(mensaje),0); 
            //bzero(mensaje, sizeof(mensaje)); 
            //recv(sockTren, mensaje, sizeof(mensaje),0); 
           // printf("Estacion envio: %s \n", mensaje); 
        } 
        bzero(mensaje, sizeof(mensaje)); 
    } 
} 

/*
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
/*
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
}*/