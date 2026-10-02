# -----------------------------
# Functions
rwildcard = $(foreach d,$(wildcard $1/*),$(call rwildcard,$d,$2)) \
            $(filter $(subst *,%,$2),$(wildcard $1/$2))
# -----------------------------

# -----------------------------
# Toolchain
# -----------------------------
ASM     = nasm
CC      = x86_64-elf-g++
LD      = x86_64-elf-ld
ASMFLAGS= 
CFLAGS  = -std=gnu++20 -ffreestanding -O0 -g -Wall -Werror=return-type -Wextra -mno-red-zone -m64 -fno-exceptions -fno-rtti -mcmodel=kernel -mno-red-zone -mgeneral-regs-only -nostdlib -I. -Ipico/src -include pico/src/Std/AbsoluteMinimum.h
LDFLAGS = -nostdlib -m elf_x86_64 -static -z max-page-size=0x1000 --gc-sections -T linker.ld 

# -----------------------------
# Directories
# -----------------------------

# picokernel
PRJ_DIR     = pico
SRC_DIR     = $(PRJ_DIR)/src

# General
BIN_DIR     = bin
BUILD_DIR   = bin-int
LIMINE_DIR  = limine
ISO_DIR     = $(BIN_DIR)/iso

# -----------------------------
# Files
# -----------------------------
KERNEL      = $(BUILD_DIR)/kernel.elf
ISO            = $(BIN_DIR)/kernel.iso
SRC	   = $(call rwildcard,$(SRC_DIR),*.cpp)
ASMSRC	   = $(call rwildcard,$(SRC_DIR),*.asm)
OBJ           = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))
OBJ	  += $(patsubst $(SRC_DIR)/%.asm,$(BUILD_DIR)/%.assembly.o,$(ASMSRC))

# -----------------------------
# Targets
# -----------------------------

all: $(ISO)

# Build ISO
$(ISO): $(KERNEL) $(LIMINE_DIR)/limine-bios.sys
	mkdir -p $(ISO_DIR)
	cp $(LIMINE_DIR)/limine-bios.sys $(ISO_DIR)/
	cp $(KERNEL) $(ISO_DIR)/
	cp limine.conf $(ISO_DIR)/
	cp $(LIMINE_DIR)/limine-bios-cd.bin $(ISO_DIR)/
	cp $(LIMINE_DIR)/limine-uefi-cd.bin $(ISO_DIR)/

	# Create ISO
	xorriso -as mkisofs -b limine-bios-cd.bin -no-emul-boot -boot-load-size 4 -boot-info-table --efi-boot limine-uefi-cd.bin -efi-boot-part --efi-boot-image --protective-msdos-label $(ISO_DIR)/ -o $(ISO)


# Compile C++ kernel
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.assembly.o: $(SRC_DIR)/%.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $< -f elf64 -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link kernel
$(KERNEL): $(OBJ) linker.ld | $(BUILD_DIR)
	$(LD) $(LDFLAGS) -o $@ $(OBJ)

# Run in QEMU
run: $(ISO)
	qemu-system-x86_64 -machine q35 -cdrom $(ISO) -m 1G -cpu qemu64 -smp 2 -boot d -display sdl -serial stdio

# Clean everything
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean run
