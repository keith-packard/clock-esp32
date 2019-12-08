/*
 * Copyright © 2019 Keith Packard <keithp@keithp.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "snek-adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"

#define NO_OF_SAMPLES   16          //Multisampling

#define  SNEK_ADC_CHANNEL	ADC1_CHANNEL_0

float
snek_adc_read(void)
{
	gpio_num_t gpio;

	adc1_pad_get_io_num(SNEK_ADC_CHANNEL, &gpio);
	uint32_t adc_reading = 0;
	for (int i = 0; i < NO_OF_SAMPLES; i++) {
		uint32_t adc_raw = adc1_get_raw(SNEK_ADC_CHANNEL);
		printf("%d ", adc_raw);
		adc_reading  += adc_raw;
	}
	return (float) adc_reading / (4095.0f * NO_OF_SAMPLES);
}

void
snek_adc_init(void)
{
	adc_power_on();
	adc_gpio_init(ADC_UNIT_1, SNEK_ADC_CHANNEL);
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(SNEK_ADC_CHANNEL, ADC_ATTEN_DB_11);
}
