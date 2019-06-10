//This serves for extending the basic functionalities of the interpreter
//This sample extension implements memory sector-based text IO
//Output sector is $3000, input sector is $2000
//Flush the input by writing 0x00 at $2000

//This will be called at startup.

void interrupt(unsigned char a1, unsigned char a2)
{
    if(a1==11) //INT 11 = ii = scanf to $2000
    {
        scanf("%[^\n]",&memory[0x2000]);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    else if(a1==00)
    {
        int i=0x3000;
        while(memory[i]!=0x0)
        {
            printf("%c",memory[i]);
            memory[i]=0x0;
            i++;
        }
    }
    PC+=2;
}

bool extend(void (**bc)(unsigned char a1, unsigned char a2),unsigned char* memory)
{
    bc[0x03]=interrupt;
    return 1;
}

//This will be called at every step.

bool extstep(void (**bc)(unsigned char a1, unsigned char a2),unsigned char* memory)
{
    return 0;
}