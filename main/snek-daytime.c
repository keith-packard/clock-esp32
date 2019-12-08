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

#include "snek-daytime.h"
#include <sys/socket.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

static const char mon_names[12][4] = {
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC"
};

static void
daytime_task(void *pvParameters)
{
	struct sockaddr_in addr;
	int s;
	char	text[40];
	int	day;
	char	mon[10];
	int	year;
	int	hour;
	int	min;
	int	sec;
	char	tz[10];

	addr.sin_family = AF_INET;
	addr.sin_port = htons(13);
	addr.sin_addr.s_addr = htonl(0x0a000001),

	s = socket(AF_INET, SOCK_DGRAM, 0);
	connect (s, (struct sockaddr *) &addr, sizeof(addr));
	for (;;) {
		write(s, "", 1);
		if (read(s, text, sizeof(text)) > 0) {
			printf("text %s\n", text);
			if (sscanf(text, "%d %s %d %d:%d:%d %s",
				   &day, mon, &year,
				   &hour, &min, &sec, tz) == 7) {
				printf("time %02d:%02d:%02d day %d\n",
				       hour, min, sec, day);

				struct tm tm;;

				for (tm.tm_mon = 0; tm.tm_mon < 12; tm.tm_mon++)
					if (!strcmp(mon_names[tm.tm_mon], mon))
						break;
				tm.tm_year = year - 1900;
				tm.tm_mday = day;
				tm.tm_hour = hour;
				tm.tm_min = min;
				tm.tm_sec = sec;
				struct timeval now = { .tv_sec = mktime(&tm) };
				settimeofday(&now, NULL);
			}
		}
		vTaskDelay(10000 / portTICK_PERIOD_MS);
	}
}

void
snek_daytime_init(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    esp_netif_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(daytime_task, "daytime_task", 2048, NULL, 12, NULL);
}
