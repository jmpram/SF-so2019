#include <stdio.h>
#include <string.h>
#include "user_interface.h"
#include "user_commands.h"

int main(int argc, char *argv[]) {
    ST_APP_WINDOW pWin;
    initUserInterface(&pWin);
    drawUserInterface(&pWin);
    
    printWindowTitle(pWin.pLogFrame, "### Mensajes ###");
    printWindowTitle(pWin.pCmdFrame, "### Ventana para ingresar comandos ###");
    
    printMessage(&pWin, "Escriba \"help\" para obtener información", WHITE);
    
    wmove(pWin.pCmdWindow, 1,1);

    char linea[CMD_LINE_LENGHT + 1];
    memset(linea, '\0', CMD_LINE_LENGHT + 1);
    wgetnstr(pWin.pCmdWindow, linea, CMD_LINE_LENGHT + 1);
    
    while(strncmp(linea, "exit", CMD_LINE_LENGHT + 1)!=0){
        processCommand(&pWin, linea);
        memset(linea, '\0', 21);
        wgetnstr(pWin.pCmdWindow, linea, CMD_LINE_LENGHT + 1);
    }
    
    printMessage(&pWin, "Saliendo...", RED);
    unInitUserInterface(&pWin);
    
    return 0;
}

