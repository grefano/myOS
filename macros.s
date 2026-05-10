extern exception_handler
extern handler_keyboard
extern handler_mouse
extern handler_pit
extern handler_irq
extern handler_gpf
extern handler_pf
extern handler_syscall
%macro isr_err_stub 1
isr_stub_%+%1:
    cli
    pusha
    call exception_handler
    popa
    add esp, 4 ; descarta o error code
    iret 
%endmacro
; if writing for 64-bit, use iretq instead
%macro isr_no_err_stub 1
isr_stub_%+%1:
    cli
    pusha
    call exception_handler
    popa
    iret
%endmacro

%macro isr_gpf 1
isr_stub_%+%1:
    cli
    pusha
    call handler_gpf
    popa
    add esp, 4
    iret
%endmacro

%macro isr_pf 1
isr_stub_%+%1:
    cli
    pusha
    call handler_pf
    popa
    iret
%endmacro

%macro irq_stub 1
isr_stub_%+%1:
  cli
  pusha
  call handler_irq
  popa
  iret
%endmacro

%macro isr_pit 1
isr_stub_%+%1:
    cli
    pusha
  call handler_pit
    popa
  iret
%endmacro

%macro isr_keyboard 1
isr_stub_%+%1:
    cli
    pusha
  call handler_keyboard
    popa
  iret
%endmacro

%macro isr_mouse 1
isr_stub_%+%1:
    cli
    pusha
  call handler_mouse
    popa
  iret
%endmacro

%macro isr_syscall 1
isr_stub_%+%1:
    cli
    pusha
  call handler_syscall
    popa
  iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_gpf 13
isr_pf 14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
isr_pit 32
isr_keyboard 33
irq_stub 34
irq_stub 35
irq_stub 36
irq_stub 37
irq_stub 38
irq_stub 39
irq_stub 40
irq_stub 41
irq_stub 42
irq_stub 43
irq_stub 44
irq_stub 45
irq_stub 46
irq_stub 47
isr_syscall 48
;isr_mouse 44


global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    49 
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep
