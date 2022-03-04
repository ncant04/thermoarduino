/********************************************************************

   thermoarduino/slave.ino

   Receives command sent from "master" board, reads value of
   temperature sensor and sends back data.

   Copyright (c) Nicolò Cantori. All rights reserved.
   Licensed under the MIT License.

********************************************************************/

int n = 0;
#define sensor  A0

void setup(){
	Serial.begin(9600);
}

void loop(){
	if(Serial.available()){
		char cmd = Serial.read();

		if(cmd == 'R'){
			n = analogRead(sensor);
			Serial.print(n);
			delay(500);
		}
		Serial.flush();
	}
	delay(500);
}
