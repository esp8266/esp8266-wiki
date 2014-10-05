#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

static volatile os_timer_t some_timer;
static uint8_t status = 0;

void some_timerfunc(void *arg)
{
    //Do blinky stuff
    if (status == 0)
    {
        //Update the global variable with current state
        status = 1;

        //Set GPIO2 to HIGH
        gpio_output_set(BIT2, 0, BIT2, 0);
    }
    else
    {
        //Update the global variable with current state
        status = 0;

        //Set GPIO2 to LOW 
        gpio_output_set(0, BIT2, BIT2, 0);
    }
}

void ICACHE_FLASH_ATTR
user_init()
{
    //Set GPIO2 to output mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);

    //Set GPIO2 low
    gpio_output_set(0, BIT2, BIT2, 0);

    //Disarm timer
    os_timer_disarm(&some_timer);

    //Setup timer
    os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);

    //Arm the timer
    //&some_timer is the pointer
    //1000 is the fire time in ms
    //0 for once and 1 for repeating
    os_timer_arm(&some_timer, 1000, 0);
}
