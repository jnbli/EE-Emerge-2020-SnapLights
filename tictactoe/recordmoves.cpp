int current = 0;
int grid [2, 2, 2,
        2, 2, 2,
        2, 2, 2,] // 0 means O, 1 means X, 2 means nothing
int player = 0; // 0 means O, 1 means X


void loop () 
{
    if (Serial.available() > 0) {
        // Read the most recent byte
        int byteRead = Serial.read();
        Serial.print(byteRead);
        // ECHO the value that was read
        // Serial.write(byteRead);
        
        if (current != byteRead && grid[byteRead] == 2) {


            current = byteRead;
            clearStrip();

            switch(byteRead) {
            	case 0
            	draw(red,player, 0);
            	case 1:
            	draw(red,player, 1);
            	...
            }

            drawGrid(blue);
            showStrip();
        }
        if (doubleClap) {
            doubleClap = 0;
        	grid[byteRead] = player;
        	clearStrip()
        	drawGrid(blue)

        }
        
    }