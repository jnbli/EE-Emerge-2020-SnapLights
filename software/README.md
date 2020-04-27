# Software
Our project involves a board and two sensors, which are a camera and microphone.

# Board
The Texas Instruments MSP430 microcontroller is the brains. It processes the data coming from the two sensors (camera, microphone) and controls LEDs grid display. The code is in Energia, which is essentially C++. 

# Camera
The OpenMV Camera detects in its field of view which of the nine quadrants a face is in. Then, through UART, it and sends the information to the board. The board then knows which of the nine Neopixel LEDs to light up. The Camera is coded in Python.

# Microphone
The KY-037 digital microphone amplifies sound using an op-amp and converts it to a digital signal, which it then sends over one pin to the board. Because a double clap is distinct, the board can tell when a user confirms his spot on the 3x3 Neopixel Grid. To use the microphone, the board only needs to include a sound pin.

# LEDs
Adafruit Neopixels are the LED of choice as they can display X and O in many colors. To interface with the Neopixels, the board needs to import the Adafruit Neopixel libraries.
