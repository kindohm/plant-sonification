/*  Script to sonify plants as they are touched by Keston
 *  Make two leads with nails on one end and pins on the other 
 *  Place the nails in the soil and the pins analog in A0 and A3
 *  Attach two leads to a speaker or audio cable
 *  Speaker [+] to digital out pin 9 [-] to GND
 */

int sensorPin[] = {A0,A1,A2,A3,A4,A5};    // array of sensors
int sensorValue[] = {0,0,0,0,0,0};  // variable to store the value coming from the sensor
int speakerPin = 9;

const int numReadings = 10;
int readings[numReadings];      // the readings from an analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  // declare speakerPin as an OUTPUT:
  pinMode(speakerPin, OUTPUT);
  // Needed to display values, comment when no longer needed
  Serial.begin(9600);
}

void loop() {
  // read the values from the sensors:
  sensorValue[0] = analogRead(sensorPin[0]);
  sensorValue[3] = analogRead(sensorPin[3]);

  // This code smooths pin 0 data into a var
  // called average
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = sensorValue[0];
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;

// Generate a delay between writing to the digital outs
//  int del = map(sensorValue[3],0,1023,map(sensorValue[0],0,1023,1,20),1043);
  int del = floor(sensorValue[3]*0.25);
//  int del = average;
//  int del = 100;
  
  // set a threshold for making sound
  if (sensorValue[0] < 300) {
  //  int dur = map(sensorValue[3],0,1023,5,205);
  //   for ( long i = 0; i < dur; ++i ) { 
        int tone = map(sensorValue[3],0,1023,0,10000);
//        int tone = sensorValue[3];  
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
  //   }
        
  }
//  Serial.print("Pin 0: ");
//  Serial.print(sensorValue[0]);
//  Serial.print(" Pin 3: ");
//  Serial.println(sensorValue[3]);
//  Serial.print("Average: ");
//  Serial.println(average);
  delay(del);
}

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
