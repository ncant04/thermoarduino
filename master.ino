/********************************************************************

   thermoarduino/master.ino

   Sends command to "slave" board, receives sensor data from it,
   manages I/O lines and user interaction.

   Copyright (c) Nicolò Cantori. All rights reserved.
   Licensed under the MIT License.

********************************************************************/

#include <LiquidCrystal.h>

// Define output pins for LCD.
#define rs  2
#define e   3
#define d4  4
#define d5  5
#define d6  6
#define d7  7

// push-button
#define sw  8

LiquidCrystal lcd(rs,
                e,
                d4, d5, d6, d7);    // LCD data lines

int pushbutton, n;
float Vin, temp;
String data = "";

void setup() {
    Serial.begin(9600);
    pinMode(sw, INPUT);

    // Initialize the LCD:
    
    lcd.begin(16,   // columns
              2);   // rows

    lcd.setCursor(0, 0);
}

void loop() {
    pushbutton = digitalRead(sw);
    
    while(pushbutton == 0)
        pushbutton = digitalRead(sw);
    
    while(pushbutton == 1)
        pushbutton = digitalRead(sw);

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

    // We need to convert the string into a decimal value.
    n = data.toInt();
    Serial.flush();
    
    Vin = n * 0.00488;

    // For the LM35, we have to multiply the previous value by 100.
    temp = Vin * 100; 

    lcd.clear();
    lcd.print("Temp: "); lcd.print(temp); lcd.print(char(223)); lcd.print("C");
    
    data = "";
    delay(5000);
    lcd.clear();
}
