# Table of Contents
* [references](#references)
* [First TA Meeting](#Firstmeeting)
* [MCU Board Design Progress 1](#MCUProgress1)
* [MCU Board Design Progress 2](#MCUProgress2)
* [MCU Board Design Progress 3](#MCUProgress3)
* [MCU Board Routing Phase 1](#MCURouting1)
* [MCU Board Routing Phase 2](#MCURouting2)
* [Component Ordering Last Minute Edits of the Version 1](#Order1) 
* [I2C Display Code Progress 1](#Code1)

# references <a name= "references"></a>
* https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061B.pdf 
* https://learn.adafruit.com/adafruit-gfx-graphics-library

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

# 2021-02-18 MCU Board Design Progress 1 <a name= "MCUProgress1"></a>
Previously on my startup project, I used ATMega328P to design custom MCU board with USB protocol, Motor controller and UI interface capability. Since basics of the MCU board design doesn't changes, I based the design on my previous work. 

**Crystal Oscillator Selection**

Crystal oscillators are hard to find due to supply shortages recently. Challenge is to find capable crystal oscillator that will be able to support our desire clock frequency and also meet ATMega328 requirements. In this design, I will be using resonator rather than the oscillator due to power circuit's characteristic of being noisy. Although resonators may consume more energy, we want more robust and noise resilient clock source since the MCU will be used for duty cycle, MPPT, of the Buck-Boost circuit.

To match performance of the Arduino Boards (the maximum processing power reference we need), 16MHz resonator CSTNE16M0V51Z000R0 by Murata Electronics was selected. This resonator has a built in capacitive substrate so separate capacitors are not needed. 

# 2021-02-19 MCU Board Design Progress 2 <a name= "MCUProgress2"></a>

Today, all the necessary MCU level design plans were completed. Some major design plans to note are written below. Other than the design planning, basic schematics were completed. 

**USB to UART Design Plan**

To interface between ATMEGA328 and programming device, USB to UART converter device is needed. However, the problem is that almost all of these devices have long lead time and currently not available. Only chip available at this time point was FT231rl chip, which was chosen to be our USB to UART chip. In case this chip also goes out of stock, our backup plan is to create a connector space for USB data communication pins (TX,RX,DTR) and use over-the-shelf FT232 based interface board. 

**Power Circuit Planning** 

ATMEGA328 requires 5V and 500mA voltage and current supplies. This also should provide enough power to run necessary peripherals that needs to be powered from the MEGA (LCD display, current sensor etc). The main challenge in designing power circuit for the MCU board was managing 5V coming from the USB connection while debug / programming laptop is plugged in. We want the MCU board to be powered via internal power supply all the time. To shut off the plugged in USB from supplying the power while internal system is providing the power, comparator logic below was used.

![MCU Power Comparator Logic](comparator_mcu_power.PNG) 

From the schematic above, VIN comes from the internal power system. Because the comparator uses 3.3V and 5V to compare the input power, VIN port needs to be more than 6.6V for this logic to appropriately select VIN instead of USB's 5V supply. Thus, internal power system will provide 7V to MCU and MCU board has on-board 7V to 5V LDO to match the ATMEGA's specification. 

# 2021-02-20 MCU Board Design Progress 3 <a name= "MCUProgress3"></a>

All the necessary schematics were finished including the NiCd battery charging logic. In addition, all the components were chosen initially as Design Document deadline was approaching. 

**NiCd Battery Charging** 

NiCd Battery is our primary portable energy storage source where 1.2V output is available through this medium. Under some research, we decided that using Panasonic's 700mAh rechargeable battery is the best choice. To charge NiCd battery, supply constant current is the most important factor. This current rate needs to be 10% of the battery capacity (700mA * 0.1 = 70mA). To supply constant 70mA current to battery (or batteries), LM315 power management IC was chosen for its compact size and sufficient functionality. LM315 was configured to be operating in constant current output mode to achieve the constant 70mA charging. This way, as long as series battery connections are below 40V, LM315 can charge as many battery as possible at constant rate of 70mA. In addition, I wanted to add PWM control (and potentially control battery charging speed control based on the charge level) to shut off the battery charging depending on the battery charge rate. Overall circuitry was modeled using PSPICE (image below) to fine tune the charging current and PWM logic. 

![NiCd Battery Charging Design Simulation](NiCd_sim.PNG) 

In the simulation, it is possible to see square wave voltage source representing ATMEGA's PWM pin. As 5V control pin is set high, LM315 supplies 70mA to the load and as soon as 5V is shut off, no current is provided to the load. 

# 2021-03-05 MCU Board PCB Routing 1 <a name= "MCURouting1"></a>

The board is a four layer board with top and bottom signal layers with ground and 5V layer sandwiched in between. This design was chosen due to lots of signals and also power conversion is being processed on the board. Four layer design not only makes the routing simpler but also isolates some noise sources (power signals) from the noise-sensitive signals.

As the deadline for the PCB board review approaches, I tried to finish up general outline of the PCB. The most challenging part about the routing was laying out power components and deciding the trace width. Especially for the LM317, heat generation is an issue. Although not too large of a trace width is required, to ensure heat dissipation, 2mm trace width was chosen considering the length of the trace. In addition, polygon pour was poured for additional heat dissipation.   

# 2021-03-06 MCU Board PCB Routing 2 <a name= "MCURouting2"></a>

Due to the usage of lots of SMD components, via stitching was done. 

# 2021-03-12 Component Ordering Last Minute Edits of the Version 1 <a name= "Order1"></a>

Initial components were selected and order was placed. We realized that lots of components we originally intended to use on design document were out of stock so had to find replacements. Also, FT231 USB to UART chip is out of stock. Therefore, we decided to proceed with our back-up option of using over-the-self USB to UART board and interface with the connector. 

# 2021-03-20 I2C Display Code Progress 1 <a name= "Code1"></a>
 
 I2C display test code was written. To make this functional, Adafruit GFX Graphics library and SSD1306 library are used. Display will need to convey largely two information: Total Harvested Energy by using this device and Battery charge level. Today, battery charge level code was written along with general setup code to write custom messages. On the battery charge level display function, code to control the charging of battery was also written. 
 
----------------------------------------------

I decided to add some of open source kicad parts to complement our PCB design. 

Here are the links to their github: 

[MX Alps library](https://github.com/ai03-2725/MX_Alps_Hybrid)

[USB C library](https://github.com/ai03-2725/Type-C.pretty)

[random keyboard parts library](https://github.com/ai03-2725/random-keyboard-parts.pretty)
