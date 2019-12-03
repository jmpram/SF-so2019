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
 *
 * estacion2.c
 * 
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>  
#include "tren.h"
#include "estacion.h"
#include "comunicaciones.h"
#define MAX 80
#define MAX_TRENES 30
#define TRUE 1 
#define FALSE 0 
#define PORT 5080
   
int main (int argc , char *argv[]){ 

    pthread_t hilo;

    ST_TREN tren,anden;
    ST_TREN cola [MAX_TRENES]; 
    
    char tipoEnt;
    char * buffer=(char*)malloc(sizeof(char)*MAX) ; 
    memset(buffer,'\0',MAX);
    struct sockaddr_in estacionAddr; 
    struct sockaddr_in estacion2;  
  
    int conectado=0,option = TRUE,usoanden=FALSE,sockEstacion2,new_socket,sockTrenes[MAX_TRENES],
    max_trenes = 30,activity,i,valread,numDescripTren,max_numDescripTren,sockEst1;   
  
    inicializarTren(&tren);
    inicializarcola(cola,MAX_TRENES);
    inicializar (sockTrenes,MAX_TRENES);
    //se inicilizan el array socket trenes a valores 0
    
    //puntero  los descriptores de los trenes
    fd_set descriptoresTrenes;   
       
    //se crea el socket estacion 
    if( (sockEstacion2= socket(AF_INET , SOCK_STREAM , 0)) == 0){   
        perror("creacion de estacion fallida");   
        exit(EXIT_FAILURE);   
     }   
     
    //se configura la estacion para que reciba multiples conexiones   
    if( setsockopt(sockEstacion2, SOL_SOCKET, SO_REUSEADDR, (char *)&option,
            sizeof(option)) < 0){   
        perror("error en las opciones del socket estacion");   
        exit(EXIT_FAILURE);   
    }   
     
    //se establece el tipo de socket 
    estacionAddr.sin_family = AF_INET;   
    estacionAddr.sin_addr.s_addr = INADDR_ANY;   
    estacionAddr.sin_port = htons(PORT);   
         
    //enlaza el socket al  localhost 
    if (bind(sockEstacion2, (struct sockaddr *)&estacionAddr, 
            sizeof(estacionAddr))<0){   
        perror("fallo en el enlace");   
        exit(EXIT_FAILURE);   
    }   
    printf("la estacion esta escuchando en el puerto: %d \n", PORT);   
         
    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(sockEstacion2, MAX_TRENES) < 0)   
    {   
        perror("La Estacion ya no puede recibir mas trenes");   
        exit(EXIT_FAILURE);   
    }   
         
    //accept the incoming connection  
    int addrlen = sizeof(estacionAddr);   
    puts("esperando por comunicaciones entrantes...");   
         
    while(TRUE)   
    {   
        //clear the socket set  
        FD_ZERO(&descriptoresTrenes);   
     
        //add master socket to set  
        FD_SET(sockEstacion2, &descriptoresTrenes);   
        max_numDescripTren = sockEstacion2;   
             
        //add child sockets to set  
        for ( i = 0 ; i < MAX_TRENES ; i++)   
        {   
            //socket descriptor  
            numDescripTren = sockTrenes[i];   
                 
            //if valid socket descriptor then add to read list  
            if(numDescripTren > 0)   
                FD_SET( numDescripTren , &descriptoresTrenes);   
                 
            //highest file descriptor number, need it for the select function  
            if(numDescripTren> max_numDescripTren)   
                max_numDescripTren = numDescripTren;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
        activity = select( max_numDescripTren + 1 , &descriptoresTrenes , NULL , 
                NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
             
        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(sockEstacion2, &descriptoresTrenes))   
        {   
            if ((new_socket = accept(sockEstacion2,(struct sockaddr*)&estacionAddr,
                    (socklen_t*)&addrlen))<0)   
            {   
                perror("error al aceptar la conexion");   
                exit(EXIT_FAILURE);   
            }   
             
            //muestra al usuario el numero de socket - used in send and receive commands  
            printf("nueva conexion, el socket descriptor es %d , ip is : %s , "
                    "port : %d\n" , new_socket , inet_ntoa(estacionAddr.sin_addr),
                ntohs(estacionAddr.sin_port));  
                 
            //add new socket to array of sockets  
            for (i = 0; i < MAX_TRENES; i++)   
            {   
                //if position is empty  
                if( sockTrenes[i] == 0 )   
                {   
                    sockTrenes[i] = new_socket;   
                    printf("añadiendolo a la lista de socket trenes %d\n" , i);   
                         
                    break;   
                }   
            }   
        }   
             
         //sino es una operacion de entrada salida u otro socket
        for (i = 0; i < MAX_TRENES; i++){ 

            numDescripTren = sockTrenes[i];   
                 
            if (FD_ISSET( numDescripTren , &descriptoresTrenes)){   
                //se chequea si alguien se desconecto o  se recibe el mensaje del tren 
                if ((valread = read( numDescripTren , buffer, MAX)) == 0){   
                //Somebody disconnected , get his details and print  
                    getpeername(numDescripTren , (struct sockaddr*)&estacionAddr,
                      (socklen_t*)&addrlen );   
                    printf("Host disconnected , ip %s , port %d \n" ,inet_ntoa(estacionAddr.sin_addr)
                    ,ntohs(estacionAddr.sin_port));   
                    // CIERRA EL SOCKET DEL TREN QUE SE DESCONECTO Y MARCA LA LISTA COMO 0 PRAA REUSAR
                    close( numDescripTren );   
                    sockTrenes[i] = 0;
                    cola[i].tViaje=0;
                    balanceo(cola,sockTrenes,MAX_TRENES);
                }else{  
                        printf("msj recibido:%s\n",buffer);
                        tipoEnt=identificarEntidad(buffer);
                        if(tipoEnt=='T'){

                            decodificarTren(buffer, &tren);   
                            printf("tren id: %s estado:%s\n", tren.idTren,tren.estado);
                            cola[i]=tren;
                            balanceo(cola,sockTrenes,MAX_TRENES);
                         }
                          /* if(tipoEnt=='E'){
                            int id=fork();
                            if (id==0){
                                execlp("./tren","./tren",NULL);
                            }
                          }*/
                    
                    printf("Tren %d %s\n",new_socket, buffer);
                 
                }   
            }      
           
        }   
    }    

return 0;   
  
}