
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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tren.h"
#include "estacion.h"
#include <curses.h>
#define MAX 80

void itoa(char *linea,int valor){

    sprintf(linea,"%d",valor); 
}

void concatenarMsj (char *buffer,char *aux, char* origen){
    char coma=',';
    strcpy(aux,origen);
    strcat(buffer,aux);
    strcat(buffer,&coma);
}

void obtenerPalabra (const char* linea, char * palabra, int *indice){
    int i=0;
    while(*linea && *linea!=',' && *linea!='.'){
        *(palabra+i)=*linea;
        linea++;
        *indice=*indice+1;
        i++;
    }
    *indice=*indice+1;
}

void enviarTrenE(ST_TREN * tren, int sockToE){
    char * mensaje=(char*)malloc(sizeof(char)*MAX);
    memset(mensaje,'\0',MAX);

    //printf("El tren se  esta poniendo en marcha.\n"); 
    
    codificarMsj(mensaje,tren);
    send(sockToE, mensaje,strlen(mensaje),0); 
    free(mensaje);
    return ;
}

ERROR clearLogWindow(WINDOW *pWin){
    werase(pWin);
    wrefresh(pWin);
    return ERR_OK;
}

/**
 * Limpia la ventana de comandos cuando se llena.
 * 
 * @param pWin ventana de comandos
 * @return ERR_OK
 */
ERROR clearCmdWindow(WINDOW *pWin){
    int maxRow = 0;
    int maxCol = 0;
    int row = 0;
    int col = 0;
    getyx(pWin, row, col);
    getmaxyx(pWin, maxRow, maxCol);
    if(row == maxRow-1){
        werase(pWin);
    }
    
    return ERR_OK;
}

ERROR processCommand(int sockTren,ST_TREN * tren,ST_APP_WINDOW *pAppWin, 
        const char *commandLine){
    if(strncmp(commandLine,"help", 4)==0){
        clearLogWindow(pAppWin->pLogWindow);
        printHelp(pAppWin);
        clearLogWindow(pAppWin->pCmdWindow);
    
    }
    if(strncmp(commandLine,"info", 4)==0){
        clearLogWindow(pAppWin->pLogWindow);
        imprimirInfoTren(tren,pAppWin);
        clearLogWindow(pAppWin->pCmdWindow);
    }
    
    if(strncmp(commandLine, "reg", 3)==0){
        clearLogWindow(pAppWin->pLogWindow);
        enviarTrenE(tren, sockTren);
        printMessage(pAppWin,"El tren se registro",GREEN);
        clearLogWindow(pAppWin->pCmdWindow);
    }
          
    clearCmdWindow(pAppWin->pCmdWindow);
    return ERR_OK;
}

/*void escribirMensajeT(int sockTren,ST_TREN * tren) { 
    char * mensaje=(char*)malloc(sizeof(char*)*MAX); 
     
        while (1){

            memset(mensaje,'\0',MAX); 
            printf("Ingrese el mensaje: \n"); 
            gets(mensaje);
        
            if ((strncmp(mensaje, "info", 4)) == 0) { 

                        imprimirInfoTren(tren);

            } else if ((strncmp(mensaje, "registrar tren", 4)) == 0) { 
                
                        enviarTrenE(tren, sockTren);


            } else if ((strncmp(mensaje, "exit", 4)) == 0) { 

            			printf("te desconectaste.\n"); 

            			break; 
        	}else{
        
                        send(sockTren, mensaje, strlen(mensaje),0); 
                
            } 
            
        }  
        
    free(mensaje);
} */
 
void escribirMensajeEst(ST_TREN anden,ST_TREN v[],int n,int u,int socktren[]) { 
    char * mensaje=(char*)malloc(sizeof(char*)*MAX); 
    
    

         
        
    while (1){

        memset(mensaje,'\0',MAX);
        printf("Ingrese el mensaje: \n");

        if ((strncmp(mensaje, "info", 4)) == 0) { 

            printEstacion(anden,v,n,u,socktren[0]);

        } else if ((strncmp(mensaje, "enviar tren", 4)) == 0) { 

                enviarTrenE(&anden, socktren[1]);

                    

        }else if((strncmp(mensaje, "enviar anden", 4)) == 0){

                if (u==0){

                    anden=enviarAnden(v,socktren,n,&u);

                }else{
                    printf("El anden está ocupado en este momento\n");
                }

        } else if ((strncmp(mensaje, "exit", 4)) == 0) { 

                    printf("te desconectaste.\n"); 

                break; 
        } else{
        
                    send(*socktren, mensaje, sizeof(mensaje),0); 
            
        } 
    }    
     
} 

int crearSockTren(const char * port){
    int sockTren;
    struct sockaddr_in estacionAddr;

    int puerto=atoi(port);

    if((sockTren = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 

        printf("la creacion del Tren fallo..\n"); 
        exit(0); 
    } 
    // se asigna la ip y el puerto a usar
    estacionAddr.sin_family = AF_INET; 
    estacionAddr.sin_addr.s_addr = INADDR_ANY; 
    estacionAddr.sin_port = htons(puerto); 

     // se conecta el tren con la estacion
     if (connect(sockTren,(struct sockaddr*)&estacionAddr, sizeof(estacionAddr)) != 0) { 
        printf("La conexion con la estacion fallo..\n"); 
        exit(0); 
    }
    
    printf("Esta conectado con la estacion..\n"); 
    
    return sockTren;

}