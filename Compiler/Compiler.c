//c6502 Compiler
//Copyright (C) 2019 Amélia O. F. da S.
//Development started at 00:33, April 29th 2018

#include <stdio.h>
#include <stdlib.h>
#define size 15
#define SP 0x7000
#define labelbin "c6502.lbin"
void (*com[size])(char* a);
char* f[size];
char* sug;
FILE* in;
FILE* out;
FILE* tout;
int pc=0;

char** l;
int* ll;
int* lll;
int la=0;

int* sublab;
int sle;
int sli;

void copy(void* a,void* b,int len)
{
    int i,j;
    char u;
    for(i=0;i<len;i++){
        ((char*)a)[i]=u=((char*)b)[i];
    }
}

int cof(char* a)
{
    int i=0,j,ret=-1,sui=0,put;
    free(sug);
    sug=malloc(15);
    for(i=0;i<size;i++)
    {
        j=0;
        put=0;
        while(a[j]!=0x0)
        {
            if(a[j]!=f[i][j])
                goto next;
            if(!put)
            {
                sug[sui*3]=f[i][0];
                sug[sui*3+1]=f[i][1];
                sug[sui*3+2]=f[i][2];
                sug[sui*3+3]=',';
                sui++;
                put=1;
            }
            j++;
        }
        ret=i;
        break;
        next:;
    }
    sug[sui*3]=0x0;
    return ret;
}

void imm(char* a, char* b) //b={immediate,zp,zpx,abs,absx,absy,indx,indy}
{
    int i=0,state=0;
    char buf[3];
    char tbuf[3];
    while(a[i]!=0x0)
    {
        switch(state)
        {
            case 0:
                switch(a[i])
                {
                    case '#': //COM %N
                        if(b[0]=="0x00")
                        {
                            printf("Warning: Format \"%s\" uses immediate addressing. This mnemonic does not support it. Ignoring.\n",a);
                            return;
                        }
                        buf[0]=b[0];
                        buf[1]=(char)atoi(&a[1]);
                        fwrite(buf,2,1,out);
                        pc+=2;
                        return;
                    break;
                    default:
                        i--;
                        state=1;
                    break;
                }
            break;
            case 1:
                if(a[i]=='(')
                {
                    if(a[i+6]==')') //COM {$10,X}
                    {
                        buf[0]=(char)b[6];
                        a[i+2]=(char)0x0;
                        buf[1]=(char)strtol(&a[i+2],NULL,16);
                        fwrite(buf,2,1,out);
                        pc+=2;
                        return;
                    }
                    else //COM {$10},Y
                    {
                        buf[0]=(char)b[7];
                        a[i+5]=(char)0x0;
                        buf[1]=(char)strtol(&a[i+2],NULL,16);
                        fwrite(buf,2,1,out);
                        pc+=2;
                        return;
                    }
                    
                }
                else if(a[i+3]==0x0) //COM $XX
                {
                    buf[0]=(char)b[1];
                    buf[1]=(char)strtol(&a[i+1],NULL,16);
                    fwrite(buf,2,1,out);
                    pc+=2;
                    return;
                }
                else if(a[i+3]==',') //COM $XX,X
                {
                    buf[0]=(char)b[2];
                    a[i+2]=(char)0x0;
                    buf[1]=(char)strtol(&a[i+1],NULL,16);
                    fwrite(buf,2,1,out);
                    pc+=2;
                    return;
                }
                else if(a[i+5]==0x0) //COM $XXXX
                {
                    buf[0]=(char)b[3];
                    *(short int*)&buf[1]=(short int)strtol(&a[i+1],NULL,16);
                    tbuf[0]=buf[1];
                    buf[1]=buf[2];
                    buf[2]=tbuf[0];
                    fwrite(buf,3,1,out);
                    pc+=3;
                    return;
                }
                else //COM $XXXX,R
                {
                    buf[0]=a[i+6]=='X'?(char)b[4]:(char)b[5];
                    a[i+5]=(char)0x0;
                     *(short int*)&buf[1]=(short int)strtol(&a[i+1],NULL,16);
                    tbuf[0]=buf[1];
                    buf[1]=buf[2];
                    buf[2]=tbuf[0];
                    fwrite(buf,3,1,out);
                    pc+=3;
                    return;
                }
                
            break;
        }
        i++;
    }
}

