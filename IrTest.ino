
void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone

  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver

  Serial.begin(115200);                        // Set data rate to 9600 bps
}  


 int prevLeft = 1;
 int prevRight = 1;
void loop()                                  // Main loop auto-repeats
{
  int irLeft = irDetect(9, 10, 38000);  
  int irRight = irDetect(2, 3, 38000);  // Check for object
  


  if((irLeft != prevLeft) | (irRight != prevRight)){
    Serial.print("Left:  ");
    Serial.print(irLeft);
    Serial.print("Right:  ");  // Display 1/0 no detect/detect
    Serial.println(irRight);
  }
  
  prevLeft = irLeft;
  prevRight = irRight;
  
  delay(10);                                // 0.1 second delay
}

// IR Object Detection Function

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

