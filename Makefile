
TARGET = libiopccmd_client.so

CFLAGS += -I$(SDKSTAGE)/usr/include/
CFLAGS += -I$(SDKSTAGE)/usr/include/iopccommon

LDFLAGS += -L$(SDKSTAGE)/usr/lib/ 
LDFLAGS += -lc -lpthread 

SRC = 
SRC += common.c
SRC += client_vm.c
SRC += client_db.c
SRC += client_mntbase.c
SRC += client_raiddev.c

include Makefile.include.lib
