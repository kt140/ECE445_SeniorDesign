# Kanin's Work Log

## 02-24-2022 - Completed simulations for Design Document

During this time, I was able to find a research paper that was published regarding the voltage regulation of a MPPT converter when connected to the grid. This paper provides useful insight into the feasibility of our design, essentially verifying that our design 

Utilized LTSpice to simulate our Buck converter that is being cascaded together with our Buck-Boost converter. During this time, I was able to simulate how the duty cycle affects our overall output ripple voltage. This allows us to essentially control and utilize. 

We can see this simulation result from the images below:

![](../../Simulation/output-buck-mppt-buck-boost.png)

![](../../Simulation/output-zener-diode-voltage-regulator.png)

Points to note with these are that we still have significant ringing for our output voltages. What this means for our project is that we must find additional ways to limit our output voltage and make sure that we fall within the bounds of 2% that we set.


