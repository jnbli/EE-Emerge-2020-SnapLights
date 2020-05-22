# SnapLights

Snaplights is project that uses face recognition and clap detection to play the game of tic-tac-toe. It is a two-player game. In this project, 9 [Adafruit Neopixel LEDs](https://www.adafruit.com/product/1487) are arranged in 3-by-3 patterns in a wooden frame with a camera and a microphone attached to the frame. The [Open MV H7](https://openmv.io/products/openmv-cam-h7) camera is used for the face recognition. [KY-037 Microphone sensor](http://sensorkit.en.joy-it.net/index.php?title=KY-037_Microphone_sensor_module_(high_sensitivity)) for the clap detection, and the neopixels to display the output. Players choose their spot with their face and double clap to confirm. The first to claim three spots in a row wins!

# Getting Started

The early idea was to have a finger snap turn on a set of lights, by Jonathan. In discussions, Aldric convinced the team to pivot the project to be an interactive game. 

# How does Snaplights work? 
The control system of Snaplights, the MSP430G2553 is programmed using the Texas Instruments Code Composer. The code creats a UART connection between the camera and the microntroller. It also process the signal received from the microphone. The OpenMV H7 camera is programmed using OpenMV IDE, the code splits the camera lens screen into 3x3 matrices coordinates. If the face is detected in any of the sections, the corresponding neopixel will turn on to be X for the first player and at the same time if the microphone senses a clap then the displayed X will be locked in the neopixel. If a clap is not sensed then as the person moves their face onto a different section, the corresponding neopixel will turn on, turning off the previous neopixel. After locking the first input, the next player will start playing with O and follow the same process as X. 

# Assembly
This is the general assembly of the mechanical components of our project. It consists of a wooden frame, another foamboard frame to be placed within the larger frame, nine 3D printed grid assemblies to dissipate light to a greater area, and nine neopixels. 
![Assembly](https://github.com/jnbli/EE-Emerge-2020-SnapLights/blob/master/mechanical/Assembly.png)

# Wiring Diagram
This is the wiring configuration of Snaplights. The diagram presents how the wires connects all the part together. DaisyChain is the type of wiring scheme used for the neopixels. 
![Wiring Diagram](https://github.com/jnbli/EE-Emerge-2020-SnapLights/blob/master/documentation/Wiring.jpeg)

# Project Team

* **[Anshu Paudyal](https://github.com/anshupaudyal)** - *Contributed on 3D modeling, hardware, and software for Snaplights*
* **[Aldric Sangalang](https://github.com/AldricSangalang)** - *Hardware Lead*
* **[Jonathan Li](https://github.com/jnbli)** - *Software Lead*
* **[Sean Alling](https://github.com/SeanAlling)** - *Teaching Assistant*
* **Andre Knoesen** - *EE-Emerge Professor*

**[Back to top](#table-of-contents)**

# Acknowledgments
Thank you to Justin Wong and Raunaq Chopra for helping in the Fall and to Aakansha Bhatt for helping in Winter. A big thank you to TA Sean Alling, who guided us and helped us with important aspects of the project. And a big thank you to Professor Knoesen for the help and guidance.

Also we would like to thank Texas Instruments for sponsoring us and UC Davis for providing us the facility to build our project.

**[Back to top](#table-of-contents)**
