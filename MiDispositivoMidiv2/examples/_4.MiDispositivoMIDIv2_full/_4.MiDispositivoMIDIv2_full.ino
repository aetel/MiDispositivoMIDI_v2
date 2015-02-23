
/****-------------------- MIDISPOSITIVOMIDI V2.0 --------------------****
* This is a simple code to MiDispositivoMidi v2.0, a DIY MIDI Controller
* developed by Pablo de Miguel Morales and Alvaro Lopez Revuelta at the
* Polythecnical University of Madrid, for a workshop given in 2014.
* This code was developed by Alvaro Lopez Revuelta for the project MiDispositivoMidi v2.0
* and uses the function "formar_array" of Pablo de Miguel Morales
*
*                            Feel free to contact us:
*                            midispositivomidi@gmail.com
*                        https://github.com/midispositivomidi
*                     https://www.facebook.com/midispositivomidi
*           For further information about the license, visit us on GitHub                      
*
* Features of Example 4:
* It also uses our Arduino library (MiDispositivoMidiv2.h) for led handling
* The main functionalities are:
*    -Send MIDI Messages that can be setted by the user
*    -It has seven pages of notes/colors
*    -Pressed--->Send NoteOn
*    -Released-->Send NoteOff
*    -The user can also set the color of each page
*    -and the color of each pressed button
*/
#include <analogmuxdemux.h>
#include <SimpleTimer.h>
#include <MiDispositivoMidiv2.h>
#include <Keypad.h>
#include <MIDI.h>
#define NO_PINS 8
#define R 1
#define G 2
#define B 3
#define Y 4
#define C 5
#define M 6
#define W 7

/*--------------------------C U S T O M I Z E  T H E  C O D E---------------------------*/

/* In this arrays bellow, you can customize the code by selecting which note
*  wil be sent pressing each button, what colour do you want on each page, and
*  what colour do you want to light up when pressed. Also you can set how many
*  expansions you want to use (from 0 to 3);
*/

#define N_EXP 0                          //If 2 or 3 is selected, lateral pots (2) wont work
#define MAX_NUM_PAGES 7                  //Change the array length if you change this value
#define DEFAULT_PAGE 0                   //This is the page shown after botting (default page)
int led_pages[4][MAX_NUM_PAGES][4] = {   //Colour of each page when no button is pressed
 //pag 1    //pag 2   //pag 3   //pag 4   //pag 5   //pag 6   //pag 7
{{B,B,B,B},{G,G,G,G},{B,B,B,B},{Y,Y,Y,Y},{C,C,C,C},{M,M,M,M},{W,W,W,W}},
{{B,B,B,B},{G,G,G,G},{B,B,B,B},{Y,Y,Y,Y},{C,C,C,C},{M,M,M,M},{W,W,W,W}},
{{B,B,B,B},{G,G,G,G},{B,B,B,B},{Y,Y,Y,Y},{C,C,C,C},{M,M,M,M},{W,W,W,W}},
{{B,B,B,B},{G,G,G,G},{B,B,B,B},{Y,Y,Y,Y},{C,C,C,C},{M,M,M,M},{W,W,W,W}},
};

int led_pressed[4][MAX_NUM_PAGES][4] = {  //Colour when pressed. When released it will be the same as before
 //pag 1    //pag 2   //pag 3   //pag 4   //pag 5   //pag 6   //pag 7
{{G,G,G,G},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R}},
{{G,G,G,G},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R}},
{{G,G,G,G},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R}},
{{G,G,G,G},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R},{R,R,R,R}},
};

int notes[4][MAX_NUM_PAGES][4] = {       //Here you can set which note do you want to send
  //pag 1       //pag 2        //pag 3       //pag 4       //pag 5      //pag 6       //pag 7
{{0 ,1 ,2 , 3},{16,17,18,19},{32,33,34,35},{48,49,50,51},{64,65,66,67},{80,81,82,83},{96 , 97 ,98 ,99}},
{{4 ,5 ,6 , 7},{20,21,22,23},{36,37,38,39},{52,53,54,55},{68,69,70,71},{84,85,86,87},{100,101,102,103}},
{{8 ,9 ,10,11},{24,25,26,27},{40,41,42,43},{56,57,58,59},{72,73,74,75},{88,89,90,91},{104,105,106,107}},
{{12,13,14,15},{28,29,30,31},{44,45,46,47},{60,61,62,63},{76,77,78,79},{92,93,94,95},{108,109,110,110}},
};
/* --------------------------end of customizing code---------------------------------------*/


