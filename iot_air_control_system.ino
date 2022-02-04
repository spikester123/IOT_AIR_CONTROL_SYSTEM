#include <ThingSpeak.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <LiquidCrystal_I2C.h>
#include "MQ135.h"
#include <SoftwareSerial.h>

//wifi details
char ssid[] = "TALKTALKE65547";
char pass[] = "U9QN9RCN";
int status = WL_IDLE_STATUS; 

//thinspeak details
const unsigned long channel_id = "1647296";
const char write_api_key[] = "V6XOLIA968AEDPPC";
WiFiClient client;



const int sensorPin= 0;
int air_quality;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("----------");
delay(100);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED ) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected!");

 
  ThingSpeak.begin(client);


lcd.begin();
lcd.setCursor (0,0);
lcd.print ("circuitdigest ");
lcd.setCursor (0,1);
lcd.print ("Sensor Warming ");
delay(1000);
lcd.clear();


}

void loop() {

  delay(2000);
  
  // put your main code here, to run repeatedly:
MQ135 gasSensor = MQ135(A0);
float air_quality = gasSensor.getPPM();

lcd.setCursor (0, 0);
lcd.print ("Air Quality: ");
lcd.print (air_quality);
lcd.print ("PPM ");
lcd.setCursor (0,1);
if (air_quality<=1000)
{
lcd.print("Fresh Air");

}
else if( air_quality>=1000 && air_quality<=2000 )
{
lcd.print("Poor Air");

}
else if (air_quality>=2000 )
{
lcd.print("Danger!");
   // turn the LED on
}
lcd.scrollDisplayLeft();
delay(1000);


Serial.print("Air Quality: ");
Serial.print(air_quality);
Serial.print("PPM ");
if (air_quality<=1000)
{
  Serial.println("Fresh Air");
  
}
else if (air_quality>=1000 && air_quality<=2000 )
{
  Serial.println("Poor Air");
  
}
else if (air_quality<=2000 )
{
  Serial.println("Danger!");
  
}

ThingSpeak.setField(1, float(air_quality));
ThingSpeak.writeFields(channel_id, write_api_key);

}
