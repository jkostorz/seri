# seri - SErial to Remote Interactive interface to control Onkyo audio equipment via an RI port based on Arduino Uno (ATmega328P).

#### To use the interface, connect Arduino NANO usb port to computer and pins D5/GND to RI port, then send commands through serial port (8n1 57600).

Commands:

- xnnn - send RI code (e.g. x004, x08d)
- i - send incremened code (e.g. send x003, i, i, i is equal to send x003, x004, x005, x006)
- r - repeat code (e.g. send x003, r, r, r is equal to send x003, x003, x003, x003)
- s - skip incemented code (e.g. send x003, s, i, i is equal to send x003, x005, x006)
- q - reboot (for use with a server for a periodic restart, e.g. once a day, week, month)

All commands are case insensitive.

One RI code lasts from 49ms (x000) to 61ms (xfff), safe minimum time between commands is 65ms. If a galvanic isolation system is used, add another 40ms for relay delays.

#### Codes for A-9150
- x002 - Volume up
- x003 - Volume down
- x004 - Power toggle
- x005 - Mute toggle
- x020 - Input D1
- x02f - Power On
- x0d5 - Source next
- x0d6 - Source prev
- x0d7 - Mute on (sound off)
- x0d8 - Mute off (sound on)
- x0d9 - Power on
- x0da - Power off
- x0e0 - Input D2
- x0fb - Power On
- x170 - Input D3
- x17f - Power On
- x420 - Service mode - power off
- x421 - Service mode - blink all leds
- x422 - Service mode - audio tests
- x423 - Service mode
- x424 - Service mode

#### Codes for TX-SR304E
- x020 - Input CD
- x120 - Input DVD
- x170 - Input HDD
- x1a0 - Input Video2
- x1a2 - Volume up
- x1a3 - Volume down
- x1a4 - Mute on (sound off)
- x1a5 - Mute off (sound on)
- x1ae - Power off
- x1af - Power on
- x2b0 - Display dim max
- x2b1 - Display dim mid
- x2b2 - Display dim min
- x2b8 - Display dim day
- x2bf - Display dim night
- x420 - Service mode off
- x421 - Service mode 1-00
- x422 - Service mode 2-00
- x423 - Service mode 3-00
- x424 - Service mode 4-00
- x425 - Service mode 4-01
- x426 - Service mode 4-02
- x427 - Service mode 4-03
- x428 - Service mode 4-04
- x429 - Service mode 4-05
- x42a - Service mode 4-06
- x42b - Service mode 4-07
- x42c - Service mode 4-08
- x42d - Service mode 4-09
- x42e - Service mode 4-00