void adc(char* a)
{
    char x[]={0x69,0x65,0x75,0x6D,0x7D,0x79,0x61,0x71};
    imm(a,x);
}

//b={immediate,zp,zpx,abs,absx,absy,indx,indy}

void inx(char* a)
{
	char*buf=malloc(1);
	buf[0]=(char)0xe8;
	fwrite(buf,1,1,out);
	pc+=1;
}

void stx(char* a)
{
    char x[]={0x00,0x86,0x96,0x8E,0x00,0x00,0x00,0x00};
    imm(a,x);
}

void ldx(char* a)
{
    char x[]={0xA2,0xA6,0xB6,0xAE,0x00,0xBE,0x00,0x00};
    imm(a,x);
}

void sty(char* a)
{
    char x[]={0x00,0x84,0x94,0x8C,0x00,0x00,0x00,0x00};
    imm(a,x);
}

void ldy(char* a)
{
    char x[]={0xA0,0xA4,0xB4,0xAC,0x00,0xBC,0x00,0x00};
    imm(a,x);
}

void cpx(char* a)
{
    char x[]={0xE0,0xE4,0x00,0xEC,0x00,0x00,0x00,0x00};
    imm(a,x);
}

void sta(char* a)
{
    char x[]={0x00,0x85,0x95,0x8D,0x9D,0x99,0x81,0x91};
    imm(a,x);
}

void lda(char* a)
{
    char x[]={0xA9,0xA5,0xB5,0xAD,0xBD,0xB9,0xA1,0xB1};
    imm(a,x);
}

void cmp(char* a)
{
    char x[]={0xC9,0xC5,0xD5,0xCD,0xDD,0xD9,0xC1,0xD1};
    imm(a,x);
}

void beq(char* a)
{
    char* buf=malloc(2);
    buf[0]=(char)0xf0;
    buf[1]=(char)atoi(&a[1]);
    fwrite(buf,2,1,out);
    pc+=2;
}

void markl(int ad)
{
    if(ad<0x7000)
    {
        int* nsublab=malloc(sle+1);
        copy(nsublab,sublab,sle*sizeof(int));
        nsublab[sle]=pc+1;
        free(sublab);
        sublab=malloc(sle+1);
        sle++;
        copy(sublab,nsublab,sle*sizeof(int));
    }
}

void jmp(char* a)
{
    char* buf=malloc(3);
    int ad;
    if(a[0]=='(') //JMP ($0000)
    {
        buf[0]=(char)0x6c;
        ad=lab(&a[1]);
        *(short int*)&buf[1]=(short int)(ll[ad]);
    }
    else
    {
        buf[0]=(char)0x4c;
        ad=lab(&a[0]);
        *(short int*)&buf[1]=(short int)(ll[ad]);
    }
    markl(ll[ad]);
    fwrite(buf,3,1,out);
    pc+=3;
}

void jsr(char* a)
{
    char* buf=malloc(3);
    buf[0]=(char)0x20;
    *(short int*)&buf[1]=(ll[lab(&a[0])]);
    markl(*(short int*)&buf[1]);
    fwrite(buf,3,1,out);
    pc+=3;
}

void rts(char* a)
{
    char* buf=malloc(1);
    buf[0]=0x60;
    fwrite(buf,1,1,out);
    pc+=1;
}

void inte(char* a)
{
    char* buf=malloc(2);
    buf[0]=(char)0x03;
    buf[1]=(char)atoi(a);
    fwrite(buf,2,1,out);
    pc+=2;
}

int setL(char* a,int pc)//Sets the address {pc} that points {a} points to
{
    int p=lab(a);
    printf("Associated label %s to %X\n",a,pc);
    ll[p]=pc;
    return p;
}

int creL(char* a)//Creates a new label {a}
{
    printf("Created label %s\n",a);
    char** tempBuf;
    int* tempInt;
    tempBuf=malloc((la+1)*sizeof(char*));
    tempInt=malloc((la+1)*sizeof(int));
    for(int i=0;i<la;i++)
    {
        tempBuf[i]=malloc(3);
        for(int j=0;j<3;j++)
        {
            tempBuf[i][j]=l[i][j];
        }
        tempInt[i]=ll[i];
    }
    l=tempBuf;
    l[la]=malloc(3);
    l[la][0]=a[0];
    l[la][1]=a[1];
    l[la][2]=a[2];
    ll=tempInt;
    ll[la]=la;
    return la++;
}

