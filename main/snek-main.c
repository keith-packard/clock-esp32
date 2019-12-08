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

#include "snek-draw-int.h"
#include "snek-lcd.h"
#include "snek-clock.h"
#include "snek-daytime.h"
#include "snek-adc.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"
#include "driver/gpio.h"

#if 0
static QueueHandle_t uart0_queue;
static QueueHandle_t input_queue;

int
snek_getc(void)
{
	uint8_t	c;

	fflush(stdout);
	while (!xQueueReceive(input_queue, &c, portMAX_DELAY))
		;
	return c;
}

#define BUF_SIZE 1024

static uint8_t uart_data[BUF_SIZE];

static void uart_event_task(void *pvParameters)
{
	uart_event_t event;
	int i;
	for(;;) {
		if(xQueueReceive(uart0_queue, (void * )&event, (portTickType)portMAX_DELAY)) {
			switch(event.type) {
			case UART_PATTERN_DET:
				snek_abort = true;
				/* fall through */
			case UART_DATA:
				uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, uart_data, event.size, portMAX_DELAY);
				for (i = 0; i < event.size; i++)
					xQueueSendToBack(input_queue, &uart_data[i], 0);
				break;
			default:
				break;
			}
		}
	}
}

static void initialize_console(void)
{
    input_queue = xQueueCreate(BUF_SIZE, sizeof(uint8_t));

    /* Disable buffering on stdin */
    setvbuf(stdin, NULL, _IONBF, 0);

    /* Minicom, screen, idf_monitor send CR when ENTER key is pressed */
    esp_vfs_dev_uart_set_rx_line_endings(ESP_LINE_ENDINGS_CR);
    /* Move the caret to the beginning of the next line on '\n' */
    esp_vfs_dev_uart_set_tx_line_endings(ESP_LINE_ENDINGS_CRLF);

    /* Configure UART. Note that REF_TICK is used so that the baud rate remains
     * correct while APB frequency is changing in light sleep mode.
     */
    const uart_config_t uart_config = {
            .baud_rate = CONFIG_ESP_CONSOLE_UART_BAUDRATE,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .use_ref_tick = true
    };
    ESP_ERROR_CHECK( uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uart_config) );

    /* Install UART driver for interrupt-driven reads and writes */
    ESP_ERROR_CHECK( uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM,
            BUF_SIZE, BUF_SIZE, 20, &uart0_queue, 0) );

    //Set uart pattern detect function.
    uart_enable_pattern_det_baud_intr(CONFIG_ESP_CONSOLE_UART_NUM, '\003', 1, 9, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(CONFIG_ESP_CONSOLE_UART_NUM, 20);

    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);
}

#endif

void app_main(void)
{
	for (int p = 0; p < 6; p += 2) {
		gpio_set_direction(p, GPIO_MODE_OUTPUT);
		gpio_set_level(p, 0);
	}

	snek_adc_init();

#if 0
	initialize_console();
#endif

	snek_draw_lcd_init();

	snek_daytime_init();

	struct timeval tv, prev_tv;

	tv.tv_sec = 1;
	prev_tv.tv_sec = 2;
	int level = 0;
	float avg_v = 0.5f;
	for (;;) {
		do {
			vTaskDelay(100/portTICK_PERIOD_MS);
			gettimeofday(&tv, NULL);
		} while (tv.tv_sec == prev_tv.tv_sec);
		tv.tv_usec = 0;
		snek_draw_fill(&snek_lcd_pixmap, 0xff000000, SNEK_DRAW_SOURCE, 0, 0, 1024, 1024);

		snek_clock_paint(&tv);

		snek_draw_lcd();
		prev_tv = tv;

		float v = snek_adc_read();
		printf("adc %f\n", v);

		if (v > 0.5f)
			v = 0.5f;
		v = v * 2.0f;

		avg_v = 0.9f * avg_v + 0.1f * v;

#define MIN_LIGHT	100
#define MAX_LIGHT	4095

		level = avg_v * (MAX_LIGHT - MIN_LIGHT) + MIN_LIGHT;

		/*
		 * Pick light level
		 */
		printf("level %d\n", level);
		snek_lcd_set_backlight(level);
		if (level == 255)
			level = 0;
		else {
			level += 32;
			if (level > 255)
				level = 255;
		}
	}
}

#ifdef SNEK_DRAW_MALLOC_TRACE
#undef malloc
void *Malloc(size_t size)
{
	void  *r = malloc(size);

	if (!r)
		printf("malloc %d fail\n", size);
	else
		printf("malloc %d success %08x\n", size, (uintptr_t) r);
	return r;
}

#undef free
void Free(void *r)
{
	free(r);
	printf("free %08x\n", (uintptr_t) r);
}
#endif
