#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

// ## Step 2: Add RAM functions
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  // mar = Memory Address Register. It holds a memory address

  // Goes to the CPU's RAM, at the index specified by mar
  return cpu->ram[mar];
}

// ## Step 2: Add RAM functions
void cpu_ram_write(struct cpu *cpu, unsigned char index, unsigned char mdr)
{
  // mdr = Memory Data Register. It holds a value?
  // nothing needs to be returned bc we are just writing to memory

  // writing the mdr to RAM
  cpu->ram[index] = mdr;
}




/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  // initialize operand variables
  unsigned char operandA, operandB;

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char IR = cpu->ram[cpu->pc];

    // 2. Figure out how many operands this next instruction requires
    unsigned int num_operands = IR >> 6;

    // 3. Get the appropriate value(s) of the operands following this instruction
    if (num_operands == 2)
    {
      operandA = cpu_ram_read(cpu, cpu->pc + 1);
      operandB = cpu_ram_read(cpu, cpu->pc + 2);
    }
    else if (num_operands == 1)
    {
      operandA = cpu_ram_read(cpu, cpu->pc + 1);
    }

    // 4. switch() over it to decide on a course of action.
    switch (IR)
    {
      case LDI:
        break;

      case PRN:
        break;

      // ## Step 5: Implement the `HLT` instruction handler
      case HLT:
        // set running to 0 so that we break out of the while loop
        running = 0;
        break;

      default:
        printf("Just Send It");
        exit(1);
        break;
    }
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}



// ## Step 3: Implement the core of `cpu_init()`
/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu = malloc(sizeof(struct cpu));
  cpu->pc = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->reg, 0, sizeof(cpu->reg));
}
