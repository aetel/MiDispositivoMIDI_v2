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
* Features of Example 1:
* The aim of this code is to check that the leds work properly, and start using
* the functions developed for handling the leds, which are the following:
*  -lightUpDir (light up one element with selected colour)
*  -lightUpRow (light up one row with selected colur)
*  -lightUpCol (light up one col with selected colour)
*  -lightUpAll (light up all leds with selected colour)
*  -lightUpArray (light up a determinate pattern)
* Available colours
*  -Red 'r'
*  -Green 'g'
*  -Blue 'b'
*  -Yellow 'y'
*  -Cyan 'c'
*  -Magenta 'm'
*  -White 'w'
*/

#include <MiDispositivoMidiv2.h>
MiDispositivoMidiv2 curso;

const int retardo=300;
void setup(){
}
void loop(){
  
  curso.lightUpRow('r',1); delay(retardo);
  curso.lightUpRow('r',2); delay(retardo);  
  curso.lightUpRow('g',3); delay(retardo);
  curso.lightUpRow('g',4); delay(retardo);
  
  curso.lightUpCol('b',1); delay(retardo);
  curso.lightUpCol('b',2); delay(retardo);  
  curso.lightUpCol('m',3); delay(retardo);
  curso.lightUpCol('m',4); delay(retardo);

  curso.lightUpDir(1,1,'c'); delay(retardo);
  curso.lightUpDir(2,2,'m'); delay(retardo);
  curso.lightUpDir(3,3,'y'); delay(retardo);
  curso.lightUpDir(4,4,'w'); delay(retardo);
  
  curso.lightUpDir(4,4,'c'); delay(retardo);
  curso.lightUpDir(3,3,'m'); delay(retardo);
  curso.lightUpDir(2,2,'y'); delay(retardo);
  curso.lightUpDir(1,1,'w'); delay(retardo);
  
  curso.lightUpAll('y'); delay(retardo);
  curso.lightUpAll('m'); delay(retardo);
  curso.lightUpAll('c'); delay(retardo);
  curso.lightUpAll('b'); delay(retardo);
}
