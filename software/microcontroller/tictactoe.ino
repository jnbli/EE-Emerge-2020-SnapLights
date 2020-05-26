#include <msp430.h>
#include "ws2812.h"

#include <stdint.h>

#define soundPin P1_4

int sensorValue = 0;
int eventstatus = 0;

int grid[9] = {2, 2, 2, 
               2, 2, 2, 
               2, 2, 2}; // 0 means O, 1 means X, 2 means nothing

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
    initStrip();  
    pinMode(soundPin, INPUT);
}
  
void loop () 
{
    bool exitClap = 0;
    int current = 9;
    int player = 0; // 0 means O, 1 means X
    int tieCounter = 0;
    for(int i = 0; i < 9; i++){
        grid[i] = 2;
    }
    
    
    do {
        if (Serial.available() > 0) {
            // Read the most recent byte
            int intRead = Serial.read() - 48;
            
            // swap edges due to its wiring
            if (intRead == 0) 
              intRead = 2;
            else if (intRead == 2) 
              intRead = 0;
            else if (intRead == 3)
                intRead = 5;
            else if (intRead == 5)
                intRead = 3;
            else if (intRead == 6)
                intRead = 8;
            else if (intRead == 8)
                intRead = 6;
    
            // limit intRead < 9 because we have 9 LEDs
            if (current != intRead && intRead < 9) {
    
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
            tieCounter = tieCounter + 1;
        }
        
        if(isWinner()) {
            delay(2000);
            clearStrip();
            fillStrip(COLOR_OFF);
    
            int winner = 1-player;
            
            draw(winner, 0, COLOR_GREEN);
            draw(winner, 1, COLOR_GREEN);
            draw(winner, 2, COLOR_GREEN);
            drawW(64*3, COLOR_GREEN);
            drawO(64*4, COLOR_GREEN);
            drawN(64*5, COLOR_GREEN);
            draw(winner, 6, COLOR_GREEN);
            draw(winner, 7, COLOR_GREEN);
            draw(winner, 8, COLOR_GREEN);
          
            showStrip();
            while(exitClap == 0) {
                exitClap = doubleClap();
            }
        }
        
        if(tieCounter == 9 && isWinner() == false){
            delay(2000);
            clearStrip;
            fillStrip(COLOR_OFF);
            
            drawT(64*3, COLOR_GREEN);
            drawI(64*4, COLOR_GREEN);
            drawE(64*5, COLOR_GREEN);
            
            showStrip();
            while(exitClap == 0) {
                exitClap = doubleClap();
            }
        }
    } while(exitClap == 0);
}

bool isWinner() {

    if (grid[0] != 2 && grid[0] == grid[1] && grid[0] == grid[2] && grid [1] == grid[2]) { // horizontals
      return true;
    }
    else if (grid[3] != 2 && grid[3] == grid[4] && grid[3] == grid[5] && grid[4] == grid[5]) {
      return true;
    }
    else if (grid[6] != 2 && grid[6] == grid[7] && grid[6] == grid[8] && grid[7] == grid[8]) {
      return true;
    }
    else if (grid[2] != 2 && grid[2] == grid[5] && grid[2] == grid[8] && grid[5] == grid[8]) { // verticals
      return true;
    }
    else if (grid[1] != 2 && grid[1] == grid[4] && grid[1] == grid[7] && grid[4] == grid[7]) {
      return true;
    }
    else if (grid[0] != 2 && grid[0] == grid[3] && grid[0] == grid[6] && grid[3] == grid[6]) {
      return true;
    }
    else if (grid[2] != 2 && grid[2] == grid[4] && grid[2] == grid[6] && grid[4] == grid[6]) { // diagonals
      return true;
    }
    else if (grid[0] != 2 && grid[0] == grid[4] && grid[0] == grid[8] && grid[4] == grid[8]) {
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
      if ((i == 0 || i == 7) || 
         (i == j && i < 4) || 
         (i == 4 && j == 3) ||
         (i == 5 && j == 2) ||
         (i == 6 && j == 1)){
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
      if (i == 0 || i == 7 || (i == 7-j)){
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}

void drawT(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (i == 3 || i == 4 || j == 7 || j == 6){
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}

void drawI(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (i == 6 || i == 7 || j == 4 || j == 3 || i == 1 || i == 0){
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}

void drawE(int k, ColorMap color) {
  for(int i=0; i<8; i++) {
    for(int j=0; j<8; j++) {
      if (i == 0 || i == 1 || (j != 5 && j != 2)){
        setLEDColor(i*8+j+k, color);
      }
    }
  }
}


bool doubleClap() {
  eventstatus = 0;  
  sensorValue = digitalRead(soundPin);  
  delay(1);
  
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
    return true;
  }
  
  return false;
}
