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

.globl swap_endian64
swap_endian64:
  mov rax, rdi
  bswap rax 
  ret

.globl swap_endian32
swap_endian32:
  mov eax, edi
  bswap eax
  ret

.globl swap_endian16
swap_endian16:
  movzx ax, di 
  xchg ah, al
  ret


