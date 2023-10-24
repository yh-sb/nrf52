if(NOT DEFINED OPENOCD_PARAMS)
    message(FATAL_ERROR "OPENOCD_PARAMS is not defined.\n"
        "Example: \"set(OPENOCD_PARAMS -f interface/stlink-v2.cfg transport select hla_swd -f target/nrf52.cfg)\"")
endif()

add_custom_target(flash
    COMMAND openocd ${OPENOCD_PARAMS} -c "init; halt; program ${ZEPHYR_BINARY_DIR}/${KERNEL_BIN_NAME} 0x08000000 verify; reset run; exit"
    USES_TERMINAL
)

add_custom_target(erase
    COMMAND openocd ${OPENOCD_PARAMS} -c "init; halt; nrf52 mass_erase 0; exit"
    USES_TERMINAL
)

add_custom_target(reset
    COMMAND openocd ${OPENOCD_PARAMS} -c "init; reset run; exit"
    USES_TERMINAL
)

add_custom_target(debug DEPENDS flash
    COMMAND openocd ${OPENOCD_PARAMS} -c "gdb_port 2331; debug_level 2; set WORKAREASIZE 0x2000; reset_config srst_only"
    USES_TERMINAL
)
