/*
*		BSD 3-Clause License
*
* 	©2021 Janusz Kostorz
* 	All rights reserved.
*
* 	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
*		1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
*		2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
*		3. The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.
*
* 	THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* 	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* 	End of BSD license
*
*/

/*
*
* HARDWARE
*
* PD0 - SERIAL INPUT (VIA ARDUINO NANO USB)
* PD1 - SERIAL OUTPUT (VIA ARDUINO NANO USB)
* PD2 - OUT - REMOTE INTERACTIVE OUTPUT
* PD5 - OUT - RELAY OUTPUT
*
*/

#ifndef _SERI_
#define _SERI_

// SERIAL PORT SETTINGS
#define USART_BAUDRATE 57600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE / 2 * 16UL))) - 1)

// PORTS
#define IC_RI_P PORTD
#define IC_RI_O (1 << 2)
#define IC_GI_O (1 << 5)

// RELAY DELAY
#define REL_DELAY 20

// REMOTE INTERACTIVE TIMING
#define RI_PULSE_TIME 1

// DECLARATIONS
void func_ri_send(uint16_t data);
static inline void asm_wait_us(uint16_t count);
void wait_ms(uint16_t time);

#define wait_us(us) asm_wait_us((uint16_t)(((((us)*1000L) / (1000000000 / F_CPU)) - 1) / 4))

// MACROS
#define IC_RI_Lo IC_RI_P &= ~IC_RI_O;
#define IC_RI_Hi IC_RI_P |= IC_RI_O;

#define IC_GI_Lo IC_RI_P &= ~IC_GI_O;
#define IC_GI_Hi IC_RI_P |= IC_GI_O;

#endif
