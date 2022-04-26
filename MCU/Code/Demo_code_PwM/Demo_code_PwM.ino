// Period = 2 ms / Frequenz = 500 Hz. 
void setup(){ 
pinMode(3, OUTPUT);  
pinMode(11, OUTPUT);  
TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);  
TCCR2B = _BV(CS20);  
OCR2A = 205;  
OCR2B= 205;  


TCCR2A = 0b10110000 | (TCCR2A & 0b00001111) ;
} 
void loop() { 
}
