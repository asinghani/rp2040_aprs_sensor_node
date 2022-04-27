#include <stdbool.h>

#define DRA_RX 4
#define DRA_TX 5

#define DRA_PTT 18
#define DRA_PD 19
#define DRA_PWR 20

void dra818_init_aprs();
void dra818_set_lowpower(bool low_power);

void dra818_key(bool transmit);
