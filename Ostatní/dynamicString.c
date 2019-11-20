#include "dynamicString.h"

void DSInit(DS *dynamicStr)
{
    dynamicStr->str = NULL;
    dynamicStr->maxLenght = 0;
    dynamicStr->actIndex = 0;
}

bool DSAddChar(DS *dynamicStr, char character)
{
    if(dynamicStr->maxLenght - dynamicStr->actIndex <= 1)
    {
        dynamicStr->maxLenght += CHUNK;
        dynamicStr->str = realloc(dynamicStr->str, dynamicStr->maxLenght);

        if(dynamicStr->str == NULL)
        {
            return false;
        }
    }

    dynamicStr->str[dynamicStr->actIndex++] = character;
    dynamicStr->str[dynamicStr->actIndex] = '\0';

    return true;
}

bool DSAddStr(DS *dynamicStr, char *str)
{
    while(*str != '\0')
    {
        if(!DSAddChar(dynamicStr, *str))
        {
            return false;
        }

        str++;
    }

    return true;
}

/*bool DSAddStr(DS *dynamicStr, tokenStruct *token)
{
    token->stringValue = malloc(dynamicStr->maxLenght);
    while((dynamicStr->maxLenght - dynamicStr->actIndex) <= strLenght)
    {
        dynamicStr->maxLenght += CHUNK;
        dynamicStr->str = realloc(dynamicStr->str, dynamicStr->maxLenght);

        if(dynamicStr->str == NULL)
        {
            return false;
        }
    }

    strcpy(token->stringValue, dynamicStr->str);
    return true;
}*/

void DSDelete(DS *dynamicStr)
{
    free(dynamicStr->str);
    DSInit(dynamicStr);
}
