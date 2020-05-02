#ifndef OPCODES_H
#define OPCODES_H

/*
 * NOP
 *
 */
case 0x00:
{
    regPC.value++;
    return 4;
}

/*
 * LD nn, n
 *
 */
case 0x06:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regB,value);
    regPC.value+=2;
    return 8;
}
case 0x0E:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regC,value);
    regPC.value+=2;
    return 8;
}
case 0x16:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regD,value);
    regPC.value+=2;
    return 8;
}
case 0x1E:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regE,value);
    regPC.value+=2;
    return 8;
}
case 0x26:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regH,value);
    regPC.value+=2;
    return 8;
}
case 0x2E:
{
    u8 value = memory->Read(regPC.value+1);    
    LoadImmediate8Bit(regL,value);
    regPC.value+=2;
    return 8;
}

/*
 * LD r1, r2
 *
 */
case 0x7F:
    Load8BitReg(regA, regA);
    regPC.value++;
    return 4;
case 0x78:
    Load8BitReg(regA, regB);
    regPC.value++;
    return 4;
case 0x79:
    Load8BitReg(regA, regC);
    regPC.value++;
    return 4;
case 0x7A:
    Load8BitReg(regA, regD);
    regPC.value++;
    return 4;
case 0x7B:
    Load8BitReg(regA, regE);
    regPC.value++;
    return 4;
case 0x7C:
    Load8BitReg(regA, regH);
    regPC.value++;
    return 4;
case 0x7D:
    Load8BitReg(regA, regL);
    regPC.value++;
    return 4;
case 0x7E:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regA,value);
    regPC.value++;
    return 8;
}
case 0x40:
    Load8BitReg(regB, regB);
    regPC.value++;
    return 4;
case 0x41:
    Load8BitReg(regB, regC);
    regPC.value++;
    return 4;
case 0x42:
    Load8BitReg(regB, regD);
    regPC.value++;
    return 4;
case 0x43:
    Load8BitReg(regB, regE);
    regPC.value++;
    return 4;
case 0x44:
    Load8BitReg(regB, regH);
    regPC.value++;
    return 4;
case 0x45:
    Load8BitReg(regB, regL);
    regPC.value++;
    return 4;
case 0x46:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regB,value);
    regPC.value++;
    return 8;
}
case 0x48:
    Load8BitReg(regC, regB);
    regPC.value++;
    return 4;
case 0x49:
    Load8BitReg(regC, regC);
    regPC.value++;
    return 4;
case 0x4A:
    Load8BitReg(regC, regD);
    regPC.value++;
    return 4;
case 0x4B:
    Load8BitReg(regC, regE);
    regPC.value++;
    return 4;
case 0x4C:
    Load8BitReg(regC, regH);
    regPC.value++;
    return 4;
case 0x4D:
    Load8BitReg(regC, regL);
    regPC.value++;
    return 4;
case 0x4E:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regC,value);
    regPC.value++;
    return 8;
}
case 0x50:
    Load8BitReg(regD, regB);
    regPC.value++;
    return 4;
case 0x51:
    Load8BitReg(regD, regC);
    regPC.value++;
    return 4;
case 0x52:
    Load8BitReg(regD, regD);
    regPC.value++;
    return 4;
case 0x53:
    Load8BitReg(regD, regE);
    regPC.value++;
    return 4;
case 0x54:
    Load8BitReg(regD, regH);
    regPC.value++;
    return 4;
case 0x55:
    Load8BitReg(regD, regL);
    regPC.value++;
    return 4;
case 0x56:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regD,value);
    regPC.value++;
    return 8;
}
case 0x58:
    Load8BitReg(regE, regB);
    regPC.value++;
    return 4;
case 0x59:
    Load8BitReg(regE, regC);
    regPC.value++;
    return 4;
case 0x5A:
    Load8BitReg(regE, regD);
    regPC.value++;
    return 4;
case 0x5B:
    Load8BitReg(regE, regE);
    regPC.value++;
    return 4;
case 0x5C:
    Load8BitReg(regE, regH);
    regPC.value++;
    return 4;
case 0x5D:
    Load8BitReg(regE, regL);
    regPC.value++;
    return 4;
case 0x5E:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regE,value);
    regPC.value++;
    return 8;
}
case 0x60:
    Load8BitReg(regH, regB);
    regPC.value++;
    return 4;
case 0x61:
    Load8BitReg(regH, regC);
    regPC.value++;
    return 4;
case 0x62:
    Load8BitReg(regH, regD);
    regPC.value++;
    return 4;
case 0x63:
    Load8BitReg(regH, regE);
    regPC.value++;
    return 4;
case 0x64:
    Load8BitReg(regH, regH);
    regPC.value++;
    return 4;
case 0x65:
    Load8BitReg(regH, regL);
    regPC.value++;
    return 4;
case 0x66:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regH,value);
    regPC.value++;
    return 8;
}
case 0x68:
    Load8BitReg(regL, regB);
    regPC.value++;
    return 4;
case 0x69:
    Load8BitReg(regL, regC);
    regPC.value++;
    return 4;
case 0x6A:
    Load8BitReg(regL, regD);
    regPC.value++;
    return 4;
case 0x6B:
    Load8BitReg(regL, regE);
    regPC.value++;
    return 4;
case 0x6C:
    Load8BitReg(regL, regH);
    regPC.value++;
    return 4;
case 0x6D:
    Load8BitReg(regL, regL);
    regPC.value++;
    return 4;
case 0x6E:
{
    u8 value = memory->Read(regHL.value);
    LoadImmediate8Bit(regL,value);
    regPC.value++;
    return 8;
}
case 0x70:
{
    memory->Write(regHL.value,regB);
    regPC.value++;
    return 8;
}
case 0x71:
{
    memory->Write(regHL.value,regC);
    regPC.value++;
    return 8;
}
case 0x72:
{
    memory->Write(regHL.value,regD);
    regPC.value++;
    return 8;
}
case 0x73:
{
    memory->Write(regHL.value,regE);
    regPC.value++;
    return 8;
}
case 0x74:
{
    memory->Write(regHL.value,regH);
    regPC.value++;
    return 8;
}
case 0x75:
{
    memory->Write(regHL.value,regL);
    regPC.value++;
    return 8;
}
case 0x36:
{
    u8 value = memory->Read(regPC.value+1);
    memory->Write(regHL.value,value);
    regPC.value+=2;
    return 8;
}

/*
 * LD A, n
 *
 */
case 0x0A:
{
    u8 value = memory->Read(regBC.value);
    LoadImmediate8Bit(regA, value);
    regPC.value++;
    return 8;
}
case 0x1A:
{
    u8 value = memory->Read(regDE.value);
    LoadImmediate8Bit(regA, value);
    regPC.value++;
    return 8;
}
case 0xFA:
{
    u8 low = memory->Read(regPC.value+1);
    u8 high = memory->Read(regPC.value+2);
    u8 value = memory->Read(((u16)high << 8) | low);
    LoadImmediate8Bit(regA, value);
    regPC.value+=3;
    return 16;
}
case 0x3E:
{
    u8 value = memory->Read(regPC.value+1);
    LoadImmediate8Bit(regA, value);
    regPC.value+=2;
    return 8;
}

/*
 * LD n, A
 *
 */
case 0x47:
    Load8BitReg(regB, regA);
    regPC.value++;
    return 4;
case 0x4F:
    Load8BitReg(regC, regA);
    regPC.value++;
    return 4;
