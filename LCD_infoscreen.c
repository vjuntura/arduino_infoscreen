#include <Wire.h>

#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


//Ahtomittari

const int ahtoInput = A0;

//E85

const int viinaInput = A1;

//Volttimittari
const int volttiInput = A2;

//Lampomittari

const int lampoInput = A3;

//Mittarivalot

const int mittariPin = 11;

//Photoresistor

const int valoPin = A4;

int raakavalo = 0;

//Erikoismerkki

byte aste[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
};

void setup(){

  pinMode(ahtoInput, INPUT);
  pinMode(viinaInput, INPUT);
  pinMode(volttiInput, INPUT);
  pinMode(lampoInput, INPUT);
  pinMode(mittariPin, OUTPUT);
  pinMode(valoPin, INPUT);
  lcd.begin(20, 4);
  lcd.createChar(0, aste);
  raakavalo = analogRead(valoPin);
}

void loop(){

  //Ahtomittari
  int raakaahto = analogRead(ahtoInput);
  float mapahto = raakaahto * (2.06 / 819.20);


  //E85
  int raakaviina = analogRead(viinaInput);
  float mapviina = raakaviina * (100.0 / 1023.0);



 // Volttimittari
  int raakavoltti = analogRead(volttiInput);
  float mapvoltti = raakavoltti * (55.00 / 1023.00);


  //Lampomittari

  int raakalampo = analogRead(lampoInput);
  float maplampo = raakalampo * (60.0 / 1023.0);

  //Valoisuus

  int mapvalo = map(raakavalo, 0, 1023, 0, 255);
  analogWrite(mittariPin, mapvalo);

 {
  lcd.setCursor(0, 0);
  lcd.print("BOOST ");
  lcd.print(mapahto);
  lcd.print(" BAR");
  lcd.setCursor(0, 1);
  lcd.print("E85-% ");
  lcd.print(mapviina, 1);
  lcd.setCursor(0, 2);
  lcd.print("VOLTAGE ");
  lcd.print(mapvoltti);
  lcd.print(" V");
  lcd.setCursor(0, 3);
  lcd.print("TEMPERATURE ");
  lcd.print(maplampo, 1);
  lcd.write(byte(0));
  lcd.print("C");
  delay(500);

}
}
