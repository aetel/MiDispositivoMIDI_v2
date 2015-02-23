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
* Features of Example 3:
*  -This code can be used to send midi messages when pressing/releasing a key. It also
*   has two timmers running that can be used to stablish a periodic iluminating patron.
*  -It also can be used with the programs MiDispositivoMidiCustomSamplerv2, MiDispositivoMidiSamler
*  or any commercial DAW such as Nuendo, Pro Tools,...
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

int timerid_1 = 0;
int timerid_2 = 0;

int notes[4][4] = {       //Here you can set which note do you want to send
{32,33,34,35},
{36,37,38,39},
{40,41,42,43},
{44,45,46,47},
};

int prev_integrated0 = 0;                //For integrated pots
int prev_integrated1 = 0;
int pushedRow=0;                         //Coordinate y of pressed button
int pushedCol=0;                         //Coordinate x of pressed button
unsigned int contador1 = 0;              //Counter for one timmer
unsigned int contador2 = 0;
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
void setup() {
  //Serial.begin(115200);
  MIDI.begin(0);         //or this if you are using HIDUINO firmware
  pinMode(13,OUTPUT);

  ledhandling.setCommonAnode(); //Or Common.Cathod()
  
  timerid_1 = timer.setInterval(1, repeatMe);
  timerid_2 = timer2.setInterval(1, repeatMe2);
  
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
  timer.run();
  timer2.run();
  ledhandling.lightUpAll('r');
      if (kpd.getKeys()){
        for (int i=0; i<LIST_MAX; i++){   //Scan the whole list
            if ( kpd.key[i].stateChanged ){ //Only keys that have changed
              getPushedButton(kpd.key[i].kchar); //Get the value of pushedRow/Col
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                      MIDI.sendNoteOn(notes[pushedRow][pushedCol],127,1); //Send the note defined by the user at the begining
                      //timer.toggle(timerid_1);
  
                break;
                    case HOLD:
                      //Empty
                break;
                    case RELEASED:
                      //Serial.println(button); //debug
                      MIDI.sendNoteOff(notes[pushedRow][pushedCol],0,1);
                      
                      //timer2.toggle(timerid_2);
                      // Serial.println(button); //Debug
                //break;
                  //  case IDLE:
                    //Serial.println('Debug');
                }
            }
        }
    }
integratedPots();
}//End Loop

void repeatMe() { //Led routine 1
  contador1++;
  if(contador1<150){ledhandling.lightUpCol('g',1);
  }else if(contador1<300){ledhandling.lightUpCol('g',2);
  }else if(contador1<450){ledhandling.lightUpCol('g',3);
  }else if(contador1<600){ledhandling.lightUpCol('g',4);
  }else if(contador1<750){ledhandling.lightUpCol('g',3);
  }else if(contador1<900){ledhandling.lightUpCol('g',2);
  }else{contador1=0;}
}

void repeatMe2(){ //Led routine 2
  contador2++;
  if(contador2<150){ledhandling.lightUpRow('b',1);
  }else if(contador2<300){ledhandling.lightUpRow('b',2);
  }else if(contador2<450){ledhandling.lightUpRow('b',3);
  }else if(contador2<600){ledhandling.lightUpRow('b',4);
  }else if(contador2<750){ledhandling.lightUpRow('b',3);
  }else if(contador2<900){ledhandling.lightUpRow('b',2);
  }else{contador2=0;}
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
