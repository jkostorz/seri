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

#include <avr/wdt.h>

#include "seri.h"

// MAIN
int16_t main(void)
{
	// WATCHDOG ENABLE
	wdt_reset();
	wdt_enable(WDTO_15MS);

	// SERIAL PORT CONFIG
	UBRR0H = (BAUD_PRESCALE >> 8); // SERIAL BAUD RATE
	UBRR0L = (BAUD_PRESCALE);
	UCSR0A |= (1 << U2X0);									 // DOUBLE USART TRANSMISSION SPEED
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8n1
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);	 // TX AND RX ENABLE

#ifdef _GI_

	// CHANGE GI PIN AS OUTPUT
	DDRD |= IC_GI_O;

#endif

	// VARIABLES
	uint16_t code = 0;
	uint8_t i = 0, j = 0;

	// MAIN LOOP
	while (1)
	{
		// WATCHDOG RESET
		wdt_reset();

		// GET CHARACTERS FROM SERIAL PORT
		while (!(UCSR0A & (1 << RXC0)))
			wdt_reset();
		j = UDR0;
		switch (j)
		{
		case 'x':
		case 'X':
			code = 0;
			i = 0;
			break;
		case '0':
			code |= (0 << (4 * (2 - i)));
			i++;
			break;
		case '1':
			code |= (1 << (4 * (2 - i)));
			i++;
			break;
		case '2':
			code |= (2 << (4 * (2 - i)));
			i++;
			break;
		case '3':
			code |= (3 << (4 * (2 - i)));
			i++;
			break;
		case '4':
			code |= (4 << (4 * (2 - i)));
			i++;
			break;
		case '5':
			code |= (5 << (4 * (2 - i)));
			i++;
			break;
		case '6':
			code |= (6 << (4 * (2 - i)));
			i++;
			break;
		case '7':
			code |= (7 << (4 * (2 - i)));
			i++;
			break;
		case '8':
			code |= (8 << (4 * (2 - i)));
			i++;
			break;
		case '9':
			code |= (9 << (4 * (2 - i)));
			i++;
			break;
		case 'a':
		case 'A':
			code |= (10 << (4 * (2 - i)));
			i++;
			break;
		case 'b':
		case 'B':
			code |= (11 << (4 * (2 - i)));
			i++;
			break;
		case 'c':
		case 'C':
			code |= (12 << (4 * (2 - i)));
			i++;
			break;
		case 'd':
		case 'D':
			code |= (13 << (4 * (2 - i)));
			i++;
			break;
		case 'e':
		case 'E':
			code |= (14 << (4 * (2 - i)));
			i++;
			break;
		case 'f':
		case 'F':
			code |= (15 << (4 * (2 - i)));
			i++;
			break;
		case 'i':
		case 'I':
			code++;
			i = 8;
			break;
		case 'r':
		case 'R':
			i = 8;
			break;
		case 's':
		case 'S':
			code++;
			i = 16;
			break;
		case 'q':
		case 'Q':
			while (1)
				;
			break;
		default:
			code = 0;
			i = 128;
			break;
		}

		// PUT CHARACTER TO SERIAL PORT - HEX PREFIX
		if (i == 0 || i == 8)
		{
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = 'x';
		}

		// PUT CHARACTER TO SERIAL PORT - SKIP PREFIX
		if (i == 16)
		{
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = 's';
		}

		// PUT CHARACTER TO SERIAL PORT - BITS 11 ... 8
		if (i == 1 || i == 8 || i == 16)
		{
			j = ((code >> 8) & 0xf) + 48;
			if (j > 57)
				j += 7;
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = j;
		}

		// PUT CHARACTER TO SERIAL PORT - BITS 7 ... 4
		if (i == 2 || i == 8 || i == 16)
		{
			j = ((code >> 4) & 0xf) + 48;
			if (j > 57)
				j += 7;
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = j;
		}

		// PUT CHARACTER TO SERIAL PORT - BITS 3 ... 0
		if (i == 3 || i == 8 || i == 16)
		{
			j = ((code >> 0) & 0xf) + 48;
			if (j > 57)
				j += 7;
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = j;
		}

		// PUT CHARACTER TO SERIAL PORT - END OF LINE
		if (i == 3 || i == 8 || i == 16)
		{
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = 13;
			while (!(UCSR0A & (1 << UDRE0)))
				wdt_reset();
			UDR0 = 10;
		}

		// SEND REMOTE INTERACTIVE
		if (i == 3 || i == 8)
		{
			// CHANGE RI PIN AS OUTPUT
			DDRD |= IC_RI_O;

#ifdef _GI_

			// DEFAULT Lo ON DI PIN BEFORE RELAY ON
			IC_RI_Lo;

			// RELAY ON
			IC_GI_Hi;

			// RELAY ON TIMEOUT
			wait_ms(REL_DELAY);

#endif

			// REMOTE INTERACTIVE SEND
			func_ri_send(code);

#ifdef _GI_

			// RELAY OFF
			IC_GI_Lo;

			// CAPACITOR CHARGING
			wait_ms(REL_DELAY);

#endif

			// CHANGE DI PIN AS INPUT
			DDRD &= ~IC_RI_O;

			i = 128;
		}
	}
}

// SEND REMOTE INTERACTIVE FUNCTION
void func_ri_send(uint16_t data)
{

	// HEADER
	IC_RI_Hi;
	wait_ms(RI_PULSE_TIME * 3);
	IC_RI_Lo;
	wait_ms(RI_PULSE_TIME);

	//DATA BITS
	for (uint8_t b = 0; b < 12; b++)
	{
		IC_RI_Hi;
		wait_ms(RI_PULSE_TIME);
		IC_RI_Lo;
		wait_ms(RI_PULSE_TIME);
		if (data & (0b100000000000 >> b))
			wait_ms(RI_PULSE_TIME);
	}

	// TRAILER
	IC_RI_Hi;
	wait_ms(RI_PULSE_TIME);
	IC_RI_Lo;
	wait_ms(RI_PULSE_TIME * 20);
}

// DELAY FUNCTIONS

static inline void asm_wait_us(uint16_t count)
{
	asm volatile("cp %A0, __zero_reg__ \n\t"
							 "cpc %B0, __zero_reg__ \n\t"
							 "breq loop_out_%= \n\t"
							 "loop%=: \n\t"
							 "sbiw %0, 1 \n\t"
							 "brne loop%= \n\t"
							 "loop_out_%=: \n\t"
							 : "=w"(count)
							 : "0"(count));
}

void wait_ms(uint16_t time)
{
	while (time--)
	{
		wait_us(1000);
#if defined(_AVR_WDT_H_)
		wdt_reset();
#endif
	}
}
