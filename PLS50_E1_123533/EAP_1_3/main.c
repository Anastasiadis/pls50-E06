#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int C = 2;
    int x=0; // H eisodos tou xrhsth (dekadikos arithmos) / decimal user input

    while (1){
        printf("Dwste to dekadiko arithmo pou thelete na metatrapei se dyadiko:\n");
        scanf(" %d", &x);
        if (x==0) break; //Eksodos se periptwsh eisodou tou '0' / quit if user gives '0' as an input
        printf("\nO arithmos %d ANTESTRAMENOS sto dyadiko systhma einai : ", x);

        //o kwdikas apo katw typwnei ton arithmo antistrofa vhma-vhma me th xrhsh diaireshs kai mod
        short mod = x%C;
        mod == 1 ? putchar('1') : putchar('0'); //To ligotero shmantiko pshfio typwnetai prwto
        do{
            if (x==0) break;
            x/=C;
            mod = x%C;
            mod == 1 ? printf("%d", 1) : printf("%d", 0);
        }while(x!=0);
        printf("\n\n");
        x = 0;
    }
    printf("\n\nClosing Program. . .\nAutor: Vasilis Anastasiadis\nAM: 123533\n\n");
    return 0;
}
