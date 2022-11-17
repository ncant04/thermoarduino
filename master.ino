/*
 * master.ino
 *
 * Copyright (c) 2022 Nicolò Cantori.
 * SPDX-License-Identifier: MIT
 */

#include <LiquidCrystal.h>

// ** LCD pins **

#define RS  2
#define E   3
#define D4  4
#define D5  5
#define D6  6
#define D7  7

//---------------

#define SW  8  // Push-button

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

int pushbutton, n;
float Vin, temp;
String data = "";

void PrintTemp(const float);

void setup()
{
    Serial.begin(9600);
    pinMode(sw, INPUT);

    // Initialize the LCD:
    
    lcd.begin(16,   // columns
              2);   // rows

    lcd.setCursor(0, 0);
}


void loop()
{
    pushbutton = digitalRead(SW);
    
    while(!pushbutton)
        pushbutton = digitalRead(SW);
    
    while(pushbutton)
        pushbutton = digitalRead(SW);

    Serial.print('R');
        delay(250);
    
    while(Serial.available() == 0)
        delay(500);
        
    /*
     *  Serial.read() only returns the first byte of incoming serial data 
     *  available (or -1 if no data is available). We need to read all avaiable
     *  bytes and re-build the complete string (sent from the "slave" board).
     */

    while (Serial.available() > 0)
        data += (char)Serial.read();
   
    n = data.toInt();   // Convert string to decimal value.
    Serial.flush();
    
    Vin = n * 0.00488;

    // For the LM35, we have to multiply the previous value by 100.
    temp = Vin * 100;
    
    PrintTemp(temp);
   
    data = "";
    delay(5000);
    lcd.clear();
}


void PrintTemp(const float nTemp)
{
    lcd.clear();
    lcd.print("Temp: ");
    lcd.print(nTemp);
    lcd.print(char(223));
    lcd.print("C");
}
