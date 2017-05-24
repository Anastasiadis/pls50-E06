#include <stdio.h>
#include <stdlib.h>
//Author Anastasiadis Vasileios
int main()
{
    float a, c;
    char b;
    float result;
    int ok = 0; //to xrhsimopoiw dan boolean (0 = false, alliws true) gia na ksanarwthsw to xrhsth se periptwsh lathoys sthn eisodo, me do-while
    do{
    ok = 1;
    a = c = result = 0.0f; // arxikopoihsh twn metavlhtwn mou
    printf("Dwste thn praksh me th morfh:\n (arithmos) (praksh) (arithmos), xwris tis parentheseis kai pieste enter\n");
    scanf("%f %c %f", &a, &b, &c);
    switch (b){
        case '+':
        {
            result = a + c;
            break;
        }
        case '*':
        {
            result = a*c;
            break;
        }
        case '/':
        {
            if (c==0)
            {
                printf("Diairesh me to 0! Parakalw ksanaprospathiste ->\n");
                ok = 0;
                break;
            }
            result = a/c;
            break;
        }
        default:
            {
                printf("Dwsate lathos praksh! Parakalw ksanaprospathiste ->\n");
                ok = 0;
                break;
            }
    }
    } while (!ok);

    printf("To apotelesma einai %f %c %f = %f \n", a,b,c,result);

    return 0;
}
