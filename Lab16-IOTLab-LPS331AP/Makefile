APPLICATION = Main

BOARD ?= native

FEATURES_REQUIRED += periph_i2c

DEVELHELP ?= 1
RIOTBASE ?= $(CURDIR)/../../RIOT

#Les différents modules ajoutés au projet
USEMODULE += shell
USEMODULE += xtimer
USEMODULE += periph_i2c
USEMODULE += saul_default
USEMODULE += lpsxxx

include $(RIOTBASE)/Makefile.include
