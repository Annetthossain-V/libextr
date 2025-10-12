.intel_syntax noprefix

.section .rodata
double_one_extr: .double 1.0

.section .text
.globl pow_extr
# double pow_extr(double num, uint expo)
pow_extr:
  push rbx
  xor ebx, ebx

  movapd xmm1, xmm0
  movsd xmm0, qword ptr [rip + double_one_extr]

.pow_loop:
  mulsd xmm0, xmm1

  inc ebx
  cmp ebx, edi
  jne .pow_loop

  pop rbx
  ret