case 0x57:
    Load8BitReg(regD, regA);
    regPC.value++;
    return 4;
case 0x5F:
    Load8BitReg(regE, regA);
    regPC.value++;
    return 4;
case 0x67:
    Load8BitReg(regH, regA);
    regPC.value++;
    return 4;
case 0x6F:
    Load8BitReg(regL, regA);
    regPC.value++;
    return 4;
case 0x02:
    memory->Write(regBC.value,regA);
    regPC.value++;
    return 8;
case 0x12:
    memory->Write(regDE.value,regA);
    regPC.value++;
    return 8;
case 0x77:
    memory->Write(regHL.value,regA);
    regPC.value++;
    return 8;
case 0xEA:
{
    u8 low = memory->Read(regPC.value+1);
    u8 high = memory->Read(regPC.value+2);
    u16 addr = (((u16)high << 8) | low);
    memory->Write(addr,regA);
    regPC.value+=3;
    return 16;
}

/*
 * LD A,(C)
 *
 */
case 0xF2:
{
    u8 value = memory->Read(0xFF00+regC);
    LoadImmediate8Bit(regA,value);
    regPC.value++;
    return 8;
}

/*
 * LD (C), A
 *
 */
case 0xE2:
{
    u16 addr = 0xFF00 + regC;
    memory->Write(addr, regA);
    regPC.value++;
    return 8;
}

/*
 * LDD A, (HL)
 *
 */

case 0x3A:
{
    LoadFromMemory8Bit(regA, regHL.value);
    regHL.value--;
    regPC.value++;
    return 8;
}

/*
 * LDD (HL), A
 *
 */

case 0x32:
    memory->Write(regHL.value, regA);
    regHL.value--;
    regPC.value++;
    return 8;

/*
 * LDI A, (HL)
 *
 */

case 0x2A:
{
    LoadFromMemory8Bit(regA, regHL.value);
    regHL.value++;
    regPC.value++;
    return 8;
}


/*
 * LDI (HL), A
 *
 */

case 0x22:
    memory->Write(regHL.value, regA);
    regHL.value++;
    regPC.value++;
    return 8;

/*
 * LDH (n), A
 *
 */

case 0xE0:
{
    u16 address = 0xFF00 + memory->Read(regPC.value+1);
    memory->Write(address,regA);
    regPC.value+=2;
    return 12;
}

/*
 * LDH A, (n)
 *
 */

case 0xF0:
{
    LoadFromMemory8Bit(regA, 0xFF00 + memory->Read(regPC.value+1));
    regPC.value+=2;
    return 12;
}

/*
 * LD n, nn
 *
 */

case 0x01:
{
    
    u8 low = memory->Read(regPC.value+1); 
    u8 high = memory->Read(regPC.value+2); 
    u16 value = ((u16)high << 8) | low;

    LoadImmediate16Bit(regBC, value);
    regPC.value+=3;
    return 12;
}
case 0x11:
{
    u8 low = memory->Read(regPC.value+1); 
    u8 high = memory->Read(regPC.value+2); 
    u16 value = ((u16)high << 8) | low;

    LoadImmediate16Bit(regDE, value);
    regPC.value+=3;
    return 12;
}
case 0x21:
{
    u8 low = memory->Read(regPC.value+1); 
    u8 high = memory->Read(regPC.value+2); 
    u16 value = ((u16)high << 8) | low;

    LoadImmediate16Bit(regHL, value);
    regPC.value+=3;
    return 12;
}
case 0x31:
{
    u8 low = memory->Read(regPC.value+1); 
    u8 high = memory->Read(regPC.value+2); 
    u16 value = ((u16)high << 8) | low;

    LoadImmediate16Bit(regSP, value);
    regPC.value+=3;
    return 12;
}

/*
 * LD SP, HL
 *
 */

case 0xF9:
    Load16BitReg(regSP, regHL);
    regPC.value++;
    return 8;

/*
 * LDHL SP, n
 *
 */

case 0xF8:
{
    s8 value = (s8)memory->Read(regPC.value+1);
    u16 result = regSP.value+value;

    ClearFlags(ZERO|ADDSUB);

    ((result&0xFF) < (regSP.value&0xFF))?SetFlags(CARRY):ClearFlags(CARRY);

    ((result&0xF) < (regSP.value&0xF))?SetFlags(HALFCARRY):ClearFlags(HALFCARRY);
    
    regHL.value=result;
    regPC.value+=2;
    return 12;
}

/*
 * LD (nn), SP
 *
 */
case 0x08:
{
    u8 low = memory->Read(regPC.value+1);
    u8 high = memory->Read(regPC.value+2);

    u16 address = ((u16)high << 8) | low;
    memory->Write(address, regSP.value);
    regPC.value+=3;
    return 20;
}

/*
 * PUSH nn
 *
 */
case 0xF5:
{
    PushStack(regAF.value);
    regPC.value++;
    return 16;
}
case 0xC5:
{
    PushStack(regBC.value);
    regPC.value++;
    return 16;
}
case 0xD5:
{
    PushStack(regDE.value);
    regPC.value++;
    return 16;
}
case 0xE5:
{
    PushStack(regHL.value);
    regPC.value++;
    return 16;
}

/*
 * POP nn
 *
 */
case 0xF1:
{
    /*
     * For some reason this needs to be masked
     * with 0xFFF0?
     */ 
    regAF.value = (PopStack()&0xFFF0);
    regPC.value++;
    return 12;
}
case 0xC1:
{
    regBC.value = PopStack();
    regPC.value++;
    return 12;
}
case 0xD1:
{
    regDE.value = PopStack();
    regPC.value++;
    return 12;
}
case 0xE1:
{
    regHL.value = PopStack();
    regPC.value++;
    return 12;
}

/*
 * ADD A,n
 *
 */
case 0x87:
{
    Add8BitReg(regA,regA);
    regPC.value++;
    return 4;
}
case 0x80:
{
    Add8BitReg(regA,regB);
    regPC.value++;
    return 4;
}
case 0x81:
{
    Add8BitReg(regA,regC);
    regPC.value++;
    return 4;
}
case 0x82:
{
    Add8BitReg(regA,regD);
    regPC.value++;
    return 4;
}
case 0x83:
{
    Add8BitReg(regA,regE);
    regPC.value++;
    return 4;
}
case 0x84:
{
    Add8BitReg(regA,regH);
    regPC.value++;
    return 4;
}
case 0x85:
{
    Add8BitReg(regA,regL);
    regPC.value++;
    return 4;
}
case 0x86:
{
    Add8BitImmediate(regA, memory->Read(regHL.value));
    regPC.value++;
    return 8;
}
case 0xC6:
{
    Add8BitImmediate(regA, memory->Read(regPC.value+1));
    regPC.value+=2;
    return 8;
}

/*
 * ADD HL,n
 *
 */
case 0x09:
{
    Add16BitReg(regHL,regBC);
    regPC.value++;
    return 8;
}
case 0x19:
{
    Add16BitReg(regHL,regDE);
    regPC.value++;
    return 8;
}
case 0x29:
{
    Add16BitReg(regHL,regHL);
    regPC.value++;
    return 8;
}
case 0x39:
{
    Add16BitReg(regHL,regSP);
    regPC.value++;
    return 8;
}


/*
 * ADC A,n
 *
 */

