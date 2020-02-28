#include <msp430.h>
#include "ws2812.h"

#include<stdint.h>

void gradualFill(uint32_t n, ColorMap);


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
    WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
    if (CALBC1_16MHZ==0xFF)    // If calibration constant erased
    {
        while(1);              // do not load, trap CPU!!
    }

    // configure clock to 16 MHz
    BCSCTL1 = CALBC1_16MHZ;    // DCO = 16 MHz
    DCOCTL = CALDCO_16MHZ;


    P1DIR |= BIT0;              // P1.0 (Red) -> Output
    toggleLED();

    

    // initialize LED strip
    initStrip();  // ***** HAVE YOU SET YOUR NUM_LEDS DEFINE IN WS2812.H? ******

    // set strip color red
    // fillStrip(COLOR_BLUE);
    //setLEDColor(3, COLOR_BLUE);
    drawCross(0);

    // show the strip
    showStrip();
    // toggleLED();
    
    
}


// gradually fill for ever and ever
void loop () 
{
    byte current = 0;
    if (Serial.available() > 0) {
        // Read the most recent byte
        byte byteRead = Serial.read();
        Serial.print(byteRead);
        // ECHO the value that was read
        // Serial.write(byteRead);
        
        if (current != byteRead) {
            current = byteRead;
            clearStrip();


            switch(byteRead) {
                drawCross(byteRead-48); //convert parse char to int

                // case '0':
                //     drawCross(0);
                // case '1':
                //     drawCross(1);
                // case '2':
                //     drawCross(2);
                // case '3':
                //     drawCross(3);
                // case '4':
                //     drawCross(4);
                // case '5':
                //     drawCross(5);
            }

            showStrip();
        }
        
    }
    
}

void gradualFill(uint32_t n, ColorMap color)
{
    
    for (uint32_t i = 0; i < n; i++)
    {        // n is number of LEDs
        setLEDColor(i, color);
        showStrip();
        __delay_cycles(1000000);       // lazy delay
    }
}


void drawCross(int k) {
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if (i == j || 7-j == i) {
                // a little different
                setLEDColor(i*8+j+k*64, COLOR_BLUE);
            }
        }
    }
}


void drawCircle(int k) {
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
                    setLEDColor(i*8+j+k*64, COLOR_BLUE);
            }
            
        }
    }
}



