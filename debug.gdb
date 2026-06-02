target remote :1234
break kernel_main
#break swtch
break exception_handler
#break handler_pit
#break handler_keyboard
break handler_syscall
break handler_gpf
break handler_pf
break handler_irq
#layout split
continue
