
# ESP32 RFM69HCW / RFM95/96/97/98(W) Gateway

The purpose of this gateway is to either:

- connect a RFM69-based network to Wi-Fi
- connect a LoRa&trade; transceiver to Wi-Fi

The gateway was designed for power efficiency without sacrificing functionality.

**Status:** (*this is work in progress !*)

## Features

- the core is a ESP32-WROOM-32x Wi-Fi+BT+BLE module
- RFM69HCW or RFM95/96/97/98(W) module
- Li-Ion / Li-Polymer battery charger
- Li-Ion / Li-Polymer backup battery with 18650 or 14500 sockets
- high efficiency synchronous buck converter
- supply voltage supervisor
- 4 LEDs for status
- humidity and temperature sensor
- placeholder for ATSHA204A, ATECC508A or ATECC608A IC
- (*optional*) boot mode selection using DTR and RTS signal

## Software

The code dedicated to this board is not yet built.

## Development Environment

Operating system is [Debian](https://www.debian.org/)

Tools:

- [KiCad EDA](http://kicad-pcb.org/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Espressif IoT Development Framework](https://github.com/espressif/esp-idf)
- [Git](https://git-scm.com/)
- [GIMP](https://www.gimp.org/)
- [Inkscape](https://inkscape.org/en/)

## Versions

### Version 1

- *Fab* files are moved to the Fab-v1 directory
- The PCBs from SeeedStudio arrived
- Most components are sourced
- I should build some boards
- I should start to write some software

## License

The software and documentation are released under the [GNU GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) License. See the __LICENSE-GPLv3.txt__ file.

The hardware schematics are licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).
See the __LICENSE-CC-BY-SA-4.0.txt__ file.

## About RFM modules

### RFM69

From it's datasheet:

*The RFM69HCW is a transceiver module capable of operation over a wide frequency range, including the 315,433,868 and 915MHz license-free ISM (Industry Scientific and Medical) frequency bands.*

*All major RF communication parameters are programmable and most of them can be dynamically set. The RFM69HCW offers the unique advantage of programmable narrow-band and wide- band communication modes.*

*The RFM69HCW is optimized for low power consumption while offering high RF output power and channelized operation. Compliance ETSI and FCC regulations.*

### RFM95/96/97/98(W)

From it's datasheet:

*The RFM95/96/97/98(W) incorporates the LoRa TM spread spectrum modem which is capable of achieving significantly longer range than existing systems based on FSK or OOK modulation.*

*[...] Another benefit of the spread modulation is that each spreading factor is orthogonal - thus multiple transmitted signals can occupy the same channel without interfering. This also permits simple coexistence with existing FSK based systems.*

*Standard GFSK, FSK, OOK, and GMSK modulation is also provided to allow compatibility with existing systems or standards such as wireless MBUS and IEEE 802.15.4g.*
