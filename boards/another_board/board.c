#include <zephyr/init.h>
#include <zephyr/kernel.h>

// Function to run prior to zephyr initialisation
static int my_board_init(void)
{
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(my_board_init, APPLICATION, 0);