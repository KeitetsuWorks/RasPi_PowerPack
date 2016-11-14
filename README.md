Model Railway Power Pack using Raspberry Pi
========

## Description

Model Railway Power Pack using Raspberry Pi.


## Demo


## Requirement

### Hardware

* [Raspberry Pi](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)

### Software

* [Raspbian](https://www.raspberrypi.org/downloads/raspbian/)
* [WiringPi](http://wiringpi.com/)


## Circuit


## Usage

* Must be root to run `RasPi_PowerPack`.

        $ sudo ./bin/RasPi_PowerPack

* See the help list to get optional usage.

        $ ./bin/RasPi_PowerPack --help


## Installation

1. Download and Install WiringPi

        $ git clone git://git.drogon.net/wiringPi
        $ cd wiringPi
        $ ./build
        $ gpio -v

2. Download and Compile RasPi_PowerPack

        $ git clone https://github.com/KeitetsuWorks/RasPi_PowerPack.git
        $ cd RasPi_PowerPack
        $ make
        $ ./bin/RasPi_PowerPack --version

After that you can find `RasPi_PowerPack` under the `./bin/` directory.


## Blog


## License

* MIT

