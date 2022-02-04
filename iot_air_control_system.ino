#include "DHT.h"

#include <LiquidCrystal_I2C.h>

#include "MQ135.h"
#include <SoftwareSerial.h>
const int sensorPin= 0;
int air_quality;
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define DHTPIN 3

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("----------");


 
lcd.begin();
lcd.setCursor (0,0);
lcd.print ("circuitdigest ");
lcd.setCursor (0,1);
lcd.print ("Sensors Warming ");
delay(1000);
lcd.clear();

dht.begin();
}

void loop() {

  delay(2000);
  
  // put your main code here, to run repeatedly:
MQ135 gasSensor = MQ135(A0);
float air_quality = gasSensor.getPPM();

float t = dht.readTemperature();
float h = dht.readHumidity();

if (isnan(h) || isnan(t))
{
  Serial.println("failed to read from dht sensor");

  lcd.clear();
  lcd.print("Failed to read from dht sensor!");
  return;
}

lcd.setCursor (0, 0);
lcd.print ("Air Quality: ");
lcd.print (air_quality);
lcd.print ("PPM");
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
lcd.setCursor(1,0);
lcd.print ("Temp:");
lcd.print (t);
lcd.print ("*C");
lcd.setCursor (1,1);
lcd.print ("Humidity:");
lcd.print (h);
lcd.print ("%");
lcd.scrollDisplayLeft();
delay(1000);


Serial.print("Air Quality: ");
Serial.print(air_quality);
Serial.print("PPM");
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
Serial.println("Temp:");
Serial.print(t);
Serial.print("*C");
Serial.println("Humidity:");
Serial.print(h);
Serial.print("%");


}
