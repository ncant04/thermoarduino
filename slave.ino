/*
 * slave.ino
 *
 * Copyright (c) 2022 Nicolò Cantori.
 * SPDX-License-Identifier: MIT
 */

int n = 0;
#define SENSOR	A0

void setup(){
	Serial.begin(9600);
}

void loop(){
	if(Serial.available()){
		char cmd = Serial.read();

		if(cmd == 'R'){
			n = analogRead(SENSOR);
			Serial.print(n);
			delay(500);
		}
		Serial.flush();
	}
	delay(500);
}
