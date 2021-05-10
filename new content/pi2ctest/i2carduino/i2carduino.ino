#include <Wire.h>

void clockwise() {
  digitalWrite(PWMa, HIGH);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
}

void anticlockwise() {
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, HIGH);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, HIGH);
}

void forwards() {
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, HIGH);
  digitalWrite(PWMc, HIGH);
  digitalWrite(PWMd, LOW);
}

void backwards() {
  digitalWrite(PWMa, HIGH);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, HIGH);
}

void Stop() {
  digitalWrite(PWMa, LOW);
  digitalWrite(PWMb, LOW);
  digitalWrite(PWMc, LOW);
  digitalWrite(PWMd, LOW);
}

void setup() {
  Serial.begin(9600);// open the serial port at 9600 bps:
  Wire.begin(0x07); //Set Arduino up as an I2C slave at address 0x07
  Wire.onRequest(requestEvent); //Prepare to send data
  Wire.onReceive(receiveEvent); //Prepare to recieve data
}

void loop() {
}

void requestEvent()
{
  unsigned char char_ar[16] = "Hi Raspberry Pi"; //Create String
  Wire.write(char_ar,16); //Write String to Pi.
}

void receiveEvent(int numBytes){
  //Set Up Vars
  int receive_int=0;
  int count=0;

  //We'll recieve one byte at a time. Stop when none left
  while(Wire.available())
  {
    char c = Wire.read();    // receive a byte as character
    //Create Int from the Byte Array
    receive_int = c << (8 * count) | receive_int;
    count++;
  }
  //Print the Int out.
  Serial.print("Received Number: "); 
  Serial.println(receive_int);
  
}
