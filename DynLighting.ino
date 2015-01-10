void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(10, INPUT);  
  pinMode(9, OUTPUT);   // Left IR LED & Receiver

  Serial.begin(115200);                        // Set data rate to 9600 bps
}  

enum state{
  Waiting,
  Enter1,
  Enter2,
  Enter3,
  Exit1,
  Exit2,
  Exit3
};

#define noDet 1
#define Det 0

state STATE = Waiting;
int prevLeft = 1;
int prevRight = 1;
int room1Count = 0;
int room2Count = 0;


void loop()                                  // Main loop auto-repeats
{
  int irLeft = irDetect(9, 10, 38000);  
  int irRight = irDetect(2, 3, 38000);  // Check for object

  if(room1Count > 0){
    Serial.println("LightOn");
  }
  if(room1Count == 0){
    Serial.println("LightOff");
  }  


  switch(STATE){
  case Waiting:
    {
      if(irLeft == noDet && irRight == Det){ //starting entry process
        STATE = Enter1;
      }

      break;
    }
  case Enter1:
    {//left no detect, right detect

      if(irLeft == Det && irRight == Det){ //furthering entry process
        STATE = Enter2;
      }
      if(irLeft == noDet && irRight == noDet){ //bailing on entry
        STATE = Waiting;
      }
      break;
    }
  case Enter2:
    { //double detect
      if(irLeft == Det && irRight == noDet){ //furthering enty process
        STATE = Enter3;
      }
      if(irLeft == noDet && irRight == Det){ //backing up from entry
        STATE = Enter2;
      }
      break;
    }
  case Enter3://left detect right no detect
    {
      if(irLeft == noDet && irRight == noDet){//finishing entry
        room1Count++;
        STATE = Waiting;
      }
      if(irLeft == Det && irRight == Det){//backing up from entry
        STATE = Enter2;
      }
      break;
    }
  case Exit1:
    {
      break;
    }
  case Exit2:
    {
      break;
    }
  case Exit3:
    {
      break;
    }

  default:
    {
      Serial.println("FUCKKKKKKKKKK");
      break;
    }
  }


//  if((irLeft != prevLeft) | (irRight != prevRight)){
//    Serial.print("Left:  ");
//    Serial.print(irLeft);
//    Serial.print("Right:  ");  // Display 1/0 no detect/detect
//    Serial.println(irRight);
//  }
//
//  prevLeft = irLeft;
//  prevRight = irRight;

  delay(10);                                // 0.1 second delay
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  


