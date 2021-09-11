# ----------------------------
# Makefile Options
# ----------------------------

NAME        = OIRAMUNL
ICON        = icon.png
DESCRIPTION = "Oiram Unlimited CE"
COMPRESSED  = YES
ARCHIVED    = YES

CFLAGS   = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
