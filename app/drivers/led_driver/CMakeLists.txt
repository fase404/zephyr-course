if(CONFIG_OUR_LEDDRIVER)
    target_sources(app PRIVATE led_driver.c)
endif()