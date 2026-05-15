global swtch
swtch:
  mov eax, [esp + 4]
  mov edx, [esp + 8]

  ; push ebp,
  ; push ebx,
  ;push esi,
  push ebp 
 push ebx
 push esi
 push edi

  mov [eax], esp ; guardando stack atual
  mov esp, edx ; ???? passando new context pro ESP? ta passando o endereço do new context na stack

  ;pop edi
  ;pop
pop edi
pop esi
pop ebx
pop ebp

  ret
