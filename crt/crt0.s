.global _start

.section .text
.type _start, @function

_start:
	call main

	mov %eax, %ebx
	mov $0, %eax
	int $0x80

	hlt               # should never reach here, safety