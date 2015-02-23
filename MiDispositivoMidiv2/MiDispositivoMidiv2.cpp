

#include "Arduino.h"
#include "MiDispositivoMidiv2.h"

const int latchPin = 10;
const int dataPin = 11;
const int clockPin = 12;

// Estas variables almacenaran en hexadecimal los valores necesarios
// para representar en los led lo que se quiera
char parteAlta = 0x00;
char parteBaja = 0x00;


byte dataArrayRG[4]; // Datos RED GREEN
byte dataArrayBC[4]; // Datos BLUE y COL
byte dataRG;
byte dataBC;
#define RED 1
#define BLU 0
#define GRN 2
int anodoComun = 1;  //cambiar anodo o catodo comun.  anodo =1

// Almacenara los valores de los led que se quieran encender
int ledMatrix[4][4][3]={
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0},}, // RGB
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0},},
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0},},
    {{0,0,0},{0,0,0},{0,0,0},{0,0,0},},
};

// Constructor de nuestro dispositivo
MiDispositivoMidiv2::MiDispositivoMidiv2()
{
    // Se ponen asignan los pines para los registros de desplazamiento como salidas
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    //Se encinden los leds con el valor inicial de las variables
    // parteAlta y parteBaja. Este valor hace que esten apagados
}


//--------------PARA LOS LEDS---------------------//

void MiDispositivoMidiv2::setCommonAnode(){
    anodoComun = 1;
}
void MiDispositivoMidiv2::setCommonCathode(){
    anodoComun = 0;
}

void MiDispositivoMidiv2::turnOn(){
    //Apaga la salida para que al realizar el desplazamiento no se vea
    digitalWrite(latchPin, LOW);
    //Lleva los datos a los registros
    if(!anodoComun){  //si es de catodo comun en vez de anodo comun
        parteBaja = ~parteBaja;
        parteAlta = ~parteAlta;
    }
    shiftOut(dataPin, clockPin, LSBFIRST, parteBaja);
    shiftOut(dataPin, clockPin, LSBFIRST, parteAlta);
    // turn on the output so the LEDs can light up:
    digitalWrite(latchPin, HIGH);
}
//Lleva a los registros de desplazamiento todos los datos necesarios para iluminar los leds
void MiDispositivoMidiv2::setLed(char alta, char baja){
    parteAlta=alta;
    parteBaja=baja;
    turnOn();
}
//Enciende todo de un mismo color
void MiDispositivoMidiv2::lightUpAll(char color){
    if(color=='b'){
        setLed(0xF0,0xFF);
    }
    if(color=='r'){
        setLed(0x0F,0xFF);
    }
    if(color=='g'){
        setLed(0xFF,0x0F);
    }
    if(color=='y'){
        setLed(0x0F,0x0F);
    }
    if(color=='m'){
        setLed(0x00,0xFF);
    }
    if(color=='c'){
        setLed(0xF0,0x0F);
    }
    if(color=='w'){
        setLed(0x00,0x0F);
    }
}
//Enciende una fila de un determinado color
void MiDispositivoMidiv2::lightUpRow(char color, int fila ){
    if(color=='b'){ //Color azul
        if(fila==1){setLed(0xFE,0xFF);}
        if(fila==2){setLed(0xFD,0xFF);}
        if(fila==3){setLed(0xFB,0xFF);}
        if(fila==4){setLed(0xF7,0xFF);}
    }if(color=='r'){ //Color rojo
        if(fila==1){setLed(0xEF,0xFF);}
        if(fila==2){setLed(0xDF,0xFF);}
        if(fila==3){setLed(0xBF,0xFF);}
        if(fila==4){setLed(0x7F,0xFF);}
    }if(color=='g'){ //Color verde
        if(fila==1){setLed(0xFF,0xEF);}
        if(fila==2){setLed(0xFF,0xDF);}
        if(fila==3){setLed(0xFF,0xBF);}
        if(fila==4){setLed(0xFF,0x7F);}
    }
    if(color=='y'){ //Color amarillo = verde + rojo
        if(fila==1){setLed(0xEF,0xEF);}
        if(fila==2){setLed(0xDF,0xDF);}
        if(fila==3){setLed(0xBF,0xBF);}
        if(fila==4){setLed(0x7F,0x7F);}
    }
    if(color=='m'){ //Color magenta = rojo + azul
        if(fila==1){setLed(0xEE,0xFF);}
        if(fila==2){setLed(0xDD,0xFF);}
        if(fila==3){setLed(0xBB,0xFF);}
        if(fila==4){setLed(0x77,0xFF);}
    }
    if(color=='c'){ //Color cyan = verde + azul
        if(fila==1){setLed(0xFE,0xEF);}
        if(fila==2){setLed(0xFD,0xDF);}
        if(fila==3){setLed(0xFB,0xBF);}
        if(fila==4){setLed(0xF7,0x7F);}
    }
    if(color=='w'){ //Color blanco = verde + rojo + azul
        if(fila==1){setLed(0xEE,0xEF);}
        if(fila==2){setLed(0xDD,0xDF);}
        if(fila==3){setLed(0xBB,0xBF);}
        if(fila==4){setLed(0x77,0x7F);}
    }
}

