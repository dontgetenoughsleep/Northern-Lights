#include <SPI.h>
const int CS = 53;
int inputpin = A8;
int analogValue;


// FLOAT VARIABLES //////////////////////////////////
float Avg[50];
float tot = 0;
float val = 0;
float thresh = 0;
float reading = 0;
float sensor = 0.0;

// INTERGER VARIABLES////////////////////////////////
int A = 3;
int B = 5 ;
int C = 6;
int T = 5;
int i = 0;
int j = 0;
int Y = 5;
int yah = 1;
int color = 1;
int switchup = 0;
int var = 0;
int zeroes = 0;
int ones = 0;
int counter = 0;
int k = 0;
int This = 11;
int test = 0;
float high = 0 ;
float total = 0 ;
float percent = 0;

void setup() {
  pinMode (CS, OUTPUT);
  SPI.begin();
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(inputpin, INPUT);
  pinMode(inputpin, INPUT);
  Serial.begin(9600);

  while (Y == 5) {

    //Loop to take the average of 10 audio input values
    for (i; i < 50 ; i++) {
      float ana = analogRead(inputpin);

      //Conversion formula for voltage
      val = (ana * 5) / 1024;
      Avg[i] = val;

    } for ( j; j < 50 ; j++) {

      if (j > 0) {
        tot = tot + Avg[j];
      }
    }
    // thresh is for when the color organ is triggered, I added a bit of offset
    thresh = ((tot / 50) + 0.2);
    i = 0;
    j = 0;
    // Incase the arduino reads an abnormaly high value
    if (thresh < 3.50) {
      Y = 6;
    }
    else {
      tot = 0;
    }
    Serial.print("threshold is ");
    Serial.println(thresh, 4);
  }
}

void loop() {
  ///POT VALUE////////////////////////////////////////////////////////////////POT VAL//////////////////////////////////////////////////POT VAL////////////////////////
  // Digital potentiometer value
  MCP41010Write(This);
  Serial.print("/////////////////////////////////The pot is now: ");
  Serial.println(This);
  delay(100);
  ///POT VALUE////////////////////////////////////////////////////////////////POT VAL//////////////////////////////////////////////////POT VAL////////////////////////
  total++;
  Caluclations();
  //increments for function Switch()
  switchup ++;
  //if arduino reads a value over the thresh, then go to Switch function
  if (reading >= thresh) {
    Switch();
  }
  //If the arduino does not read a value over thresh, jump into the function count()
  else {
    count() ;
  }
}
//function to set pins for the LED strip
void setColor(int a, int b, int c) {
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);
}

