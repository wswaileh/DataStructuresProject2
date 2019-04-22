#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#define eqSize 101

float postFixEvaluate(char *);
int prio(char );
int isOperation(char );
char* infixToPostfix(char *);
int isBracket(char );

int main()
{
    int i,arraySize=2*numOfLines(),maxEqLength=0;
    int choice;
    char equations[arraySize][eqSize];
    showMenu();
    scanf("%d",&choice);
    while (choice!=8)
    {
        switch (choice)
        {
        case 1:
            FillArray(equations,&maxEqLength);
            break;
        case 2:
            isValid(equations,&arraySize,&maxEqLength);
            break;
        case 3:
            covertValidToPostFix(equations,&arraySize,&maxEqLength);
            break;
        case 4:
            evaluateValidPostFix(equations,&arraySize,&maxEqLength);
            break;
        case 5:
            writeReport(equations,&arraySize,&maxEqLength);
            break;
        case 6:
            writeReportToFile(equations,&arraySize,&maxEqLength);
            break;
        case 7:
            system("cls");
            break;
        case 9:
            postFixSolveMenu();
            break;
        case 10:
            convertInfixToPostfixMenu();
            break;
        }
        showMenu();
        scanf("%d",&choice);
    }

    printf("GoodBye :)");
    return 0;
}

void isValid(char equations[][eqSize],int *arraySize,int *maxEqLength)
{
    int i;
    for (i=0; i<*arraySize; i++)
        if (isEquationValid(equations[i]))
            printf("Eq#%-2d\t%-*s is Valid!\n",i+1,*maxEqLength,equations[i]);
        else
            printf("Eq#%-2d\t%-*s is Not Valid!\n",i+1,*maxEqLength,equations[i]);
}

int isEquationValid(char *equation)
{
    int i=0;
    if (!correctBrackets(equation))
    {
        return 0;
    }

    while (i<strlen(equation))
    {
        if (i==0 && equation[i]!='-' && isOperation(equation[i])  )
            return 0;

        else if (equation[i]==' ')
        {
            return 0;
        }

        else if ( (isOperation(equation[i]) && isOperation(equation[i+1]) )&& ( equation[i]!='-' && equation[i+1] != '-' )  )
        {
            return 0;
        }

        else if ( isOperation(equation[strlen(equation)-1]) )
        {
            return 0;
        }

        else if (!isdigit(equation[i]) && !isOperation(equation[i]) && !isBracket(equation[i]))
        {
            return 0;
        }
        else if ( ( equation[i] =='(' || equation[i] =='[' || equation[i] =='{' ) && ( equation[i+2] ==')' || equation[i+2] ==']' || equation[i+2] =='}' ) && isdigit(equation[i+1]) )
            return 1;
        else if (equation[i-2]=='-' && equation[i-1]=='-' &&( equation[i]=='(' || equation[i]=='['|| equation[i]=='{' )  )
            return 0;

        i++;
    }
    return 1;

}

int isBracket(char x)
{
    if (x =='(' || x == ')')
        return 1;
    else if (x == '[' || x==']')
        return 1;
    else if ( x== '{' || x== '}')
        return 1;
    return 0;
}
int correctBrackets(char *equation)
{
    stack charStack = createStack();
    int i=0;

    while (i<strlen(equation))
    {
        if ( (equation[i] == '(' || equation[i] == '[' || equation[i] == '{' )&& ( equation[i+1] == ']' || equation[i+1] == '}' || equation[i+1] == ')') )
            return 0;
        else if (  isdigit(equation[i]) && ( equation[i+1] =='(' || equation[i+1] =='[' || equation[i+1] =='{' )   )
            return 0;
        else if (  isdigit(equation[i+1]) && ( equation[i] ==')' || equation[i] ==']' || equation[i] =='}' )   )
            return 0;
        else if ( ( equation[i+1] =='(' || equation[i+1] =='[' || equation[i+1] =='{' ) && (equation[i] ==')' || equation[i] ==']' || equation[i] =='}' ))
            return 0;
        else if ( ( equation[i] =='(' || equation[i] =='[' || equation[i] =='{' ) && ( equation[i+2] ==')' || equation[i+2] ==']' || equation[i+2] =='}' ) && !isdigit(equation[i+1]) )
            return 0;
        else if (equation[i] == '(' || equation[i] == '[' || equation[i] == '{' )
            push(charStack,equation[i]);
        else if (equation[i] == ')' && getTop(charStack)!='(')
            return 0;
        else if (equation[i] == ')' && getTop(charStack)=='(')
            pop(charStack);
        else if (equation[i] == ']' && getTop(charStack)!='[')
            return 0;
        else if (equation[i] == ']' && getTop(charStack)=='[')
            pop(charStack);
        else if (equation[i] == '}' && getTop(charStack)!='{')
            return 0;
        else if (equation[i] == '}' && getTop(charStack)=='{')
            pop(charStack);

        i++;
    }

    if (!isEmpty(charStack))
        return 0;

    return 1;
}
void writeReportToFile(char equations[][eqSize],int *arraySize,int *maxEqLength)
{
    char fileName[21];
    printf("Enter the name of the file you want to save report in followed by \".txt\" : \n");
    scanf("%s",fileName);
    FILE *in = fopen(fileName,"w");
    int i;
    char s[6];
    for (i=0; i<*arraySize; i+=2)
    {
        if ( postFixEvaluate(infixToPostfix(equations[i]))  == postFixEvaluate(infixToPostfix(equations[i+1])))
            strcpy(s,"True");
        else
            strcpy(s,"False");

        fprintf(in,"[Eq#%-2d Postfix => %-*s Solution Is => %7.2f] ?= [Eq#%-2d Postfix => %-*s Solution Is => %7.2f] -> %s\n",i+1,*maxEqLength,infixToPostfix(equations[i]),postFixEvaluate(infixToPostfix(equations[i])),i+2,*maxEqLength,infixToPostfix(equations[i+1]),postFixEvaluate(infixToPostfix(equations[i+1])),s );
    }
    fclose(in);
}

