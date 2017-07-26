# ChannelVisualizer

With this program, you can use your ESP32 MCU to visualize the relative frequency of all packets on every* channel on a serial monitor. *channel 1 - 13 on 2.4 GHz frequency band

This project is inspired from [Spacehuhns PacketMonitor](https://github.com/spacehuhn/PacketMonitor) (go and buy yourself one of those on [tindie](https://www.tindie.com/products/lspoplove/wifi-packet-monitor-preflashed-d-duino-b/) or [AliExpress](https://www.aliexpress.com/item/WiFi-Packet-Monitor-Preflashed-D-duino-B-ESP8266-1-3OLED/32816508278.html)!)

The code is kind a mess, but nevermind.

![alt text](https://github.com/Staubgeborener/ChannelVisualizer/blob/master/media/channel_visualizer.gif "gif serial monitor")

**Note:** It's still in progress. At the moment only a visualization on the serial monitor works. An update for OLED-Display will come in the next few weeks. And maybe (just maybe) an option to show those graphs also on a more beautiful (even beautifuller you may ask?) way using python script for the shell. Also a *bluetooth update* will come in the next months.


Want to see something cool? Just turn on your microwave near the ESP32 and start the program.

## What it does
For this project, we use the promiscuous mode of the ESP32.  The ESP32 will change every 50 ms the channel. In parallel, each time we receive a paket, the callback will triggered. The ESP32 will just look in this moment which channel is setted, increment this and calculate the relative frequency.

This project could help for the decision which channel you should use.

## Execution

Just type `make monitor` in your terminal window.

## Installation
Download the rep:

`$ git clone https://github.com/Staubgeborener/ChannelVisualizer/`

Now open your terminal of choice, navigate to the 'channel_visualizer' directory and type

`make flash`

## Which is still to be said
To view this in a more elegant way use some kind of `clear terminal` command in line 66. I have renounced it, because the command to do this is dependent of your terminal.

## License
 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
 
This project is licensed under The MIT License. Take a look at the [license file](https://github.com/Staubgeborener/ChannelVisualizer/blob/master/LICENSE) for more informations.
