#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned int b, br, bl, mul, add, sub, addi, subi, adds, subs, addis, subis, and, orr, eor, andi, orri, eori, lsl, lsr, cbz, cbnz, beq, bne, blt, ble, bgt, bge, blo, bls, bhi, bhs, ldur,stur,ldursw,sturw,ldurh,sturh,ldurb,sturb;
unsigned int regarray[32];
unsigned int *codearray[256][5];
unsigned int *datarray[256][2];
int entry, position,dataindex = 0;
int N, Z, V, C;

unsigned int num;
char dataflg = 0;
int addr = 0xfffffff0;
int daddr = 0x11111110;

void addFLAG(unsigned int c, unsigned int a, unsigned int b){
    N=0;
    Z=0;
    V=0;
    C=0;
    
    N=c>>31;
    if(c==0){Z=1;}
    
    if( (a>>31)==0 && (b>>31)==0 && (c>>31)==1 ){V=1;}// (+) + (+) = (-)
    if( (a>>31)==1 && (b>>31)==1 && (c>>31)==0 ){V=1;C=1;}// (-) + (-) = (+)
    
    if( (a>>31)==1 && (b>>31)==0 && (c>>31)==0 ){C=1;}// 1 + 0 = 0
    if( (a>>31)==0 && (b>>31)==1 && (c>>31)==0 ){C=1;}// 0 + 1 = 0
    //printf("A = %d, B = %d, C= %d\n",a>>31,b>>31,c>>31);
}


void subFLAG(unsigned int c, unsigned int a, unsigned int b){
    N=0;
    Z=0;
    V=0;
    C=0;

    N=c>>31;
    if(c==0){Z=1;}
    
    if( (a>>31)==0 && (b>>31)==1 && (c>>31)==1 ){V=1;}// (+) - (-) = (-)
    if( (a>>31)==1 && (b>>31)==0 && (c>>31)==0 ){V=1;}// (-) - (+) = (+)
    
    if( (a>>31)==0 && (b>>31)==0 && (c>>31)==1 ){C=1;}// 0 - 0 = 1
    printf("A = %d, B = %d, C= %d\n",a>>31,b>>31,c>>31);
    printf("N=%d, Z=%d, V=%d, C=%d, Data Flag=%d\n\n",N, Z, V, C,dataflg);
    

}


unsigned int* OPINPUT(char *token){ //if ladder for "registers"
    //need to add logic to search for comments
        if(strcmp(token,"x0")==0){
            return &regarray[0];
        }
        else if(strcmp(token,"x1")==0){
            return &regarray[1];
        }
        else if(strcmp(token,"x2")==0){
            return &regarray[2];
        }
        else if(strcmp(token,"x3")==0){
            return &regarray[3];   
        }
        else if(strcmp(token,"x4")==0){
            return &regarray[4];   
        }
        else if(strcmp(token,"x5")==0){
            return &regarray[5];   
        }
        else if(strcmp(token,"x6")==0){
            return &regarray[6];   
        }
        else if(strcmp(token,"x7")==0){
            return &regarray[7];   
        }
        else if(strcmp(token,"x8")==0){
            return &regarray[8];   
        }
        else if(strcmp(token,"x9")==0){
            return &regarray[9];   
        }
        else if(strcmp(token,"x10")==0){
            return &regarray[10];   
        }
        else if(strcmp(token,"x11")==0){
            return &regarray[11];   
        }
        else if(strcmp(token,"x12")==0){
            return &regarray[12];   
        }
        else if(strcmp(token,"x13")==0){
            return &regarray[13];   
        }
        else if(strcmp(token,"x14")==0){
            return &regarray[14];   
        }
        else if(strcmp(token,"x15")==0){
            return &regarray[15];   
        }
        else if(strcmp(token,"x16")==0){
            return &regarray[16];   
        }
        else if(strcmp(token,"x17")==0){
            return &regarray[17];   
        }
        else if(strcmp(token,"x18")==0){
            return &regarray[18];   
        }
        else if(strcmp(token,"x19")==0){
            return &regarray[19];   
        }
        else if(strcmp(token,"x20")==0){
            return &regarray[20];   
        }
        else if(strcmp(token,"x21")==0){
            return &regarray[21];   
        }
        else if(strcmp(token,"x22")==0){
            return &regarray[22];   
        }
        else if(strcmp(token,"x23")==0){
            return &regarray[23];   
        }
        else if(strcmp(token,"x24")==0){
            return &regarray[24];   
        }
        else if(strcmp(token,"x25")==0){
            return &regarray[25];   
        }
        else if(strcmp(token,"x26")==0){
            return &regarray[26];   
        }
        else if(strcmp(token,"x27")==0){
            return &regarray[27];   
        }
        else if(strcmp(token,"x28")==0){
            return &regarray[28];   
        }
        else if(strcmp(token,"x29")==0){
            return &regarray[29];   
        }
        else if(strcmp(token,"x30")==0){
            return &regarray[30];   
        }
        else if(strcmp(token,"x31")==0){
            return &regarray[31];   
        }
        else if(strcmp(token,"sp")==0){
            return &regarray[28];   
        }
        else if(strcmp(token,"lr")==0){
            return &regarray[30];   
        }
        else if(strcmp(token,"xzr")==0){
            return &regarray[31];   
        }
        else{
            if(strchr(token,'#')){
                token[0] = '0';
                num = atoi(token);
                //prunsigned intf("%s",token);
                return &num;
            }//add else statement here to return error locations
        return 0;}
    
return 0;   
}

