#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_leddriver

LOG_MODULE_REGISTER(leddriver, LOG_LEVEL_INF);

const struct device *gpioe = DEVICE_DT_GET(DT_NODELABEL(gpioe));


static int leddriver_sample_fetch(const struct device *dev,
				   enum sensor_channel chan)
{
	gpio_pin_set(gpioe, 1, 1);
    LOG_INF("LED yellow on");
	return 0;
}

static int leddriver_channel_get(const struct device *dev,
				  enum sensor_channel chan,
				  struct sensor_value *val)
{
	gpio_pin_set(gpioe, 1, 0);
    LOG_INF("LED yellow off");
	return 0;
}

static DEVICE_API(sensor, leddriver_api) = {
	.sample_fetch = leddriver_sample_fetch,
	.channel_get = leddriver_channel_get,
};

static int leddriver_init(const struct device *dev)
{
	if (!device_is_ready(gpioe)) {
		return -ENODEV;
	}

	return gpio_pin_configure(gpioe, 1, GPIO_OUTPUT_INACTIVE);
}


DEVICE_DT_INST_DEFINE(0, leddriver_init, NULL, NULL, NULL, POST_KERNEL, 80, &leddriver_api);