.global _start
.intel_syntax noprefix

print:
	mov rax, 1
	mov rdi, 1
	syscall
	ret
_start:
	lea rsi, [hello_world]
	mov rdx, 18
	call print
	

	lea rsi, [hello2]
	mov rdx, 5
	call print
	

	mov rax, 60
	mov rdi, 0
	syscall

hello_world: .asciz "Hello, World!\n"
hello2: .asciz "again!\n"
