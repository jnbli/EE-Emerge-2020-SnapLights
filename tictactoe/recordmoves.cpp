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

            drawRed(player, bytRead);
            drawGrid(blue); //Draws whatever is in grid 
            showStrip();
            }

        if (doubleClap()) { //returns 1 or 0
            doubleClap() = 0;
        	grid[byteRead] = player; //saves player choice in grid array
        	clearStrip();
        	drawGrid(blue);
        	showStrip();
            if(isWinner()) //returns 1 or 0 for winner
                Serial.println(player, " Win");
            player = ~player;
        }
        
    }
    
}
