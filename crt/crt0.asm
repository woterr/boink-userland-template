; crt0.asm
[bits 32]
global _start
extern main
section .text
_start:
	; esp points to: [argc][argv]
	mov eax, [esp]        ; argc
	mov ebx, [esp + 4]    ; argv
	
	push ebx              ; push argv (second)
	push eax              ; push argc (first)
	
	
	
	call main             ; main(argc, argv)
	
	; exit syscall
	mov ebx, eax          ; return code → ebx
	mov eax, 0            ; syscall: exit
	int 0x80
	
	hlt                   ; just in case