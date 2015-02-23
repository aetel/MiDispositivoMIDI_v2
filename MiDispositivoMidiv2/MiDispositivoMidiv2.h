
#ifndef MiDispositivoMidiv2_h
#define MiDispositivoMidiv2_h
#include "Arduino.h"
class MiDispositivoMidiv2
{
public: MiDispositivoMidiv2();

    void turnOn();
    // Da el valor asignado a las variables parteAlta pareBaja
    void setLed(char alta, char baja);
    
    void setCommonAnode();   //hacer esto enel setup para indice que es anodo comun. Esta pr defecto
    void setCommonCathode();  //hacer esto si es cathodo comun. NO esta por defecto
    // Funciones para el manejo de los leds
    void lightUpDir(int fila, int columna, char color);  // Elemento concreto 1,4 y color
    void lightUpRow(char color, int fila);                   // Fila entera 1,4 y color
    void lightUpCol(char color, int columna);             // Columna entera 1,4 y color
    void lightUpAll(char color);                             // Enciende todos del color
    void lightUpArray(int MatrixB[4][4]);
    void shiftOut2(int myDataPin, int myClockPin, byte myDataOut);

    
private:
    
};

#endif