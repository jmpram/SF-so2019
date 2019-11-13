#include "tren.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80

   void createTren(ST_TREN * tren){
     
     memset(tren->idTren,'\0',8);
     memset(tren->estacionOrigen,'\0',strlen(tren->estacionOrigen));
     memset(tren->estacionDestino,'\0',strlen(tren->estacionDestino));
     memset(tren->pasajeros,'\0',strlen(tren->pasajeros));
     tren->combustible=0;
     tren->tViaje=0;
     strcpy(tren->estado,"estacion");//estacion,anden, transito
     memset(tren->motivo ,'\0',strlen(tren->motivo));//PASO O ANDEN
}

void obtenerPalabra (const char* linea, char * palabra, int *indice){
    int i=0;
    while(*linea!=',' && *linea!='.'){
        *(palabra+i)=*linea;
        linea++;
        *indice=*indice+1;
        i++;
    }
    *indice=*indice+1;

}

void cargarTren(const char* linea,ST_TREN * tren){
         int i=0;
     int indice=0;
     char * palabra=(char*)malloc(sizeof(char)*MAX);

     while(*linea!='\0'){
            indice=0;
            memset(palabra,'\0',MAX);
            obtenerPalabra(linea,palabra,&indice);
            i++;
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
    
}

void enviarTren(ST_TREN * tren, int sockTren){

char* mensaje=(char*)malloc(sizeof(char)*MAX);
	codificarMsj(mensaje,tren);
 send(sockTren, mensaje, sizeof(mensaje),0); 


}
 void codificarMsj(const char* buffer, ST_TREN * tren){
    char * aux=(char*)malloc(sizeof(char)*MAX);
    memset(aux,'\0',MAX);
    char coma[2];
    memset(coma,'\0',2);
    coma[0]=',';

    itoa(estacion.sId,aux);
    strcpy(buffer,aux);
    strcat(buffer,coma);
    memset(aux,'\0',MAX);
    itoa(estacion.usoAnden,aux);
    strcat(buffer,aux); 
   strcat(buffer,coma);  

}
/*void pasardatosabuffer(char*linea, ST_TREN tren){
    strcat
    *linea =itoa(tren.idTren);
    linea=linea+1; //dejo un epacio
    *linea=' ';
    itoa (tren.pasajeros,linea,10);//cuento pos de pasajeros
    linea = linea+1 //1 para el espacio
    *linea=' ';
    itoa (tren.combustible,linea,10);
    linea=linea+1;
    *linea=' ';
    itoa(tren.tViaje,linea,10);
    linea=linea+1;
    *linea=' ';
    itoa (tren.estado,linea,10);
    *linea='\0';
}*/
/*void bufferatren(const char * linea, ST_TREN*tren){
    int cant=0;
    char* token=malloc(5);
    memset(token,'\0',5);
    token=strtok(token,' ');
    tren->id=token;
    while(token){
        cant++;
        if (cant==2)
            strcpy(tren->pasajeros,token);
        if (cant==3)
            tren->estado=atoi(token);
        if(cant==4)
            tren->combustible=atoi(token);
        token=strtok(NULL,' ');
    }
}*/
