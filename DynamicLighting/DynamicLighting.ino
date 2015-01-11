#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone


  //for use with the room's light being on or off
  pinMode(13,OUTPUT); //room 1
  pinMode(12,OUTPUT);//room2

  pinMode(10, INPUT);  
  pinMode(9, OUTPUT);   // Left IR LED & Receiver

  pinMode(3, INPUT);
  pinMode(2, OUTPUT);

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);

  Serial.begin(115200);                        // Set data rate to 115200 bps
  rest.set_id("001");
  rest.set_name("light");
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
int prevCount1 = 0;
int prevCount2 = 0;
int readIn = -1;

void loop()                                  // Main loop auto-repeats
{


  // rest.handle("/digital/7/1");
  rest.handle(Serial); 



  if(digitalRead(7) == HIGH){
    if(room1Count>0)
    {
      digitalWrite(13,HIGH);
    }
    else
    {
      digitalWrite(13,LOW);
    }
  }
  if(digitalRead(6) == HIGH){
    if (room2Count>0)
    {
      digitalWrite(12,HIGH);
    }
    else
    {
      digitalWrite(12,LOW);
    }
  }




  int irLeft = irDetect(9, 10, 38000);  
  int irRight = irDetect(2, 3, 38000);  // Check for object
  //  if(statey!=STATE)
  //  {
  //    Serial.print("Last: ");
  //    Serial.print(statey);
  //    Serial.print("        Current: ");
  //    Serial.println(STATE);
  //    statey=STATE;
  //  }
  //    Serial.print("Room1: ");
  //   Serial.print(room1Count);
  //  Serial.print("  Room2: ");
  //  Serial.println(room2Count);


  switch(STATE){
  case Waiting:
    {
      if(irLeft == noDet && irRight == Det){ //starting entry process
        STATE = Enter1;
      }
      else if(irLeft == Det && irRight == noDet){//starting exit process
        STATE = Exit1;
      }
      break;
    }
  case Enter1:
    {//left no detect, right detect

      if(irLeft == Det && irRight == Det){ //furthering entry process
        STATE = Enter2;
      }
      else if(irLeft == noDet && irRight == noDet){ //bailing on entry
        STATE = Waiting;
      }
      break;
    }
  case Enter2:
    { //double detect
      if(irLeft == Det && irRight == noDet){ //furthering enty process
        STATE = Enter3;
      }
      else if(irLeft == noDet && irRight == Det){ //backing up from entry
        STATE = Enter1;
      }
      else if(irLeft == noDet && irRight ==noDet)
      {
        STATE= Waiting; 
      }
      break;
    }
  case Enter3://left detect right no detect
    {
      if(irLeft == noDet && irRight == noDet){//finishing entry
        room1Count++;
        if(room2Count > 0){
          room2Count --;
        }
        STATE = Waiting;
      }
      else if(irLeft == Det && irRight == Det){//backing up from entry
        STATE = Enter2;
      }
      break;
    }
  case Exit1:
    {//left detect, right no detect

      if(irLeft == Det && irRight == Det){ //furthering exit process
        STATE = Exit2;
      }
      else if(irLeft == noDet && irRight == noDet){ //bailing on exit
        STATE = Waiting;
      }
      break;
    }
  case Exit2:
    { //double detect
      if(irLeft == noDet && irRight == Det){ //furthering exit process
        STATE = Exit3;
      }
      else if(irLeft == noDet && irRight == Det){ //backing up from exit
        STATE = Exit1;
      }
      else if(irLeft == noDet && irRight ==noDet)
      {
        STATE= Waiting; 
      }
      break;
    }
  case Exit3://left detect right no detect
    {
      if(irLeft == noDet && irRight == noDet){//finishing exit
        if(room1Count > 0){
          room1Count--;
        }
        room2Count ++;

        STATE = Waiting;
      }
      else if(irLeft == Det && irRight == Det){//backing up from exit
        STATE = Exit2;
      }
      break;
    }

    /*
  case Exit1://Left detected and right no detect
     {
     if(irLeft == Det && irRight == Det){//further exit process
     STATE = Exit2;
     }
     else if(irLeft = noDet && irRight == noDet){//back up to waiting
     STATE = Waiting;
     } 
     break;
     }
     case Exit2://Left detected and right detected
     {
     if(irLeft == noDet && irRight == Det){//further exit process
     STATE = Exit3;
     }
     else if(irLeft== Det && irRight== noDet){//back up into Exit1
     STATE = Exit1;
     }
     break;
     }
     case Exit3://left no detect and right detected
     {
     if(irLeft == noDet && irRight == noDet){//finish exit process
     if(room1Count > 0){
     room1Count --;
     }
     room2Count++;
     STATE = Waiting;
     }
     else if(irLeft == Det && irRight == Det){//back up into exit 2
     STATE = Exit2;
     }
     break;
     }
     */
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

  //delay(10);                                // 0.1 second delay
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(6,state);
  return 1;
}

