#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t *seats;
    FILE *fp;
    fp = fopen("bus.txt", "r");
    char plateName[4];
    int plateNum;
    int numberOfSeats;
    for (int i = 0; i<3; i++)
    {
        plateName[i] = getc(fp);
    }
    plateName[3] = '\0';
    fscanf (fp, "%d", &plateNum);
    fscanf (fp, "%d", &numberOfSeats);
    if (numberOfSeats<=5) //Elegxos gia mikro arithmo thesewn
    {
        printf("Number of seats <= 5. This is not a bus, this is a car!\n Please change the file and run the program again.");
        return(-1);
    }
    if (numberOfSeats>53) //Elegxos gia megalo arithmo thesewn
    {
        printf("Number of seats > 53.\nPlease change the bus.txt file and run the program again.");
        return(-1);
    }
    if ((numberOfSeats - 5)%4 !=0) // Elegxos gia isxy tou typou 4N+5
    {
        printf("There are %d excess seats on the number the file contains \n(or %d less seats, depending on how you look at it). \nNext time please put a valid number int the file!", (numberOfSeats - 5)%4, (4 - (numberOfSeats - 5)%4));
        return(-2);
    }
    printf("BUS PLATE: %s%d\n", plateName, plateNum);
    printf("No OF SEATS: %d  (%d*4 + 5)\n", numberOfSeats, (numberOfSeats-5)/4);

    seats = calloc(numberOfSeats, (sizeof(size_t))); //calloc gia na arxikopoihthoun sto 0 oles oi theseis / for zero initialization

    while(1)
    {
        size_t choice = 0;
        printf("Chose one of the following options:\n");
        printf("1: Print the number of free (available) seats on the bus right now\n");
        printf("2: Reserve a specific seat\n");
        printf("3: reserve first free seat\n");
        printf("4: Cancel seat reservation\n");
        printf("5: Check if a specific seat is reserved\n");
        printf("5: Show reserved seats list sorted based on seat number\n");
        printf("7: Show seat diagram\n");
        printf("8: Save licence plate and seat diagram in output file\n");
        printf("0: Exit program\n");

        printf("Your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
    //EPILOGH: EMFANISH ARITHMOU THESEWN****************
        case 1: ;
            int freeSeats = 0;
            for (int i = 0; i<numberOfSeats; i++)
            {
                if (seats[i]==0) freeSeats++;
            }
            printf("The number of available seats is %d\n", freeSeats);
            break;
    //EPILOGH: KRATHSH SYGKEKRIMENHS THESHS****************
        case 2:
            {
            int seat = 0;
            printf("\nPlease specify the seat number which you want to reserve: ");
            scanf("%d", &seat);
            if (seat-1 >= numberOfSeats || seat-1 <= 0)
            {
                printf("\nSorry, that seat doesn't exist!\n\n");
                continue;
            }
            if (seats[seat-1] != 0)
            {
                printf("\nSorry, that seat is already taken!\n\n");
                continue;
            }
            printf("\nOK! The seat %d is reserved for you.\n\n", seat);
            seats[seat-1] = 1;
            }
            break;
    //EPILOGH: KRATHSH TYXAIAS THESHS****************
        case 3: ; //Kenh ekfrash gia na pernaei to compile logw ths dhlwshs sthn amesws epomenh grammh
            int seat = -1;
            for (int i = 0; i<numberOfSeats; i++)
            {
                if (seats[i]==0)
                {
                    seat = i;
                    break;
                }
            }
            if (seat == -1)
            {
                printf("\nSorry, there are no free seats!\n\n");
                continue;
            }
            printf("\nOK! The seat %d is reserved for you.\n\n", seat+1);
            seats[seat] = 1;
            break;
    //EPILOGH: AKYRWSH THESHS****************
        case 4:
            {
            int seat = 0;
            printf("Please specify the seat number which you want to cancel (seat numbers 1-%d): ", numberOfSeats);
            scanf("%d", &seat);
            if (seats[seat-1] == 0)
            {
                printf("Sorry, that seat is not reserved!");
                continue;
            }
            if (seats[seat-1] >= numberOfSeats || seats[seat-1] <= 0)
            {
                printf("Sorry, that seat doesn't exist!");
                continue;
            }
            printf("OK! The reservation for seat %d is cancelled.\n", seat);
            seats[seat-1] = 0;
            }
            break;
    //EPILOGH: ELEGXOS KATASTASHS THESHS****************
        case 5: ;
            {
            int seat = 0;
            printf("Please specify the seat number which you want to check (seat numbers 1-%d): ", numberOfSeats);
            scanf("%d", &seat);
            if (seat-1 >= numberOfSeats || seat-1 <= 0)
            {
                printf("Sorry, that seat doesn't exist!");
                continue;
            }
            if (seats[seat-1] == 0)
            {
                printf("That seat is NOT reserved!");
                continue;
            }
            printf("The seat %d is reserved!\n", seat);
            }
            break;
    //EPILOGH: EMFANISH KRATHMENWN THESEWN****************
        case 6:
            printf("The seats that are already reserved are seats ");
            for(int i = 0; i<numberOfSeats; i++)
            {
                if (seats[i]==1) printf("%d | ", i+1);
            }
            break;
    //EPILOGH: EKTYPWSH PINAKIDAS KAI DIAGRAMMATOS*****************
        case 7:
            printf("%s%d\n", plateName, plateNum);
            if (seats[0]==1) printf("*"); else printf("_");
            for(int i = 1; i<numberOfSeats; i++)
            {
                if (numberOfSeats-5>i)
                {
                    if (i%4==0) printf("\n");
                    else if (i%2==0) printf(" ");
                }
                else if (numberOfSeats-5==i) printf("\n");
                if (seats[i]==1) printf("*");
                else printf("_");
            }
            printf("\n\n\n");
            break;
    //EPILOGH: EKTYPWSH PINAKIDAS KAI DIAGRAMMATOS SE ARXEIO LAYOUT.TXT**********************
        case 8: ;
            FILE *fp;
            fp = fopen("layout.txt", "w");
            fprintf(fp, "%s%d\n", plateName, plateNum);
            if (seats[0]==1) fprintf(fp, "*"); else fprintf(fp, "_");
            for(int i = 1; i<numberOfSeats; i++)
            {
                if (numberOfSeats-5>i)
                {
                    if (i%4==0) fprintf(fp, "\n");
                    else if (i%2==0) fprintf(fp, " ");
                }
                else if (numberOfSeats-5==i) fprintf(fp, "\n");
                if (seats[i]==1) fprintf(fp, "*");
                else fprintf(fp, "_");
            }
            fclose(fp);
            printf("\nLayout.txt file saved.\n\n");
            break;
    //EPILOGH: EKSODOS
        case 0:
            printf("\n\nClosing program. . .\nAuthor: Vasilis Anastasiadis\nAM:123533\n\n");
            return 0;
        }
    }
    return 0;
}
