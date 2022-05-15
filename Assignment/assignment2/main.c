#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

typedef enum {UG, PG} studentLevelT;

typedef struct StudentT {
    char* sName;
    studentLevelT level;
    int mark;
} StudentT;

char getGrade(StudentT student) {
    if (student.level == UG) {
        if(student.mark >= 86) {
            return 'A';
        } else if (student.mark >= 71) {
            return 'B';
        } else if (student.mark >= 61) {
            return 'C';
        } else if (student.mark >= 50) {
            return 'D';
        } else return 'F';
    } else {
        if(student.mark >= 85) {
            return 'A';
        } else if (student.mark >= 71) {
            return 'B';
        } else if (student.mark >= 60) {
            return 'C';
        } else return 'F';
    }
}

void displayStudentNameAndGrade(char* key, StudentT* value) {
    char grade = getGrade(*value);
    printf("%s %s\n%c\n", key, value->sName, grade);
}


int main() {
    FILE *studentData;
    symtabADT table = EmptySymbolTable();
    studentData = fopen("E:\\Projects\\CSCI2100C_Asgn2_Q8\\studentData.txt", "r");
    if (studentData == NULL) {
        printf("File %s not existed or read failure.\n", "studentData.txt");
        exit(EXIT_FAILURE);
    }
    char line[50];
    while(fgets(line, sizeof(line), studentData) != NULL) {
        char sid[50];
        strcpy(sid, strtok(line, "\n"));
        studentLevelT level = line[1] == '0' ? PG : UG;
        if (fgets(line, sizeof(line), studentData) == NULL) {
            exit(EXIT_FAILURE);
        }
        char name[50];
        strcpy(name, strtok(line, "\n"));
        if (fgets(line, sizeof(line), studentData) == NULL) {
            exit(EXIT_FAILURE);
        }
        int mark = 0;
        sscanf_s(line, "%d", &mark);
        StudentT *student = (StudentT *)malloc(sizeof(*student));
        student->level = level;
        student->sName = (char*)malloc((strlen(name) + 1) * sizeof(char));
        strcpy(student->sName, name);
        student->mark = mark;
        Enter(table, sid, student);
    }
    fclose(studentData);
    FILE *dataCorrection;
    dataCorrection = fopen("E:\\Projects\\CSCI2100C_Asgn2_Q8\\dataCorrection.txt", "r");
    if (dataCorrection == NULL) {
        printf("File %s not existed or read failure.\n", "dataCorrection.txt");
        exit(EXIT_FAILURE);
    }
    while(fgets(line, sizeof(line), dataCorrection) != NULL) {
        char sid[50];
        strcpy(sid, strtok(line, "\n"));
        StudentT* student = (StudentT *)Lookup(table, sid);
        if (fgets(line, sizeof(line), dataCorrection) == NULL) {
            exit(EXIT_FAILURE);
        }
        int mark = 0;
        sscanf_s(line, "%d", &mark);
        if (student != NULL) {
            student->mark = mark;
            //  Enter(table, sid, student); You don't need this line actually.
        }
    }
    forEachEntryDo(displayStudentNameAndGrade, table);
    return 0;
}