//Enciende una columna de un determinado color
void MiDispositivoMidiv2::lightUpCol(char color, int columna){
    if(color=='b'){ //Color azul
        if(columna==1){setLed(0xF0,0xF8);}
        if(columna==2){setLed(0xF0,0xF4);}
        if(columna==3){setLed(0xF0,0xF2);}
        if(columna==4){setLed(0xF0,0xF1);}
    }if(color=='r'){ //Color rojo
        if(columna==1){setLed(0x0F,0xF8);}
        if(columna==2){setLed(0x0F,0xF4);}
        if(columna==3){setLed(0x0F,0xF2);}
        if(columna==4){setLed(0x0F,0xF1);}
    }if(color=='g'){ //Color verde
        if(columna==1){setLed(0xFF,0x08);}
        if(columna==2){setLed(0xFF,0x04);}
        if(columna==3){setLed(0xFF,0x02);}
        if(columna==4){setLed(0xFF,0x01);}
    }
    if(color=='y'){ //Color amarillo = verde + rojo
        if(columna==1){setLed(0x0F,0x08);}
        if(columna==2){setLed(0x0F,0x04);}
        if(columna==3){setLed(0x0F,0x02);}
        if(columna==4){setLed(0x0F,0x01);}
    }
    if(color=='m'){ //Color magenta = rojo + azul
        if(columna==1){setLed(0x00,0xF8);}
        if(columna==2){setLed(0x00,0xF4);}
        if(columna==3){setLed(0x00,0xF2);}
        if(columna==4){setLed(0x00,0xF1);}
    }
    if(color=='c'){ //Color cyan = verde + azul
        if(columna==1){setLed(0xF0,0x08);}
        if(columna==2){setLed(0xF0,0x04);}
        if(columna==3){setLed(0xF0,0x02);}
        if(columna==4){setLed(0xF0,0x01);}
    }
    if(color=='w'){ //Color blanco = verde + azul + rojo
        if(columna==1){setLed(0x00,0x08);}
        if(columna==2){setLed(0x00,0x04);}
        if(columna==3){setLed(0x00,0x02);}
        if(columna==4){setLed(0x00,0x01);}
    }
}
//Enciende un elemento concreto del array de un color
void MiDispositivoMidiv2::lightUpDir(int fila, int columna, char color){
    char primero=0x00;
    char segundo=0x00;
    if(columna==1){segundo|=0x08;}
    if(columna==2){segundo|=0x04;}
    if(columna==3){segundo|=0x02;}
    if(columna==4){segundo|=0x01;}
    
    if(color=='g'){primero=0xFF;
        if(fila==1){segundo|=0xE0;}
        if(fila==2){segundo|=0xD0;}
        if(fila==3){segundo|=0xB0;}
        if(fila==4){segundo|=0x70;}
    }
    if(color=='r'){segundo|=0xF0;
        if(fila==1){primero|=0xE0;}
        if(fila==2){primero|=0xD0;}
        if(fila==3){primero|=0xB0;}
        if(fila==4){primero|=0x70;}
    }
    if(color=='b'){segundo|=0xF0;
        if(fila==1){primero|=0x0E;}
        if(fila==2){primero|=0x0D;}
        if(fila==3){primero|=0x0B;}
        if(fila==4){primero|=0x07;}
    }
    if(color=='y'){primero=0x0F; // Amarillo = verde + rojo
        if(fila==1){segundo|=0xE0; primero=0xEF;}
        if(fila==2){segundo|=0xD0; primero=0xDF;}
        if(fila==3){segundo|=0xB0; primero=0xBF;}
        if(fila==4){segundo|=0x70; primero=0x7F;}
    }
    if(color=='m'){segundo|=0xF0; // Magenta = rojo + azul
        if(fila==1){primero|=0xEE;}
        if(fila==2){primero|=0xDD;}
        if(fila==3){primero|=0xBB;}
        if(fila==4){primero|=0x77;}
    }
    if(color=='c'){primero=0xF0; // Cyan = verde + azul
        if(fila==1){segundo|=0xE0; primero=0xFE;}
        if(fila==2){segundo|=0xD0; primero=0xFD;}
        if(fila==3){segundo|=0xB0; primero=0xFB;}
        if(fila==4){segundo|=0x70; primero=0xF7;}
    }
    if(color=='w'){              // Blanco = rojo + verde + azul
        if(fila==1){segundo|=0xE0; primero=0xEE;}
        if(fila==2){segundo|=0xD0; primero=0xDD;}
        if(fila==3){segundo|=0xB0; primero=0xBB;}
        if(fila==4){segundo|=0x70; primero=0x77;}
    }
     setLed(primero, segundo);
}

