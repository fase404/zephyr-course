#ifndef TASK2_H_
#define TASK2_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int leddriver_set_count(const struct device *dev, int count);

#ifdef __cplusplus
}
#endif

#endif /* TASK2_H_ */