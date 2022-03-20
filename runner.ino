//SMART MAILBOX

#include <SoftwareSerial.h>

  //Pin Definitions
  int photo = 5;                // photo resistor
  int pir_sensor = 2;           // PIR motion sensor
  int state = LOW;              // by default, no motion detected
  int val = 0;   // variable to store the pir motion sensor status (value)

  // Configure software serial port
  SoftwareSerial SIM900(7, 8); 

  void setup() 
  {
      //Inputs
      pinMode(photo, INPUT_PULLUP);  // initialize photo resistor as input
      pinMode(pir_sensor, INPUT);    // initialize sensor as an input

      Serial.begin(9600);
      // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
      SIM900.begin(19200);
      // Give time to your GSM shield log on to network
      delay(20000);   
  }

  void loop() 
  { 
    //if/else loop checks if photoresistor is high or low
    if(digitalRead(photo)==LOW)
    {
      Serial.println("Photo Resistor (low)");
    }
    
    else
    {
      Serial.println("Photo Resistor (high)");
    }

    if((digitalRead(pir_sensor)==HIGH))
      {
        Serial.println("Motion Sensor (high)");
      }
    
    else
      {
        Serial.println("Motion Sensor (low)");
      }

      
    if((digitalRead(photo)==HIGH) && (digitalRead(pir_sensor)==HIGH))
    {
       Serial.println("New mail detected!");
       sendSMS();
       Serial.println("******************SMS sent successfully!******************");
       delay(10000);
    }

  }

  void sendSMS() 
  {
    // AT command to set SIM900 to SMS mode
    SIM900.print("AT+CMGF=1\r"); 
    delay(100);
    SIM900.println("AT + CMGS = \"+918860977563\""); 
    delay(100);
    SIM900.println("Hi, you have received a new mail! Thanks :)"); 
    delay(100);
    // End AT command with a ^Z, ASCII code 26
    SIM900.println((char)26); 
    delay(100);
    SIM900.println();
    // Give module time to send SMS
    delay(5000); 
  }
