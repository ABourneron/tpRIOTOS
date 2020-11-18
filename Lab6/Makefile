APPLICATION=HelloWorld

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../RIOT
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += xtimer

FEATURES_REQUIRED += periph_gpio

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
