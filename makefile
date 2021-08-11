# ----------------------------
# Makefile Options
# ----------------------------

NAME        ?= OIRAMUNL
ICON        ?= icon.png
DESCRIPTION ?= "Oiram Unlimited!"
COMPRESSED  ?= YES
ARCHIVED    ?= YES

CFLAGS      ?= -Wall -Wextra -Oz
CXXFLAGS    ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
