# Andrew Table of Contents
* [references](#references)
* [First meeting with TA](#Firstmeeting)
* [keyboard PCB design initial progress](#keyboard1)
* [keyboard PCB design (finished schematic)](#keyboard2)
* [Keyboard parts](#keyboard3)
* [initial Keyboard Board design](#keyboard4)
* [Keyboard Board design completed](#keyboard5)
* [Initial software setup/testing](#software1)
* [soldering the keyboard PCB](#keyboard6)
* [wrap up soldering and programming the MCU](#keyboard7)
* [programming the MCU 2](#keyboard8)
* [programming the MCU 3](#keyboard9)
* [programming the MCU 4](#keyboard10)
* [debugging the keyboard 1](#debug1)
* [debugging the keyboard 2](#debug2)
* [plover installation](#plover)
* [practicing stenography](#plover2)
# references <a name= "references"></a>
https://github.com/ai03-2725/MX_Alps_Hybrid
https://github.com/ai03-2725/Type-C.pretty
https://github.com/ai03-2725/random-keyboard-parts.pretty
https://bgaudioclub.org/uploads/docs/Crystal_Oscillator_Circuits_Krieger_Matthys.pdf
http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Summary.pdf
https://learn.sparkfun.com/tutorials/beginners-guide-to-kicad/all
https://www.reddit.com/r/MechanicalKeyboards/wiki/switch_suppliers#wiki_diodes
https://www.openstenoproject.org/plover/
https://github.com/qmk/qmk_toolbox/releases
https://wiki.ai03.com/books/pcb-design/chapter/pcb-designer-guide


# 2021-09-14 First meeting with TA <a name= "Firstmeeting"></a>

Our team had our first meeting with the assigned TA to discuss about our Project direction. We also got our proposal checked to make sure it includes what it should.

# 2021-09-16 started PCB design for the keyboard.<a name= "keyboard1"></a>

Below is the picture of the schematic of the keyboard that we started designing. I added the ATMEGA32U4 microcontroller and placed the crystal which tells the microcontroller how fast it should run. Then, I added decoupling capacitors to help it from accumulating too much noise. 

----------------------------------------------
![keyboard](Notebooks/Andrew/keyboard1.PNG)

__Initial keyboard Schematic__

----------------------------------------------

I decided to add some of open source kicad parts to complement our PCB design. 

Here are the links to their github: 

[MX Alps library](https://github.com/ai03-2725/MX_Alps_Hybrid)

[USB C library](https://github.com/ai03-2725/Type-C.pretty)

[random keyboard parts library](https://github.com/ai03-2725/random-keyboard-parts.pretty)

# 2021-09-22 finished PCB schematic for the keyboard<a name= "keyboard2"></a>

I finished the schematic for the keyboard. Added a 2 by 11 matrix to represent the 22 switches for the keyboard. 

We started working on the design document for the review session next week.

----------------------------------------------
![keyboard](Notebooks/Andrew/keyboard2.PNG)

__Initial keyboard Schematic__

----------------------------------------------
I decided to use Atmega32U4 as the Microcontroller chip unit. This is the iconic MCU for keyboards. The design uses an USB-C connector and a protection circuit to prevent electro-static discharges that destroy the keyboard electronics. I created a new kicad project and opened my schematic file to start placing labels and wires to keyboard components.

**MCU**

The MCU was very easy to wire:
- VCC, AVCC, UVCC are connected to the +5V power symbol
- VBUS should be connected to +5V as well. This is used by the MCU to monitor if the keyboard is connected or disconnected from the USB port. From looking at the datasheet, the MCU requires it to be connected to a 10uF capacitor.
- GND and UGND are connected to the GND power symbol
- Most of the other data pins are connected to the row and columns of the matrix that will be created. Unused pins are present with X.

I realized that the MCU can work without a crystal (has builtin clock generation) but I thought it would be a better idea to provide an external clock via crystal oscillator. This specific resonator will produce a square signal at 16MHz. When powered with +5V the MCU can run at 16MHz.

The next thing is to wire HWB to GND with a pull down resistor to ensure the MCU to boot with the boot-loader. 

The UCAP is the internal USB pins voltage regulator, it has to be connected to a 1uF capacitor referencing the chip datasheet.

The datasheet recommends every +5V pins of the MCU to have decoupling capacitors. This is quite important as if the component starts to draw current when it's running, the voltage of the power source will drop, which causes many problems for other components sharing the same power source. There are 4 VCC pins on the chip. (2*(AVCC, UVCC) and 2*VCC) so we would need 5 0.1uF capacitor and one 10uF for VBUS but in practice we can share the 10uF capacitor for both VBUS and UVCC. 

![keyboard](Notebooks/Andrew/keyboard5.PNG)

**ISP header**

To program our MCU, we need to access the Serial Peripheral Interface programming interface and use the ISP programming mode and this cannot be done with USB port.

I then added a reset circuit to mcu and the USB c connector. 
 
**USB Connector**
An USB-C connector has 2 by 2 USB 2.0 signal wires which are D+ and D-. I connected those together with 22 ohms resistor as the MCU datasheet suggests. Then, i wired borth GND and the shield together, then both the VBUS pins.

To protect from the +5V against current surge, i added a polyfuse_small to VCC and 5V.

Next, I added the ESD protection system by adding PRTR5VoU2X.

The complete picture of this section looks like following:

![keyboard](Notebooks/Andrew/keyboard6.PNG)

** The Matrix**

I designed our key cell by adding a SW_PUSH and a regular diode then formed a matrix of 4 by 11 which somewhat resembles the stenographic keyboards layout.

# 2021-09-25 choosing the keyboard parts <a name= "keyboard3"></a>

The numbers on the right indicates the quantities needed for the pcb. I orderer a few more than I needed just because the shipping takes a lot of time and in case, I end up breaking some of the parts. 

Microcontroller: https://www.digikey.com/short/znvnmm
1

Diodes: https://lcsc.com/product-detail/Switching-Diode_MCC-Micro-Commercial-Components-1N4148W-TP_C77978.html
38

techfuse: https://lcsc.com/product-detail/PTC-Resettable-Fuses_TECHFUSE-nSMD025-24V_C70069.html
10

Crystal: https://www.digikey.com/short/znvn0z
1

22pF Capacitors: https://www.digikey.com/short/znvn8b
2

0.1uF Capacitors: https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B104KBFNNNE/3889266
4

1uF Capacitors: https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B105KAFNFNE/3891012
1

10uF Capacitors: https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B106KOQNNNG/5958100
1

22 Ohm Resistors: https://www.digikey.com/en/products/detail/vishay-dale/CRCW080522R0FKEAC/7928834
2

10k Ohm Resistors: https://www.digikey.com/short/znvr47
2

5.1k ohm Resistors: https://www.digikey.com/short/znvrmt
2

PRTR5V0U2X: https://lcsc.com/product-detail/Diodes-ESD_Nexperia-PRTR5V0U2X-215_C12333.html
1

Ferrite bead: https://lcsc.com/product-detail/Ferrite-Beads_Murata-Electronics-BLM21PG600SN1D_C18305.html
1

Button: https://www.digikey.com/short/znvnb2
1

USB C Connector: \https://lcsc.com/product-detail/USB-Type-C_Korean-Hroparts-Elec-TYPE-C-31-M-12_C165948.html
1

# 2021-09-27 initial keyboard design in board layout <a name= "keyboard4"></a>
After completing the keyboard schematic, next was to create a PCBnew for it. I assigned footprints to the components that i found and rearranged the footprints to be located where i want them to be from what was initially a clutter of parts at the center.

After the relocation, i started routing the rows and columns of the key matrix and cut the edges to represent my PCB border.


# 2021-10-05 Completed the keyboard design <a name= "keyboard5"></a>

After routing the columns and the rows, I looked into the D+ and D- USB data lines form which is called a differential pair. The idea is to send a complement signal to two wires instead of on one. I realized that the differential pairs needs to be routed carefully because the noise will affect both wire the same way.

First was to respect the symmetry.

![keyboard](Notebooks/Andrew/keyboard4.PNG)

The noise cancelling advantage of a differential pair would only come in effect if both of the signals arrive at the same time at the endpoints of the wires. If the traces have varying lengths, one will arrive later than the other negating this effect. However, there is some tolerance and it is ok to have a few centimeters of difference in length assuming the USB full speed standard at 12 Mbits/s.

I also had to consider minimizing the number of via because each via adds inductance to the trace. There are also other rules of thumb which had to be taken in consideration when wiring the differential pair such as the spacing around differential pairs, return current, not routing close to crystals, crossing a differential pair, not using striplines, avoiding u-turns and the list goes on.

Next was routing the crystal oscillator which was also relatively easy as there are few tracks and components. There were couple of rule of thumbs that i had to keep in mind while routing which were to have the XTAL1 and XTAL2 traces as short as possible, to space other signals as much as possible to prevent the clock noise to be coupled with other traces.

Next was routing the power rails, I wired the USB type c power traces. Then i routed the +5V down to the MCU.

I decided to make a little change to the design which now has 38 keys of 4 rows and 11 columns with the last row only containing 5 columns, reason being besides the keyboard performing stenography, I felt we needed to add more keys to fully take control of the user interface of the device i.e. switching between TTS to STT and vice versa, running our scripts from bootup. I also added a ferrite bead which is a kind of a lowpass filter. The purpose of this is to filter out the high freuency noise that could couple with the USB shield before it reaches the USB GND or couples to the datalines.

Lastly, i connected the reset button and the ISP header. 

The final result of the PCB looks as the following picture:

![keyboard](Notebooks/Andrew/keyboard3.PNG)

# 2021-10-13 Initial software setup/testing<a name= "software1"></a>
 our raspberry pi and SD card have finally arrived and we can start testing out the libraries that we've explored while waiting for the items to deliver. Since I am still waiting for the Keyboard PCB and the components to arrive to solder, I have shifted my focus in the project from hardware to software which is what will be on the pi at the time of device performance. 

 The very first thing that I had to do with PI was to download an operating system on it which wasn'g big of a hassle with many guides online as pi is a popular choice with many personal projects out there.
 The referenced guide in this case was: https://www.youtube.com/watch?v=ntaXWS8Lk34


 The first option of TTS libraries I explored was the pyttsx3 which required no internet and was a python library. It has no limits in English words meaning it could convert just about anything in English sentences in to speech without delays, and the inclusion of the library did not intoduce many lines of code i.e. the execution code was simple enough too as can be seen in the image below.

 ![software1](Notebooks/Andrew/software1.jpg)

 The only real problem with pyttsx3 library was the quality of sound/pronunciation with the voice speaking the text. We believed this library would work just fine when we have tested on our windows laptop which we later realized had a different voice because it was using the windows built in narrator voice token. The microsoft's narraotr voice token is something that we cannot take advantages of with raspberry pi so i decided to put a hold on testing this library and started to look for an alternative TTS library or another way to play different voice with pyttsx3 library.

 An example of pyttsx3 library in work: https://www.youtube.com/watch?v=wTuWzjIxtJU

# 2021-10-20 soldering the keyboard PCB<a name= "keyboard6"></a>
![keyboard](Notebooks/Andrew/keyboard7.jpg)

The keyboard PCB has finally arrived at ECEB and I could start soldering the components on the board. The SMD componenets that go on the board have already arrived before the PCB so i could get started right away with soldering. The 0805 was small but not too small to make handsoldering experience difficult. The only really difficult part today was soldering the USB C port which had a lot of data lines and power lines closely located next to each other that i had to be extra careful to make sure there is no overlapped solder across neighboring pads. Taking advantages of the soldering assignment i did earlier in the course, i applied flux and used the microscope to double check that it is good to go. 

I have soldered 38 diodes, resistors, capacitors and USB port today. Remaining parts to solder are: crystal oscillator, microcontroller(which has not arrived yet) and Ferrite bead.

# 2021-10-24 wrap up soldering and programming the MCU<a name= "keyboard7"></a>
MCU arrived. I wrapped up the soldering of remaining parts which are including the MCU, ferrite bead, and crystal oscillator.

![keyboard](Notebooks/Andrew/keyboard12.jpg)

For programming the MCU, I had to an extensive search online to learn about how to actually program the MCU to work like a keyboard. Following couple of guides and referencing some of DIY keyboard blogs and reddit posts, I decided to use the QMK, Quantum Mechanical Keyboard, an open source community's well established firmware to program my MCU.

link to their git repository: https://github.com/qmk/qmk_firmware 

and link to their set up guide for getting started: https://docs.qmk.fm/#/newbs_getting_started

Being a MacOS user, i had to install homebrew on my device to get started and the magice one line command to install qmk firmware using homebrew: "brew install qmk/qmk/qmk"

After that, i had to run QMK Setup in my terminal with: "qmk setup"
which poped up a bunch of questions that i could say yes or no to for the configuration of qmk. i pressed y to answer all of them as is suggested in the qmk setup documentation.

The environment to program qmk should be set at this point but i tested by build environment by building the keyboard's default keymap with the command:
"qmk compile -kb <keyboard> -km default"
where keyboard is any keyboard in the qmk firmware, for example like a rev3.

I knew my set up was alright after i saw messages like: 
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)

 This told me that using my qmk setup, i could compile one of the keyboard's keymap completely and generated a .hex file which then can later be flashed the MCU on the controller using the qmk toolbox.

The installation github repository to qmk toolbox is: https://github.com/qmk/qmk_toolbox/releases

# 2021-10-30  programming the MCU2<a name= "keyboard8"></a>
Following the documentation from qmk, to create my own keymap i had to create a copy of the default keymap from qmk. The command to do so is: qmk new-keymap -kb <steno>

I named the keyboard name as steno to reflect the functionality of what i am about to program.

The following list of files are now created in the directory:
steno/config.h
steno/info.json
steno/keymaps/default/keymap.c
steno/keymaps/steno/keymap.c
steno/readme.md
steno/rules.mk
steno/steno.c
steno/steno.h

I needed to edit those files in order to map the hardware and the keyboard switch matrix i created. 

The first one to edit was the config.h file in which i am defining the number of rows, columns and the corresponding pins on the MCU that i am using.

Reffering back to the schematics, i could figure out which pins are associated with which rows, which columns and are unused.

![keyboard](Notebooks/Andrew/keyboard13.jpg)

Here is an excerpt from the config.h 

![keyboard](Notebooks/Andrew/keyboard8.PNG)

Next edit was in the rules.mk where i tell the qmk firmware about the MCU. For the variables listed in this
file, for any of the feature that my keyboard is not using, i assigned the value to no and otherwise yes.

![keyboard](Notebooks/Andrew/keyboard9.PNG)

1. I set the MCU variable to equal to atmega32u4 which is the microcontroller i am using for the keyboard

2. I set the BOOTLOADER to atmel-dfu.

3. BOOTMAGIC_ENABLE is the virtual DIP switch which i don't really need since i have a physical reset button
on the pcb but in case i need it in the future after i put an enclosure, i enabled it.

4. Again EXTRAKEY_ENABLE allows for audio control and system control which are the features i wouldn't need for this keyboard but i've set it to be enabled because it doesn't hurt to do so. 

5. For other features that i knew that i wouldn't absolutely need in the future, i disabled them by setting the corresponding variables to no.

# 2021-11-02  programming the MCU 3<a name= "keyboard9"></a>

Continuing from what I left off last time with coding, the next edit was made in the steno.h header fie where i finally define the layout key to matrix position mapping. 

![keyboard](Notebooks/Andrew/keyboard10.PNG)

Here, the LAYOUT consists of four rows and 11 columns which is how my custom steno keyboard is designed to have. Each row at the end is separated with the new line character "\" to tell the compiler that whatever comes after it is on the next row. 

The keys are labelled as KXY where X is the row number that the key is in and Y is the column number that the key is in.

The KCNO label in the LAYOUT is to tell that there is nothing there to be tracked. (my keyboard only has 5 keys in the last row)

Last but not least, I edited the keymap.c under keymaps/steno directory i created. 

![keyboard](Notebooks/Andrew/keyboard11.PNG)

Here is where i actually assign the keycodes associated with each key on the matrix. 
Depending on the set keycode i put in the specific row and column of the LAYOUT, the keyboard will produce
different character with the key presses. If I've wanted to change what my keypresses produce, this is the place i would come back later and modify and compile again and flash the MCU to make the change.

The file essentially defines keycodes for two layers one is _BASE which stands for the base keymap and the _FN which is the second layer which can be used while a function key is being pressed.

For the purpose of this project and considering the compactness of the keyboard, i did not define any keys in the _FN layer as is unneccessary. I did so by putting ____ in the position for each key in that layer as that tells the qmk that i am leaving that key empty in that layer.

I had to refer to the basic keycodes from this table given from the qmk website.

link: https://docs.qmk.fm/#/keycodes_basic

Finally, I am building the firmware.

![keyboard](Notebooks/Andrew/keyboard14.JPG)

This, as mentioned before, generates a .hex file in the qmk_firmware directory which i will later flash the MCU with qmk toolbox.

# 2021-11-04  programming the MCU 4<a name= "keyboard10"></a>

The only and final thing left to do was flashing the MCU with the created .hex file that contains every information necessary for the MCU to do what I want with it to act like a keyboard. 

However, i was faced with a problem which was that my pcb was not being recognized by the os through the USB connection. I had no clue why and while trying to troubleshoot, i ended up breaking the PCB pads for the USB port and had to go back and do the soldering again from the beginning on a new PCB, desoldering from the old and soldering again on the new. 

After that I was able to fix the error that said: device not recognized device descriptor request failed which oddly enough did not happen with the new soldered pcb. I am suspecting that maybe i did not put enough solder on one of the pins of the MCU. Ironically, what seemed like a stepback solved the issue. 

Finally onto flashing, the toolbox was able to recognize my MCU and all seemed good and after flashing, i tested by connecting the keyboard to a computer and started pressing each keys but surprisingly i wasn't getting the right characters that i wanted and each key press either did nothing or output a random character that the key was supposed to be not associated with. 

After a rigorous search online, one of the posts i found suggested to someone of similar issue to do a clear eeprom for reasons that i did not understand but magically fixed my issue as well. 

The link to the post: https://www.keebtalk.com/t/keys-messed-up-all-of-the-sudden/7562

The qmk toolbox window

![keyboard](Notebooks/Andrew/keyboard15.JPG)

# 2021-11-07  debugging the keyboard 1 <a name= "debug1"></a>

Although the keyboard when connected to my computer does work and display characters of my key choice, it had some stability issue which was that if the position of the keyboard were to be changed a little the keyboard would lose connection would not work any longer unless I reconnection the cable to the port. Now this was very critical as the keyboard would be attached to the belt to be worn and is meant to be used outdoor with the user walking around. I almost immediately suspected that the problem stems from the usb port whether it was the soldering of the pads or the port itself. 

All I had to do was replace the usb port to a new one on the pcb and it fixed the stability issue.

# 2021-11-15  debugging the keyboard 2 <a name= "debug2"></a>

Now I have finished the software and hardware side of the steno keyboard and is relatively easy to remap the keys to any character I want. I looked at the open source stenography software plover which we will use in our pi to get stenography running. 

![debug](Notebooks/Andrew/debug2.png)

This is the stenographic keyboard layout from the plover webpage. The bolded characters are the steno alphabets which plover will convert from the characters on top of the same key. For example, once plover is turned on, pressing Q,W,E,R would display corresponding words associated with S,T,P,H in stenography.

In order to reflect plover usage and with our device user interface, the final layout of the keyboard looks like the following:

![debug2](Notebooks/Andrew/debug3.jpg)

where F1,F2 are used to switch between the STT mode and TTS mode, ENT (enter) is used to sound what the user typed in, BSPACE(backspace) for any typos, LALT(alt),LCTL(Ctrl),LSHIFT(shift),TAB(tab),ESCAPE(ESC) to open the terminal and run our User Interface python script. The reason I have the rest of the keys in the second row and the next are self-explanatory from the layout picture above.

# 2021-11-17  plover installation <a name= "plover"></a>

Now was the time to actually install plover on our control module, raspberry pi so that when the keyboard is connected, the users can have real time conversation with any interactor. The installation process was not easy although the plover website had a very organized instructions and files necessary to complete because we are using raspberry pi os instead of MacOs, windows or Linux. So I had some of compatibility issues with installation which wasn't able to run the GUI for plover to enable stenography.

I ended up contacting one of the developers of plover through their discord channel. The problem was there are a number of issues with pi OS that makes the installation a little complicated such as outdated packages, missing python metadata for the distribution provided PyQt5 package, no PyQt5 wheel in the custom PyPI index of pi OS and many more. 

Consequently, I had to run the following .txt script with ./pi_install_plover.txt to safely install plover.

Here is the contents of the pi_install_plover.txt file:
"---------------------------------------------------------------------------------------------"
#!/bin/bash

set -ex -o pipefail

package_deps=(
  python3-appdirs
  python3-cmarkgfm
  python3-dbus # Current version is missing proper metadata.
  python3-dev
  python3-pip
  python3-pkginfo
  python3-pygments
  python3-pyqt5 # Same as above.
  python3-pyqt5.qtsvg
  python3-readme-renderer
  python3-requests
  python3-requests-cache
  python3-requests-futures
  python3-serial
  python3-setuptools
  python3-wcwidth
  python3-wheel
  python3-xlib
)

# Install package dependencies.
sudo apt-get update
sudo apt-get install ${package_deps[@]}

# Check if python3-pyqt5 includes the necessary metadata, manually patch it if not.
if ! dpkg --listfiles python3-pyqt5 | grep -q '\.\(egg\|dist\)-info$'
then
  tmpdir="$(mktemp -d)"
  trap 'rm -rf "$tmpdir"' EXIT
  (
    cd "$tmpdir"
    apt-get download python3-pyqt5
    deb="$(echo -n python3-pyqt5*.deb)"
    pyqt5_version="$(dpkg-deb --field "$deb" Version | sed -n '/^\([0-9]\+\(\.[0-9]\+\)*\)\(+.*\)$/{s//\1/p;Q0};Q1')"
    ar x "$deb" data.tar.xz
    xz -d data.tar.xz
    tar tf data.tar | grep -Fqx ./usr/lib/python3/dist-packages/
    mkdir dist-info
    cat >dist-info/METADATA <<EOF
Metadata-Version: 2.1
Name: PyQt5
Version: $pyqt5_version
Requires-Python: >=3.6
Summary: Python bindings for the Qt cross platform application toolkit
Home-Page: https://www.riverbankcomputing.com/software/pyqt/
Author: Riverbank Computing Limited
Author-Email: info@riverbankcomputing.com
License: GPL v3

PyQt5 - Comprehensive Python Bindings for Qt v5
EOF
    tar rf data.tar --transform="s,^,./usr/lib/python3/dist-packages/PyQt5-$pyqt5_version.," dist-info/
    xz -0 data.tar
    ar r "$deb" data.tar.xz
    sudo dpkg -i "$deb"
  )
fi

# Ensure pip / setuptools / wheel are up-to-date.
python3 -m pip install --user --upgrade pip setuptools wheel

# Install Plover and the plugins manager.
python3 -m pip install --user --upgrade --only-binary=plover --find-links 'https://github.com/openstenoproject/plover/releases/continuous' 'plover[gui_qt]>=4.0.0.dev10' 'plover_plugins_manager'
"---------------------------------------------------------------------------------------------"

Now I am able to run plover on pi with just typing "plover" in the terminal.

source: https://github.com/openstenoproject/plover/discussions/1430

# 2021-11-23  practicing stenography <a name= "plover2"></a>

Plover GUI conveniently default comes with a stenography dictionary as well as a lookup table for users to search what word he wants to type and it will tell us the keypresses to type the word. My practice environment looks like following:

![practice](Notebooks/Andrew/practice.jpg)

I have the keyboard layout top left, notes to record associated keypresses and what word it translates to on the right and the lookup table on bottom left.

To sum up the Notebook, here is the final picture of the stenokeyboard, which is one of the three major component of our device that I worked on throughout this semester.

![practice](Notebooks/Andrew/final.jpg)