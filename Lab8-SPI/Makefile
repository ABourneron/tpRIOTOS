APPLICATION=HelloWorld

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../RIOT
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += printf_float
USEMODULE += xtimer

FEATURES_REQUIRED += periph_spi

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