uint16_t prev_expA[8]={0,0,0,0,0,0,0,0}; //Last value read of potExpansion A
uint16_t prev_expB[8]={0,0,0,0,0,0,0,0}; //Last value read of potExpansion B
uint16_t prev_expC[8]={0,0,0,0,0,0,0,0}; //Last value read of potExpansion C
int num_page = 0;                        //Current page (from 1 to 7)
int prev_integrated0 = 0;                //For integrated pots
int prev_integrated1 = 0;
int pushedRow=0;                         //Coordinate y of pressed button
int pushedCol=0;                         //Coordinate x of pressed button
int contador1 = 0;                       //Counter for one timmer
boolean shift_pushed =false;

AnalogMux Amux(17,18,19, 2); //EXP
AnalogMux Bmux(17,18,19, 0); //EXP
AnalogMux Cmux(17,18,19, 1); //EXP

SimpleTimer timer;
SimpleTimer timer2;
MiDispositivoMidiv2 ledhandling;
MIDI_CREATE_DEFAULT_INSTANCE();
byte rowPins[4] = {5, 4, 3, 2}; //connect to the row pinouts of the kpd
byte colPins[4] = {6, 7, 8, 9}; //connect to the column pinouts of the kpd
char keys[4][4] = {
{'a','b','c','d'},
{'e','f','g','h'},
{'i','j','k','l'},
{'m','n','o','p'}
};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );
int current_page[4][4] = {   //Colors values of currentPage
{1,1,1,1},
{1,1,1,1},
{1,1,1,1},
{1,1,1,1}
};

void setup() {
  //Serial.begin(115200);    //Use this to debug with hairless
  MIDI.begin(0);         //or this if you are using HIDUINO firmware
  pinMode(13,OUTPUT);

  ledhandling.setCommonAnode(); //Or Common.Cathod()
  
  timer.setInterval(1, repeatMe);
  timer2.setInterval(1, repeatMe2);
  for(int i=0; i<4; i++){ //Initialice the array
    for (int j=0;j<4; j++){
      current_page[i][j] = led_pages[i][DEFAULT_PAGE][j];
    }  
  }
  //Welcome animation
  for(int i=1;i<5;i++){
    for (int j=1;j<5;j++){
      ledhandling.lightUpDir(i,j,'g');
      delay(50);    
      ledhandling.lightUpDir(i,j,'w'); 
      delay(50); 
     } 
   }
}

void loop() {
  //timer.run();
  //timer2.run()
  readPageNum(); //Read page number (1 to 7). Also set the colors to current_page                
  ledhandling.lightUpArray(current_page); //Light up them
      if (kpd.getKeys()){
        for (int i=0; i<LIST_MAX; i++){   //Scan the whole list
            if ( kpd.key[i].stateChanged ){ //Only keys that have changed
              getPushedButton(kpd.key[i].kchar); //Get the value of pushedRow/Col
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                      MIDI.sendNoteOn(notes[pushedRow][num_page][pushedCol],127,1); //Send the note defined by the user at the begining
                      refreshButtonStatePressed();//Update the colours to lightup the one that was pushed
                break;
                    case HOLD:
                      //Empty
                break;
                    case RELEASED:
                      //Serial.println(button); //debug
                      MIDI.sendNoteOff(notes[pushedRow][num_page][pushedCol],0,1);
                      refreshButtonStateReleased();
                      // Serial.println(button); //Debug
                //break;
                  //  case IDLE:
                    //Serial.println('Debug');
                }
            }
        }
    }
allPots();  //Read all pots (depending on the number of exp)
}//End Loop

void repeatMe() { //Led routine 1. Currently disabled
  contador1++;
  if(contador1<150){ledhandling.lightUpCol('w',1);
  }else if(contador1<300){ledhandling.lightUpCol('w',2);
  }else if(contador1<450){ledhandling.lightUpCol('w',3);
  }else if(contador1<600){ledhandling.lightUpCol('w',4);
  }else if(contador1<750){ledhandling.lightUpCol('w',3);
  }else if(contador1<900){ledhandling.lightUpCol('w',2);
  }else{contador1=0;}
}

void repeatMe2(){ //Led routine 2. Currently disabled
 ledhandling.lightUpDir(1,1,'r'); 
}

