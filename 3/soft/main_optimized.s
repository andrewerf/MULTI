#################################################################################
#    File : main.s
#    Author : Alain Greiner
#    Date : 15/09/2009
#################################################################################
#    This is a very simple application directly written in MIPS32
#    assembly language, in order to precisely control the memory mapping.
#    The sections names are specific to control the linker.
#################################################################################

    .section     .mydata

    .word    main
    .space  124

A : .word  1,  2,  3,  4,  5,  6,  7,  8,  9,  10
    .word  11, 12, 13, 14, 15, 16, 17, 18, 19, 20
    .space 64

B : .word  101, 102, 103, 104, 105, 106, 107, 108, 109, 110
    .word  111, 112, 113, 114, 115, 116, 117, 118, 119, 120
    .space 48

C : .word  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    .word  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

        .section     .mycode

        .set noreorder
main :
        la   $8,     A        # $8 <= &A[0]
        li   $7,     20       # $7 <= 20
        li   $6,     0        # $7 <= 0

loop :
        lw   $10,    0($8)         # $10 <= A[i]
        lw   $11,    144($8)       # $11 <= B[i]
        addi $6,     $6,     1     # i <= i+1
        addi $8,     $8,     4     # $8 <= &A[i+1]
        add  $12,    $10,     $11  # $12 <= A[i]+B[i]
        bne  $6,     $7,     loop  # fin de boucle ?
        sw   $12,    268($8)       # C[i] <= $12
print:
        la   $4, message
        addi $29,    $29,     -4
        jal  tty_puts
        nop
        addi $29,    $29,     +4
suicide:
        jal  exit
        nop
message:
        .asciiz   "\n!!! vector sum completed !!!\n"

