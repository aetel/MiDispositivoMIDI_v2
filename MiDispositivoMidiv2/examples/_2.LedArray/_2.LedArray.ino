
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
* Features of Example 2:
*
*   -This example allows the user to set the colour to each pixel, changing
*   the pattern matrix. Note that the colours that can be used are the defined
*   at the begining of the code: R,G,B,Y,C,M,W.
*/

#include <MiDispositivoMidiv2.h>
MiDispositivoMidiv2 curso;
#define R 1
#define G 2
#define B 3
#define Y 4
#define C 5
#define M 6
#define W 7
int pattern[4][4] = {   //Colors values of currentPage
  {G,B,B,G},
  {G,B,B,G},
  {B,B,B,B},
  {G,B,B,G}
};
void setup(){
}
void loop(){
  curso.lightUpArray(pattern);
}

