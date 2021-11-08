#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

typedef uint32_t uintr_t;

struct Registers
{
    uintr_t r5; // EDI
    uintr_t r6; // ESI
    uintr_t r4; // EBP
    uintr_t sp; // ESP
    uintr_t r1; // EBX
    uintr_t r3; // EDX
    uintr_t r2; // ECX
    uintr_t r0; // EAX
    uintr_t pc; // EIP

    Registers()
    {
        clear();
    }

    void clear()
    {
        r6 = r5 = r4 = r3 = r2 = r1 = r0 = pc = sp = 0;
    }

    void copy(Registers &registers)
    {
        this->r6 = registers.r6;
        this->r5 = registers.r5;
        this->r4 = registers.r4;
        this->r3 = registers.r3;
        this->r2 = registers.r2;
        this->r1 = registers.r1;
        this->r0 = registers.r0;
        this->sp = registers.sp;
        this->pc = registers.pc;
    }
} __attribute__((packed));
#endif