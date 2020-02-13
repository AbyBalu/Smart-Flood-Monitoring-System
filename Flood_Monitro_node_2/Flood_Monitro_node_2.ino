#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D1,D2);

char auth[] = "f2a44ecc55f64a98906eba3d0542f8d7";   // You should get Auth Token in the Blynk App.
                                                    // Go to the Project Settings (nut icon).
char ssid[] = "Redmi";              // Your WiFi credentials.
char pass[] = "1234567890";         // Set password to "" for open networks.
int distance;                       // defines variables

BLYNK_WRITE(V1)                     // This code will update the virtual port 1
{
  int UData = param.asInt();
  if(UData<=20)
  {
    smsAlert();                     // Function call
  }
}

BLYNK_WRITE(V4)                     // This code will update the virtual port 4
{
  int WData = param.asInt();
  if(WData>=5)
  {
    smsWarning();                   // Function call
  }
}

void setup()
{
  mySerial.begin(9600);             // Setting the baud rate of GSM Module  
  Serial.begin(9600);               // Starts the serial communication
  Blynk.begin(auth, ssid, pass);
  pinMode(D3, OUTPUT);              // defines pin number
  pinMode(D4, OUTPUT);              // defines pin number
  pinMode(D5, OUTPUT);              // defines pin number
}

void loop()
{
  Blynk.run();
}

void smsWarning()
{
  Serial.print("Warning");
  digitalWrite(D5, HIGH);            // turn the LED on (HIGH is the voltage level)                   
  smsWarning1();
  smsWarning2();
  smsWarning3();
  smsWarning4();
  digitalWrite(D5, LOW);                            // turn the LED off by making the voltage LOW

}

void smsAlert()
{
  Serial.print("Alert");
  digitalWrite(D3, HIGH);                           // turn the Buzzer on (HIGH is the voltage level)
  digitalWrite(D4, HIGH);                           // turn the LED on (HIGH is the voltage level)
  smsAlert1();
  smsAlert2();
  smsAlert3();
  smsAlert4();
  digitalWrite(D3, LOW);                            // turn the Buzzer off by making the voltage LOW
  digitalWrite(D4, LOW);                            // turn the LED off by making the voltage LOW
}

void smsWarning1()
{
  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+917994730902\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD WARNING!!!!   Move to Area 1 ");        // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500); 
}

void smsWarning2()
{
  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+918848723212\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD WARNING!!!!   Move to Area 1 ");        // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500);
}


void smsWarning3()
{
  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+917356021996\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD WARNING!!!!   Move to Area 1 ");        // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500);
}


void smsWarning4()
{

  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+919496208268\"\r");  // Replace x with mobile number
  delay(500);                                       // wait for a millisecond
  mySerial.println("!!!!FLOOD WARNING!!!!   Move to Area 1 ");        // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500); 
}


void smsAlert1()
  {
  mySerial.println("AT+CMGF=1");                    //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a millisecond
  mySerial.println("AT+CMGS=\"+917994730902\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD ALERT!!!!  !!!URGENT!!!   Move to Area 2");          // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500); 
  }

void smsAlert2()
  {
  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+918848723212\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD ALERT!!!!  !!!URGENT!!!   Move to Area 2");          // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500); 
  }

void smsAlert3()
  {
  mySerial.println("AT+CMGF=1");                    //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+917356021996\"\r");  // Replace x with mobile number
  delay(500); 
  mySerial.println("!!!!FLOOD ALERT!!!!  !!!URGENT!!!   Move to Area 2");          // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500); 
  }

void smsAlert4()
  {
  mySerial.println("AT+CMGF=1");     //Sets the GSM Module in Text Mode
  delay(1000);                                      // wait for a second
  mySerial.println("AT+CMGS=\"+919496208268\"\r");  // Replace x with mobile number
  delay(500);                                      // wait for a second
  mySerial.println("!!!!FLOOD ALERT!!!!  !!!URGENT!!!   Move to Area 2");          // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);                       // ASCII code of CTRL+Z for saying the end of sms to  the module 
  delay(500);                                      // wait for a second

  }

