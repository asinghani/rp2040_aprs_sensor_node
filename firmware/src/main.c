#include <aprs_pico.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include "dra818.h"
#include "tmp102.h"

#define LED 24

// This should ideally be once every few minutes at most
// in order to avoid congesting / abusing the APRS network
#define TX_INTERVAL_MS 60000
#define TX_AMPL 200 // Out of 256

// NOTE: Insert user callsign here
#define CALLSIGN "-----"

// NOTE: Insert destination callsign here
#define DST_CALLSIGN "-----"

// For a sensor-node, we expect the location of the node to
// be fixed and as-such we avoid including a GPS module for
// cost reasons, so the coordinates are hard-coded. For a
// mobile platform, these coordinates would be obtained with GPS
#define LAT 40.4422
#define LNG -79.9467
#define ALT 100.0

int main() {
    sleep_ms(2000);

    stdio_init_all();
    tmp102_init();
    sleep_ms(2000);
    dra818_init_aprs();
    dra818_set_lowpower(true);
    sleep_ms(2000);

    void* aprs = aprs_pico_init();

    char msg[128];
    while (true) {
        // Read and transmit the temperature and device uptime
        float temp = tmp102_read_temperature();
        uint64_t uptime = to_us_since_boot(get_absolute_time()) / 1000 / 1000;
        sprintf(msg, "DATA temperature_F=%f uptime_sec=%lu", temp, uptime);

        // Transmit the data
        dra818_key(true);
        aprs_pico_sendAPRS(aprs, CALLSIGN, DST_CALLSIGN,
            "WIDE1-1", "WIDE2-1",
            msg, LAT, LNG, ALT, TX_AMPL);
        dra818_key(false);

        sleep_ms(TX_INTERVAL_MS);
    }

    return 0;
}
