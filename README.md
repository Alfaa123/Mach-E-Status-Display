# Project Overview
This project's goal is to create a simple dashboard for my car, a 2021 Ford Mustang Mach-E GT. This dashboard will show lots of information that is normally hidden behind the scan tool interface, but it nevertheless very interesting to see while the car is in operation.

# Hardware
This project uses a single Waveshare ESP32-S3-LCD-4 (available [here](https://www.waveshare.com/esp32-s3-touch-lcd-4.htm)). This is a great purpose-built LCD display that is perfect for in-car applications because of the following properties:

 - It has a wide input voltage range of 7-36 vdc, meaning it can be powered directly by the car's electrical system without any extra voltage regulation
 - It has a built-in hardware CAN interface, which absolutely necessary when interfacing with a vehicle's CAN bus system (no more missed frames a-la MCP2515). By default, this setup in interrupt mode with adjustable size buffers that can be tuned for your application.
 - The ESP32-S3 is an extremely powerful 240mhz 32-bit dual-core microcontroller. This enables the ability to run the display task on a separate core from the communication tasks and truly multitask.
 - By default, the ESP development framework (ESP-IDF) incorporates FreeRTOS, which features a (by default) preemptive multitasking scheduler. While this notches up the complexity a bit, the reward is well worth the trade-off when you start to utilize multitasking.
 - The ESP32-S3 also includes another great feature - a full RGB mode display driver. While this is hardware limited RGB565, it is more than adequate for limited color used in this application.
 - The other hardware features on this display can be found on the [Waveshare Wiki](https://www.waveshare.com/wiki/ESP32-S3-Touch-LCD-4#Overview) page. There are a lot more features that are not currently utilized but may be in the future.

# Connection to the Vehicle
In light of the fact that the hardware is so fully featured, this project connects to the vehicle with a single OBD2 breakout cable. The connections are shown below:

The hardware is always powered by the vehicle's battery (even when the vehicle is turned off) and must implement it's own power management strategy to not drain the vehicle's battery.
# Communication with the Vehicle
## Vehicle Gateway

