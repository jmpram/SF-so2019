/**
 * TRABAJO PRACTICO
 * #SISTEMAS OPERATIVOS#
 * PROF.: ALEJANDRO MOSTOVOI
 * ALUMNOS:
 * Amado Pablo
 * Leguizamon Marcos
 * Juan Ramasco
 */
/**
 *tren.c
 */

#include <stdbool.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tren.h"
#define MAX 80 
#define PORT 8080
#define SA struct sockaddr 

 
int main(int argc, char * argv[]) { 
    int sockTren; 
    ST_TREN tren;
    createTren(&tren);
    struct sockaddr_in estacionAddr;
    
    FILE * config=NULL;
    char * linea=(char*)malloc(sizeof (char) *MAX);
    memset(linea,'\0',MAX);

    config=fopen(argv[1],"r");

    if(config!=NULL){
        printf("se abrio el archivo\n");    
    } else{
        exit(EXIT_FAILURE);
    }
    
    fgets(linea,MAX,config);
    
    cargarTren(linea,&tren);
       
    memset(linea,'\0',MAX);
   
    // se crea el socket
    sockTren = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockTren == -1) { 
        printf("la creacion del socket fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Se creo el tren..\n"); 
        bzero(&estacionAddr, sizeof(estacionAddr));  
    
    // se asigna la ip y el puerto a usar
    estacionAddr.sin_family = AF_INET; 
    estacionAddr.sin_addr.s_addr = INADDR_ANY; 
    estacionAddr.sin_port = htons(PORT); 
  
    // se conecta el tren con la estacion
    if (connect(sockTren, (SA*)&estacionAddr, sizeof(estacionAddr)) != 0) { 
        printf("La conexion con la estacion fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Esta conectado con la estacion..\n"); 
    
    
    escribirMensaje(sockTren, &tren); 
  
    
    close(sockTren); 
    
} 
