#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define DATA_LEN 6

 // Load the binary bytes from a .ls8 source file into a RAM array
void cpu_load(struct cpu *cpu, char *filename) {
  FILE *fp = fopen(filename, "r"); // open up the file that was entered in the command line

  if (fp == NULL) { // fp is NULL if the filename entered in the command line doesn't exist
    fprintf(stderr, "Error opening file: %s\n", filename);
    exit(2);
  }

  int address = 0;
  
  char line[1024];

  while (fgets(line, 1024, fp) != NULL) {
    char *endptr; // keeps track of chars that are not numbers in the file

    unsigned int val = strtoul(line, &endptr, 2); // converts string to number

    if (endptr == line) { // prevents lines with no numbers from being stored on RAM
      continue;
    }

    cpu->ram[address++] = val; // stores the values in RAM
  }

  fclose(fp); // closes the file
}


// ## Step 2: Add RAM functions
// mar = Memory Address Register. It holds a memory address
// Goes to the CPU's RAM, at the index specified by mar
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  return cpu->ram[mar];
}


// mdr = Memory Data Register. It holds a value?
// nothing needs to be returned bc we are just writing to memory
// writing the mdr to RAM
void cpu_ram_write(struct cpu *cpu, unsigned char index, unsigned char mdr)
{
  cpu->ram[index] = mdr;
}




// ALU
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] *= cpu->reg[regB];
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

  unsigned char operandA, operandB; // initialize operand variables

  while (running) {
    unsigned char IR = cpu->ram[cpu->pc]; // 1. Get the value of the current instruction (in address pc).

    unsigned int num_operands = IR >> 6; // 2. Figure out how many operands this next instruction requires. Shifting over 6 bits bc this info is stored in the IR at the far left 2 bits.

    if (num_operands == 2) { // 3. Get the appropriate value(s) of the operands following this instruction
      operandA = cpu_ram_read(cpu, cpu->pc + 1);
      operandB = cpu_ram_read(cpu, cpu->pc + 2);

    } else if (num_operands == 1) {
      operandA = cpu_ram_read(cpu, cpu->pc + 1);
    }

    switch (IR) // 4. switch() over it to decide on a course of action.
    {
      case LDI: // ## Step 6: Add the `LDI` instruction. Set the value of a register to an integer.
        cpu->reg[operandA] = operandB;
        break;

      case PRN: // ## Step 7: Add the `PRN` instruction. Print numeric value stored in the given register.
        printf("%d\n", cpu->reg[operandA]);
        break;

      case HLT: // ## Step 5: Implement the `HLT` instruction handler. Stops the while loop.
        running = 0;
        break;

      case MUL: // ## Step 9: Implement Multiply.
        alu(cpu, ALU_MUL, operandA, operandB);
        break;

      default:
        printf("Just Send It!!!");
        exit(1);
        break;
    }
    // 5. Do whatever the instruction should do according to the spec.



    cpu->pc += num_operands + 1; // 6. Move the PC to the next instruction.
  }
}




// ## Step 3: Implement the core of `cpu_init()`
// Initialize a CPU struct
// TODO: Initialize the PC and other special registers
void cpu_init(struct cpu *cpu)
{
  cpu = malloc(sizeof(struct cpu));
  cpu->pc = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->reg, 0, sizeof(cpu->reg));
}
