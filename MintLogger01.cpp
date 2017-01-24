#include <Arduino.h>
#include "RTCInt.h"// include the RTCint library

RTCInt rtc;             //create an RTCInt type object

#define REDLED 13
void time_interrupt(void);
int ctInput;

void setup() {
	pinMode(REDLED, OUTPUT);
	Serial.begin(115200);
	Serial.println("Mint System Ltd");

	rtc.begin(TIME_H24);  //init RTC in 24 hour mode

	//time settings
	rtc.setHour(15,0);  //setting hour
	rtc.setMinute(43);   //setting minute
	rtc.setSecond(0);    //setting second
	rtc.setDay(24);      //setting day
	rtc.setMonth(1);     //setting month
	rtc.setYear(17);     //setting year

	rtc.enableAlarm(SEC,ALARM_INTERRUPT,time_interrupt); //enabling alarm in interrupt mode
	rtc.local_time.hour=17;   //setting hour alarm
	rtc.local_time.minute=5;  //setting minute alarm
	rtc.local_time.second=10; //setting second to match
	rtc.setAlarm();           //write second in alarm register
}

int loopcounter=0;
//---- Loop ----
void loop() {
	//time_interrupt();
	//digitalWrite(REDLED, HIGH);
	//delay(30);
	//digitalWrite(REDLED, LOW);

	delay(970);
}

void time_interrupt(void)
{
	digitalWrite(REDLED, HIGH);
	rtc.getDate();       //getting date in local structure (local_date) for the print commands
	rtc.getTime();       //getting time in local structure (local_time) for the print commands

	//printing date in format YYYY/MM/DD
	Serial.print(rtc.local_date.year+2000); //year
	Serial.print('/');
	Serial.print(rtc.local_date.month);     //month
	Serial.print('/');
	Serial.print(rtc.local_date.day);       //day
	Serial.print(' ');

	//printing time
	Serial.print(rtc.local_time.hour);      //hour
	Serial.print(':');
	Serial.print(rtc.local_time.minute);    //minute
	Serial.print(':');
	Serial.println(rtc.local_time.second);  //second

	// Read and print CT reading
	ctInput = analogRead(0);
	Serial.print("Current Reading = ");
	Serial.println(ctInput);

	// keep an eye on how long its been running
	Serial.print("Iteration ");
	Serial.println(loopcounter++);
	Serial.print('\n');
    RTC->MODE2.INTFLAG.bit.ALARM0=1; //clearing alarm0 flag
	digitalWrite(REDLED, LOW);
}
