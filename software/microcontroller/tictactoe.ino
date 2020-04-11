#include <msp430.h>
#include "ws2812.h"

#include<stdint.h>

#define soundPin P1_4

int sensorValue = 0;
int eventstatus = 0;

int current = 9;
int grid[9] = {2, 2, 2, 2, 2, 2, 2, 2, 2}; // 0 means O, 1 means X, 2 means nothing
int player = 0; // 0 means O, 1 means X

void toggleLED()
{
    static     uint8_t state = 0;
    if(state==0)
    {
        state = 0;
        P1OUT &= ~BIT0;   
    }
    else
    {
        state = 0;
        P1OUT |= BIT0;      // else LED ON
    }
}

void setup(void) 
{
    Serial.begin(9600);
//    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
//    if (CALBC1_16MHZ==0xFF)    // If calibration constant erased
//    {
//        while(1);              // do not load, trap CPU!!
//    }
//
//    // configure clock to 16 MHz
//    BCSCTL1 = CALBC1_16MHZ;    // DCO = 16 MHz
//    DCOCTL = CALDCO_16MHZ;
//
//
//    P1DIR |= BIT0;              // P1.0 (Red) -> Output
//    toggleLED();
//
//    // initialize LED strip
    initStrip();  // ***** HAVE YOU SET YOUR NUM_LEDS DEFINE IN WS2812.H? ******

    pinMode(soundPin, INPUT);
    
//    drawCross(0, COLOR_GREEN);
//    showStrip();
//    delay(1000);
//    clearStrip();
//    drawCircle(0, COLOR_BLUE);
//    showStrip();
//    delay(1000);
//    clearStrip();
//    drawCircle(0, COLOR_OFF);
//    showStrip();
//      fillStrip(COLOR_OFF);
//      clearStrip();
    
}
  
void loop () 
{

    if (Serial.available() > 0) {
        // Read the most recent byte
        int intRead = Serial.read() - 48;

        // swap 2 and 0 to match how LEDs are wired
        if (intRead == 0) {
          intRead = 2;
        }
        else if (intRead == 2) {
          intRead = 0;
        }

//        Serial.println("Hello World");
        // ECHO the value that was read
        // Serial.write(intRead);

        // limit intRead < 6 because we only have 6 LEDs
        if (current != intRead && intRead < 6) {

            current = intRead;
            clearStrip();

            draw(player, intRead, COLOR_RED);
            drawGrid(COLOR_BLUE); //Draws whatever is in grid 
            showStrip();
        }
    }

        if (current != 9 && doubleClap() && grid[current] == 2) { //returns 1 or 0
        	grid[current] = player; //saves player choice in grid array
        	clearStrip();
        	drawGrid(COLOR_BLUE);
        	showStrip();
                
            player = 1 - player;
        }

        if(isWinner()) {
//                Serial.println(player, " Win");
              delay(2000);
              clearStrip();
              fillStrip(COLOR_OFF);

              int winner = 1-player;

              draw(winner, 1, COLOR_GREEN);
              drawW(winner, 3, COLOR_GREEN);
              drawO(winner, 4, COLOR_GREEN);
              drawN(winner, 3, COLOR_GREEN);
//              drawCircle(0, COLOR_GREEN);
              showStrip();
              while(1) {
                //maintain this state, until reset is hit
              }
        }
        
}

bool isWinner() {
//        if (grid[0] != 2 && grid[0] == grid[1] && grid[1] == grid[2]) {
//            return true;
//        }
//        else if (grid[3] != 2 && grid[3] == grid[4] && grid[4] == grid[5]) {
//            return true;
//        }
    // because the daisy chain is zig zagged the verticals are as so
    if (grid[0] != 2 && grid[0] == grid[5]) {
      return true;
    }
    else if (grid[1] != 2 && grid[1] == grid[4]) {
      return true;
    }
    else if (grid[2] != 2 && grid[2] == grid[3]) {
      return true;
    }
    return false;
}

void drawGrid(ColorMap color) {
    for (int i=0; i<9; i++) {
        if (grid[i] != 2) {
            draw(grid[i], i, color);
        }
    }

}


void draw(int player, int position, ColorMap color) {
    if (player == 0) {
        drawCircle(position*64, color);
    }
    else if (player == 1) {
        drawCross(position*64, color);
    }

}


void drawCross(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (i == j || 7-j == i) {
        // a little different
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}


void drawCircle(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if ((i == 0 && j >=2 && j <= 5) ||
          (i == 1 && j == 1) || 
          (i == 6 && j == 1) ||
          (i == 1 && j == 6) ||
          (i == 6  && j == 6) || 
          (j == 0 && i >= 2 && i <= 5) || 
          (j == 7 && i >= 2 && i <= 5) || 
          (i == 7 && j >=2 && j <= 5)) {
            setLEDColor(i*8+j+k, color);
      } 
    }
  }
}


void drawW(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (i == 7 || j == 0 || j == 3 || j == 4 || j == 7) {
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}


void drawO(int k, ColorMap color) {
  drawCircle(k, color);
}


void drawN(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (j == 0 || j == 7 || i == j) {
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}


bool doubleClap() {
  // put your main code here, to run repeatedly: 
  eventstatus = 0;  
  sensorValue = digitalRead(soundPin);  
  delay(1);
  
//   if(sensorValue == 1)
//     Serial.println("yeah");
  
  
  if(eventstatus == 0){
    if(sensorValue == 1){
      eventstatus = 1;      
    }
  }
  
    if(eventstatus == 1){  
    for(int k = 10; k > 0; k--){
      delay(10);
      sensorValue = digitalRead(soundPin);
      if(sensorValue == 0){
        eventstatus = 2;
        break;
      }      
    }
  }
  
  if(eventstatus == 2){
    for(int n=500; n>0; n--){
      delay(1);
      sensorValue = digitalRead(soundPin);
      if(sensorValue == 1){
        eventstatus = 3;
      break;
      }
    }
  }
  
  if(eventstatus == 3){
    
    // Serial.println("activated");
//    delay(500);
    return true;
  }
  return false;
}