void OPCODE(unsigned int *datain){ //if ladder for opcode

    //printf("Exec-> %x\n",datain);


    if(datain == &mul){
        //printf("MUL start\n");
        *codearray[position][2] = *codearray[position][3] *  *codearray[position][4];
        printf("MUL start = %d\n",*codearray[position][2]);
        //printf("%d X %d = %d\n",*codearray[position][3],*codearray[position][4],*codearray[position][2]);
        //*codearray[position][2]=calc;

    }    if(datain == &add){
        if(*codearray[position][3]==regarray[28]){
            unsigned int calc = *codearray[position][3] + (*codearray[position][4])/8;
            *codearray[position][2]=calc;
        }else{      
            unsigned int calc = *codearray[position][3] + *codearray[position][4];
            *codearray[position][2]=calc;
        }


        printf("ADD start=%d\n", *codearray[position][2]);

    }
    else if(datain == &sub){
                
       if(*codearray[position][3]==regarray[28]){
            unsigned int calc = *codearray[position][3] - (*codearray[position][4])/8;
            *codearray[position][2]=calc;
        }else{      
            unsigned int calc = *codearray[position][3] - *codearray[position][4];
            *codearray[position][2]=calc;
        }        
    printf("SUB start=%d\n", *codearray[position][2]);
    }
    else if(datain == &addi){        
        //printf("ADDI start\n");
        if(*codearray[position][3]==regarray[28]){
            unsigned int calc = *codearray[position][3] + ((unsigned int)codearray[position][4])/8;
            *codearray[position][2]=calc;
        }else{      
            unsigned int calc = *codearray[position][3] + ((unsigned int)codearray[position][4]);
            *codearray[position][2]=calc;
        }
        printf("ADDI start = %d\n",*codearray[position][2]);
    }
    else if(datain == &subi){
        //printf("SUBI start\n");
        if(*codearray[position][3]==regarray[28]){
            unsigned int calc = *codearray[position][3] - ((unsigned int)codearray[position][4])/8;
            *codearray[position][2]=calc;
        }else{      
            unsigned int calc = *codearray[position][3] - ((unsigned int)codearray[position][4]);
            *codearray[position][2]=calc;
        }
        printf("SUBI start = %d\n",*codearray[position][2]);
    }
    else if(datain == &adds){
        printf("ADDS start\n");
        unsigned int a = *codearray[position][3];
        unsigned int b = *codearray[position][4];
        unsigned int calc = *codearray[position][3] + *codearray[position][4];
        *codearray[position][2]=calc;
        addFLAG(calc,a,b);
    }
    else if(datain == &subs){

        unsigned int a = *codearray[position][3];
        unsigned int b = *codearray[position][4];       
        unsigned int calc = *codearray[position][3] - *codearray[position][4];
        *codearray[position][2]=calc;
        printf("SUBS start=%d\n", *codearray[position][2]);

        subFLAG(calc,*codearray[position][3],*codearray[position][4]);
        addFLAG(calc,a,b);
    }
    else if(datain == &addis){        
        printf("ADDIS start\n");
        unsigned int a = *codearray[position][3];
        unsigned int b = ((unsigned int)codearray[position][4]);
        unsigned int calc = *codearray[position][3] + ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
        addFLAG(calc,a,b);
    }
    else if(datain == &subis){
        printf("SUBIS start\n");
        unsigned int a = *codearray[position][3];
        unsigned int b = ((unsigned int)codearray[position][4]);      
        unsigned int calc = *codearray[position][3] - ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
        subFLAG(calc,a,b);
    }
    else if(datain == &and){
        printf("AND start\n");        
        unsigned int calc = *codearray[position][3] & *codearray[position][4];
        *codearray[position][2]=calc;
    }
    else if(datain == &orr){
        printf("ORR start\n");        
        unsigned int calc = *codearray[position][3] | *codearray[position][4];
        *codearray[position][2]=calc;
    }
    else if(datain == &eor){
        printf("EOR start\n");        
        unsigned int calc = *codearray[position][3] ^ *codearray[position][4];
        *codearray[position][2]=calc;
    }
    else if(datain == &andi){
               
        unsigned int calc = *codearray[position][3] & ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
        printf("ANDI Value = %d\n",*codearray[position][2]); 
    }
    else if(datain == &orri){
        printf("ORRI start\n");        
        unsigned int calc = *codearray[position][3] | ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
    }
    else if(datain == &eori){
        printf("EORI start\n");        
        unsigned int calc = *codearray[position][3] ^ ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
    }
    else if(datain == &lsl){
        unsigned int calc = *codearray[position][3] << ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
        printf("LSL start=%d\n", *codearray[position][2]);
    }
    else if(datain == &lsr){
        //printf("LSR start\n");        
        unsigned int calc = *codearray[position][3] >> ((unsigned int)codearray[position][4]);
        *codearray[position][2]=calc;
        printf("LSR start = %d\n",*codearray[position][2]);
    }
    else if(datain == &cbnz){
        int jump = 0;
        printf("CBNZ start\n");        
        if(*codearray[position][2]!=0){

            while(codearray[position][3] != codearray[jump][1]){ 
            jump++;
            }
        printf("jump to %d\n",jump);
        position = jump;
        } 
    }
    else if(datain == &cbz){
        int jump = 0;
        printf("CBZ start\n");        
        if(*codearray[position][2]==0){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &beq){
        int jump = 0;
        printf("B.EQ start\n");        
        if(Z==1){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bne){
        int jump = 0;
        printf("B.NE start\n");        
        if(Z==0){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &blt){
        int jump = 0;
        printf("B.LT start\n");        
        if(N!=V){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &ble){
        int jump = 0;
        printf("B.LE start\n");        
        if(~(Z==0 && N==V)){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bgt){
        int jump = 0;
        printf("B.GT start\n");        
        if((Z==1)){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bge){
        int jump = 0;
        printf("B.GE start\n");        
        if(N==V){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &blo){
        int jump = 0;
        printf("B.LO start\n");        
        if(C==0){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bls){
        int jump = 0;
        printf("B.LS start\n");        
        if(~(Z==0 && C==1)){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bhi){
        int jump = 0;
        printf("B.HI start\n");        
        if((Z==0 && C==1)){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &bhs){
        int jump = 0;
        printf("B.HS start\n");        
        if(C==1){
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump;
        }  
    }
    else if(datain == &ldur){
        //printf("LDUR start\n");
            //if(*codearray[position][3]!= regarray[28]){
            //    printf("Invalid Memory for LDUR\n");
            //    exit(0);
            //}
        unsigned int a2 = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
        unsigned int a1 = regarray[29] - a2;
        *codearray[position][2] = datarray[a1][1];
        printf("LDUR start = %x\n",a2);
    }
    else if(datain == &ldursw){
        printf("LDURSW start\n");
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for LDURW\n");
            exit(0);
        }        
        //*codearray[position][3] = datarray[0][0]; 
        *codearray[position][2] = (int)datarray[(((unsigned int)codearray[position][4]))/8][1];

    }
    else if(datain == &ldurh){
        printf("LDURH start\n"); 
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for LDURH\n");
            exit(0);
        }        
        //*codearray[position][3] = datarray[0][0]; 
        *codearray[position][2] = (short) datarray[(((unsigned int)codearray[position][4]))/4][1];

    }
    else if(datain == &ldurb){
        printf("LDURB start\n");
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for LDURH\n");
            exit(0);
        }        
        //*codearray[position][3] = datarray[0][0]; 
        *codearray[position][2] = (char) datarray[(((unsigned int)codearray[position][4]))/2][1];


    }
    else if(datain == &stur){
        //if(*codearray[position][3]!= regarray[28]){
        //    printf("Invalid Memory for STUR\n");
        //    exit(0);
        //}        
        
        unsigned int a2 = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
        unsigned int a1 = regarray[29] - a2;
        datarray[a1][1] = *codearray[position][2];
        datarray[a1][0] = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
    printf("STUR start = %x\n",a2);
    }
    else if(datain == &sturw){
        printf("STURW start\n");        
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for STURW\n");
            exit(0);
        }        
        unsigned int a2 = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
        unsigned int a1 = regarray[29] - a2;
        datarray[a1][1] = *(unsigned int*)codearray[position][2];
        datarray[a1][0] = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
    }
    else if(datain == &sturh){
        printf("STURH start\n");        
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for STURH\n");
            exit(0);
        }        
        unsigned int a2 = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
        unsigned int a1 = regarray[29] - a2;
        datarray[a1][1] = *(unsigned short*)codearray[position][2];
        datarray[a1][0] = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
    }
    else if(datain == &sturb){
        printf("STURB start\n");        
        if(*codearray[position][3]!= regarray[28]){
            printf("Invalid Memory for STURB\n");
            exit(0);
        }        
        unsigned int a2 = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
        unsigned int a1 = regarray[29] - a2;
        datarray[a1][1] = *(unsigned char*)codearray[position][2];
        datarray[a1][0] = *codearray[position][3]+(((unsigned int)codearray[position][4])/8);
    }
    else if(datain == &bl){
        int jump = 0;
        regarray[30] = position;
        printf("BL start\n");        
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump; 
    }

    else if(datain == &br){
        printf("BR start\n");
        if(regarray[28] == regarray[29]){
            printf("Bottom of stack\n");
            position = entry;
        }else{
            position = *codearray[position][3];
            printf("Position at %d\n",position);
        }
    }
    else if(datain == &b){
        int jump = 0;
        printf("B start\n");        
            while(codearray[position][3] != codearray[jump][1]){ 
            //printf("jump to %d\n",jump);
            jump++;
            }
        position = jump; 
    }      
regarray[31] = 0;
}




void opcode2array(char *string){ //if ladder for opcode
    //printf("\n\t\t\t%s",string);
    char *token;
    char string2[strlen(string)];
    memmove(string2, string, strlen(string));
    //printf("String = %s\n",string);
    token = strtok(string," ,\n");
    //printf("Token = %s\n",token);
    if(token!=NULL){
        if(strcmp(token,"MUL")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&mul;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            //*codearray[entry][2] = *codearray[entry][3] + *codearray[entry][4];
            
            addr++;
            entry++;

        }
        if(strcmp(token,"ADD")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&add;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            //*codearray[entry][2] = *codearray[entry][3] + *codearray[entry][4];
            
            addr++;
            entry++;

        }
        if(strcmp(token,"SUB")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&sub;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            //*codearray[entry][2] = *codearray[entry][3] - *codearray[entry][4];
            
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"ADDI")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&addi;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            //*codearray[entry][2] = *codearray[entry][3] + ((unsigned int)codearray[entry][4]);
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"SUBI")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&subi;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            //*codearray[entry][2] = *codearray[entry][3]- ((unsigned int)codearray[entry][4]);        
            addr++;
            entry++;

        }
        if(strcmp(token,"ADDS")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&adds;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
                    
            addr++;
            entry++;

        }
        else if(strcmp(token,"SUBS")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&subs;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);        
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"ADDIS")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&addis;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"SUBIS")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&subis;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,*codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,*codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]); 

            addr++;
            entry++;

        }
        
        else if(strcmp(token,"AND")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&and;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
                    
            addr++;
            entry++;

        }
        else if(strcmp(token,"ORR")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&orr;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);        
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"EOR")==0){
            dataflg = 0;
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&eor;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= OPINPUT(token); 
            printf("%s = %x\n",token,codearray[entry][4]);        
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"EORI")==0){
            
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&eori;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"ORRI")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&orri;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            
            addr++;
            entry++;

        }
        else if(strcmp(token,"ANDI")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&andi;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"LSR")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&lsr;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"LSL")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&lsl;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"CBNZ")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&cbnz;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"CBZ")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&cbz;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.EQ")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&beq;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.NE")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bne;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.LT")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&blt;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.LE")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ble;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.GT")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bgt;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.GE")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bge;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.LO")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&blo;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.LS")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bls;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.HI")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bhi;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B.HS")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bhs;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"LDUR")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ldur;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"LDURSW")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ldursw;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"LDURH")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ldurh;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"LDURB")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ldurb;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"LDUR")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&ldur;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"STURW")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&sturw;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"STURH")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&sturh;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"STURB")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&sturb;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }
        else if(strcmp(token,"STUR")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&stur;
            printf("%s = %x\n",token,codearray[entry][1]);
            token = strtok(NULL," ,\n");
            codearray[entry][2]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][2]);
            token = strtok(NULL," ,[]\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);
            token = strtok(NULL," ,[]#\n");
            codearray[entry][4]= atoi(token); 
            printf("%s = %x\n",token,codearray[entry][4]);
            addr++;
            entry++;

        }


        else if(strcmp(token,"BL")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bl;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"BR")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&br;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            codearray[entry][3]= OPINPUT(token);
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }
        else if(strcmp(token,"B")==0){
            dataflg = 0;

            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            codearray[entry][1]=&bl;
            printf("%s = %x\n",token,codearray[entry][1]);
            
            token = strtok(NULL," ,\n");
            unsigned int *a = ((unsigned int*)token);    
            codearray[entry][3] = *a;
            printf("%s = %x\n",token,codearray[entry][3]);

            addr++;
            entry++;

        }       





        else if(strstr(token,".code[")!= NULL){
            dataflg = 0;
            char caddr[10];
            memmove(caddr, &token[6], 10);
            caddr[strlen(caddr)-1] =' ';
            addr = (int)strtol(caddr,NULL,16);
        }
        else if(token[strlen(token) - 1] == ':'){
            codearray[entry][0]=addr;
            printf("Store @ %x\n",codearray[entry][0]);
            token[strlen(token)-1]=0x0;
            int *b = ((int*)token);    
            codearray[entry][1] = *b;
            printf("%s = %x\n",token,codearray[entry][1]);
            addr++;
            printf("entry = %d\n\n",entry);
            entry++;
            char string3[strlen(string2)-strlen(token)];
            memmove(string3, &string2[strlen(token)+2], strlen(string2)-strlen(token));
            printf("string3 = %s\n",string3);
            opcode2array(string3);
            

        }
        else if(strstr(token,".data[")!= NULL){
            dataflg = 1;
            char caddr[10];
            memmove(caddr, &token[6], 10);
            caddr[strlen(caddr)-1] =' ';
            daddr = (int)strtol(caddr,NULL,16);
            regarray[29] = (int)strtol(caddr,NULL,16);
            regarray[28] = regarray[29];

        }
        else{
            if(dataflg==1){
                datarray[dataindex][0]=daddr;
                datarray[dataindex][1]= (int)strtol(token,NULL,16);
                regarray[28] = daddr;
                daddr--;
                dataindex++;
                
            }

        }
    }
    printf("\n");
}



