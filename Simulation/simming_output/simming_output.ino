/*
   Pseudo Code for set Register Timer2 (Phase correct PWM) on the Arduino UNO
   Application for switching Synchronous Buck Converter 
   Dev by : www.electronicsDNA.com
   Date : 12/1/2021 (V.0)
*/
#include "TimerOne.h"

int Output_PWM = 0;
int DT = 5; // set Dead Time

void setup()
{
pinMode (3, OUTPUT);
pinMode (11, OUTPUT);
Serial.begin(9600);
TCCR2A =0b11100001; // Set Register Phase Correct PWM
TCCR2B =0b00000001; // Set Fsw = 31.372 kHz
delay(300);
}

void loop()
{
Output_PWM = analogRead(A0); // Read ADC CH0 for Adj PWM
Output_PWM = 1024-Output_PWM; // Inv data of Output_PWM
Output_PWM = (Output_PWM/4); // Set Data form ADC (10Bit) to register OCR2x (8Bit)

OCR2A = Output_PWM; // PIN D11
OCR2B = (Output_PWM-DT); // PIN D3
delay(100);
}
