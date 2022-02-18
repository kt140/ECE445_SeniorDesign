# Table of Contents
* [references](#references)
* [First TA Meeting](#Firstmeeting)

# references <a name= "references"></a>

# 2022-02-08 to 2022-02-10  Project Proposal <a name= "Firstmeeting"></a>
We had our first TA meeting Feb 8th to get our project proposal draft checked out. While the project proposal served to present general project idea to the TAs and the faculty, it helped us to sort out general design approaches and set priority goals. One concern we brought up to the TA during this phase was usage of the ECEB solar panel. Buying solar power that is small sized, but capable least 10W is quite expensive in the market. Since our project goal is to output 10W, having an access to ECEB solar panel (on the sunny days, using only small part of it can harvest around 80W) will be extremely beneficial. 

# 2021-02-16 MCU Board Research <a name= "keyboard1"></a>
As indicated on the project proposal, potential microcontroller candidates are ATMEGA2560 and ATMEGA328. ATMEGA328 will be preferable if it can support all the peripherals we require. 

Lukas and I purchased DIP package of ATMEGA328 (with our own money). Comparing the DIP package and the SMD (TQFP), DIP lacks 4 pins (28 vs 32 pins) which are two ADCs (ADC6 and ADC7), one VCC pin and one GND pin. To get accurate represent of what our system requires, I created a chart below. 

![System IO Requirement Chart](SystemIOReq1.PNG) 
__System IO Requirements__

Typically, display interface require a lot more data pins to be connected to it. However, it seems like using built-in I2C capable display will reduce the required number of the data pin to two. With this assumption, our system will roughly require around 10 data pins from the MCU. 

For the MCU specific functional requirements, 2 XTAL designated pins need to be reserved for the crystal oscillators, 3 data pins for the USB protocol interface and 1 pin for auto-reset needs to be reserved. Therefore, minimum data pin requirement for the MCU is 16 pins. 

ATMega328 is capable of total 23 I/O pins. This is enough quantity of I/O pins for our system from the rough analysis. Extra 7 pins are also available to encounter for the potential expansion and error on high level design phase. 

----------------------------------------------

I decided to add some of open source kicad parts to complement our PCB design. 

Here are the links to their github: 

[MX Alps library](https://github.com/ai03-2725/MX_Alps_Hybrid)

[USB C library](https://github.com/ai03-2725/Type-C.pretty)

[random keyboard parts library](https://github.com/ai03-2725/random-keyboard-parts.pretty)
