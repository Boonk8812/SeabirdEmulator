; Definitions for various bit widths
%define REGISTER_WIDTH 8
%if REGISTER_WIDTH == 4
%define FLAG_COUNT 2
%elif REGISTER_WIDTH == 8
%define FLAG_COUNT 3
%elif REGISTER_WIDTH == 16
%define FLAG_COUNT 5
%elif REGISTER_WIDTH == 32
%define FLAG_COUNT 7
%elif REGISTER_WIDTH == 64
%define FLAG_COUNT 9
%else
%error Invalid register width specified
%endif

; General-purpose registers
register r0, 0x0000
register r1, 0x0001
register r2, 0x0002
register r3, 0x0003
%assign reg_index 4
%rep ((0x7000 >> REGISTER_WIDTH) - 4)
%if reg_index < 10
register r0%reg_index, (0x0000 | (reg_index << REGISTER_WIDTH))
%else
register r%reg_index, (0x0000 | (reg_index << REGISTER_WIDTH))
%fi
%assign reg_index (+reg_index)
%endrep

; Status flag registers
register sf, 0x6FFE
register zf, 0x6FFF

; Backwards compatible instructions
inst mov, imm, dst, src
inst cmp, imm, dst, src
inst add, imm, dst, src
inst sub, imm, dst, src
inst inc, imm, dst
inst dec, imm, dst

; Helper macro for generating instructions
%macro GENERIC_INSTRUCTION 5
  %5 %1, %3, %2, %4
%endmacro

; Specific instruction definitions
%define mov GENERIC_INSTRUCTION mov, imm, dst, src
%define cmp GENERIC_INSTRUCTION cmp, imm, dst, src
%define add GENERIC_INSTRUCTION add, imm, dst, src
%define sub GENERIC_INSTRUCTION sub, imm, dst, src
%define inc GENERIC_INSTRUCTION inc, imm, dst
%define dec GENERIC_INSTRUCTION dec, imm, dst

; Sample instruction execution
mov r0, 0x0001, r1, 0x0002
cmp r0, 0x0001, r1, 0x0003
add r0, 0x0001, r1, r0
sub r0, 0x0001, r1, r0
inc r0, 0x0001, r0
dec r0, 0x0001, r0
