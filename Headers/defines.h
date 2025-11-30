#ifndef DEFINES_H
#define DEFINES_H

// Set a bit
#define SETBIT(WORD,BIT) (WORD|=(1<<BIT))

// Clear a bit
#define CLRBIT(WORD,BIT) (WORD&=(~(1<<BIT)))

// Read SourceWORD[SBIT] and write it to DistnationWORD[DBIT]
#define READWRITEBIT(DWORD,DBIT,SWORD,SBIT)\
((DWORD&(~(1<<DBIT)))|(((SWORD>>SBIT)&1)<<DBIT))

// Read a bit
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)

// Write bit level (1 or 0)
#define WRITEBIT(WORD,BIT,BITLEVEL)\
BITLEVEL?(SETBIT(WORD,BIT)):(CLRBIT(WORD,BIT))

// Write 1 byte at BITST position
#define WRITEBYTE(WORD,BITST,BYTE)\
WORD=((WORD&~(0xff<<BITST)| (BYTE<<BITST)))

// Read nibble (4 bits)
#define READNIBBLE(WORD,NIB)  ((WORD>>NIB)&0xf)

// Write nibble at NIB_BIT position
#define WRITENIBBLE(WORD,NIB_BIT,NIB)\
WORD=((WORD &(~(0x0f<<NIB_BIT)))| (NIB<<NIB_BIT))

#endif //DEFINES_H
