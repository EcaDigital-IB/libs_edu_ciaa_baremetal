APP=program


MODULES=lpc_chip_43xx lpc_board_ciaa_edu_4337
DEFINES=CORE_M4 __USE_LPCOPEN

TARGET=$(APP).elf
SRC=$(foreach m, $(MODULES), $(wildcard $(m)/src/*.c)) $(wildcard $(APP)/*/src/*.c)
INCLUDES=$(foreach m, $(MODULES), -I$(m)/inc) -Ilpc_chip_43xx/inc/usbd/ $(foreach i, $(wildcard $(APP)/*/inc), -I$(i))
_DEFINES=$(foreach m, $(DEFINES), -D$(m))
OBJECTS=$(SRC:.c=.o)
DEPS=$(SRC:.c=.d)
LDSCRIPT=ldscript/ciaa_lpc4337.ld

ARCH_FLAGS=-mcpu=cortex-m4 -mthumb
ARCH_FLAGS+=-mfloat-abi=hard -mfpu=fpv4-sp-d16

CFLAGS=$(ARCH_FLAGS) $(INCLUDES) $(_DEFINES) -ggdb3 -O2
LDFLAGS=$(ARCH_FLAGS) -T$(LDSCRIPT) -nostartfiles -O2
LDFLAGS+=-Wl,-gc-sections
LDFLAGS+=$(foreach l, $(LIBS), -l$(l))

all: $(TARGET)

test_build_all:
	@rm logs/*.log
	@./logs/test_build_all.sh | tee logs/test_build_all.log

_:
	@echo $(CFLAGS)
	@echo $(LDFLAGS)

CROSS=arm-none-eabi-
CC=$(CROSS)gcc
LD=$(CROSS)gcc
SIZE=$(CROSS)size
OBJCOPY=$(CROSS)objcopy
LIST=$(CROSS)objdump -xCedlSwz
GDB=$(CROSS)gdb
OOCD=openocd

ifeq ("$(origin V)", "command line")
BUILD_VERBOSE=$(V)
endif
ifndef BUILD_VERBOSE
BUILD_VERBOSE = 0
endif
ifeq ($(BUILD_VERBOSE),0)
Q = @
else
Q =
endif


-include $(DEPS)

%.o: %.c
	@echo "CC $<"
	$(Q)$(CC) -MMD $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS) Makefile
	@echo "LD $@"
	$(Q)$(LD) -o $@ $(OBJECTS) $(LDFLAGS)
	$(Q)$(OBJCOPY) -v -O binary $@ $(APP).bin
	$(Q)$(LIST) $@ > $(APP).lst
	$(Q)echo Executable SIZE:
	$(Q)$(SIZE) $@

.PHONY: clean debug openocd

openocd:
	$(Q)$(OOCD) -f ciaa-nxp.cfg

debug: $(TARGET)
	$(Q)$(GDB) $< -ex "target remote :3333" -ex "mon reset halt" -ex "load" -ex "continue"

run: $(TARGET)
	$(Q)$(GDB) $< -batch -ex "target remote :3333" -ex "mon reset halt" -ex "load" -ex "mon reset run" -ex "quit"

download: $(TARGET)
	$(Q)$(OOCD) -f ciaa-nxp.cfg \
		-c "init" \
		-c "halt 0" \
		-c "flash write_image erase unlock $(APP).bin 0x1A000000 bin" \
		-c "reset run" \
		-c "shutdown"

erase:
	$(Q)$(OOCD) -f ciaa-nxp.cfg \
		-c "init" -c "halt 0" -c "flash erase_sector 0 0 last" -c "shutdown"

clean:
	@echo "CLEAN"
	$(Q)rm -fR $(OBJECTS) $(TARGET) $(DEPS) $(APP).lst
