#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);

// TURBIDITY
int sensorPin = A0; 

// DS18B20
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);	
DallasTemperature sensors(&oneWire);

// LED pins
#define GREEN_LED_PIN 5
#define RED_LED_PIN 4

void setup() { 
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize LED pins
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  
  // Turn off both LEDs initially
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}

void loop() {
  // TURBIDITY SENSOR
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  delay(100);
  
  lcd.setCursor(0, 0);
  lcd.print("TU:");
  lcd.setCursor(3, 0);
  
  // Check turbidity and control LEDs
  if (turbidity < 20) {
    lcd.print("JERNIH   ");
    Serial.println("AIR JERNIH");
    Serial.println(turbidity);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else if ((turbidity >= 20) && (turbidity <= 50)) {
    lcd.print("KERUH   ");
    Serial.println("AIR CENDERUNG KERUH");
    Serial.println(turbidity);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  } else {
    lcd.print("KERUH++");
    Serial.println("AIR KERUH SEKALI");
    Serial.println(turbidity);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }

  // DS18B20
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
