#include <stdio.h>
#include "stack.h"
#include "generator.h"
#include <compiler.h>
#include <symtable.c>
#include <dynamicString.h>

int analysis();

char* doubleToString(double convertedNumber){
    
    char doubleInString[50];
    snprintf( doubleInString, 50, "%f", convertedNumber);

    return doubleInString;
}

int analysis()
    {
        DS dynamicStr;

        DSInit(&dynamicStr);
        setDynamicString(&dynamicStr);

        CompilerData compilerData;
            


        

    }

    static int Prog (TData *data){
        

    }

    static int anotherCommand (){

    }

    static int Commands (){

    }

    static int commandValue (){

    }

    static int Values(){

    }

    static int Value(){

    }

    static int Params(){

    }

    static int Params(){

    }

    static int anotherParam (){

    }

    static int commandValue (){

    }

    static int listCommandFunction(){

    }



/*int main(int argc, char *argv[])
{
    tokenStruct *t;

    DS dynamicString;

    DSInit(&dynamicString);

    setDynamicString(&dynamicString);

    bool newLine = true;

    Stack indentationStack;

    initStack(&indentationStack);
    stackPush(&indentationStack, 0);


    t = malloc(sizeof(tokenStruct));
    t->stringValue = malloc(sizeof(DS));
    DSInit(t->stringValue);


    FILE *sourceCode;

    if(argc == 2)
    {
        sourceCode = fopen(argv[1], "r");
    }
    else
    {
        sourceCode = stdin;
    }

    setSourceCodeFile(sourceCode);
    
    generateHeader();


    
    while(t->tokenType != TOKEN_EOF)
    {
        if(getToken(t, newLine, &indentationStack) == ERROR_LEX)
        {
            printf("LEX ERROR");
            free(t);
            fclose(sourceCode);

            return -1;
        }
        if(t->tokenType == TOKEN_KEYWORD && t->keyword == PRINT)
        {
            getToken(t, false, &indentationStack);
            if(t->tokenType == TOKEN_LEFT_BRACKET)
            {
                while ( getToken(t, false, &indentationStack ) ){//prochazim termy a ukladam je do tisknuteho retezce dokud nenarazim na pravou zavorku
                    if ( t->tokenType == TOKEN_RIGHT_BRACKET ){
                        break;
                    }

                    //do dynamicStringu ukladam hodnoty jednotlivych termu a generuji vysledny tisknutelny retezec
                    //jak je uluzena hodnota tokenu po prvotni analyze? vse ve stringu?
                    else if ( t->tokenType == TOKEN_STRING){
                        dynamicString.str = DSAddStr(dynamicString.str, t->stringValue);
                    }
                    else if( t->tokenType == TOKEN_DOUBLE){
                        dynamicString.str = DSAddStr(dynamicString.str, doubleToString( t->doubleValue));
                    }
                     else if( t->tokenType == TOKEN_INTEGER)
                    {
                        dynamicString.str = DSAddStr(dynamicString.str, t->integerValue);
                    }
                    else if( t->tokenType == TOKEN_IDENTIFIER){
                        //patri sem hodnota z tabluky symbolu
                    }
                    else{
                        printf("SYNTAX ERROR");
                        return -6;
                    }

                    getToken(t, false, &indentationStack );
                     if ( t->tokenType == TOKEN_RIGHT_BRACKET ){
                        break;
                    }
                    else if ( t->tokenType == TOKEN_COLON){
                        ;
                    }
                    else{
                        printf("SYNTAX ERROR");
                        return -6;
                    }
                }

                if (t->tokenType == TOKEN_RIGHT_BRACKET){
                        generateWriteValue("s", t->stringValue->str);
                }
                else{
                    printf("SYNTAX ERROR");
                    return -6;
                }

                
            }
            else
            {
                printf("SYNTAX ERROR");
                return -6;
            }
            
        }
        if(t->tokenType == TOKEN_KEYWORD && t->keyword == DEF)
        {
            getToken(t, false, &indentationStack);
            if(t->tokenType == TOKEN_IDENTIFIER)
            {
                generateFunctionStart(t->stringValue->str);
            }
            else
            {
                printf("SYNTAX ERROR");
                return -6;
            }

        }
        if(t->tokenType == TOKEN_KEYWORD && t->keyword == RETURN)
        {
            getToken(t, false, &indentationStack);
            generateFunctionReturn("test", t);
        }
    }

    */

    free(t);
    fclose(sourceCode);

    generateFunctionEnd("test");

    printf("%s", dynamicString.str);

}