int lab(char* a)
{
    int i=0,j,ret=-1,sui=0,put;
    sug=malloc(15);
    for(i=0;i<la;i++)
    {
        j=0;
        put=0;
        while(a[j]!=0x0)
        {
            if(a[j]!=l[i][j])
                goto next;
            if(!put)
            {
                sug[sui*3]=l[i][0];
                sug[sui*3+1]=l[i][1];
                sug[sui*3+2]=l[i][2];
                sug[sui*3+3]=',';
                sui++;
                put=1;
            }
            j++;
        }
        ret=i;
        break;
        next:;
    }
    sug[sui*3]=0x0;
    if(ret==-1)ret = creL(a);
    printf("Label %s found. Address %X. ID %d\n",a,ll[ret],ret);
    return ret;
}

int main(int argc,char** args)
{
    printf("cc6502\nCopyright (C) 2019 Amélia O. F. da S.\n");

    sli=0;
    sle=0;
    sublab=malloc(1);

    f[0]="ADC";
    com[0]=adc;

    f[1]="STA";
    com[1]=sta;

    f[2]="LDA";
    com[2]=lda;

    f[3]="CMP";
    com[3]=cmp;

    f[4]="BEQ";
    com[4]=beq;

    f[5]="JMP";
    com[5]=jmp;
    
    f[6]="STX";
    com[6]=stx;

    f[7]="LDX";
    com[7]=ldx;

    f[8]="CPX";
    com[8]=cpx;
    
    f[9]="INX";
    com[9]=inx;

    f[10]="LDY";
    com[10]=ldy;

    //Nonstandard. Byte 0x03
    f[11]="INT";
    com[11]=inte;

    f[12]="RTS";
    com[12]=rts;

    f[13]="JSR";
    com[13]=jsr;

    f[14]="STY";
    com[14]=sty;

    int i;
    char* buf=malloc(64);
    char* bufb=malloc(64);
    sug=malloc(1);
    /*for(i=0;i<argc;i++)
    {
        printf("%s",args[i]);;
    }*/
    if(argc==1)
    {
        printf("Please specify the input file: ");
        scanf("%s",buf);
        in=fopen(buf,"r");
        printf("Please specify the output file: ");
        scanf("%s",buf);
        tout=fopen(buf,"wb");
    }
    else if(argc==2)
    {
        in=fopen(args[1],"r");
        printf("Please specify the output file: ");
        scanf("%s",buf);
        tout=fopen(buf,"wb");
    }
    else
    {
        in=fopen(args[1],"r");
        tout=fopen(args[2],"wb");
    }
    out=fopen(labelbin,"wb");
    printf("Compiling file...\n");
    int j=0;
    while(fscanf(in,"%s",buf)!=EOF)
    {
        if(buf[0]=='#')
        {
            fscanf(in,"%[^\n]\n",bufb);
            continue;
        }
        if(buf[0]==':')
        {
            setL(&buf[1],pc+SP);
            continue;
        }
        fscanf(in,"%s",bufb);
        if(argc>3)printf("%s %s\n",buf,bufb);
        i=cof(buf);
        if(i==-1)
        {
            printf("Compilation error at line \"%s %s\". Mnemonic not found (Did you mean %s?).\n",buf,bufb,sug);
            return -1;
        }
        com[i](bufb);
    }
    fclose(out);
    printf("Compilation complete.\nAddressing labels...\n");
    out=fopen(labelbin,"r");
    char c;
    sli=0;
    pc=0;
    while((c=fgetc(out))!=EOF)
    {
        fputc(c,tout);
        pc++;
        if(argc>4)printf("%X ", (unsigned char)c);
        if(pc==sublab[sli] && sli<sle)
        {
            buf[0]=fgetc(out);
            buf[1]=fgetc(out);
            i=(*(short int*)buf);
            if(i<0x7000)
            {
                i=ll[i];
                fputc(((char*)&i)[0],tout);fputc(((char*)&i)[1],tout);
            }
            else
            {
                fputc(buf[0],tout);fputc(buf[1],tout);
            }
            pc+=2;
            sli++;
        }
    }
    fclose(tout);
    printf("Done!\n");
    return 0;
}
