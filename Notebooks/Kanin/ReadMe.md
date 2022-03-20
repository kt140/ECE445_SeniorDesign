# Kanin's Work Log

## Table of contents:
- [Design Document Check](#designdoccheck)
- [Design Document Complete](#designdocfull)
- [Initial PCB Design](#initialPCB)

# 02/21/2022 - Design Document Check <a name="designdoccheck"></a>

Presented in class during that presentation. Talked about our overall design and our verification points within our design document. The main feedback that we got from this session was that we needed to improve our overall detail of our design document. More specifically, we wanted to make sure that we make all of our requirements and verifications as quantitative as much as possible. This meant including different tolerances and calculations. Additionally we needed to make sure that our overall format was presentable and easy to read.

# 02/24/2022 - Completed simulations for Design Document<a name="designdocfull"></a>

During this time, I was able to find a research paper that was published regarding the voltage regulation of a MPPT converter when connected to the grid. This paper provides useful insight into the feasibility of our design, essentially verifying that our MPPT must utilize either a buck or a boost converter. The link to the paper can be referenced [here](https://www.sciencedirect.com/science/article/pii/S0378779618304085?via%3Dihub).

Utilized LTSpice to simulate our Buck converter that is being cascaded together with our Buck-Boost converter. During this time, I was able to simulate how the duty cycle affects our overall output ripple voltage. This allows us to essentially control and utilize. 

We can see this simulation result from the images below:

![](../Simulation/output-buck-mppt-buck-boost.png)

![](../../Simulation/output-zener-diode-voltage-regulator.png)

Points to note with these are that we still have significant ringing for our output voltages. What this means for our project is that we must find additional ways to limit our output voltage and make sure that we fall within the bounds of 2% that we set.

# 03/12/2022 - Initial PCB design<a name="initialPCB"></a>

During this time, I managed to initiate the first power side PCB. After deliberation during the meeting, we finalized that upon the power side we would need to connect our load directly from our solar cell. With that in mind, we would need to create a separate interleaved buck converter circuit that would allow us to directly. We would also need to use the solar cell to power a separate 7 V input to the MCU as designed by Wonjoon. This involved the use of the chip LM5009 (the datasheet can be referenced [here](../../Resources/LM5009_datasheet.pdf)). This allows us to take a variable input voltage and step that down to exactly 7 V depending upon the ratios of our input resistors. The issues with this is we actually have not created a way to implement the thermal shutdown circuit which protects the chip from being destroyed.

# 03/16/2022 - 03/18/2022 - Reiteration for 7 V operation of our MCU

Some of the issues that came about from the initial PCB design is that the current output of the LM5009 is 150 mA which is not enough current to power our MCU subsystem. As a result, we needed to implement a different solution. During the initial stages, I believed that amplifying our current using a current amplifier. However this would require us to utilize a second voltage source to power the operational amplifier. The topology used can be referenced using [this](https://electronics.stackexchange.com/questions/228148/how-to-design-current-amplifier-circuit-to-amplify-the-signal-current-to-1a).

Without the current amplifier as a viable solution, we needed to quickly pivot away from this idea. The solution that was eventually decided was to utilize a LM2575 adjustable output buck regulator as it is rated for 1 A operation on the output side. During this time we looked at two companies, Microchip and Renesas, and they had options to request for free samples. Ultimately I decided to go with Microchip as they have an option to request for free samples. As a contingency plan, I've also requested free samples from both companies.

