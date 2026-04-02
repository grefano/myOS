extern kernel_main
; ================================
; MULTIBOOT HEADER
; ================================
section .multiboot
align 8
multiboot2_header_start:
    dd 0xE85250D6                  ; magic
    dd 0                           ; architecture: i386
    dd multiboot2_header_end - multiboot2_header_start
    dd -(0xE85250D6 + 0 + (multiboot2_header_end - multiboot2_header_start))

    ; tag: framebuffer
    align 8
    dw 5                           ; type
    dw 0                           ; flags
    dd 20                          ; size
    dd 800                         ; width
    dd 600                         ; height
    dd 32                          ; depth

    ; tag: end
    align 8
    dw 0
    dw 0
    dd 8
multiboot2_header_end:


; ================================
; STACK (BSS)
; ================================
section .bss
align 16
stack_bottom:
    resb 16384     ; 16 KiB
stack_top:


; ================================
; DATA
; ================================
section .data
gdtr:
    dw 0           ; limit
    dd 0           ; base

ldtr:


; ================================
; TEXT
; ================================
section .text
global setGdt
setGdt:
    mov ax, [esp + 4]
    mov [gdtr], ax

    mov eax, [esp + 8]
    mov [gdtr + 2], eax

    lgdt [gdtr]
    ret


global reloadSegments
reloadSegments:
    jmp 0x08:reload_CS

reload_CS:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret


global setIdt
setIdt:
    lidt [ldtr]
    ret


global teste
teste:
    int 0x0D
    ret


global _start
_start:
    ; setup stack
    mov esp, stack_top

    ; push multiboot params
    push ebx    ; multiboot2_info
    push eax    ; magic

    call kernel_main

    cli
hang:
    hlt
    jmp hang
