#include "expr.h"
#include "fileScanner.h"
#include "symtable.h"
#include "symstack.h"

/*E -> E + E
E = E
E – E
E < E
E > E
E * E
E / E
E // E
E <= E
E >= E
E != E
E == E
E
id
*/


symStack stack;

symTable *dummyTable;

int precedenceTable[TABLE_SIZE][TABLE_SIZE] =
{
    {R, S, R, S, S, R, R},
    {R, R, R, S, S, R, R},
    {S, S, ER, S, S, R, R},
    {R, R, R, ER, ER, R, R},
    {S, S, S, S, S, EQ, ER},
    {R, R, R, ER, ER, R, R},
    {S, S, S, S, S, ER, ER},
};


precedenceTabSym tokenToSymbol(tokenStruct *token)
{
    switch (token->tokenType)
    {
    case TOKEN_PLUS_SIGN:
        return SYM_PLUS;
        break;
    case TOKEN_MINUS_SIGN:
        return SYM_MINUS;
        break;
    case TOKEN_MULTIPY_SIGN:
        return SYM_MUL;
        break;
    case TOKEN_DIVIDE_SIGN:
        return SYM_DIV;
        break;
    case TOKEN_WHOLE_DIVISION_SIGN:
        return SYM_SPEC_DIV;
        break;
    case TOKEN_ASSIGN_SIGN:
        return SYM_ASSIGN;
        break;
    case TOKEN_LESS:
        return SYM_LESS;
        break;
    case TOKEN_MORE:
        return SYM_MORE;
        break;
    case TOKEN_LESS_EQUAL:
        return SYM_LESS_EQ;
        break;
    case TOKEN_MORE_EQUAL:
        return SYM_MORE_EQ;
        break;
    case TOKEN_EQUALS:
        return SYM_EQ;
        break;
    case TOKEN_NOT_EQUAL:
        return SYM_NOT_EQ;
        break;
    case TOKEN_LEFT_BRACKET:
        return SYM_LEFT_BRACKET;
        break;
    case TOKEN_RIGHT_BRACKET:
        return SYM_RIGHT_BRACKET;
        break;
    case TOKEN_IDENTIFIER:
        return SYM_ID;
        break;
    case TOKEN_INTEGER:
        return SYM_INT;
        break;
    case TOKEN_DOUBLE:
        return SYM_DOUBLE;
        break;
    case TOKEN_STRING:
        return SYM_STRING;
        break;
    default:
        return SYM_DOLAR;
        break;
    }
}

int getTokenType(tokenStruct *token, symTable *localTable)
{
    if(token->tokenType == TOKEN_INTEGER)
    {
        return INT;
    }
    else if(token->tokenType == TOKEN_DOUBLE)
    {
        return DOUBLE;
    }
    else if(token->tokenType == TOKEN_STRING)
    {
        return STRING;
    }
    else if(token->tokenType == TOKEN_IDENTIFIER)
    {
        symTableItem *sym;
        if((sym = STSearch(localTable, token->stringValue->str)) == NULL)
        {
            return NONE;
        }
        else
        {
            return sym->type;
        }

    }



}

int symbolToType(precedenceTabSym symbol)
{
    if(symbol == SYM_PLUS || symbol == SYM_MINUS)
    {
        return PREC_TAB_PLUS_MINUS;
    }
    else if(symbol == SYM_MUL || symbol == SYM_DIV || symbol == SYM_SPEC_DIV)
    {
        return PREC_TAB_MUL_DIV_IDIV;
    }
    else if(symbol == SYM_ASSIGN ||
            symbol == SYM_LESS || symbol == SYM_LESS_EQ ||
            symbol == SYM_MORE || symbol == SYM_MORE_EQ ||
            symbol == SYM_EQ || symbol == SYM_NOT_EQ)
    {
        return PREC_TAB_RELATION_OPERATOR;
    }
    else if(symbol == SYM_ID || symbol == SYM_INT || symbol == SYM_DOUBLE || symbol == SYM_STRING)
    {
        return PREC_TAB_ID;
    }
    else if(symbol == SYM_LEFT_BRACKET)
    {
        return PREC_TAB_LEFT_BRACKET;
    }
    else if(symbol == SYM_RIGHT_BRACKET)
    {
        return PREC_TAB_RIGHT_BRACKET;
    }
    else if(symbol == SYM_DOLAR)
    {
        return PREC_TAB_DOLAR;
    }
}


symStackItem *getTopTerm()
{
    symStackItem *topItem = (&stack)->top;
    while (topItem != NULL)
    {
        if(topItem->symbol <= SYM_DOLAR)
            return topItem;
        topItem = topItem->nextItem;
    }

    return NULL;

}

bool getitemsBeforeStop(int *itemsBeforeStop)
{
    symStackItem *tempItem = (&stack)->top;

    while (tempItem != NULL)
    {
        if(tempItem->symbol != SYM_STOP)
        {
            (*itemsBeforeStop)++;
        }
        else
        {
            return true;
        }
        
        tempItem = tempItem->nextItem;
    }
    return false;
}

