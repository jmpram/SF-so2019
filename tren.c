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


#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tren.h"
#include "comunicaciones.h"
#include <curses.h>
#include "user_interface.h"
#define MAX 80 
#define PORT 8080

int main(int argc, char * argv[]) { 

    /*/  if(argv[2]==NULL){
        printf("estamos en un fork\n");
    }*/

    int sockTren; 
    ST_TREN tren;
    FILE * config=NULL;
    struct sockaddr_in estacionAddr;
    char * linea=(char*)malloc(sizeof (char) *MAX);
    char *puerto=argv[2];
    inicializarTren(&tren);
    memset(linea,'\0',MAX);
    
    if( (config=fopen(argv[1],"r") ) == NULL){

        printf("no se pudo abrir el archivo de configuracion.\n"); 
        exit(EXIT_FAILURE);
    }
    
    
    
    
    fgets(linea,MAX,config);
    
    cargarTren(linea,&tren);
       
    memset(linea,'\0',MAX);
    

    sockTren=crearSockTren(puerto);
    ncurses(sockTren, &tren);
    /*sockTren = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockTren == -1) { 
        printf("la creacion del socket fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Se creo el tren..\n"); 
        
    
    estacionAddr.sin_family = AF_INET; 
    estacionAddr.sin_addr.s_addr = INADDR_ANY; 
    estacionAddr.sin_port = htons(PORT); 
  
    
    if (connect(sockTren, (struct sockaddr *)&estacionAddr, sizeof(estacionAddr)) != 0) { 
        printf("La conexion con la estacion fallo...\n"); 
        exit(0); 
    } 
    else
        printf("Esta conectado con la estacion..\n"); */
    
    
    // escribirMensajeT(sockTren, &tren); 
  
    
    close(sockTren); 
    
} 
