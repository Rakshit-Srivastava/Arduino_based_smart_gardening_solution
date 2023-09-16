#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int ldrPin = A0;
const int soil_pin=A2;
const int rain_pin=A4;
float rain_stat=0;
float soil_status=0;
int yled=9;
int rled=10;
int bled=11;
int gled=12;
int buzzer=6;

LiquidCrystal lcd(5,4,3,2,1,0);

void setup() {
  lcd.clear();
  lcd.begin(16, 2); 
  dht.begin();
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(6,OUTPUT);
 
}

void loop()
{
  ldr();
  delay(2000);
  temp();
  delay(2000);
  soil_humidity();
  delay(2000);
  rain();
  delay(2000);

}

void ldr() {
  float ldrValue = analogRead(ldrPin);
  float ldr_per=map(ldrValue,0.0,1023.0,100.0,0.0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LightVal");
  lcd.setCursor(0, 1); 
  lcd.print(ldr_per);
  lcd.print("%");
  if(ldr_per <= 50)
  {
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  tone(6,5000);
  }
  else
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  noTone(6);
  }
}

void temp()
{
  float temp=dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempVal");
  lcd.setCursor(0, 1); 
  lcd.print(temp);
  lcd.print("C");
  if(temp < 25 )
  {
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  tone(6,5000);
  }
  else if(temp >= 25 && temp <=35)
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  noTone(6);
  }
  else
  {
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  tone(6,5000);
  }
}

void soil_humidity()
{
  soil_status=analogRead(soil_pin);
  float water=(100.0-((soil_status/1023.0)*100.0));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WaterVal");
  lcd.setCursor(0, 1); 
  lcd.print(water);
  lcd.print("%");
  if (water < 50)
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  tone(6,5000);
  }
  else
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  noTone(6);
  }
}

void rain()
{
  rain_stat=analogRead(A4);
  float rain_val=map(rain_stat,0.0,1023.0,100.0,0.0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RainVal");
  lcd.setCursor(0, 1); 
  lcd.print(rain_val);
  lcd.print("%");
  if(rain_val > 50)
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  tone(6,5000);
  }
  else
  {
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  noTone(6);
  }
}