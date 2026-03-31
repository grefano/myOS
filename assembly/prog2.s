.global _start
.intel_syntax noprefix

end:
  mov rax, 60
  mov rdi, 1
  syscall
  ret  

_start:

  call end
