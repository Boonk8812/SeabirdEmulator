; Test program for vCPU
section .text
global _start

_start:
    ; Initialize registers
    mov ax, 5
    mov bx, 3

    ; Perform arithmetic operations
    add ax, bx
    mov cx, ax ; Store the sum in cx

    sub ax, bx
    mov dx, ax ; Store the difference in dx

    mul bx
    mov si, ax ; Store the product in si

    div bx
    mov di, ax ; Store the quotient in di

    push dx ; Preserve the remainder on stack

    ; Display the results
    mov ah, 0x0E ; TTY mode
    xor bh, bh ; Page number

print_result:
    pop ax ; Retrieve a value from the stack
    add al, 0x30 ; Convert digit to ASCII
    int 0x10 ; Display the character
    xchg ax, bp ; Swap the dividend (ax) and divisor (bp) temporarily
    mov bp, 10 ; Divide by ten
    div bp
    push ax ; Push the quotient back onto the stack
    cmp al, 0 ; Determine if there is a remaining digit
    jne print_result

    ; Terminate the test program
    hlt
