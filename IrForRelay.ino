/*Activate relay using a remote
//In order to add more buttons follow these steps:
1. Connect the arduino to the computer.
2. Open the serial monitor.
3. Press the new button while pointing the remote control towards the arduino.
4. copy the hexa code recieved in the serial monitor in hexa
5. add a new long using the code for the new button in the second if statement and of course, give it an intial value using long.
*/

#include <IRremote.h>

int RECV_PIN = 11; //Infra PIN
long IRs = 0x0; //reset IR code recieved to zero and define it as hexa.
long Tv = 0x213CB44B; //Yes remote green Button
long Tv_off = 0xF4BA2988; //Yes remote power button.
long Denon = 0x6E56F924; //Denon remote "0" button.
int Relay = 2;
int relayState = 0;         // variable for reading the relay status
int LED_PIN = 13; // Red LED PIN

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(Relay, OUTPUT);     //Set Pin2 as output 
  pinMode(LED_PIN, OUTPUT);  //Set led pin to output
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    IRs = results.value,HEX;
    Serial.println(results.value, HEX); //Can be used to print out the remote button IR code in HEXA on the serial monitor.
    irrecv.resume(); // Receive the next value
  }
  if ((IRs == Tv) || (IRs == Denon)){ //check if the right buttons on the remote have been pressed, can add more, read the startings comments for more infromation.
   // Serial.println("it's working"); Line for debugging on serial monitor
      if (digitalRead(Relay)!= LOW){
    digitalWrite(Relay, LOW);   //Turn off relay   
      }
      else{
        digitalWrite(Relay,HIGH);
      }
   if (digitalRead(Relay) == LOW)   {
     digitalWrite(LED_PIN, HIGH); //Turn LED on if everything is ON.
   }
     else {
       digitalWrite(LED_PIN, LOW); //Turn LED off if everything is OFF.
     }
   }
    IRs = 0; //reset the code to zero at the end of the loop.
  }