void convertDATA(){
    FILE *datain = fopen("testp3.asm","r");

    char string[100];
    
    
    while(fgets(string,sizeof(string),datain)){
        if (string[0] != '\n'){
        opcode2array(string);
        }
    }
    fclose(datain);
}





void readDATA(){
    //printf("---Addr of Registers---\n");
    //for(int i = 0 ;i <31; i++){
    //printf("Register x%d @ %x\n\n",i+1,&regarray[i]);  
    //}
    
    
    printf("\n\nentry = %d\n", entry);
    for(position = 0 ;position < entry; position++){
    OPCODE(codearray[position][1]);  
    }
    int i = 0;
    printf("\n\n---Value in Memory---\n");
    for(int i = 0; i< 256; i++){
        if(datarray[i][0]!=0){
            printf("%x = %x\n\n",datarray[i][0],datarray[i][1]);  
        }

    }

    printf("\n\n---Value in Registers---\n");
    for(int j = 0 ;j <32; j++){
    printf("Register x%d = %x\n\n",j,regarray[j]);  
    }
    printf("SP=%x, FP=%x\n\n",regarray[28], regarray[29]);
    printf("---Processor Flags---\nN=%d, Z=%d, V=%d, C=%d Data Flag=%d\n\n",N, Z, V, C,dataflg);
    
}


int main(){

convertDATA();
readDATA();




}