case 0x8F:
{
   Add8BitReg(regA,regA,true); 
   regPC.value++;
   return 4;
}
case 0x88:
{
   Add8BitReg(regA,regB,true); 
   regPC.value++;
   return 4;
}
case 0x89:
{
   Add8BitReg(regA,regC,true); 
   regPC.value++;
   return 4;
}
case 0x8A:
{
   Add8BitReg(regA,regD,true); 
   regPC.value++;
   return 4;
}
case 0x8B:
{
   Add8BitReg(regA,regE,true); 
   regPC.value++;
   return 4;
}
case 0x8C:
{
   Add8BitReg(regA,regH,true); 
   regPC.value++;
   return 4;
}
case 0x8D:
{
   Add8BitReg(regA,regL,true); 
   regPC.value++;
   return 4;
}
case 0x8E:
{
   Add8BitImmediate(regA,memory->Read(regHL.value),true);
   regPC.value++;
   return 8;
}
case 0xCE:
{
    Add8BitImmediate(regA,memory->Read(regPC.value+1),true); 
    regPC.value+=2;
    return 8;
}

/*
 * SUB n
 *
 */
case 0x97:
{
    Sub8BitReg(regA, regA);
    regPC.value++;
    return 4;
}
case 0x90:
{
    Sub8BitReg(regA, regB);
    regPC.value++;
    return 4;
}
case 0x91:
{
    Sub8BitReg(regA, regC);
    regPC.value++;
    return 4;
}
case 0x92:
{
    Sub8BitReg(regA, regD);
    regPC.value++;
    return 4;
}
case 0x93:
{
    Sub8BitReg(regA, regE);
    regPC.value++;
    return 4;
}
case 0x94:
{
    Sub8BitReg(regA, regH);
    regPC.value++;
    return 4;
}
case 0x95:
{
    Sub8BitReg(regA, regL);
    regPC.value++;
    return 4;
}
case 0x96:
{
    u8 value = memory->Read(regHL.value);
    Sub8BitImmediate(regA, value);
    regPC.value++;
    return 8;
}
case 0xD6:
{
    u8 value = memory->Read(regPC.value+1);
    Sub8BitImmediate(regA, value);
    regPC.value+=2;
    return 8;
}

/*
 * SBC A,n
 *
 */
case 0x9F:
{
    Sub8BitReg(regA, regA, true);
    regPC.value++;
    return 4;
}
case 0x98:
{
    Sub8BitReg(regA, regB, true);
    regPC.value++;
    return 4;
}
case 0x99:
{
    Sub8BitReg(regA, regC, true);
    regPC.value++;
    return 4;
}
case 0x9A:
{
    Sub8BitReg(regA, regD, true);
    regPC.value++;
    return 4;
}
case 0x9B:
{
    Sub8BitReg(regA, regE, true);
    regPC.value++;
    return 4;
}
case 0x9C:
{
    Sub8BitReg(regA, regH, true);
    regPC.value++;
    return 4;
}
case 0x9D:
{
    Sub8BitReg(regA, regL, true);
    regPC.value++;
    return 4;
}
case 0x9E:
{
    u8 value = memory->Read(regHL.value);
    Sub8BitImmediate(regA, value, true);
    regPC.value++;
    return 8;
}

case 0xDE:
{
    u8 value = memory->Read(regPC.value+1);
    Sub8BitImmediate(regA, value, true);
    regPC.value+=2;
    return 8;
}

/*
 * AND n
 *
 */
case 0xA7:
{
    AND8BitReg(regA, regA);
    regPC.value++;
    return 4;
}
case 0xA0:
{
    AND8BitReg(regA, regB);
    regPC.value++;
    return 4;
}
case 0xA1:
{
    AND8BitReg(regA, regC);
    regPC.value++;
    return 4;
}
case 0xA2:
{
    AND8BitReg(regA, regD);
    regPC.value++;
    return 4;
}
case 0xA3:
{
    AND8BitReg(regA, regE);
    regPC.value++;
    return 4;
}
case 0xA4:
{
    AND8BitReg(regA, regH);
    regPC.value++;
    return 4;
}
case 0xA5:
{
    AND8BitReg(regA, regL);
    regPC.value++;
    return 4;
}
case 0xA6:
{
    u8 value = memory->Read(regHL.value);
    AND8BitImmediate(regA, value);
    regPC.value++;
    return 8;
}
case 0xE6:
{
    u8 value = memory->Read(regPC.value+1);
    AND8BitImmediate(regA, value);
    regPC.value+=2;
    return 8;
}

/*
 * OR n
 *
 */
case 0xB7:
{
    OR8BitReg(regA, regA);
    regPC.value++;
    return 4;
}
case 0xB0:
{
    OR8BitReg(regA, regB);
    regPC.value++;
    return 4;
}
case 0xB1:
{
    OR8BitReg(regA, regC);
    regPC.value++;
    return 4;
}
case 0xB2:
{
    OR8BitReg(regA, regD);
    regPC.value++;
    return 4;
}
case 0xB3:
{
    OR8BitReg(regA, regE);
    regPC.value++;
    return 4;
}
case 0xB4:
{
    OR8BitReg(regA, regH);
    regPC.value++;
    return 4;
}
case 0xB5:
{
    OR8BitReg(regA, regL);
    regPC.value++;
    return 4;
}
case 0xB6:
{
    u8 value = memory->Read(regHL.value);
    OR8BitImmediate(regA, value);
    regPC.value++;
    return 8;
}
case 0xF6:
{
    u8 value = memory->Read(regPC.value+1);
    OR8BitImmediate(regA, value);
    regPC.value+=2;
    return 8;
}

/*
 * XOR n
 *
 */
case 0xAF:
{
    XOR8BitReg(regA,regA);
    regPC.value++;
    return 4;
}
case 0xA8:
{
    XOR8BitReg(regA,regB);
    regPC.value++;
    return 4;
}
case 0xA9:
{
    XOR8BitReg(regA,regC);
    regPC.value++;
    return 4;
}
case 0xAA:
{
    XOR8BitReg(regA,regD);
    regPC.value++;
    return 4;
}
case 0xAB:
{
    XOR8BitReg(regA,regE);
    regPC.value++;
    return 4;
}
case 0xAC:
{
    XOR8BitReg(regA,regH);
    regPC.value++;
    return 4;
}
case 0xAD:
{
    XOR8BitReg(regA,regL);
    regPC.value++;
    return 4;
}
case 0xAE:
{
    u8 value = memory->Read(regHL.value);
    XOR8BitImmediate(regA,value);
    regPC.value++;
    return 8;
}
case 0xEE:
{
    u8 value = memory->Read(regPC.value+1);
    XOR8BitImmediate(regA,value);
    regPC.value+=2;
    return 8;
}

