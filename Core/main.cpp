//c6502 Interpreter
//Copyright (C) 2019 Amélia O. F. da S.
//Development started at 00:33, April 29th 2018

#include <iostream>
#include <fstream>
#include <string>
#include "globals.h"
#include "Instructions/ADC.h"
#include "Instructions/AND.h"
#include "Instructions/LDX.h"
#include "Instructions/LDY.h"
#include "Instructions/LDA.h"
#include "Instructions/STX.h"
#include "Instructions/STY.h"
#include "Instructions/STA.h"
#include "Instructions/ASL.h"
#include "Instructions/BCC.h"
#include "Instructions/BCS.h"
#include "Instructions/BEQ.h"
#include "Instructions/BIT.h"
#include "Instructions/BMI.h"
#include "Instructions/BNE.h"
#include "Instructions/BPL.h"
#include "Instructions/BVC.h"
#include "Instructions/BVS.h"
#include "Instructions/CLC.h"
#include "Instructions/CLD.h"
#include "Instructions/CLI.h"
#include "Instructions/CLV.h"
#include "Instructions/CMP.h"
#include "Instructions/CPX.h"
#include "Instructions/CPY.h"
#include "Instructions/DEC.h"
#include "Instructions/DEX.h"
#include "Instructions/DEY.h"
#include "Instructions/EOR.h"
#include "Instructions/INC.h"
#include "Instructions/INX.h"
#include "Instructions/INY.h"
#include "Instructions/JMP.h"
#include "Instructions/JSR.h"
#include "Instructions/RTS.h"
#include "Extensions/Ext.h"

using namespace std;

//This interpreter is little-endian

void plotmem(int s,int f,int lin)
{
	int i,j=0;
	printf("    ");
	for(i=s;i<s+lin;i++)printf("|%2X ",i-s);
	printf("\n%4X",i);
	for(i=s;i<f;i++)
	{
		if(i==PC)printf("[%2X]",memory[i]);
		else printf("|%2X ",memory[i]);
		if(++j==lin){printf("\n%4X",i);j=0;}
	}
	printf("\n");
}

