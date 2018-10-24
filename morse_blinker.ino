// Morse Code Blinker
// Written by Nick Masso
// Updated October 23 2018
// github.com/starmaid
// nicholas.masso.14@gmail.com
// Send a message via serial, it will repeat on the LED
// Connect via USB to the arduino, open serial monitor
// Type your message, but dont send it
// Hit the reset button on the arduino
// Send your message when you see the prompts
// Now the message will repeat until you poweroff or reset the 

int led_pin = 2;        // The digital port your LED is connected to
int short_pulse = 150;  // How long your 'short' pulse lasts
int long_pulse = 300;   // How long a 'long' pulse lasts
int code[6] = {1,1,2};  // Initialize the code array with the letter U, for testing
int message[30] = {0};  // Array for full message in ASCII characters
                        // If you make this number too high, your Arduino might run out of memory
int loc = 0;            // A loop control variable for reading the message from serial
int results[30][6] = {0}; // The 2-Dimensional array for storing the message translated into Morse code
long read_time = 5;   // How long the user has to enter the message, in seconds
long repeat_time = 300; // How long between repeats of the message in seconds, not including the time it takes to flash out the message

void setup() {
  pinMode(led_pin, OUTPUT);               // Setting the LED pin to output mode
  Serial.begin(9600);                     // Starting the serial connection
                                          // 9600 is slow, but we don't need it any faster
  Serial.println("PLEASE USE UPPER CASE");  // Just some instructions
  Serial.println("TYPE 31-OR-LESS-CHARACTER MESSAGE NOW");
  Serial.println("You have 5 seconds to enter your message");   // This is controlled by the read_time variable
}

void loop() {
  if (Serial.available() > 0) {
    message[loc] = Serial.read();
    Serial.println(message[loc],DEC);
    Serial.println(loc,DEC);
    loc++;
  }
  while (millis() > read_time * 5000) {
    loc = 0;
    Serial.println("PROCESSING MESSAGE");
    translate(message,results);
    for(int i = 0; i < 30; i++) {
      flash(results[i]);
    }
    delay(repeat_time * 1000);
    // The code could be modified so that another message could be entered
    // Its a future update
  }
}

void flash(int code[]) {
  // This is the function for flashing a single letter
  for(int pos = 0 ; code[pos] != 0 ; pos++) {
    digitalWrite(led_pin,HIGH);
    delay(short_pulse * code[pos]);
    digitalWrite(led_pin,LOW);
    delay(short_pulse);
  }
  delay(400);
}

void set_codes(int arrayV[], int a, int b, int c, int d, int e, int f) {
  arrayV[0] = a;
  arrayV[1] = b;
  arrayV[2] = c;
  arrayV[3] = d;
  arrayV[4] = e;
  arrayV[5] = f;
}

void translate(int arrayL[],int translated[][6]) {
  // These are the Morse patterns for all UPPER CASE letters
  // Numbers, and certain other ASCII characters
  for( int pos = 0 ; arrayL[pos] > 0 ; pos++) {
    switch (arrayL[pos])
    {
      case 1 ... 32: set_codes(translated[pos],0,0,0,0,0,0); 
                break;
      case 33:  set_codes(translated[pos],2,1,2,1,2,2);
                break;
      case 34 ... 43: set_codes(translated[pos],0,0,0,0,0,0); 
                break;
      case 44:  set_codes(translated[pos],2,2,1,1,2,2);
                break;
      case 46:  set_codes(translated[pos],1,2,1,2,1,2);
                break;  
      case 47 ... 62: set_codes(translated[pos],0,0,0,0,0,0); 
                break;
      case 63:  set_codes(translated[pos],1,1,2,2,1,1);
                break;
      case 64:  set_codes(translated[pos],0,0,0,0,0,0);
                break;             
      case 65:  set_codes(translated[pos],1,2,0,0,0,0);
                break;
      case 66:  set_codes(translated[pos],2,1,1,1,0,0);
                break;
      case 67:  set_codes(translated[pos],2,1,2,1,0,0);
                break;
      case 68:  set_codes(translated[pos],2,1,1,0,0,0);
                break;
      case 69:  set_codes(translated[pos],1,0,0,0,0,0);
                break;
      case 70:  set_codes(translated[pos],1,1,2,1,0,0);
                break;
      case 71:  set_codes(translated[pos],2,2,1,0,0,0);
                break;
      case 72:  set_codes(translated[pos],1,1,1,1,0,0);
                break;
      case 73:  set_codes(translated[pos],1,1,0,0,0,0);
                break;
      case 74:  set_codes(translated[pos],1,2,2,2,0,0);
                break;
      case 75:  set_codes(translated[pos],2,1,2,0,0,0);
                break;
      case 76:  set_codes(translated[pos],1,2,1,1,0,0);
                break;
      case 77:  set_codes(translated[pos],2,2,0,0,0,0);
                break;
      case 78:  set_codes(translated[pos],2,1,0,0,0,0);
                break;
      case 79:  set_codes(translated[pos],2,2,2,0,0,0);
                break;
      case 80:  set_codes(translated[pos],1,2,2,1,0,0);
                break;
      case 81:  set_codes(translated[pos],2,2,1,2,0,0);
                break;
      case 82:  set_codes(translated[pos],1,2,1,0,0,0);
                break;
      case 83:  set_codes(translated[pos],1,1,1,0,0,0);
                break;
      case 84:  set_codes(translated[pos],2,0,0,0,0,0);
                break;
      case 85:  set_codes(translated[pos],1,1,2,0,0,0);
                break;
      case 86:  set_codes(translated[pos],1,1,1,2,0,0);
                break;
      case 87:  set_codes(translated[pos],1,2,2,0,0,0);
                break;
      case 88:  set_codes(translated[pos],2,1,1,2,0,0);
                break;
      case 89:  set_codes(translated[pos],2,1,2,2,0,0);
                break;
      case 90:  set_codes(translated[pos],2,2,1,1,0,0);
                break;
      
    }
  }
}