int checkExprRule(symStackItem *firstItem, symStackItem *secondItem, symStackItem *thirdItem, int numberOfItems)
{
    if(numberOfItems == 1)
    {
        if(symbolToType(firstItem->symbol) == PREC_TAB_ID)
        {
            return EXPR_ID;
        }
        else
        {
            return EXPR_ERR;
        }
    }
    else if(numberOfItems == 3)
    {
        if(firstItem->symbol == SYM_NON_TERM && thirdItem->symbol == SYM_NON_TERM)
        {
            if(secondItem->symbol == SYM_PLUS)
            {
                return EXPR_PLUS;
            }
            else if(secondItem->symbol == SYM_MINUS)
            {
                return EXPR_MINUS;
            }
            else if(secondItem->symbol == SYM_MUL)
            {
                return EXPR_MUL;
            }
            else if(secondItem->symbol == SYM_DIV)
            {
                return EXPR_DIV;
            }
            else if(secondItem->symbol == SYM_SPEC_DIV)
            {
                return EXPR_SPEC_DIV;
            }
            else if(secondItem->symbol == SYM_LESS)
            {
                return EXPR_LESS;
            }
            else if(secondItem->symbol == SYM_MORE)
            {
                return EXPR_MORE;
            }
            else if(secondItem->symbol == SYM_LESS_EQ)
            {
                return EXPR_LESS_EQ;
            }
            else if(secondItem->symbol == SYM_MORE_EQ)
            {
                return EXPR_MORE_EQ;
            }
            else if(secondItem->symbol == SYM_NOT_EQ)
            {
                return EXPR_LESS_EQ;
            }
            else if(secondItem->symbol == SYM_EQ)
            {
                return EXPR_EQ;
            }
            else if(secondItem->symbol == SYM_ASSIGN)
            {
                return EXPR_ASSIGN;
            }
        }
        else
        {
            return EXPR_ERR;
        }
        
    }
    else 
    {
        return EXPR_ERR;
    }
}

int checkItems(symStackItem *firstItem, symStackItem *secondItem, symStackItem *thirdItem, int exprRule)
{
    if(exprRule == EXPR_ID && firstItem->type == TYPE_NONE)
    {
        return TYPE_NONE;
    }
    else
    {
        if(exprRule == EXPR_ID)
        {
            return firstItem->type;
        }
        if(exprRule == EXPR_LESS || exprRule == EXPR_LESS_EQ ||
           exprRule == EXPR_MORE || exprRule == EXPR_MORE_EQ ||
           exprRule == EXPR_ASSIGN ||
           exprRule == EXPR_EQ || exprRule == EXPR_NOT_EQ)
        {
            return BOOL;
        }
        if(exprRule == EXPR_DIV)
        {
            return DOUBLE;
        }
        if(exprRule == EXPR_SPEC_DIV)
        {
            return INT;
        }
        if(exprRule == EXPR_MUL || exprRule == EXPR_PLUS || exprRule == EXPR_MINUS)
        {
            if(firstItem->type == INT && thirdItem->type == INT)
            {
                return INT;
            }
            else if(firstItem->type == DOUBLE && thirdItem->type == DOUBLE)
            {
                return DOUBLE;
            }
            else if(firstItem->type == STRING && thirdItem->type == STRING)
            {
                return STRING;
            }
        }
    }
    
}

void reduce()
{
        bool hasStop = false;

        int itemsBeforeStop = 0;

        hasStop = getitemsBeforeStop(&itemsBeforeStop);
        
        int rule;

        if(hasStop)
        {
            if(itemsBeforeStop == 1)
            {
                rule = checkExprRule((&stack)->top, NULL, NULL, 1);
            }
            else if(itemsBeforeStop == 3)
            {
                rule = checkExprRule((&stack)->top->nextItem->nextItem, (&stack)->top->nextItem, (&stack)->top, 3);
            }
            else
            {
                return 2;
            }
            
        }
        else
        {
            return 2;
        }

        int type;
        type = checkItems((&stack)->top->nextItem->nextItem, (&stack)->top->nextItem, (&stack)->top, rule);
        
        if(type != TYPE_NONE)
        {
            generateExpresion(rule);
        }

        for(int i = 0; i <= itemsBeforeStop; i++)
        {
            symStackPop(&stack);
        }           
        
        symStackPush(&stack, SYM_NON_TERM, INT);
}

void shift(precedenceTabSym currentSym, tokenStruct *token)
{
    symStackPushStop(&stack);

    symStackPush(&stack, currentSym, getTokenType(token, dummyTable));

    if(symbolToType(currentSym) == PREC_TAB_ID)
    {
        generateStackPush(token);
    }
}


int solveExpr(tokenStruct *token)
{

    int returnValue;

    bool end = false;
    precedenceTabSym currentSym;

    symStackItem *symStackTopSym;

    symStackInit(&stack);

    symStackPush(&stack, SYM_DOLAR, NONE);

    int currentSymType;
    int symStackTopSymType;

    while(!end)
    {
        symStackItem *tempItemPrint = (&stack)->top;


        currentSym = tokenToSymbol(token);
        symStackTopSym = getTopTerm();

        currentSymType = symbolToType(currentSym);
        symStackTopSymType = symbolToType(symStackTopSym->symbol);


        switch (precedenceTable[symStackTopSymType][currentSymType])
        {
        case ER:
            {
                if(currentSym == SYM_DOLAR && symStackTopSym->symbol == SYM_DOLAR)
                {
                    end = true;
                }
                else
                {
                    return 2;
                }
            }
            break;
        case EQ:
            {
                symStackPush(&stack, currentSym, getTokenType(token, dummyTable));
                returnValue = getToken(token);
            }
            break;
        case S:
            {
                
                shift(currentSym, token);
                returnValue = getToken(token);
            }
            break;
        case R:
            {

                reduce();
            }
            break;

        default:
            break;
        }

    }

}

int main(int argc, char *argv[])
{
    DS dynamicString;

    DSInit(&dynamicString);
    setDynamicString(&dynamicString);

    generateHeader();

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
    precedenceTabSym currentSym;

    tokenStruct token;

    token.stringValue = malloc(sizeof(DS));

    symStackItem *symStackTopSym;



    getToken(&token);
    getToken(&token);

    solveExpr(&token);
    printf("%s", dynamicString.str);

}