int main(int argc, char** argv)
{
	printf("c6502\nCopyright (C) 2019 Amélia O. F. da S.\n");

	if(argc<2)
	{
		printf("No input file. Shutting down.\n");
		return 0;
	}
	
	//Function pointer array, so that we can easily "translate" bytecode into function calls
	void (*bc[0xff])(unsigned char a1, unsigned char a2); // a1= arg1, a2= arg2
	//Here's where we set the actual pointers
	//Format: bc[0xOpcode]=COM_mode (mode = [ac]cumulator, [r]elative, [im]mediate, [z]ero-page, [z]+[x], [abs]olute, [abs]+[x], [abs]+[y], ([ind]irect,[x]), ([ind]irect)+[y])
	
	bc[0x69]=ADC_im;
	bc[0x65]=ADC_z;
	bc[0x75]=ADC_zx;
	bc[0x6d]=ADC_abs;
	bc[0x7d]=ADC_absx;
	bc[0x79]=ADC_absy;
	bc[0x61]=ADC_indx;
	bc[0x71]=ADC_indy;
	
	bc[0xa2]=LDX_im;
	bc[0xa6]=LDX_z;
	bc[0xb6]=LDX_zy;
	bc[0xae]=LDX_abs;
	bc[0xbe]=LDX_absy;

	bc[0xa0]=LDY_im;
	bc[0xa4]=LDY_z;
	bc[0xb4]=LDY_zy;
	bc[0xac]=LDY_abs;
	bc[0xbc]=LDY_absy;

	bc[0xa9]=LDA_im;
	bc[0xa5]=LDA_z;
	bc[0xb5]=LDA_zx;
	bc[0xad]=LDA_abs;
	bc[0xbd]=LDA_absx;
	bc[0xb9]=LDA_absy;
	bc[0xa1]=LDA_indx;
	bc[0xb1]=LDA_indy;
	
	bc[0x86]=STX_z;
	bc[0x96]=STX_zy;
	bc[0x8e]=STX_abs;

	bc[0x84]=STY_z;
	bc[0x94]=STY_zx;
	bc[0x8c]=STY_abs;

	bc[0x85]=STA_z;
	bc[0x95]=STA_zx;
	bc[0x8d]=STA_abs;
	bc[0x9d]=STA_absx;
	bc[0x99]=STA_absy;
	bc[0x81]=STA_indx;
	bc[0x91]=STA_indy;
	
	bc[0x29]=AND_im;
	bc[0x25]=AND_z;
	bc[0x35]=AND_zx;
	bc[0x2d]=AND_abs;
	bc[0x3d]=AND_absx;
	bc[0x39]=AND_absy;
	bc[0x21]=AND_indx;
	bc[0x31]=AND_indy;
	
	bc[0x0a]=ASL_ac;
	bc[0x06]=ASL_z;
	bc[0x16]=ASL_zx;
	bc[0x0e]=ASL_abs;
	bc[0x1e]=ASL_absx;
	
	bc[0x90]=BCC_r;
	
	bc[0xb0]=BCS_r;
	
	bc[0xf0]=BEQ_r;
	
	bc[0x24]=BIT_z;
	bc[0x2c]=BIT_abs;
	
	bc[0x30]=BMI_r;
	
	bc[0xd0]=BNE_r;
	
	bc[0x10]=BPL_r;
	
	bc[0x50]=BVC_r;
	
	bc[0x70]=BVS_r;
	
	bc[0x18]=CLC;
	
	bc[0xd8]=CLD;
	
	bc[0x58]=CLI;
	
	bc[0xb8]=CLV;
	
	bc[0xc9]=CMP_im;
	bc[0xc5]=CMP_z;
	bc[0xd5]=CMP_zx;
	bc[0xcd]=CMP_abs;
	bc[0xdd]=CMP_absx;
	bc[0xd9]=CMP_absy;
	bc[0xc1]=CMP_indx;
	bc[0xd1]=CMP_indy;
	
	bc[0xe0]=CPX_im;
	bc[0xe4]=CPX_z;
	bc[0xec]=CPX_abs;
	
	bc[0xc0]=CPY_im;
	bc[0xc4]=CPY_z;
	bc[0xcc]=CPY_abs;
	
	bc[0xc6]=DEC_z;
	bc[0xd6]=DEC_zx;
	bc[0xce]=DEC_abs;
	bc[0xde]=DEC_absx;
	
	bc[0xca]=DEX;
	
	bc[0x88]=DEY;
	
	bc[0x49]=EOR_im;
	bc[0x45]=EOR_z;
	bc[0x55]=EOR_zx;
	bc[0x4d]=EOR_abs;
	bc[0x5d]=EOR_absx;
	bc[0x59]=EOR_absy;
	bc[0x41]=EOR_indx;
	bc[0x51]=EOR_indy;
	
	bc[0xe6]=INC_z;
	bc[0xf6]=INC_zx;
	bc[0xee]=INC_abs;
	bc[0xfe]=INC_absx;
	
	bc[0xe8]=INX;
	
	bc[0xc8]=INY;
	
	bc[0x4c]=JMP_abs;
	bc[0x6c]=JMP_ind;
	
	bc[0x20]=JSR_abs;
	
	bc[0x60]=RTS;

	bool ext=extend(bc,memory);
	
	//End of pointer-setting section
	
	ifstream fil;
	fil.open (argv[1], ios::binary);
	unsigned char b;
	unsigned short i=PS;
	printf("Downloading bytecode...\r\n");
	streampos be,en;
	be=fil.tellg();
	fil.seekg(0,ios::end);
	en=fil.tellg();
	fil.seekg(0,ios::beg);
	unsigned int size=en-be;
	while(i<PS+en)
	{
		b=fil.get();
		printf("\rByte %i of %i.",i-(PS-1),size);
		memory[i]=b;
		i++;
	}

	printf("\r\nClosing file...\r\n");
	fil.close();

	int bp=PS;
	int n=0;
	//Here starts the sorcery
	while(memory[PC]!=0)
	{
		printf("\rPC= %x, Registers [A,X,Y]=[%X,%X,%X]",PC,A,X,Y);
		if(argc>2)
		{
			printf("\nReading %x at %x\n",memory[PC],PC-0x7000);
			plotmem(0x19f,0x1ff,0xA);
			plotmem(0x7000,0x7050,0xA);
			if(argc>3 &&((PC==bp)||n))
			{
				printf("ADB ON\n");
				n=0;
				while((b=getchar())=='\n'){}
				if(b=='b')
				{
					scanf("%X",&bp);
					if(bp==-1)bp=PS;
					//bp+=PS;
				}
				else if(b=='n')n=1;
			}
		}
		if(ext)extstep(bc,memory);
		(bc[memory[PC]])(memory[PC+1],memory[PC+2]);
	}
	
	printf("\r\nBRK interruption. Halting.\r\n");
	printf("Addresses $00 through $60\n");
	plotmem(0x00,0x60,0xA);
	printf("\nProgram area\n");
	plotmem(0x7000,0x7050,0xA);
	if(argc>2)
	{
		printf("Debug mode enabled. Dumping memory to out.dump\r\n");
		ofstream ofi ("out.dump", ios::binary);
		ofi.write((const char*)memory,0xffff);
		ofi.close();
		printf("Memory dump complete.");
	}
	
	return 0;
}