case 0xCB:
{
    switch(u8 param = memory->Read(regPC.value+1))
    {

        /*
         * RLC
         *
         */
        case 0x07:
        {
            Rotate8BitRegLeft(regA,false);
            regPC.value++;
            return 4;
        }
        case 0x00:
        {
            Rotate8BitRegLeft(regB,false);
            regPC.value++;
            return 4;
        }
        case 0x01:
        {
            Rotate8BitRegLeft(regC,false);
            regPC.value++;
            return 4;
        }
        case 0x02:
        {
            Rotate8BitRegLeft(regD,false);
            regPC.value++;
            return 4;
        }
        case 0x03:
        {
            Rotate8BitRegLeft(regE,false);
            regPC.value++;
            return 4;
        }
        case 0x04:
        {
            Rotate8BitRegLeft(regH,false);
            regPC.value++;
            return 4;
        }
        case 0x05:
        {
            Rotate8BitRegLeft(regL,false);
            regPC.value++;
            return 4;
        }
        case 0x06:
        {
            RotateAddressLeft(regHL.value,false);
            regPC.value+=2;
            return 8;
        }

        /*
         * RRC
         *
         */

        case 0x0F:
        {
            Rotate8BitRegRight(regA, false);
            regPC.value++;
            return 4;
        }
        case 0x08:
        {
            Rotate8BitRegRight(regB, false);
            regPC.value++;
            return 4;
        }
        case 0x09:
        {
            Rotate8BitRegRight(regC, false);
            regPC.value++;
            return 4;
        }
        case 0xA:
        {
            Rotate8BitRegRight(regD, false);
            regPC.value++;
            return 4;
        }
        case 0xB:
        {
            Rotate8BitRegRight(regE, false);
            regPC.value++;
            return 4;
        }
        case 0xC:
        {
            Rotate8BitRegRight(regH, false);
            regPC.value++;
            return 4;
        }
        case 0xD:
        {
            Rotate8BitRegRight(regL, false);
            regPC.value++;
            return 4;
        }
        case 0xE:
        {
            RotateAddressRight(regHL.value,false);
            regPC.value+=2;
            return 16;
        }

        /*
         * SWAP n
         *
         */
        case 0x37:
        {
            SwapNibblesReg(regA);
            regPC.value+=2;
            return 8;
        }
        case 0x30:
        {
            SwapNibblesReg(regB);
            regPC.value+=2;
            return 8;
        }
        case 0x31:
        {
            SwapNibblesReg(regC);
            regPC.value+=2;
            return 8;
        }
        case 0x32:
        {
            SwapNibblesReg(regD);
            regPC.value+=2;
            return 8;
        }
        case 0x33:
        {
            SwapNibblesReg(regE);
            regPC.value+=2;
            return 8;
        }
        case 0x34:
        {
            SwapNibblesReg(regH);
            regPC.value+=2;
            return 8;
        }
        case 0x35:
        {
            SwapNibblesReg(regL);
            regPC.value+=2;
            return 8;
        }
        case 0x36:
        {
            u8 value = memory->Read(regHL.value);
            SwapNibblesImmediate(&value);
            memory->Write(regHL.value,value);
            regPC.value+=2;
            return 16;
        }

        /*
         * Bit Opcodes
         *
         */
        case 0x40:
        {
            Test8BitRegBit(regB, 0);
            regPC.value+=2;
            return 8;
        }
        case 0x50:
        {
            Test8BitRegBit(regB, 2);
            regPC.value+=2;
            return 8;
        }
        case 0x60:
        {
            Test8BitRegBit(regB, 4);
            regPC.value+=2;
            return 8;
        }
        case 0x70:
        {
            Test8BitRegBit(regB, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x41:
        {
            Test8BitRegBit(regC, 0);
            regPC.value+=2;
            return 8;
        }
        
        case 0x51:
        {
            Test8BitRegBit(regC, 2);
            regPC.value+=2;
            return 8;
        }

        case 0x61:
        {
            Test8BitRegBit(regC, 4);
            regPC.value+=2;
            return 8;
        }

        case 0x71:
        {
            Test8BitRegBit(regC, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x42:
        {
            Test8BitRegBit(regD, 0);
            regPC.value+=2;
            return 8;
        }

        case 0x52:
        {
            Test8BitRegBit(regD, 2);
            regPC.value+=2;
            return 8;
        }
        
        case 0x62:
        {
            Test8BitRegBit(regD, 4);
            regPC.value+=2;
            return 8;
        }
        case 0x72:
        {
            Test8BitRegBit(regD, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x43:
        {
            Test8BitRegBit(regE, 0);
            regPC.value+=2;
            return 8;
        }

        case 0x53:
        {
            Test8BitRegBit(regE, 2);
            regPC.value+=2;
            return 8;
        }

        case 0x63:
        {
            Test8BitRegBit(regE, 4);
            regPC.value+=2;
            return 8;
        }

        case 0x73:
        {
            Test8BitRegBit(regE, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x44:
        {
            Test8BitRegBit(regH, 0);
            regPC.value+=2;
            return 8;
        }

        case 0x54:
        {
            Test8BitRegBit(regH, 2);
            regPC.value+=2;
            return 8;
        }

        case 0x64:
        {
            Test8BitRegBit(regH, 4);
            regPC.value+=2;
            return 8;
        }

        case 0x74:
        {
            Test8BitRegBit(regH, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x45:
        {
            Test8BitRegBit(regL, 0);
            regPC.value+=2;
            return 8;
        }

        case 0x55:
        {
            Test8BitRegBit(regL, 2);
            regPC.value+=2;
            return 8;
        }

        case 0x65:
        {
            Test8BitRegBit(regL, 4);
            regPC.value+=2;
            return 8;
        }

        case 0x75:
        {
            Test8BitRegBit(regL, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x46:
        {
            TestMemoryBit(regHL.value,0); 
            regPC.value+=2;
            return 16;
        }
        case 0x56:
        {
            TestMemoryBit(regHL.value,2); 
            regPC.value+=2;
            return 16;
        }
        case 0x66:
        {
            TestMemoryBit(regHL.value,4); 
            regPC.value+=2;
            return 16;
        }
        case 0x76:
        {
            TestMemoryBit(regHL.value,6); 
            regPC.value+=2;
            return 16;
        }
       
        case 0x7C:
        {
            Test8BitRegBit(regH, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x47:
        {
            Test8BitRegBit(regA, 0);
            regPC.value+=2;
            return 8;
        }

        case 0x57:
        {
            Test8BitRegBit(regA, 2);
            regPC.value+=2;
            return 8;
        }

        case 0x67:
        {
            Test8BitRegBit(regA, 4);
            regPC.value+=2;
            return 8;
        }

        case 0x77:
        {
            Test8BitRegBit(regA, 6);
            regPC.value+=2;
            return 8;
        }

        case 0x48:
        {
            Test8BitRegBit(regB, 1);
            regPC.value+=2;
            return 8;
        }
        case 0x58:
        {
            Test8BitRegBit(regB, 3);
            regPC.value+=2;
            return 8;
        }
        case 0x68:
        {
            Test8BitRegBit(regB, 5);
            regPC.value+=2;
            return 8;
        }
        case 0x78:
        {
            Test8BitRegBit(regB, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x49:
        {
            Test8BitRegBit(regC, 1);
            regPC.value+=2;
            return 8;
        }

        case 0x59:
        {
            Test8BitRegBit(regC, 3);
            regPC.value+=2;
            return 8;
        }

        case 0x69:
        {
            Test8BitRegBit(regC, 5);
            regPC.value+=2;
            return 8;
        }

        case 0x79:
        {
            Test8BitRegBit(regC, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x4A:
        {
            Test8BitRegBit(regD, 1);
            regPC.value+=2;
            return 8;
        }

        case 0x5A:
        {
            Test8BitRegBit(regD, 3);
            regPC.value+=2;
            return 8;
        }

        case 0x6A:
        {
            Test8BitRegBit(regD, 5);
            regPC.value+=2;
            return 8;
        }

        case 0x7A:
        {
            Test8BitRegBit(regD, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x4B:
        {
            Test8BitRegBit(regE, 1);
            regPC.value+=2;
            return 8;
        }

        case 0x5B:
        {
            Test8BitRegBit(regE, 3);
            regPC.value+=2;
            return 8;
        }

        case 0x6B:
        {
            Test8BitRegBit(regE, 5);
            regPC.value+=2;
            return 8;
        }

        case 0x7B:
        {
            Test8BitRegBit(regE, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x4C:
        {
            Test8BitRegBit(regH, 1);
            regPC.value+=2;
            return 8;
        }

        case 0x5C:
        {
            Test8BitRegBit(regH, 3);
            regPC.value+=2;
            return 8;
        }

        case 0x6C:
        {
            Test8BitRegBit(regH, 5);
            regPC.value+=2;
            return 8;
        }

        case 0x4D:
        {
            Test8BitRegBit(regL, 1);
            regPC.value+=2;
            return 8;
        }

        case 0x5D:
        {
            Test8BitRegBit(regL, 3);
            regPC.value+=2;
            return 8;
        }

        case 0x6D:
        {
            Test8BitRegBit(regL, 5);
            regPC.value+=2;
            return 8;
        }

        case 0x7D:
        {
            Test8BitRegBit(regL, 7);
            regPC.value+=2;
            return 8;
        }

        case 0x4F:
        {
            Test8BitRegBit(regA, 1);
            regPC.value+=2;
            return 8;
        }
        case 0x5F:
        {
            Test8BitRegBit(regA, 3);
            regPC.value+=2;
            return 8;
        }
        case 0x6F:
        {
            Test8BitRegBit(regA, 5);
            regPC.value+=2;
            return 8;
        }
        case 0x7F:
        {
            Test8BitRegBit(regA, 7);
            regPC.value+=2;
            return 8;
        }
        case 0x4E:
        {
            TestMemoryBit(regHL.value,1);
            regPC.value+=2;
            return 8;
        }
        case 0x5E:
        {
            TestMemoryBit(regHL.value,3);
            regPC.value+=2;
            return 8;
        }
        case 0x6E:
        {
            TestMemoryBit(regHL.value,5);
            regPC.value+=2;
            return 8;
        }
        case 0x7E:
        {
            TestMemoryBit(regHL.value,7);
            regPC.value+=2;
            return 8;
        }

        /*
         * RL n
         *
         */
        case 0x17:
        {
            Rotate8BitRegLeft(regA);
            regPC.value+=2;
            return 8;
        }
        case 0x10:
        {
            Rotate8BitRegLeft(regB);
            regPC.value+=2;
            return 8;
        }
        case 0x11:
        {
            Rotate8BitRegLeft(regC);
            regPC.value+=2;
            return 8;
        }
        case 0x12:
        {
            Rotate8BitRegLeft(regD);
            regPC.value+=2;
            return 8;
        }
        case 0x13:
        {
            Rotate8BitRegLeft(regE);
            regPC.value+=2;
            return 8;
        }
        case 0x14:
        {
            Rotate8BitRegLeft(regH);
            regPC.value+=2;

            return 8;
        }
        case 0x15:
        {
            Rotate8BitRegLeft(regL);
            regPC.value+=2;
            return 8;
        }
        case 0x16:
        {
            RotateAddressLeft(regHL.value,true);
            regPC.value+=2;
            return 16;
        }

        /*
         * SLA n
         *
         */
        case 0x27:
        {
            Shift8BitRegLeftIntoCarry(regA);
            regPC.value+=2;
            return 8;
        }
        case 0x20:
        {
            Shift8BitRegLeftIntoCarry(regB);
            regPC.value+=2;
            return 8;
        }
        case 0x21:
        {
            Shift8BitRegLeftIntoCarry(regC);
            regPC.value+=2;
            return 8;
        }
        case 0x22:
        {
            Shift8BitRegLeftIntoCarry(regD);
            regPC.value+=2;
            return 8;
        }
        case 0x23:
        {
            Shift8BitRegLeftIntoCarry(regE);
            regPC.value+=2;
            return 8;
        }
        case 0x24:
        {
            Shift8BitRegLeftIntoCarry(regH);
            regPC.value+=2;
            return 8;
        }
        case 0x25:
        {
            Shift8BitRegLeftIntoCarry(regL);
            regPC.value+=2;
            return 8;
        }
        case 0x26:
        {
            ShiftAddressLeftIntoCarry(regHL.value);
            regPC.value+=2;
            return 16;
        }

        /*
         * SRA n
         *
         */
        case 0x2F:
        {
            Shift8BitRegRightIntoCarry(regA);
            regPC.value+=2;
            return 8;
        }
        case 0x28:
        {
            Shift8BitRegRightIntoCarry(regB);
            regPC.value+=2;
            return 8;
        }
        case 0x29:
        {
            Shift8BitRegRightIntoCarry(regC);
            regPC.value+=2;
            return 8;
        }
        case 0x2A:
        {
            Shift8BitRegRightIntoCarry(regD);
            regPC.value+=2;
            return 8;
        }
        case 0x2B:
        {
            Shift8BitRegRightIntoCarry(regE);
            regPC.value+=2;
            return 8;
        }
        case 0x2C:
        {
            Shift8BitRegRightIntoCarry(regH);
            regPC.value+=2;
            return 8;
        }
        case 0x2D:
        {
            Shift8BitRegRightIntoCarry(regL);
            regPC.value+=2;
            return 8;
        }
        case 0x2E:
        {
            ShiftAddressRightIntoCarry(regHL.value,false);
            regPC.value+=2;
            return 16;
        }

        /*
         * SRL n
         *
         */
        case 0x3F:
        {
            Shift8BitRegRightIntoCarry(regA, true);
            regPC.value+=2;
            return 8;
        }
        case 0x38:
        {
            Shift8BitRegRightIntoCarry(regB, true);
            regPC.value+=2;
            return 8;
        }
        case 0x39:
        {
            Shift8BitRegRightIntoCarry(regC, true);
            regPC.value+=2;
            return 8;
        }
        case 0x3A:
        {
            Shift8BitRegRightIntoCarry(regD, true);
            regPC.value+=2;
            return 8;
        }
        case 0x3B:
        {
            Shift8BitRegRightIntoCarry(regE, true);
            regPC.value+=2;
            return 8;
        }
        case 0x3C:
        {
            Shift8BitRegRightIntoCarry(regH, true);
            regPC.value+=2;
            return 8;
        }
        case 0x3D:
        {
            Shift8BitRegRightIntoCarry(regL, true);
            regPC.value+=2;
            return 8;
        }
        case 0x3E:
        {
            ShiftAddressRightIntoCarry(regHL.value,true);
            regPC.value+=2;
            return 16;
        }

        /*
         * RES 
         *
         */

        case 0x80:
        {
            ResetRegisterBit(regB,0);
            regPC.value+=2;
            return 8;
        }
        case 0x88:
        {
            ResetRegisterBit(regB,1);
            regPC.value+=2;
            return 8;
        }
        case 0x90:
        {
            ResetRegisterBit(regB,2);
            regPC.value+=2;
            return 8;
        }
        case 0x98:
        {
            ResetRegisterBit(regB,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA0:
        {
            ResetRegisterBit(regB,4);
            regPC.value+=2;
            return 8;
        }
        case 0xA8:
        {
            ResetRegisterBit(regB,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB0:
        {
            ResetRegisterBit(regB,6);
            regPC.value+=2;
            return 8;
        }
        case 0xB8:
        {
            ResetRegisterBit(regB,7);
            regPC.value+=2;
            return 8;
        }
        case 0x81:
        {
            ResetRegisterBit(regC,0);
            regPC.value+=2;
            return 8;
        }
        case 0x89:
        {
            ResetRegisterBit(regC,1);
            regPC.value+=2;
            return 8;
        }
        case 0x91:
        {
            ResetRegisterBit(regC,2);
            regPC.value+=2;
            return 8;
        }
        case 0x99:
        {
            ResetRegisterBit(regC,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA1:
        {
            ResetRegisterBit(regC,4);
            regPC.value+=2;
            return 8;
        }
        case 0xA9:
        {
            ResetRegisterBit(regC,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB1:
        {
            ResetRegisterBit(regC,6);
            regPC.value+=2;
            return 8;
        }
        case 0xB9:
        {
            ResetRegisterBit(regC,7);
            regPC.value+=2;
            return 8;
        }
        case 0x82:
        {
            ResetRegisterBit(regD,0);
            regPC.value+=2;
            return 8;
        }
        case 0x8A:
        {
            ResetRegisterBit(regD,1);
            regPC.value+=2;
            return 8;
        }
        case 0x92:
        {
            ResetRegisterBit(regD,2);
            regPC.value+=2;
            return 8;
        }
        case 0x9A:
        {
            ResetRegisterBit(regD,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA2:
        {
            ResetRegisterBit(regD,4);
            regPC.value+=2;
            return 8;
        }
        case 0xAA:
        {
            ResetRegisterBit(regD,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB2:
        {
            ResetRegisterBit(regD,6);
            regPC.value+=2;
            return 8;
        }
        case 0xBA:
        {
            ResetRegisterBit(regD,7);
            regPC.value+=2;
            return 8;
        }
        case 0x83:
        {
            ResetRegisterBit(regE,0);
            regPC.value+=2;
            return 8;
        }
        case 0x8B:
        {
            ResetRegisterBit(regE,1);
            regPC.value+=2;
            return 8;
        }
        case 0x93:
        {
            ResetRegisterBit(regE,2);
            regPC.value+=2;
            return 8;
        }
        case 0x9B:
        {
            ResetRegisterBit(regE,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA3:
        {
            ResetRegisterBit(regE,4);
            regPC.value+=2;
            return 8;
        }
        case 0xAB:
        {
            ResetRegisterBit(regE,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB3:
        {
            ResetRegisterBit(regE,6);
            regPC.value+=2;
            return 8;
        }
        case 0xBB:
        {
            ResetRegisterBit(regE,7);
            regPC.value+=2;
            return 8;
        }
        case 0x84:
        {
            ResetRegisterBit(regH,0);
            regPC.value+=2;
            return 8;
        }
        case 0x8C:
        {
            ResetRegisterBit(regH,1);
            regPC.value+=2;
            return 8;
        }
        case 0x94:
        {
            ResetRegisterBit(regH,2);
            regPC.value+=2;
            return 8;
        }
        case 0x9C:
        {
            ResetRegisterBit(regH,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA4:
        {
            ResetRegisterBit(regH,4);
            regPC.value+=2;
            return 8;
        }
        case 0xAC:
        {
            ResetRegisterBit(regH,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB4:
        {
            ResetRegisterBit(regH,6);
            regPC.value+=2;
            return 8;
        }
        case 0xBC:
        {
            ResetRegisterBit(regH,7);
            regPC.value+=2;
            return 8;
        }
        case 0x85:
        {
            ResetRegisterBit(regL,0);
            regPC.value+=2;
            return 8;
        }
        case 0x8D:
        {
            ResetRegisterBit(regL,1);
            regPC.value+=2;
            return 8;
        }
        case 0x95:
        {
            ResetRegisterBit(regL,2);
            regPC.value+=2;
            return 8;
        }
        case 0x9D:
        {
            ResetRegisterBit(regL,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA5:
        {
            ResetRegisterBit(regL,4);
            regPC.value+=2;
            return 8;
        }
        case 0xAD:
        {
            ResetRegisterBit(regL,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB5:
        {
            ResetRegisterBit(regL,6);
            regPC.value+=2;
            return 8;
        }
        case 0xBD:
        {
            ResetRegisterBit(regL,7);
            regPC.value+=2;
            return 8;
        }
        case 0x86:
        {
            ResetMemoryBit(regHL.value,0);
            regPC.value+=2;
            return 8;
        }
        case 0x96:
        {
            ResetMemoryBit(regHL.value,2);
            regPC.value+=2;
            return 8;
        }
        case 0xA6:
        {
            ResetMemoryBit(regHL.value,4);
            regPC.value+=2;
            return 8;
        }
        case 0xB6:
        {
            ResetMemoryBit(regHL.value,6);
            regPC.value+=2;
            return 8;
        }
        case 0x87:
        {
            ResetRegisterBit(regA,0);
            regPC.value+=2;
            return 8;
        }
        case 0x8F:
        {
            ResetRegisterBit(regA,1);
            regPC.value+=2;
            return 8;
        }
        case 0x97:
        {
            ResetRegisterBit(regA,2);
            regPC.value+=2;
            return 8;
        }
        case 0x9F:
        {
            ResetRegisterBit(regA,3);
            regPC.value+=2;
            return 8;
        }
        case 0xA7:
        {
            ResetRegisterBit(regA,4);
            regPC.value+=2;
            return 8;
        }
        case 0xAF:
        {
            ResetRegisterBit(regA,5);
            regPC.value+=2;
            return 8;
        }
        case 0xB7:
        {
            ResetRegisterBit(regA,6);
            regPC.value+=2;
            return 8;
        }
        case 0xBF:
        {
            ResetRegisterBit(regA,7);
            regPC.value+=2;
            return 8;
        }
        case 0x8E:
        {
            ResetMemoryBit(regHL.value,1);
            regPC.value+=2;
            return 8;
        }
        case 0x9E:
        {
            ResetMemoryBit(regHL.value,3);
            regPC.value+=2;
            return 8;
        }
        case 0xAE:
        {
            ResetMemoryBit(regHL.value,5);
            regPC.value+=2;
            return 8;
        }
        case 0xBE:
        {
            ResetMemoryBit(regHL.value,7);
            regPC.value+=2;
            return 8;
        }
        
        /*
         * SET b, r
         */
        case 0xC0:
        {
            Set8BitRegBit(regB, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD0:
        {
            Set8BitRegBit(regB, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE0:
        {
            Set8BitRegBit(regB, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF0:
        {
            Set8BitRegBit(regB, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC1:
        {
            Set8BitRegBit(regC, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD1:
        {
            Set8BitRegBit(regC, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE1:
        {
            Set8BitRegBit(regC, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF1:
        {
            Set8BitRegBit(regC, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC2:
        {
            Set8BitRegBit(regD, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD2:
        {
            Set8BitRegBit(regD, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE2:
        {
            Set8BitRegBit(regD, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF2:
        {
            Set8BitRegBit(regD, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC3:
        {
            Set8BitRegBit(regE, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD3:
        {
            Set8BitRegBit(regE, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE3:
        {
            Set8BitRegBit(regE, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF3:
        {
            Set8BitRegBit(regE, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC4:
        {
            Set8BitRegBit(regH, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD4:
        {
            Set8BitRegBit(regH, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE4:
        {
            Set8BitRegBit(regH, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF4:
        {
            Set8BitRegBit(regH, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC5:
        {
            Set8BitRegBit(regL, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD5:
        {
            Set8BitRegBit(regL, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE5:
        {
            Set8BitRegBit(regL, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF5:
        {
            Set8BitRegBit(regL, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC6:
        {
            SetMemoryBit(regHL.value, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD6:
        {
            SetMemoryBit(regHL.value, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE6:
        {
            SetMemoryBit(regHL.value, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF6:
        {
            SetMemoryBit(regHL.value, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC7:
        {
            Set8BitRegBit(regA, 0);
            regPC.value+=2;
            return 8;
        }
        case 0xD7:
        {
            Set8BitRegBit(regA, 2);
            regPC.value+=2;
            return 8;
        }
        case 0xE7:
        {
            Set8BitRegBit(regA, 4);
            regPC.value+=2;
            return 8;
        }
        case 0xF7:
        {
            Set8BitRegBit(regA, 6);
            regPC.value+=2;
            return 8;
        }
        case 0xC8:
        {
            Set8BitRegBit(regB, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xD8:
        {
            Set8BitRegBit(regB, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xE8:
        {
            Set8BitRegBit(regB, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xF8:
        {
            Set8BitRegBit(regB, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xC9:
        {
            Set8BitRegBit(regC, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xD9:
        {
            Set8BitRegBit(regC, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xE9:
        {
            Set8BitRegBit(regC, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xF9:
        {
            Set8BitRegBit(regC, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCA:
        {
            Set8BitRegBit(regD, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDA:
        {
            Set8BitRegBit(regD, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xEA:
        {
            Set8BitRegBit(regD, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFA:
        {
            Set8BitRegBit(regD, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCB:
        {
            Set8BitRegBit(regE, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDB:
        {
            Set8BitRegBit(regE, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xEB:
        {
            Set8BitRegBit(regE, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFB:
        {
            Set8BitRegBit(regE, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCC:
        {
            Set8BitRegBit(regH, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDC:
        {
            Set8BitRegBit(regH, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xEC:
        {
            Set8BitRegBit(regH, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFC:
        {
            Set8BitRegBit(regH, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCD:
        {
            Set8BitRegBit(regL, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDD:
        {
            Set8BitRegBit(regL, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xED:
        {
            Set8BitRegBit(regL, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFD:
        {
            Set8BitRegBit(regL, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCE:
        {
            SetMemoryBit(regHL.value, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDE:
        {
            SetMemoryBit(regHL.value, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xEE:
        {
            SetMemoryBit(regHL.value, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFE:
        {
            SetMemoryBit(regHL.value, 7);
            regPC.value+=2;
            return 8;
        }
        case 0xCF:
        {
            Set8BitRegBit(regA, 1);
            regPC.value+=2;
            return 8;
        }
        case 0xDF:
        {
            Set8BitRegBit(regA, 3);
            regPC.value+=2;
            return 8;
        }
        case 0xEF:
        {
            Set8BitRegBit(regA, 5);
            regPC.value+=2;
            return 8;
        }
        case 0xFF:
        {
            Set8BitRegBit(regA, 7);
            regPC.value+=2;
            return 8;
        }

        /*
         * RR n
         *
         */
        case 0x18:
        {
            Rotate8BitRegRight(regB, true);
            regPC.value+=2;
            return 8;
        }
        case 0x19:
        {
            Rotate8BitRegRight(regC, true);
            regPC.value+=2;
            return 8;
        }
        case 0x1A:
        {
            Rotate8BitRegRight(regD, true);
            regPC.value+=2;
            return 8;
        }
        case 0x1B:
        {
            Rotate8BitRegRight(regE, true);
            regPC.value+=2;
            return 8;
        }
        case 0x1C:
        {
            Rotate8BitRegRight(regH, true);
            regPC.value+=2;
            return 8;
        }
        case 0x1D:
        {
            Rotate8BitRegRight(regL, true);
            regPC.value+=2;
            return 8;
        }
        case 0x1E:
        {
            RotateAddressRight(regHL.value,true);
            regPC.value+=2;
            return 16;
        }
    default:
        std::cout<<"Opcode CB"<<std::hex <<(unsigned)param<< " not yet implemented!"<<std::endl;            
        exit(-1);

    }

}

/*
 * Jumps
 *
 */
case 0x18:
{
    Jump8BitImmediate(true);
    regPC.value+=2;
    return 8;
}
case 0x20:
{
    Jump8BitImmediate(FlagCleared(ZERO));
    regPC.value+=2;
    return 8;
}
case 0x28:
{
    Jump8BitImmediate(FlagSet(ZERO));
    regPC.value+=2;
    return 8;
}
case 0xC3:
{
    Jump16BitImmediate();
    return 12;
}

case 0x30:
{
    Jump8BitImmediate(FlagCleared(CARRY));
    regPC.value+=2;
    return 8;
} 
case 0x38:
{
    Jump8BitImmediate(FlagSet(CARRY));
    regPC.value+=2;
    return 8;
} 

case 0xC2:
{
    if(FlagCleared(ZERO))
        Jump16BitImmediate();
    else
        regPC.value+=3;
    return 12;
}
case 0xCA:
{
    if(FlagSet(ZERO))
        Jump16BitImmediate();
    else
        regPC.value+=3;
    return 12;
}
case 0xD2:
{
    if(FlagCleared(CARRY))
        Jump16BitImmediate();
    else
        regPC.value+=3;
    return 12;
}
case 0xDA:
{
    if(FlagSet(CARRY))
        Jump16BitImmediate();
    else
        regPC.value+=3;
    return 12;
}

/*
 * JP (HL)
 *
 */
case 0xE9:
{
    JumpToAddress(regHL.value);
    return 4;
}

/*
 * INC n
 *
 */
case 0x3C:
{
    Increment8BitReg(regA);
    regPC.value++;
    return 4;
}
case 0x04:
{
    Increment8BitReg(regB);
    regPC.value++;
    return 4;
}
case 0x0C:
{
    Increment8BitReg(regC);
    regPC.value++;
    return 4;
}
case 0x14:
{
    Increment8BitReg(regD);
    regPC.value++;
    return 4;
}
case 0x1C:
{
    Increment8BitReg(regE);
    regPC.value++;
    return 4;
}
case 0x24:
{
    Increment8BitReg(regH);
    regPC.value++;
    return 4;
}
case 0x2C:
{
    Increment8BitReg(regL);
    regPC.value++;
    return 4;
}
case 0x34:
{
    IncrementAddress(regHL.value);
    regPC.value++;
    return 12;
}

/*
 * CALL nn
 *
 */
case 0xCD:
{
    Call();
    return 12;
}

/*
 * CALL cc, nn
 *
 */
case 0xC4:
{
    if(FlagCleared(ZERO))
        Call();
    else
        regPC.value+=3;
    return 12;
}
case 0xCC:
{
    if(FlagSet(ZERO))
        Call();
    else
        regPC.value+=3;
    return 12;
}
case 0xD4:
{
    if(FlagCleared(CARRY))
        Call();
    else
        regPC.value+=3;
    return 12;
}
case 0xDC:
{
    if(FlagSet(CARRY))
        Call();
    else
        regPC.value+=3;
    return 12;
}

/*
 * RET
 *
 */
case 0xC9:
{
    Return();
    return 8;
}

/*
 * RET cc
 *
 */

case 0xC0:
{
    if(FlagCleared(ZERO))
        Return();
    else
        regPC.value++;
    return 8;
}
case 0xC8:
{
    if(FlagSet(ZERO))
        Return();
    else
        regPC.value++;
    return 8;
}
case 0xD0:
{
    if(FlagCleared(CARRY))
        Return();
    else
        regPC.value++;
    return 8;
}
case 0xD8:
{
    if(FlagSet(CARRY))
        Return();
    else
        regPC.value++;
    return 8;
}

/*
 * RETI
 *
 */

case 0xD9:
{
    u16 address = PopStack();
    JumpToAddress(address);
    interruptMasterEnableFlag = true;
    return 8;
}


/*
 * INC nn
 *
 */
case 0x03:
{
    Increment16BitReg(regBC);
    regPC.value++;
    return 8;
}
case 0x13:
{
    Increment16BitReg(regDE);
    regPC.value++;
    return 8;
}
case 0x23:
{
    Increment16BitReg(regHL);
    regPC.value++;
    return 8;
}
case 0x33:
{
    regSP.value++;
    regPC.value++;
    return 8;
}

/*
 * RLA
 *
 */
case 0x17:
{
    Rotate8BitRegLeft(regA);
    regPC.value++;
    return 4;
}

/*
 * DEC n
 *
 */
case 0x3D:
{
    Decrement8BitReg(regA);
    regPC.value++;
    return 4;
}
case 0x05:
{
    Decrement8BitReg(regB);
    regPC.value++;
    return 4;
}
case 0x0D:
{
    Decrement8BitReg(regC);
    regPC.value++;
    return 4;
}
case 0x15:
{
    Decrement8BitReg(regD);
    regPC.value++;
    return 4;
}
case 0x1D:
{
    Decrement8BitReg(regE);
    regPC.value++;
    return 4;
}
case 0x25:
{
    Decrement8BitReg(regH);
    regPC.value++;
    return 4;
}
case 0x2D:
{
    Decrement8BitReg(regL);
    regPC.value++;
    return 4;
}
case 0x35:
{
    DecrementAddress(regHL.value);
    regPC.value++;
    return 12;
}

/*
 * DEC nn
 *
 */
case 0x0B:
{
    regBC.value--;
    regPC.value++;
    return 8;
}
case 0x1B:
{
    regDE.value--;
    regPC.value++;
    return 8;
}
case 0x2B:
{
    regHL.value--;
    regPC.value++;
    return 8;
}
case 0x3B:
{
    regSP.value--;
    regPC.value++;
    return 8;
}

/*
 * CP n
 *
 */
case 0xBF:
{
    Compare8BitReg(regA, regA);
    regPC.value++;
    return 4;
}
case 0xB8:
{
    Compare8BitReg(regA, regB);
    regPC.value++;
    return 4;
}
case 0xB9:
{
    Compare8BitReg(regA, regC);
    regPC.value++;
    return 4;
}
case 0xBA:
{
    Compare8BitReg(regA, regD);
    regPC.value++;
    return 4;
}
case 0xBB:
{
    Compare8BitReg(regA, regE);
    regPC.value++;
    return 4;
}
case 0xBC:
{
    Compare8BitReg(regA, regH);
    regPC.value++;
    return 4;
}
case 0xBD:
{
    Compare8BitReg(regA, regL);
    regPC.value++;
    return 4;
}
case 0xBE:
{
    CompareAddress(regA, regHL.value);
    regPC.value++;
    return 8;
}
case 0xFE:
{
    Compare8BitImmediate(regA, memory->Read(regPC.value+1));
    regPC.value+=2;
    return 8;
}

/*
 * DI 
 *
 */

case 0xF3:
{
    disableInterruptsCounter = 2;
    regPC.value++;
    return 4;
}

/*
 * IE
 *
 */

case 0xFB:
{
    enableInterruptsCounter = 2;
    regPC.value++;
    return 4;
}


/*
 * CPL
 *
 */
case 0x2F:
{
    regA = ~regA;
    SetFlags(ADDSUB|HALFCARRY);
    regPC.value++;
    return 4;
}

/*
 * RST n
 *
 */
case 0xC7:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x00);
    return 32;
}
case 0xCF:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x08);
    return 32;
}
case 0xD7:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x10);
    return 32;
}
case 0xDF:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x18);
    return 32;
}
case 0xE7:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x20);
    return 32;
}
case 0xEF:
{
    PushStack(regPC.value+1);
    JumpToAddress(0x28);
    return 32;
}
case 0xF7:
{
    PushStack(regPC.value+1);
    JumpToAddress((u16)0x30);
    return 32;
}
case 0xFF:
{
    PushStack(regPC.value+1);
    JumpToAddress((u16)0x38);
    return 32;
}


/*
 * DAA
 *
 */
case 0x27:
{
    u16 aVal = regA;

    u8 lower = aVal & 0xF;
    u8 upper = (aVal & 0xF0) >> 4;

    if(FlagCleared(ADDSUB))
    {
        if(FlagSet(HALFCARRY) || lower > 9)
            aVal+=6;

        if(FlagSet(CARRY) || aVal > 0x9F)
                aVal+=0x60;
    }
    else
    {
        if(FlagSet(HALFCARRY))
            aVal = (aVal-6) & 0xFF;
        if(FlagSet(CARRY))
            aVal -= 0x60; 
    }

    ClearFlags(HALFCARRY);
    SetZeroFlagFromResult(aVal);

    if((aVal & 0x100) == 0x100)
        SetFlags(CARRY);

    aVal &= 0xFF;

    regA = (u8)aVal;

    regPC.value++;
    return 4;
}

/*
 * CCF
 *
 */
case 0x3F:
{
    (FlagSet(CARRY))?ClearFlags(CARRY):SetFlags(CARRY);
    ClearFlags(ADDSUB|HALFCARRY);
    regPC.value++;
    return 4;
}

/*
 * SCF
 */
case 0x37:
{
    SetFlags(CARRY);
    ClearFlags(ADDSUB|HALFCARRY);
    regPC.value++;
    return 4;
}

/*
 * RLCA
 *
 */
case 0x07:
{
    Rotate8BitRegLeft(regA,false);
    regPC.value++;
    return 4;
}

/*
 * RRCA
 *
 */

case 0x0F:
{
    Rotate8BitRegRight(regA, false);
    regPC.value++;
    return 4;
}

/*
 * RRA
 *
 */

case 0x1F:
{
    Rotate8BitRegRight(regA,true);
    regPC.value++;
    return 4;
}


/*
 * ADD SP, n
 *
 */

case 0xE8:
{
    u16 value = regSP.value;
    s8 addend = (s8)memory->Read(regPC.value+1);

    u16 result = value + addend;

    ClearFlags(ZERO|ADDSUB);

    ((result&0xFF) < (regSP.value&0xFF))?SetFlags(CARRY):ClearFlags(CARRY);

    ((result&0xF) < (regSP.value&0xF))?SetFlags(HALFCARRY):ClearFlags(HALFCARRY);

    regSP.value=result;
    regPC.value+=2;
    return 16;
}

/*
 * STOP
 *
 */
case 0x10:
{
    haltUntilButtonPress = true;
    halted = true;
    //regPC.value++;
    return 4;
}

/*
 * HALT
 *
 */
case 0x76:
{
    halted = true;
    return 4;
}

default:
    std::cout<<"Opcode "<< std::hex << (unsigned)opcode << " not yet implemented!"<<std::endl;            
    PrintRegisters();
    exit(1);
    break;

#endif

