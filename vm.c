#include <stdio.h>
#include <string.h>
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "machine_types.h"
//the functions in c files should work by extern within the header files so they should be visible and callable.
#define MEMORY_SIZE_IN_BYTES (65536 - BYTES_PER_WORD)
#define MEMORY_SIZE_IN_WORDS (MEMORY_SIZE_IN_BYTES / BYTES_PER_WORD)

/*typedef union
{
	word_type instrArr[MEMORY_SIZE_IN_WORDS];

} name;*/


int main(int argc, char* argv[])
{
	// get file ptr, get boffile, read it, (all in bof.c)
	const char* filename;

	//remeber we have to check invariants before each instruction
	//invariants are just the state of certain notable registers and counters shown in the manual on page 8
	reg_num_type gpr[32];

	filename = argv[0];//hopeing this works

	//file_location* curFile = file_location_make(filename,0);

	//BOFFILE bf = bof_read_open(filename);
	BOFFILE bf = bof_read_open(filename);

	//This should mean we have a full header with text length and data length
	//all header is word type which is integer except for magic word. which is char
	BOFHeader bh = bof_read_header(bf);

	bin_instr_t ir; //[MEMORY_SIZE_IN_WORDS];

	//bin_instr_t instructions[bh.text_length];

	ir = instruction_read(bf);
		
	printf("%s\n", bh.magic);
	
	//read text instructions
	for (int i = 0; i<bh.text_length; i++)
	{	
		ir = instruction_read(bf);	
		
		char binInstr[5];
				
		strcpy(binInstr, instruction_assembly_form(ir));
		
		printf("%s\n", binInstr);
	}

	/*  //read data instruction
	//maybe j should start from start adress?
	for (int j = 0; j<bh.data_length+bh.data_start_address; j++)
	{	
		ir = instruction_read(bf);	
		
		char binInstr[5];
				
		strcpy(binInstr, instruction_assembly_form(ir));
		
		printf("%s\n", binInstr);


		
	}*/
}
