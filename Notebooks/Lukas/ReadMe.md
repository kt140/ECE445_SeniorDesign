# Lukas' Work Log

## Table of contents:
- [Project Proposal](#projectproposal)
- [Design Document Complete](#designdocfull)
- [Design Document Complete](#designdocfull)

# 01/27/2022 - RFA Approved<a name="projectproosal"></a>

## Solution Components:
1. Input: Solar Panel Power Voltage Input (Solar Panels)

    1. Cost effective, efficient, and portable
    2. Commercially available solar panels on digikey are only rated at 1-2 [W], would need to create an array of solar panels to reach 10 [W] on output side
   
2. Synchronous Buck/Boost Converter

    1. Control schema to regulate the power being extracted from the solar panel
    2. Microprocessor creates duty cycle to regulate the intermediate voltage potential in the energy storage unit. The actual energy storage unit will be an off the counter mobile power bank to reduce complexity of a self designed battery.
   
 1. Design of energy transfer process

    1. Need for appropriate voltage regulators to quantify the amount of power received from the solar panel
    2. Current Transducer (CT) and/or regular current sensors can be utilized to monitor that output and the calculations of power consumption will be done on our MCU.
    3. We can store our energy within a small scale power bank (over-the-self portable power bank) that should allow us to keep reserves of the energy.
    4. Stable intermediate voltage potesntial using a custom designed micro controller unit.
3. Secondary DC-DC Converter for several outputs
    1. Use of transformers to provide several different output potential voltages
    2. Analog USB power supply design
   
4. Output: Distribution of different voltage potentials for charging.
    1. Using the rechargeable batteries ordered, we will ensure the output potentials are restricted to the recommended current for charging.



# 01/31/2022 - Researching DC-DC topologies and Battery Safety Precautions <a name="projectproosal"></a>

# 02/03/2022 - Research on MPPT and Cascaded Converters<a name="projectproosal"></a>

# 02/6/2022 - Begin Working on Project Proposal<a name="projectproosal"></a>

# 02/08/2022 - First TA Meeting <a name="projectproposal"></a>

# 02/13/2022 - Solar Panel Research <a name="designdoccheck"></a>

# 02/15/2022 - Purchased ATMEGA328P as the MCU <a name="designdoccheck"></a>


# 02/18/2022 - Second TA Meeting <a name="designdoccheck"></a>

# 02/20/2022 - Solar Panel Inspection <a name="designdoccheck"></a>

# 02/21/2022 - Design Document Check <a name="designdoccheck"></a>

# 02/22/2022 - Design Document Submission #1 <a name="designdoc"></a>


# 02/23/2022 - Design Document Submission #1 <a name="designdoc"></a>


# 02/24/2022 - Design Document Submission #1 <a name="designdoc"></a>

# 02/25/2022 - Weekly TA Meeting <a name="designdoc"></a>


# 02/28/2022 - Heat Sink Considerations <a name="designdoc"></a>


# 03/01/2022 - PCB Review <a name="designdoc"></a>

# 03/02/2022 - Design Document Review <a name="designdoc"></a>

# 03/02/2022 - Setting up Overleaf for Final Report <a name="designdoc"></a>


# 03/04/2022 - Weekly TA Meeting  <a name="designdoc"></a>

# 03/05/2022 - Revisions to Design Document   <a name="designdoc"></a>


# 03/06/2022 - Found new paper with change of topology  <a name="designdoc"></a>


# 03/09/2022 - Completed Transition from GitLab to GitHub  <a name="designdoc"></a>
I have been recording my progress in my own GitLab notebook, which ws shown to our TA during the first TA meeting. Since then, we noticed the course webpage was edited to allow for a GitHub account instead of the GitLab. This entry marks the first time I was successfully able to clone and merge my own repository with my teammates. I am not lsited as a contributor for the project for some reason, but installed GitBash to complete all future Push/Pull requests.

# 03/10/2022 - Team Meeting before spring break       <a name="designdoc"></a>
We met together at the Siebel basement to discuss our schedule for PCB orders. Wonjoon has done the majority of the work for the MCU PCB, but Yei and I have been very indecsive about which topology we want to use. In this meeting, we had Wonjoon give us a full summary of the PCB he designed, while making sure we were explicitly aware of any connectors or signals that needed to be connected to our MPPT Power PCB. This was to ensure that we can correctly route the PWM and feedback signals to the MCU, while separating the power traces from the small signal traces. Furthermore, we had a msicommunication between team members where there are two USB protocols necessary to complete our project. Wonjoon implemented the USB data protocol that allows us to program the MCU, but we have not developed the USB circuitry for 10 W charging. the 10W charging will need to be implemented on the power PCB, to avoid sending a 2 A signal to the MCU board. Currently, Yei and I need to double check the connectors of the Solar Panel in the ECE 445 Lab, finalize the MPPT converter, design an LDO or voltage regualtor for the internal power supply, and formulate how USB charging can be implemented. 

# 03/11/2022 - Finalizing Power Board Schematic with Yei  <a name="designdoc"></a>

After discussing the project with Yei, I realized that we would not be able to meet the Requirements & Verifications (R&V) we wrote in the Design Document without including an energy storage unit. We could not visualize a clear solution for how to simulatnaeouisly extract MPPT and regulate USB charging. It would be unsafe to use an external energy unit ( like a Lithium Ion Battery) to charge a USB device and harness the energy from the solar panel, because we would essentailly be running current directly through the battery and degrading its quality. This requires us to design some circuitry that allows the USB charger to be connected directly to the output of the MPPT DC-DC converter instead of the battery, however, we cannot gaurantee the maximum power point will be found in this sitaution. A PWM solar controller like the 
[SunKeeper](https://www.morningstarcorp.com/products/sunkeeper/ "SunKeeper") provided in lab is commonly used to charge batteries at fixed DC-DC power ratings. Despite eliminating a separate excess energy storage unit from our project, we realized that this was essential to locating the maximum power point. If we do not include this, the MPPT has an upper bound dependent on the USB load, and we may be unsuccesful in compelting the R&Vs outlined in the Design Document. This prohibted us from contiuning on with the power board, until we incorporated some way to store the excess energy with MPPT. 

# 03/12/2022 - TA Meeting and Group Planning <a name="designdoc"></a>
Due to several of our team members having interviews, we met on the first Saturday of Spring Break for our weekly TA meeting. We mainly discussed how to move forward ordering parts and ordering the PCB on our own. We ran into issues with the cost of our board being $133 for 5 copies, which caused us to miss the first PCB deaadline. Since the 3/8 deadline, we have audited the MCU board and placed an order ourselves to make sure it will arrive in time to test and debug. The biggest concern moving forward is finalizing the power board before the second deadline, and making sure all of our parts can be ordered as soon as possible. 

# 03/18/2022 - Research for USB-A Charging  <a name="designdoc"></a>

I have been using some of my freetime ovre spring break to understand how the USB-A Charging protocol will be implemented. 
At first we all thought that it would be controlled through the MCU, due to standard USB-A protocol also containing birediectional data ports. The following image is from 
["The Basics of USB Battery Charging"](https://www.maximintegrated.com/en/design/technical-documents/tutorials/4/4803.html "THE BASICS OF USB BATTERY CHARGING"), which shows the four input ports for typical USB communication. 
![](images_markdown/Regular-USB-Ports.PNG)
For our project, we do not want to send any data to the USB device connected as a load, which allows us to eliminate the need for both of the data lines D+ and D-. This can be done by connecting the D+ and D- lines together via a resistor. The resistance must be R $\leq 200 \ \Omega$, and this mode is referred to as a Designated Charging Port (DCP). A clear illustration of this is given Figure 10 of the [TPS2514 DATASHEET](https://www.ti.com/lit/ds/symlink/tps2513.pdf?ts=1647718862163&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTPS2513 "TPS2514 DATASHEET"). 

![](images_markdown/DCP-short-mode.PNG)

This allows the device to bypass the USB communication protocol, and directly connect to the internal battery. We can further ensure that the external USB device is recieving the correct power, by manipulating the voltage potential on either of the D- or D+ lines. The Divider 2 charging scheme is used for
10-W adapters, and applies 2.7 V on the D+ line and 2 V is applied on the D– line, as show below. Fortunately, the TPS2513 is in stock on [Digikey](https://www.digikey.com/en/products/detail/texas-instruments/TPS2513ADBVR/4494483#mktPlaceViewSection "Digikey"), and configures these two lines for us. This drastically simplifies the amount of work required to configure the USB port, where the TPS2513 automatically detects the power requirement of the input usb port. This further matches the simple Female USB connectors available [here](https://www.digikey.com/en/products/detail/sparkfun-electronics/BOB-12700/5762450?utm_adgroup=Adapter%2C%20Breakout%20Boards&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Prototyping%2C%20Fabrication%20Products&utm_term=&utm_content=Adapter%2C%20Breakout%20Boards&gclid=CjwKCAjw_tWRBhAwEiwALxFPobpQSucNdZ-V3F0eN1F23PQx7BZaxLHDijavc5yAr-V-B6fmEHjo6BoCjKIQAvD_BwE "here").



![](images_markdown/DCP-10W.PNG)


![](images_markdown/Ideal-DCP-config.PNG)

If this does not work, there is also the option of buying a premade board to do this for us, and simply interface [this board](https://www.seeedstudio.com/Lipo-Rider-Plus-p-4204.html?gclid=CjwKCAjw_tWRBhAwEiwALxFPoR--l6bB3jGPfZKoGkSbGB3EaNlgAs9KFKoq4bSAiMn4nbsBqeK3YBoCO0kQAvD_BwE "this board") with MPPT. 