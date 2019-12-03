
/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 * /
 
 /** 
 * 
 * funcionesTren.c
 * Manejo de tren
 * 
 * funciones del tren
 * Manejos de los mensajes de la estructura tren cliente
 */ 


#include "tren.h"
#include "comunicaciones.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 80


void inicializarTren(ST_TREN * tren){
     
     memset(tren->idTren,'\0',8);
     memset(tren->estacionOrigen,'\0',strlen(tren->estacionOrigen));
     memset(tren->estacionDestino,'\0',strlen(tren->estacionDestino));
     memset(tren->pasajeros,'\0',strlen(tren->pasajeros));
     tren->combustible=0;
     tren->tViaje=0;
     strcpy(tren->estado,"estacion");//estacion,anden, transito
     memset(tren->motivo ,'\0',strlen(tren->motivo));//PASO O ANDEN
     
}

void cargarTren(const char* linea,ST_TREN * tren){
     int i=0;
     int indice=0;
     char * palabra=(char*)malloc(sizeof(char)*MAX);

     while(*linea!='\0'){
            i++;
            indice=0;
            memset(palabra,'\0',MAX);
            obtenerPalabra(linea,palabra,&indice);
            
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
        linea=linea+indice;          
     }
     free(palabra);
    
}

 void codificarMsj (char * buffer, ST_TREN * tren){
    int i=0;
    char coma[2]=",";
    char tipoEnt[2]="T";
    char * aux=(char*)malloc(sizeof(char)*MAX); 
    memset(aux,'\0',MAX); 
    char * aux2=(char*)malloc(sizeof(char)*MAX); 
    memset(aux2,'\0',MAX);

   strncpy(buffer,tipoEnt,1);
    strcat(buffer,coma);

    while(i<8){
        memset(aux2,'\0',MAX);

        switch(i){
           
            case 0:
                    concatenarMsj(aux,aux2,tren->idTren);
                   
                    break;
            case 1:
                    concatenarMsj(aux,aux2, tren->estacionOrigen);
                   
                    break;
            case 2:
                    concatenarMsj(aux,aux2,tren->estacionDestino);
                    
                    break;
            case 3:
                    concatenarMsj(aux,aux2,tren->pasajeros); 
                        
                    break;
            case 4:
                    itoa(aux2,tren->combustible);
                    strcat(aux,aux2);
                    strcat(aux,coma);
                  
                    break;
            case 5:
                    
                    itoa(aux2,tren->tViaje);
                    strcat(aux,aux2);
                    strcat(aux,coma);
                    
                    break;
            case 6:
                    concatenarMsj(aux,aux2,tren->estado); 
                    
                    break;
            case 7:
                    concatenarMsj(aux,aux2,tren->motivo);
                    
                    break;    
            default:  
                    break;
        }

        i++;
    }
    strcat(buffer,aux);
    free(aux);
    free(aux2);
}

void imprimirInfoTren(ST_TREN * tren){

    printf("Informacion del tren:\n"); 
    printf("Modelo:%s\n",tren->idTren);
    printf("Origen:%s\n",tren->estacionOrigen);
    printf("Destino:%s\n",tren->estacionDestino);
    printf("Cant de pasajeros:%s\n",tren->pasajeros);
    printf("Litros de combustible:%d\n",tren->combustible);
    printf("tiempo de viaje restante:%d\n",tren->tViaje);
    printf("Estado:%s\n",tren->estado); // en transito, en anden, en estacion
    printf("Motivo:%s\n",tren->motivo); // paso o anden
}

 
