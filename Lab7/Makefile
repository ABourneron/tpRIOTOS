APPLICATION=HelloWorld

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../RIOT
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
