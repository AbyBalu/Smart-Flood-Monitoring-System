#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>               // including the library of DHT11 temperature and humidity sensor
#define BLYNK_PRINT Serial
#define DHTTYPE DHT11          // DHT 11
#define dht_dpin 3             //RX, defines pin number

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(dht_dpin, DHTTYPE);
WidgetLCD lcd1(V1);
WidgetBridge bridge1(V1);

BLYNK_CONNECTED() {
  // Place the AuthToken of the second hardware here
  bridge1.setAuthToken("f2a44ecc55f64a98906eba3d0542f8d7"); 
}


char auth[] = "acd7381d85564370ab9699190f9e9a6b";       // You should get Auth Token from the Blynk App
char ssid[] = "Redmi";        // Your WiFi credentials.
char pass[] = "1234567890";   // Set password to "" for open networks.
const int trigPin = D2;       // defines pin number
const int echoPin = D1;       // defines pin number
const int input = D7;         // defines pin number
long duration;                // defines variables
int distance;                 // defines variables

int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;

void setup() 
{
 Blynk.begin(auth, ssid, pass);
 pinMode(trigPin, OUTPUT);    // Sets the trigPin as an Output
 pinMode(echoPin, INPUT);     // Sets the echoPin as an Input
 Serial.begin(9600);          // Starts the serial communication
 pinMode(input,INPUT);        // defines pin number
 lcd.backlight();             // Turn on the backlight.
}

void loop() 
{

X = pulseIn(input, HIGH);
Y = pulseIn(input, LOW);
TIME = X + Y;
FREQUENCY = 1000000/TIME;
WATER = FREQUENCY/7.5;
LS = WATER/60;

  
 lcd1.clear();
 lcd1.print(0, 0, "Distance: ");        // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
 digitalWrite(trigPin, LOW);                // Clears the trigPin
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);               // Sets the trigPin on HIGH state for 10 micro seconds
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);         // Reads the echoPin, returns the sound wave travel time in microseconds
 distance= duration*0.034/2;                // Calculating the distance
 bridge1.virtualWrite(V1, distance); 
 Serial.print("Distance: ");                // Prints the distance on the Serial Monitor
 Serial.println(distance);
 Wire.begin(D4, D3);                        //Use predefined PINS consts
 lcd.begin();                               // The begin call takes the width and height. This should match the number provided to the constructor.
 lcd.home();
 lcd.setCursor(0, 0);                       // Move the cursor at origin
 lcd.print("Distance:");
 lcd.print(distance);
 lcd1.print(6, 1, distance);
 lcd1.print(10, 1, "cm");
 dht.begin();
 float h = dht.readHumidity();              // get readings from the DHT11 sensor
 float t = dht.readTemperature();           // get readings from the DHT11 sensor
 Blynk.virtualWrite(V3, h);                 // Send humidity to Blynk App. Display on Gauge Widget
 Blynk.virtualWrite(V2, t);                 // Send temperature to Blynk App. Display on Gauge Widget
 lcd.setCursor(0, 1);     
 lcd.print("Humidity:");
 lcd.print(h);
 lcd.print("%");
 lcd.setCursor(0, 2);
 lcd.print("Temperature:");
 lcd.print(t); 
 lcd.println("C");

if(FREQUENCY >= 0)
{
if(isinf(FREQUENCY))
{
lcd.setCursor(0,3);
lcd.print("VOL. :0.00");
lcd.print(" L/M");
Blynk.virtualWrite(V4, 0);
bridge1.virtualWrite(V4, 0); 
}
else
{
TOTAL = TOTAL + LS;
Serial.println(FREQUENCY);
Blynk.virtualWrite(V4, WATER);
bridge1.virtualWrite(V4, WATER); 
lcd.setCursor(0,3);
lcd.print("VOL. :");
lcd.print(WATER);
lcd.print(" L/M");
}
}
 
 Blynk.run();
 delay(3000); 
}