void writeReport(char equations[][eqSize],int *arraySize,int *maxEqLength)
{
    int i;
    char s[8],t[8];
    for (i=0; i<*arraySize; i+=2)
    {
        if ( isEquationValid(equations[i]) && isEquationValid(equations[i+1]) )
        {
            float eq1Value = postFixEvaluate(infixToPostfix(equations[i]));
            float eq2Value = postFixEvaluate(infixToPostfix(equations[i+1]));
            if ( eq1Value == eq2Value )
                strcpy(s,"True");
            else
                strcpy(s,"False");

            printf("[Eq#%-2d Postfix => %-*s Result => %7.2f] ?= [Eq#%-2d Postfix => %-*s Result => %7.2f] -> %s\n",i+1,*maxEqLength,infixToPostfix(equations[i]),eq1Value,i+2,*maxEqLength,infixToPostfix(equations[i+1]),eq2Value,s );
        }
        else
        {
            printf("[Eq#%-2d ",i+1);
            if (isEquationValid(equations[i]))
                printf("   Valid => Result => %7.2f]\t\t\t",postFixEvaluate(infixToPostfix(equations[i])));
            else
                printf("Invalid]\t\t\t");
            printf("[Eq#%-2d ",i+2);
            if (isEquationValid(equations[i+1]))
                printf("   Valid => Result => %7.2f]  \n",postFixEvaluate(infixToPostfix(equations[i+1])));
            else
                printf("Invalid]\n");

        }

    }
}

void evaluateValidPostFix(char equations[][eqSize],int *arraySize,int *maxEqLength)
{

    int i;
    for (i=0; i<*arraySize; i++)
        if (isEquationValid(equations[i]))
            printf("Solution For Eq#%d %-*s is => %.2f \n",i+1,*maxEqLength,equations[i],postFixEvaluate(infixToPostfix(equations[i])));

}

void covertValidToPostFix(char equations[][eqSize],int *arraySize,int *maxEqLength)
{
    int i;
    for (i=0; i<*arraySize; i++)
        if (isEquationValid(equations[i]))
            printf("Postfix For Eq#%-2d %-*s is => %s \n",i+1,*maxEqLength,equations[i],infixToPostfix(equations[i]));
}

void postFixSolveMenu()
{
    char eq[eqSize];
    printf("Enter The Equation You Want To Solve In This Format Please \"2,2,+,1,-,22,*,...\" :\n");
    scanf("%s",eq);
    printf("The Answer Is : %.2f\n",postFixEvaluate(eq));

}
void convertInfixToPostfixMenu()
{
    char eq[eqSize];
    printf("Enter The Equation You Want To Convert To PostFix Please:\n");
    scanf("%s",eq);
    printf("The Answer Is : %s\n",infixToPostfix(eq));
}


void showMenu()
{
    printf(" _______________________________________________________\n");
    printf("| Enter The Number Of Operation You Want To Do Please : |\n");
    printf("|     1.Read Data From File.                            |\n");
    printf("|     2.Check If Equations Are Valid Or Not.            |\n");
    printf("|     3.Convert Valid Equations To PostFix.             |\n");
    printf("|     4.Evaluate Valid Equations.                       |\n");
    printf("|     5.View A Complete Report About Every Equation.    |\n");
    printf("|     6.Print A Complete Report To A File.              |\n");
    printf("|     7.Clear Console.                                  |\n");
    printf("|     8.Exit                                            |\n");
    printf("|     9.Solve A PostFix Equation.                       |\n");
    printf("|     10.Covert An Infix Equation To Postfix.           |\n");
    printf("|_______________________________________________________|\n");
    printf("# Of Operation : ");

}


int numOfLines()
{
    int counter =0;
    char line[51];
    FILE *in = fopen("eq.txt","r");
    if (!in)
        return 0;
    else
        while (fgets(line,50,in) != NULL)
            counter++;
    return counter;
}

