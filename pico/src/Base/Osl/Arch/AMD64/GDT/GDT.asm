[BITS 64]

; Global descriptor table

PcLoadGDT:
    LGDT [rdi]
    MOV ax, 0x10
    MOV ds, ax
    MOV es, ax
    MOV fs, ax
    MOV gs, ax
    MOV ss, ax

    POP rdi
    MOV rax, 0x08
    PUSH rax
    PUSH rdi

    RETFQ

GLOBAL PcLoadGDT
