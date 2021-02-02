#include <stdint.h>
#include <stdbool.h>
#include "C:/ti/TivaWare_C_Series-2.1.4.178/inc/tm4c1294ncpdt.h"

void my1secDelay() {
    uint32_t numCounts = 16000000;

    NVIC_ST_RELOAD_R = numCounts - 1;
    NVIC_ST_CURRENT_R = 0;

    while ((NVIC_ST_CURRENT_R & 0x00010000) = 0)
    {
        //wait for counter flag to be = 1
    }
}