// Function that switches through different colors
void Switch() {
  high++;
  Caluclations();

  if (switchup < 25) {
    //TURN GREEN
    setColor(1, 0, 0);
    delay(100);
  }
  else if (25 <= switchup && switchup <= 50) {
    //TURN RED
    setColor(0, 1, 0);
    delay(100);
  }
  else if (50 < switchup && switchup <= 75) {
    //TURN YELLOW
    setColor(1, 1, 0);
    delay(100);
  }
  else if (75 < switchup && switchup <= 100) {
    //TURN CYAN
    setColor(1, 0, 1);
    delay(100);
  }
  else if (100 < switchup && switchup <= 125) {
    //TURN MAJENTA
    setColor(0, 1, 1);
    delay(100);
  }
  else if (125 < switchup && switchup <= 150) {
    //TURN WHITE
    setColor(1, 1, 1);
    delay(100);
  }
  else if (switchup > 150) {
    switchup = 0;
  }
}
//Function to count time since the thresh hasn't been reached
void count() {
  //Increment K as long as it follows this condition
  while (k < 100) {
    k++;
    Caluclations();
    if (reading >= thresh) {
      zeroes = 0;
      k = 101;
      Switch();

    }
    else {
      zeroes++;
      setColor(0, 0, 1);
    }
  }
  k = 0;
  // if there has been no values to trigger the color organ for a while, then jump into the function pulsing()
  if (zeroes == 100) {
    pulsing();
    zeroes = 0;
  }
}
// Puslsing lights (LED strip gradually fades through different colors) ////////////////////////
void pulsing() {

  while (5 > 1) {

    if (reading >= thresh)
    { Switch();
      break;
    }
    for (int i = 255; i > 0; i--)
    {
      Caluclations();
      if (reading >= thresh) {
        Switch();
        break;
      }

      var = var + 1;
      // blue to red
      analogWrite(A, 255);
      analogWrite(B, i);
      analogWrite(C, var);
      delay(10);
    }
    var = 0;
    //from red to green
    for (int i = 255; i > 0; i--)
    {
      Caluclations();
      if (reading >= thresh) {
        Switch();
        break;
      }
      var++;
      analogWrite(A, i);
      analogWrite(B, var);
      analogWrite(C, 255);
      delay(10);
    }
    var = 0;
    //from green to blue
    for (int i = 255; i > 0; i--)
    {

      Caluclations();
      if (reading >= thresh)
      {
        Switch();
        break;
      }
      var++;
      analogWrite(A, var);
      analogWrite(B, 255);
      analogWrite(C, i);
      delay(10);
    }
  }
}
void Caluclations () {
  int An0 = analogRead(inputpin);
  reading = (An0 * 5) / 1024.0;
  total++;
  counter++;
  TWEEKING();
  // percent is how much a song is in high mode
  percent = high / total;
  Serial.print("Voltage: ");
  Serial.println(reading, 4);
  Serial.print("Percent: ");
  Serial.println(percent);
  Serial.println(This);
}
// initializing for digital potentiometer (not mine, found online)
void MCP41010Write(byte value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(B00010001); // This tells the chip to set the pot
  SPI.transfer(value);     // This tells it the pot position
  digitalWrite(CS, HIGH);
}

void average() {
  if (T == 5) {
    {
      //Loop to take the average of 10 values
      for (i; i < 50 ; i++) {
        float ana = analogRead(inputpin);

        //Conversion formula for voltage
        val = (ana * 5) / 1024;
        Avg[i] = val;
        // Serial.println(val);
      } for ( j; j < 50 ; j++) {

        if (j > 0) {
          tot = tot + Avg[j];
        }
      }
    }
    thresh = ((tot / 50) + 0.08);
    i = 0;
    j = 0;
    tot = 0;
    T = 6;
  }
}
//
void TWEEKING() {
  if (total >= 1000 && percent != 0.00) {
    total = 100;
    high = 1;
    //Serial.println("TOTAL IS NOW 100 AGAIN!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  }
  // this changes the pot value to optimize the reactiveness of the LED strips
  if (counter == 150) {

    if (percent <= 0.04 && percent >= 0.01) {
      This++;
      MCP41010Write(This);
      delay(10);
      counter = 0;
      // Serial.print("DigPOT step: ");
      //Serial.println(This);

    } else if (percent > 0.08 && percent < 0.12) {
      This--;

      MCP41010Write(This);
      delay(10);
      counter = 0;
      // Serial.print("slow it down: ");
      //Serial.println(This);
    }
    else if (percent < 0.01) {
      if (yah == 1) {
        This = 1;
        MCP41010Write(This);
        delay(10);
        counter = 0;
        yah = 0;
        // Serial.print("Reset: ");
        //Serial.println(This);
      }
      else {
        This = 1;
        MCP41010Write(This);
        delay(10);
        counter = 0;
        yah = 1;
        //Serial.print("Reset: ");
        //Serial.println(This);
      }
    }

    else if (percent >= 0.12)
    { if (This <= 1)
      {
        This--;
        MCP41010Write(This);
        delay(10);
        counter = 0;
        //Serial.print("DigPOT step: ");
        //Serial.println(This);
      }
      else {
        This = 1;
        MCP41010Write(This);
        delay(10);
        counter = 0;
        //Serial.print("DigPOT step: ");
        //Serial.println(This);
      }
    }
    else if (percent > 0.12)
    { This--;
      This--;
      MCP41010Write(This);
      delay(10);
      counter = 0;
      //Serial.print("DigPOT step: ");
      // Serial.println(This);
    }
    else {
      counter = 0;
      //   Serial.print("DigPOT step: ");
      //   Serial.println(This);
    }
  }
}
