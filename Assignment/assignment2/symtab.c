//
// Created by Raynor on 8/3/2021.
//

#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define INITIALTABLESIZE 31

typedef struct bucketT {
    int inUse; // This is 1 if the bucket is in use, or 0 otherwise
    char *key;
    void *value; } bucketT;

struct symtabCDT { bucketT *bucket; int tableSize; };

int Hash(char *s, int n) {
    unsigned long hashcode = 0UL;
    for (int i=0; s[i]!='\0'; i++)
    hashcode = (hashcode<<6) + (unsigned long) s[i];
    return (int) (hashcode % n);
}

symtabADT EmptySymbolTable(void) {
    symtabADT table = (symtabADT)malloc(sizeof(*table));
    table->bucket = (bucketT*)malloc(sizeof(bucketT) * INITIALTABLESIZE);
    for (int i = 0; i < INITIALTABLESIZE; i++) {
        //  table->bucket[i] = (bucketT*)malloc(sizeof(bucketT));
        table->bucket[i].key = NULL;
        table->bucket[i].value = NULL;
        table->bucket[i].inUse = 0;
    }
    table->tableSize = INITIALTABLESIZE;
    return table;
}

void EnlargeTable(symtabADT table) {
    int prevTableSize = table->tableSize;
    bucketT * prevBucket = table->bucket;
    table->bucket = (bucketT*)malloc(sizeof(bucketT) * (table->tableSize + 10));
    table->tableSize = prevTableSize + 10;
    //  initialisation
    for (int i = 0; i < prevTableSize + 10; i++) {
        //  table->bucket[i] = (bucketT*)malloc(sizeof(bucketT));
        table->bucket[i].key = NULL;
        table->bucket[i].value = NULL;
        table->bucket[i].inUse = 0;
    }
    for (int i = 0; i < prevTableSize; i++) {
        if (prevBucket[i].inUse == 1) {
            Enter(table, prevBucket[i].key, prevBucket[i].value);
        }
    }
}

//  If two strings str1 and str2 are same (identical), then strcmp(str1, str2) == 0
static int FindBucket(symtabADT table, int hashCode, char* key) {
    int result = hashCode;
    int isFullFlag = 0;
    for (int i = 0; table->bucket[result].inUse; i++) {
        //  strcmp function return 0 iff two strs are identical
        if (strcmp(table->bucket[result].key, key) == 0) {
            break;
        }
        if (i == table->tableSize) {
            isFullFlag = 1;
            break;
        }
        result = (hashCode + i) % table->tableSize;
    }
    //  Cannot find an appropriate bucket to be placed
    //  This means the symbol table is full
   if (isFullFlag == 1) {
       EnlargeTable(table); // enlarge table and rehash existed elements
       hashCode = Hash(key, table->tableSize);  // rehash current element
       result = hashCode;
       for (int i = 0; table->bucket[result].inUse && i < table->tableSize; i++) {
           //  strcmp function return 0 iff two strs are identical
           if (strcmp(table->bucket[result].key, key) == 0) {
               return result;
           }
           result = (hashCode + i) % table->tableSize;
       }
   }
    return result;
}

void Enter(symtabADT table, char *key, void *value) {
    int hashCode = Hash(key, table->tableSize);
    hashCode = FindBucket(table, hashCode, key);
    table->bucket[hashCode].key = (char *) malloc(sizeof(char) * ((int)strlen(key) + 1));
    strcpy(table->bucket[hashCode].key, key);
    table->bucket[hashCode].value = value;
    table->bucket[hashCode].inUse = 1;
}

void *Lookup(symtabADT table, char *key) {
    int hashCode;
    hashCode = Hash(key, table->tableSize);
    hashCode = FindBucket(table, hashCode, key);
    if (table->bucket[hashCode].inUse == 0) return(NULL);
    return(table->bucket[hashCode].value);
}

void forEachEntryDo(symtabFnT f, symtabADT table) {
    for (int i = 0; i < table->tableSize; i++) {
        if (table->bucket[i].inUse == 1) {
            f(table->bucket[i].key, table->bucket[i].value);
        }
    }
}