void FillArray(char equations[][eqSize],int *maxEqLength)
{
    int i=0;
    char line[51];
    FILE *in = fopen("eq.txt","r");
    if (!in)
        printf("File Not Found!\n");
    else
    {
        while (fgets(line,50,in) != NULL)
        {
            char *eq1 = strtok(line,"=");
            char *eq2 = strtok(NULL,"\n");
            if (strlen(infixToPostfix(eq1)) > *maxEqLength )
                *maxEqLength = strlen(infixToPostfix(eq1));
            if (strlen(infixToPostfix(eq2)) > *maxEqLength )
                *maxEqLength = strlen(infixToPostfix(eq2));

            strcpy(equations[i++],eq1);
            strcpy(equations[i++],eq2);
        }

    }
    fclose(in);
}

float postFixEvaluate(char *x)
{
    float ans;
    numStack numStack = createNumStack();
    int isPrevDigit=0,isNegative=0,i=0;
    while (x[i] != '\0')
    {
        if (i==0&&x[i] == '-')
        {
            isNegative = 1;
            i++;
        }

        if (x[i] ==',')
        {
            isPrevDigit=0;
            isNegative=0;
        }
        else if (x[i] == '-' && isdigit(x[i+1]))
        {
            isNegative = 1;
            isPrevDigit = 0;
        }
        else if (isPrevDigit)
        {
            int num = x[i] - '0';
            if (isNegative)
            {
                pushNumber(numStack, (popNumber(numStack)*10.0)- num );
            }
            else
            {
                pushNumber(numStack, (popNumber(numStack)*10.0)+ num );

            }

        }
        else if (isdigit(x[i]))
        {
            int num = x[i] - '0';
            isPrevDigit = 1;

            if (isNegative)
                pushNumber(numStack,-1.0*num);
            else
                pushNumber(numStack,num);
        }
        else
        {
            float n2 = getTopNumber(numStack);
            popNumber(numStack);
            float n1 = getTopNumber(numStack);
            popNumber(numStack);

            switch (x[i])
            {
            case '+' :
                ans = n1+n2;
                break;
            case '-' :
                ans = n1-n2;
                break;
            case '*' :
                ans = n1*n2;
                break;
            case '/' :
                if (n2 == 0)
                {
                    printf("Invalid Operation! Division By Zero In Below Equation!\n");
                    return 0;
                }
                else
                    ans = n1/n2;
                break;
            }
            pushNumber(numStack,ans);
            isPrevDigit = 0;
            isNegative=0;
        }
        i++;
    }

    ans = getTopNumber(numStack);
    deleteNumStack(numStack);
    return ans;
}

char* infixToPostfix(char *infix)
{
    stack postStack = createStack();
    char *postfix= malloc(eqSize);
    int isPrevDigit=0,isNeg=0;
    int i=0,j=0;
    while (infix[i]!='\0')
    {
        if (i==0&&infix[i]=='-')
        {
            isNeg = 1;
            postfix[j++]=infix[i];
        }
        else if (infix[i-1] == '-' && infix[i] == '-')
        {
            if ( (infix[i+1]=='(' || infix[i+1] == '[' || infix[i+1] == '{' ) && ( infix[i+3]!=')' && infix[i+3] != ']' && infix[i+3] != '}' ) )
                isNeg=0;
            else
                isNeg=1;
        }
        else if (infix[i]=='-' && ( isOperation(infix[i-1]) || infix[i-1] == '(' ) && isdigit(infix[i+1])   )
        {
            isNeg = 1;
        }
        else if (isdigit(infix[i]))
        {
            if (isNeg && i!= 1)
            {
                postfix[j++]='-';
                postfix[j++]=infix[i];
                isNeg=0;
            }
            else
            {
                postfix[j++] = infix[i];
                isNeg=0;
            }

        }
        else if (infix[i]==')' || infix[i] == ']' || infix[i] == '}')
        {
            isPrevDigit=0;
            while ( !isEmpty(postStack) && (getTop(postStack) != '(' || getTop(postStack) == ']' || getTop(postStack) == '}' ) )
            {
                postfix[j++]=',';
                postfix[j++] = getTop(postStack);
                pop(postStack);
            }
            if (!isEmpty(postStack))
                pop(postStack);
        }
        else if (isOperation(infix[i]))
        {
            isPrevDigit=0;

            while (!isEmpty(postStack) && (prio(infix[i]) < prio(getTop(postStack))  )   )
            {
                postfix[j++]=',';
                postfix[j++] = getTop(postStack);
                pop(postStack);
            }
            push(postStack,infix[i]);
            postfix[j++]=',';


        }
        else // infix[i] = '('
        {
            isPrevDigit=0;
            push(postStack,'(');
        }
        i++;
    }
    while (!isEmpty(postStack))
    {
        postfix[j++]=',';
        postfix[j++] = getTop(postStack);
        pop(postStack);
    }

    postfix[j]='\0';

    return postfix;
}

int prio(char a)
{
    int i;
    if((a=='+')||(a=='-'))
        i=0;
    if((a=='*')||(a=='/')||(a=='%'))
        i=1;
    if(a=='(')
        i=-1;
    return i;
}

int isOperation(char x)
{
    if (x=='+')
        return 1;
    if (x=='-')
        return 1;
    if (x=='*')
        return 1;
    if (x=='/')
        return 1;
    return 0;
}