void readPageNum(){
 if(digitalRead(13)){
   if(!shift_pushed){
   shift_pushed=true;
     if(num_page<(MAX_NUM_PAGES-1)){
       num_page++;
       readCurrentPage();
   }else{num_page=0;readCurrentPage();
   }
   }
 }if(!digitalRead(13)){shift_pushed=false;}
}


void readCurrentPage(){
  for(int i=0; i<4; i++){
    for(int j=0;j<4;j++){
      current_page[i][j] = led_pages[i][num_page][j];
  } 
 } 
}

void getPushedButton(char button){
  if(button=='a'){pushedRow=0;pushedCol=0;}
  if(button=='b'){pushedRow=0;pushedCol=1;}
  if(button=='c'){pushedRow=0;pushedCol=2;}
  if(button=='d'){pushedRow=0;pushedCol=3;}
  if(button=='e'){pushedRow=1;pushedCol=0;}
  if(button=='f'){pushedRow=1;pushedCol=1;}
  if(button=='g'){pushedRow=1;pushedCol=2;}
  if(button=='h'){pushedRow=1;pushedCol=3;}
  if(button=='i'){pushedRow=2;pushedCol=0;}
  if(button=='j'){pushedRow=2;pushedCol=1;}
  if(button=='k'){pushedRow=2;pushedCol=2;}
  if(button=='l'){pushedRow=2;pushedCol=3;}
  if(button=='m'){pushedRow=3;pushedCol=0;}
  if(button=='n'){pushedRow=3;pushedCol=1;}
  if(button=='o'){pushedRow=3;pushedCol=2;}
  if(button=='p'){pushedRow=3;pushedCol=3;}
}

void refreshButtonStatePressed(){
  current_page[pushedRow][pushedCol] = led_pressed[pushedRow][num_page][pushedCol];
}

void refreshButtonStateReleased(){
  current_page[pushedRow][pushedCol] = led_pages[pushedRow][num_page][pushedCol];
}

void allPots(){
  uint16_t valA = 0;
  uint16_t valB = 0;
  uint16_t valC = 0;
    for (int pinno=0; pinno < NO_PINS; pinno++){
      Amux.SelectPin(pinno); //se usa solo uno. Los pines de control son los mismos
      Bmux.SelectPin(pinno);
      Cmux.SelectPin(pinno);
      if (N_EXP == 0){
        integratedPots();
      }
      if(N_EXP == 1){
        valA = ceil((Amux.AnalogRead())/8);
        if (valA != prev_expA[pinno]){
          MIDI.sendControlChange(pinno+2, valA,1); //chanel 0
          prev_expA[pinno] = valA;
        }
      }else if (N_EXP == 2){
        valA = ceil((Amux.AnalogRead())/8);
        valB = ceil((Bmux.AnalogRead())/8);
        if (valA != prev_expA[pinno]){
          MIDI.sendControlChange(pinno+2, valA,1); //chanel 0
          prev_expA[pinno] = valA; 
        }
        if (valB != prev_expB[pinno]){
          MIDI.sendControlChange(pinno+10, valB,1); //chanel 0
          prev_expB[pinno] = valB; 
        }
        
        
      }else if (N_EXP ==3){
        valA = ceil((Amux.AnalogRead())/8);
        valB = ceil((Bmux.AnalogRead())/8);
        valC = ceil((Cmux.AnalogRead())/8);
        if (valA != prev_expA[pinno]){
          MIDI.sendControlChange(pinno+2, valA,1);  //chanel 0
          prev_expA[pinno] = valA;
        }
        if (valB != prev_expB[pinno]){
          MIDI.sendControlChange(pinno+10, valB,1); //chanel 0
          prev_expB[pinno] = valB; 
        }
        if (valC != prev_expC[pinno]){
          MIDI.sendControlChange(pinno+18, valC,1); //chanel 0
          prev_expC[pinno] = valC; 
        }
      }    
    }
}

void integratedPots(){
  uint16_t value0 = 0;
  uint16_t value1 = 0;
  
  value0 = ceil(analogRead(0)/8);
  value1 = ceil(analogRead(1)/8);
  
  if (value0 != prev_integrated0){
    MIDI.sendControlChange(0, value0,1);
  }
  if(value1 != prev_integrated1){
    MIDI.sendControlChange(1, value1,1);
  }
  
  prev_integrated0 = value0;
  prev_integrated1 = value1;
}
