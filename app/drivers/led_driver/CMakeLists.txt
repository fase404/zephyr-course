if(CONFIG_OUR_LEDDRIVER)
    target_include_directories(app PRIVATE .)
    target_sources(app PRIVATE led_driver.c)
endif()