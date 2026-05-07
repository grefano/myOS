extern exception_handler
extern handler_keyboard
extern handler_mouse
extern handler_pic
%macro isr_err_stub 1
isr_stub_%+%1:
    cli
    pusha
    call exception_handler
    popa
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

%macro isr_pic 1
isr_stub_%+%1:
    cli
    pusha
  call handler_pic
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
isr_err_stub    13
isr_err_stub    14
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
isr_pic 32
isr_keyboard 33
; isr_mouse 44


global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    34 
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep
