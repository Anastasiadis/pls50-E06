//Author Vasileios Anastasiadis
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float square(float x){ //perimetros tetragwnou
    return (x+x+x+x);
}
float rectangle(float x, float y){ //perimetros parallhlogrammou
    return (2*x+2*y);
}
float triangle(float x, float y){ //perimetros trigwnou
    return (sqrt(pow(x,2.0)+pow(y,2.0)) + x + y);
}
float circle(float x){ //perimetros kuklou
    return (2*x * 3.1415f);
}

int main()
{
    float shape; //epilogh sxhmatos
    float x;     //mhkos - plevra - aktina
    float y;     //platos - deyterh plevra
    while(1){
    printf("Parakalw pieste 1 gia tetragwno, 2 gia parallhlogramo, 3 gia trigwno h 4 gia kuklo kai pieste [ENTER]:\n");
    scanf(" %f",&shape);

    if (shape == 0){ //An o xrhsths piesei 0 gia eksodo
        printf("*********Kleisimo arithmomhxanhs*********");
        return 0;
    }
    if (shape<1 || shape>4)  // an h timh einai lathos ksanarxise th loupa apo thn arxh
    {
        printf("\n\nLathos epilogh, prospatheiste ksana!\n\n");
        continue;
    }
    if (shape == 1){
        printf("dwste to mhkos (se ekatosta) ths mias plevras tou tetragwnou:\n");
        scanf(" %f", &x);
        printf("H perimetros tou tetragwnou me plevra %f einai %f!\n\n", x, square(x)); //oi synarthseis kalountai mesa sthn printf!
    }
    else if (shape == 2){
        printf("dwste to mhkos (se ekatosta) parallhlogramou:\n");
        scanf(" %f", &x);
        printf("dwste to ypsos (se ekatosta) parallhlogramou:\n");
        scanf(" %f", &y);
        printf("H perimetros tou parallhlogramou me diastaseis %fx%f einai %f!\n\n", x, y, rectangle(x,y));
        if (x==y) printf("(BTW, ayto einai tetragwno :p)\n\n");
    }
    else if (shape == 3){
        printf("dwste to mhkos (se ekatosta) ths prwths katheths plevras tou trigwnou:\n");
        scanf(" %f", &x);
        printf("dwste to ypsos (se ekatosta) ths deyterhs katheths plevras tou trigwnou:\n");
        scanf(" %f", &y);
        printf("H perimetros tou orthogwniou trigwnou me kathetes plevres %f kai %f cm antistoixa einai %f!\n\n", x, y, triangle(x,y));
    }
    else if (shape == 4){
        printf("dwste to mhkos (se ekatosta) ths aktinas tou kuklou:\n");
        scanf(" %f", &x);
        printf("H perimetros tou kuklou me aktina %f einai %f!\n\n", x, circle(x));
    }
    }
    return 0;
}