//Encience toda la matriz con los colores introducidos a traves de un array 4x4
void MiDispositivoMidiv2::lightUpArray(int MatrixB[4][4])
{
// Se asignan los valores de color a la terna binaria (x,x,x) en RGB
    for (int i = 0; i<4; i++){
        for (int j=0; j<4; j++){
            if(MatrixB[i][j]==1){
                ledMatrix[i][j][0]=0;
                ledMatrix[i][j][1]=0;
                ledMatrix[i][j][2]=1;
            }
            if(MatrixB[i][j]==2){
                ledMatrix[i][j][0]=1;
                ledMatrix[i][j][1]=0;
                ledMatrix[i][j][2]=0;
            }
            if(MatrixB[i][j]==3){
                ledMatrix[i][j][0]=0;
                ledMatrix[i][j][1]=1;
                ledMatrix[i][j][2]=0;
            }
            if(MatrixB[i][j]==4){
                ledMatrix[i][j][0]=1;
                ledMatrix[i][j][1]=0;
                ledMatrix[i][j][2]=1;
            }
            if(MatrixB[i][j]==5){
                ledMatrix[i][j][0]=1;
                ledMatrix[i][j][1]=1;
                ledMatrix[i][j][2]=0;
            }
            if(MatrixB[i][j]==6){
                ledMatrix[i][j][0]=0;
                ledMatrix[i][j][1]=1;
                ledMatrix[i][j][2]=1;
            }
            if(MatrixB[i][j]==7){
                ledMatrix[i][j][0]=1;
                ledMatrix[i][j][1]=1;
                ledMatrix[i][j][2]=1;
            }
        }
    }

    // Se generan los arrays de control para encender los leds pedidos
    for(int j=0;j<4;j++){
        for(int i=0;i<4;i++){
            if(ledMatrix[i][j][RED]==0){
                switch(i){
                    case 3: dataArrayRG[j]=dataArrayRG[j]|0x10;break;
                    case 2: dataArrayRG[j]=dataArrayRG[j]|0x20; break;
                    case 1: dataArrayRG[j]=dataArrayRG[j]|0x40; break;
                    default:dataArrayRG[j]=dataArrayRG[j]|0x80;
                }
            }else{
                switch(i){
                    case 3: dataArrayRG[j]=dataArrayRG[j]&0xEF; break;
                    case 2: dataArrayRG[j]=dataArrayRG[j]&0xDF; break;
                    case 1: dataArrayRG[j]=dataArrayRG[j]&0xBF; break;
                    default: dataArrayRG[j]=dataArrayRG[j]&0x7F;
                }
            }
            if(ledMatrix[i][j][GRN]==0){
                switch(i){
                    case 3: dataArrayRG[j]=dataArrayRG[j]|0x01; break;
                    case 2: dataArrayRG[j]=dataArrayRG[j]|0x02; break;
                    case 1: dataArrayRG[j]=dataArrayRG[j]|0x04; break;
                    default: dataArrayRG[j]=dataArrayRG[j]|0x08;
                }
            }else{
                switch(i){
                    case 3: dataArrayRG[j]=dataArrayRG[j]&0xFE; break;
                    case 2: dataArrayRG[j]=dataArrayRG[j]&0xFD; break;
                    case 1: dataArrayRG[j]=dataArrayRG[j]&0xFB; break;
                    default: dataArrayRG[j]=dataArrayRG[j]&0xF7;
                }
            }
            if(ledMatrix[i][j][BLU]==0){
                switch(i){
                    case 3: dataArrayBC[j]=dataArrayBC[j]|0x01; break;
                    case 2: dataArrayBC[j]=dataArrayBC[j]|0x02; break;
                    case 1: dataArrayBC[j]=dataArrayBC[j]|0x04; break;
                    default: dataArrayBC[j]=dataArrayBC[j]|0x08;
                }
            }else{
                switch(i){
                    case 3: dataArrayBC[j]=dataArrayBC[j]&0xFE; break;
                    case 2: dataArrayBC[j]=dataArrayBC[j]&0xFD; break;
                    case 1: dataArrayBC[j]=dataArrayBC[j]&0xFB; break;
                    default: dataArrayBC[j]=dataArrayBC[j]&0xF7;
                }
            }
        }
        switch(j){
            case 0: dataArrayBC[j]=dataArrayBC[j]|0x10; break;
            case 1: dataArrayBC[j]=dataArrayBC[j]|0x20; break;
            case 2: dataArrayBC[j]=dataArrayBC[j]|0x40; break;
            default: dataArrayBC[j]=dataArrayBC[j]|0x80; 
        }
        switch(j){
            case 0: dataArrayBC[j]=dataArrayBC[j]&0x1F; break;
            case 1: dataArrayBC[j]=dataArrayBC[j]&0x2F; break;
            case 2: dataArrayBC[j]=dataArrayBC[j]&0x4F; break;
            default: dataArrayBC[j]=dataArrayBC[j]&0x8F; 
        }
    }
    
    // Se encienden los Leds usando los HC595
    for (int j = 0; j < 4; j++) {
        dataBC = dataArrayBC[j];
        dataRG = dataArrayRG[j];
        digitalWrite(latchPin, LOW);
        shiftOut2(dataPin, clockPin, dataBC);
        shiftOut2(dataPin, clockPin, dataRG);
        digitalWrite(latchPin, HIGH);
        
        setLed(0x00,0x00);
    }
}

void MiDispositivoMidiv2::shiftOut2(int myDataPin, int myClockPin, byte myDataOut) {
    int i=0;
    int pinState;
    if(!anodoComun){
        myDataOut = ~myDataOut; //hacer esto si son de catodo comun
    }
    
    pinMode(myClockPin, OUTPUT);
    pinMode(myDataPin, OUTPUT);
    digitalWrite(myDataPin, 0);
    digitalWrite(myClockPin, 0);
    for (i=7; i>=0; i--)  {
        digitalWrite(myClockPin, 0);
        if ( myDataOut & (1<<i) ) {
            pinState= 1;
        }
        else {
            pinState= 0;
        }
        digitalWrite(myDataPin, pinState);
        digitalWrite(myClockPin, 1);
        digitalWrite(myDataPin, 0);
    }
    digitalWrite(myClockPin, 0);


}




