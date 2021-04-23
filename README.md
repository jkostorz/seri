# seri - SErial to Remote Interactive interface for controlling Onkyo audio equipment via RI port (interface is based on the Arduino Uno board with ATmega328P)

## To use the interface, connect Arduino NANO usb port to computer and pins D2/GND to RI port, then send commands through serial port (8n1 57600)

Commands:

- xnnn - send RI code (e.g. x004, x08d)
- i - send incremened code (e.g. send x003, i, i, i is equal to send x003, x004, x005, x006)
- r - repeat code (e.g. send x003, r, r, r is equal to send x003, x003, x003, x003)
- s - skip incemented code (e.g. send x003, s, i, i is equal to send x003, x005, x006)
- q - reboot (for use with a server for a periodic restart, e.g. once a day, week, month)

All commands are case insensitive.

One RI code lasts from 35ms (x000) to 47ms (xfff), safe minimum time between commands is 50ms. If a galvanic isolation system is used, add another 40ms for relay switching delay.

### Codes for A-9150

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

### Codes from A-9150

- x0ea - Power Off from remote or front panel (allways)
- x0ef - Amplifier ready
- x1b0, x1b1, x1b2 - Power On from remote control or front panel and Dimmer from remote control (allways)

#### &nbsp;&nbsp;&nbsp;&nbsp;When D1 input is selected...&nbsp;

- xf0a - Display
- xf40 - Up
- xf41 - Down
- xf42 - Right
- xf43 - Left
- xf8d - Enter
- xf92 - Return
- xfcf - Menu

#### &nbsp;&nbsp;&nbsp;&nbsp;When D2 input is selected...&nbsp;

- xc00 - Forward
- xc01 - Previous
- xc06 - Input
- xc07 - Display
- xc4d - Enter
- xc82 - Up (repeat three times)
- xc83 - Down (repeat three times)
- xc84 - Left (repeat three times)
- xc85 - Right (repeat three times)
- xc93 - Menu
- xc95 - Return
- xcd0 - Play
- xcd8 - Repeat
- xcd9 - Shuffle

#### &nbsp;&nbsp;&nbsp;&nbsp;When D3 input is selected...&nbsp;

- x595 - Return
- x59d - Input
- x5c2 - Up (repeat three times)
- x5c3 - Down (repeat three times)
- x5c8 - Next
- x5c9 - Previous
- x5cb - Play
- x5d2 - Shuffle
- x5d3 - Repeat
- x5d5 - Display
- x5d6 - Menu
- x5d7 - Enter

#### &nbsp;&nbsp;&nbsp;&nbsp;When exit from selected input...&nbsp;

- x521 - D3 stop
- xc21 - D2 stop
- xf21 - D1 stop

### Codes for TX-SR304E

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
