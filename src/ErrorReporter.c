//
// Created by m1504 on 2024/3/20.
//

#include "Structure/SimpleHashTable.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ErrorReporter.h"

#define IS_LEXICAL_ERROR(errorType) (errorType >= LEXICAL_ERROR_BASE && errorType <= UNDEF_LEXICAL_ERROR)
#define IS_SYNTAX_ERROR(errorType) (errorType >= SYNTAX_ERROR_BASE && errorType <= UNDEF_SYNTAX_ERROR)
#define IS_SEMANTIC_ERROR(errorType) (errorType >= SEMANTIC_ERROR_BASE && errorType <= UNDEF_SEMANTIC_ERROR)

#define ERROR_REPORTER_DEBUG

typedef struct ErrorInfo_s {
    int errorType;
    int lineNumber;
    char* externalMessage;
} ErrorInfo;
typedef ErrorInfo* ErrorInfo_t;

char semanticErrorTypeNames[][10] = {
        "UNDEF",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "11",
        "12",
        "13",
        "14",
        "15",
        "16",
        "17",
        "18",
};

SimpleHashTable_t errorTable = NULL;

FILE* errorFile = NULL;

ErrorInfo createErrorInfo(int lineNumber, int errorType, char* externalMessage) {
    ErrorInfo errorInfo;
    errorInfo.lineNumber = lineNumber;
    errorInfo.errorType = errorType;
    errorInfo.externalMessage = strdup(externalMessage);
    return errorInfo;
}

void freeErrorInfo(void* inErrorInfo) {
    ErrorInfo_t errorInfo = (ErrorInfo_t)inErrorInfo;
    if (errorInfo->externalMessage != NULL) {
        free(errorInfo->externalMessage);
    }
}

const char* getErrorTypeName(int errorType){
    if(IS_LEXICAL_ERROR(errorType))
    {
        return "A";
    }
    else if(IS_SYNTAX_ERROR(errorType))
    {
        return "B";
    }
    else if(IS_SEMANTIC_ERROR(errorType))
    {
        return semanticErrorTypeNames[errorType - SEMANTIC_ERROR_BASE];
    }
    return "UNDEF";
}

void printErrorInfo(const void* inErrorInfo) {
    fprintf(errorFile, "Error type %s at line %d: %s\n"
            , getErrorTypeName(((ErrorInfo_t)inErrorInfo)->errorType)
            , ((ErrorInfo_t)inErrorInfo)->lineNumber
            , ((ErrorInfo_t)inErrorInfo)->externalMessage);
}

void reportError(int line, int errorType, char* externalMessage) {
    if (errorTable == NULL) {
        errorTable = SimpleHashTable_createHashTable(sizeof(ErrorInfo), NULL, NULL);
    }

#ifdef ERROR_REPORTER_DEBUG
printf("DEBUG: Error type %s at line %d: %s\n\n"
            , getErrorTypeName(errorType)
            , line
            , externalMessage);
#endif

    ErrorInfo_t existedErrorInfo = (ErrorInfo_t)SimpleHashTable_find(errorTable, &line, sizeof(int));
    if(existedErrorInfo != NULL && existedErrorInfo->errorType <= errorType)
    {
#ifdef ERROR_REPORTER_DEBUG
        printf("DEBUG: Higher Priority Error already exists at line %d, ignore new error\n\n", line);
#endif
        return;
    }
    ErrorInfo errorInfo = createErrorInfo(line, errorType, externalMessage);

#ifdef ERROR_REPORTER_DEBUG
    printf("DEBUG: Error type %s in *ErrorInfo* at line %d: %s\n\n"
            , getErrorTypeName(errorInfo.errorType)
            , errorInfo.lineNumber
            , errorInfo.externalMessage);
#endif

    SimpleHashTable_forceInsert(errorTable, (char*)&line, sizeof(int), &errorInfo, NULL, freeErrorInfo);

#ifdef ERROR_REPORTER_DEBUG
    printf("DEBUG: Error type %s in *ErrorTable* at line %d: %s\n\n"
            , getErrorTypeName(((ErrorInfo_t)SimpleHashTable_find(errorTable, &line, sizeof(int)))->errorType)
            , ((ErrorInfo_t)SimpleHashTable_find(errorTable, &line, sizeof(int)))->lineNumber
            , ((ErrorInfo_t)SimpleHashTable_find(errorTable, &line, sizeof(int)))->externalMessage);
#endif

}

void reportErrorFormat(int line, int errorType, const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    reportError(line, errorType, buffer);
}

void printError(FILE *file) {
    if(errorTable == NULL || file == NULL)
    {
        return;
    }
    errorFile = file;
    SimpleHashTable_traverse(errorTable, printErrorInfo);
}

void resetErrorReporter() {
    if (errorTable != NULL) {
        SimpleHashTable_destroyHashTable(errorTable, NULL, freeErrorInfo);
    }
    errorTable = NULL;
    errorFile = NULL;
}

int hasError()
{
    return errorTable == NULL ? 0 : 1;
}
