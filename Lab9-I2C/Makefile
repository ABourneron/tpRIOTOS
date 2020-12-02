APPLICATION = Main

BOARD ?= native

FEATURES_REQUIRED += periph_hwrng 
FEATURES_REQUIRED += periph_i2c
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq

DEVELHELP ?= 1

USEMODULE += periph_hwrng 
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer
USEMODULE += periph_i2c

RIOTBASE ?= /home/at0088cm/RIOT/RIOT

include $(RIOTBASE)/Makefile.include
