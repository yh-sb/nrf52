#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app);

void blink_thread(void *p1, void *p2, void *p3)
{
    const gpio_dt_spec *led_0 = static_cast<const gpio_dt_spec *>(p1);
    
    while(1)
    {
        gpio_pin_toggle_dt(led_0);
        k_msleep(500);
    }
}

int main(void)
{
    LOG_INF("Board config: %s", CONFIG_BOARD);
    
    static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
    if(!gpio_is_ready_dt(&led_0))
    {
        LOG_ERR("Gpio %d.%d isn't ready", led_0.port, led_0.pin);
        return -1;
    }
    
    int ret = gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_ACTIVE);
    if(ret)
    {
        LOG_ERR("Failed to configure gpio %d.%d", led_0.port, led_0.pin);
        return -1;
    }
    
    static struct k_thread tdata;
    static K_THREAD_STACK_DEFINE(tstack, 512);
    k_tid_t tid = k_thread_create(&tdata, tstack, K_THREAD_STACK_SIZEOF(tstack),
        blink_thread, (void *)&led_0, nullptr, nullptr, 0, K_USER, K_NO_WAIT);
    if(!tid)
    {
        LOG_ERR("Failed to create thread");
        return -1;
    }
}
