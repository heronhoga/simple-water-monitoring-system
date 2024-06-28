#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);

//TURBIDITY
int sensorPin = A0; 

//DS18B20
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);	
DallasTemperature sensors(&oneWire);

void setup()
{ 
  Serial.begin(9600);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}
void loop() {
  //TURBIDITY SENSOR
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("C:");
  lcd.print("   ");
  lcd.setCursor(2, 0);
  lcd.print(turbidity);

  //DS18B20
  
  delay(100);
  if (turbidity < 20) {
    lcd.setCursor(5, 0);
    lcd.print("JERNIH");
    Serial.print("AIR JERNIH");
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    lcd.setCursor(5, 0);
    lcd.print("KERUH");
    Serial.print("AIR CENDERUNG KERUH");
  }
  if (turbidity > 50) {
    lcd.setCursor(5, 0);
    lcd.print("KERUH++");
    Serial.print("AIR KERUH SEKALI");
  }

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  
  // Display temperature on LCD
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  
  delay(1000);
}