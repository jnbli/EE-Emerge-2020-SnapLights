
#define soundPin P1_4

int sensorValue = 0;
int eventstatus = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(soundPin, INPUT);
}

void loop() {
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
    Serial.println("activated");
    delay(500);
  }
}
