; Init vCPU
start:
    ; Halt CPU execution
    HALT

    ; Reset CPU flags
    CLRF

    ; Zero out general purpose registers
    LOOP0:
        STR $gp0, 0, 0
        STR $sp0, 0, 0
        STR $fp0, 0, 0
        STR $rp0, 0, 0
         INCR 0, 1
         COMP 0, 16
        BRNE LOOP0

    ; Flush cache
    FLUSHCACHE

    ; Initialize interrupt handler
    LDA INTERRUPT_VECTOR
    STA ISR_ADDRESS

    ; Begin normal execution
    RESUMEEXECUTION
