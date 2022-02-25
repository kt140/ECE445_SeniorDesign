# Kanin's Work Log

## Table of contents:
- [Design Document Check](#designdoccheck)
- [Design Document Complete](#designdocfull)

# 02/21/2022 - Design Document Check <a name="designdoccheck"></a>

Presented in class during that presentation. Talked about our overall design and our verification points within our design document. The main feedback that we got from this session was that we needed to improve our overall detail of our design document. More specifically, we wanted to make sure that we make all of our requirements and verifications as quantitative as much as possible. This meant including different tolerances and calculations. Additionally we needed to make sure that our overall format was presentable and easy to read.

# 02/24/2022 - Completed simulations for Design Document<a name="designdocfull"></a>

During this time, I was able to find a research paper that was published regarding the voltage regulation of a MPPT converter when connected to the grid. This paper provides useful insight into the feasibility of our design, essentially verifying that our MPPT must utilize either a buck or a boost converter. The link to the paper can be referenced [here](https://www.sciencedirect.com/science/article/pii/S0378779618304085?via%3Dihub).

Utilized LTSpice to simulate our Buck converter that is being cascaded together with our Buck-Boost converter. During this time, I was able to simulate how the duty cycle affects our overall output ripple voltage. This allows us to essentially control and utilize. 

We can see this simulation result from the images below:

![](../../Simulation/output-buck-mppt-buck-boost.png)

![](../../Simulation/output-zener-diode-voltage-regulator.png)

Points to note with these are that we still have significant ringing for our output voltages. What this means for our project is that we must find additional ways to limit our output voltage and make sure that we fall within the bounds of 2% that we set.


