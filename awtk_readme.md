# AWTK SmartWatch sample application for nRF Connect SDK

This smartwatch demo is a lightweight version of AWTK SmartWatch demo.

## Hardware

The sample requires the following boards.
* nRF52840 DK

    https://www.nordicsemi.com/Software-and-Tools/Development-Kits/nRF52840-DK
* Adafruit 2.8" TFT Touch Shield

    https://www.adafruit.com/product/1947

Plug the Adafruit shield to the Arduino header on nRF52840 DK.

## Firmware

This repo is based on NCS v1.3.0. Put the sample application to the nrf repo.

The nrf repo west.yml is modified to bring in a AWTK library module.

## Building and running

At the root of nrf repo, build the AWTK sample and flash the nRF52840 DK.
```
west build -b nrf52840dk_nrf52840 samples/smartwatch
west flash
```

## Power up

On power up, Adafruit shield circuitry resets ILI9341. The reset process takes time and nRF52840 may be too early to send LCD data. It results in a blank screen display. In this case, you may need to press reset button on DK.

## Overclocking

ILI9341 LCD driver datasheet states the fastest clock is 10MHz. For a faster display output, this demo is driving SPI at 32MHz. On a side note, nrfx_spim sets GPIO to high current drive for 32MHz SPI clock.
