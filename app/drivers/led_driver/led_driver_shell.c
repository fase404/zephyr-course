#include <stdlib.h>
#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include "task2.h"

static int cmd_fetch(const struct shell* sh, int argc, char** argv){
    const struct device *dev = shell_device_get_binding(argv[1]);
    if(!dev){
        shell_error(sh, "could not find device %s", argv[1]);
        return -EFAULT;
    }

    int ret = sensor_sample_fetch(dev);
    if(ret!=0){
        shell_error(sh, "Error fetching, %d", ret);
        return -EFAULT;
    }
    return 0;
}

static int cmd_read(const struct shell* sh, int argc, char** argv){
    const struct device *dev = shell_device_get_binding(argv[1]);
    if(!dev){
        shell_error(sh, "could not find device %s", argv[1]);
        return -EFAULT;
    }
    
    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);  
    if(ret!=0){
        shell_error(sh, "Error reading");
        return -EFAULT;
    }
    shell_info(sh, "%d", val.val1);
    return 0;
}

static int cmd_info(const struct shell* sh, int argc, char** argv){
    const struct device *dev = shell_device_get_binding(argv[1]);
    if(!dev){
        shell_error(sh, "could not find device %s", argv[1]);
        return -EFAULT;
    }
    if(device_is_ready(dev)){
        shell_info(sh, "Device %s is ready", argv[1]);
    }else{
        shell_error(sh, "Device %s is not ready", argv[1]);
        return -EFAULT;
    }
    return 0;
}

static int cmd_count(const struct shell* sh, int argc, char** argv){
    const struct device *dev = shell_device_get_binding(argv[1]);
    char *end;
    long parsed_val = strtol(argv[2], &end, 10);

    if (end == argv[2] || *end != '\0') {
        shell_error(sh, "Error: '%s' is not a valid int.\n", argv[2]);
        return -EFAULT;
    }

    int count_val = (int)parsed_val;
    int ret = leddriver_set_count(dev, count_val);
    if(ret == 0){
        shell_info(sh, "Count is: %d", count_val);
    }
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(led_driver_subcmd, 
    SHELL_CMD_ARG(fetch, NULL, "Fetch channel of our,leddriver", cmd_fetch, 2, 0),
    SHELL_CMD_ARG(read, NULL, "Read channel of our,leddriver", cmd_read, 2, 0),
    SHELL_CMD_ARG(info, NULL, "Info of our,leddriver", cmd_info, 2, 0),
    SHELL_CMD_ARG(count, NULL, "count of our,leddriver", cmd_count, 3, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_REGISTER(led_driver, &led_driver_subcmd, "led driver subcommands", NULL);