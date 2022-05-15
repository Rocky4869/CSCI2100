//
// Created by Raynor on 8/3/2021.
//

#ifndef CSCI2100B_ASS2_SYMTAB_H
#define CSCI2100B_ASS2_SYMTAB_H

typedef struct symtabCDT* symtabADT;
typedef void (*symtabFnT)(char*, void*);

symtabADT EmptySymbolTable(void);
void Enter(symtabADT table, char *key, void *value);
void *Lookup(symtabADT table, char *key);
void forEachEntryDo(symtabFnT, symtabADT);


#endif //CSCI2100B_ASS2_SYMTAB_H
