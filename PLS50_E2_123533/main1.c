#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[40];
    unsigned short phone[10];
    unsigned int seatNo;
} seat;


//unused function - bypassed the problem that made me make it by only caring about the name to determine if a seat is reserved
seat* clean(seat* s, int n)
{
    for(int i = 0; i < n; i++)
    {
        if (s[i].seatNo>n || s[i].seatNo<0)
        {
            strcpy(s[i].name, "\0");
        }
    }
    return s;
}

//This is a function I made that takes an unsigned long representing a phone number, extracts it's digits (by 10 division)
//and puts each digit in a short array as asked.
unsigned short* phoneAssign(unsigned short* a, unsigned long int b)
{
    int i = 0;
    while (b != 0 && i<10) //get each digit of the number, reversed
    {
        a[i] = b%10;
        b = b/10;
        i++;
    }
    for(; i<10; i++) //fill the rest with -1
    {
        a[i] = -1;
    }

    int j = 9;   // j will point to last element
    i = 0;       // i will point to first element

    while (i < j)   //now reverse the array to get the right order
    {
        unsigned short temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;             // increment i
        j--;          // decrement j
    }
    return a;
}

int main()
{
    seat *seats;
    FILE *fp;
    fp = fopen("bus.txt", "r");
    char plateName[4];
    int plateNum;
    int numberOfSeats;
    unsigned long int tempPhone;
    char tempName1[40];
    char tempName2[40];
    char tmpc;
    int tempSeat;
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

    seats = malloc(numberOfSeats*(sizeof(seat)));
    for(int i = 0; i<numberOfSeats; i++)
    {
        strcpy(seats[i].name, "\0");
    }
    //reading the passengers in the file:
    while(fscanf(fp,"%s %s %u %ld", tempName1, tempName2, &tempSeat, &tempPhone) == 4) //check if i got the right number of file inputs
    {
        seat *s = malloc(sizeof(seat)); //create a new seat for the passenger
        strcpy(s->name, tempName1);
        strcat(s->name, " ");
        strcat(s->name, tempName2);
        s->seatNo = tempSeat;
        phoneAssign(s->phone, tempPhone);
        seats[tempSeat-1] = (*s); //put the passenger in the right array place
    }
    //ENTERING BASIC LOOP
    while(1)
    {
        size_t choice = 0;
        printf("Chose one of the following options:\n");
        printf("1: Print the number of free (available) seats on the bus right now\n");
        printf("2: Reserve a specific seat\n");
        printf("3: Check if a specific seat is reserved\n");
        printf("4: Cancel seat reservation\n");
        printf("5: Show reserved seats list sorted based on seat number\n");
        printf("0: Exit program\n");

        printf("Your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
        //EPILOGH: EMFANISH ARITHMOU THESEWN****************
        case 1:
            ;
            int freeSeats = 0;
            for (int i = 0; i<numberOfSeats; i++)
            {
                if (strcmp(seats[i].name,"\0") == 0)
                {
                    freeSeats++;
                    printf("%d-", i+1);
                }
            }
            printf("\nThe number of available seats is %d\n\n", freeSeats);
            break;
        //EPILOGH: KRATHSH SYGKEKRIMENHS THESHS****************
        case 2:
        {
            int myseat = 0;
            char tempname[40];
            char tmpc;
            unsigned long tmppl; //to store the phone with scanf before converting it to short[]
            seat *ts = malloc(sizeof(seat));
            printf("\nPlease specify the seat number which you want to reserve: ");
            scanf("%d", &myseat);
            if (myseat-1 >= numberOfSeats || myseat-1 <= 0) //if the seat number given is out of bounds, abort the request
            {
                printf("\nSorry, that seat doesn't exist!\n\n");
                continue;
            }
            if (strcmp(seats[myseat-1].name, "\0") != 0) //if the seat is reserved, abort the request
            {
                printf("\nSorry, that seat is already taken!\n\n");
                continue;
            }
            printf("\nPlease specify your first and last name: ");
            scanf("%s %s", tempName1, tempName2);
            while ((tmpc = getchar()) != '\n' && tmpc != EOF) { }
            strcpy(tempname, tempName1); //again in the next 2 lines we concatinate the first and last names into one
            strcat(tempname, " ");
            strcat(tempname, tempName2);
            printf("\nPlease specify your phone number: ");
            scanf("%lu", &tmppl); //take the phone in a temporary long variable
            while ((tmpc = getchar()) != '\n' && tmpc != EOF) { }
            phoneAssign(ts->phone, tmppl); //converting the long to [short array] with the phoneAssign function
            printf("\nOK! The seat %d is reserved for you.\n\n", myseat);
            //now fill the passenger details in the seat 'object' i created
            strcpy((*ts).name, tempname);
            (*ts).seatNo = myseat-1;
            phoneAssign(ts->phone, tempPhone);
            //And put that object in the array (yes, I do things 2 times for no reason, I just noticed it now that I am commenting)
            //But hey, everybody does mistakes right??
            strcpy(seats[myseat-1].name, ts->name);
            seats[myseat-1].seatNo = ts->seatNo;
            phoneAssign(seats[myseat-1].phone, tmppl);
        }
        break;
        //EPILOGH: AKYRWSH THESHS****************
        case 4:
        {
            int seat = 0;
            printf("Please specify the seat number which you want to cancel (seat numbers 1-%d): ", numberOfSeats);
            scanf("%d", &seat);
            while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
            if (seat-1 >= numberOfSeats || seat-1 <= 0)
            {
                printf("Sorry, that seat doesn't exist!");
                continue;
            }
            if (strcmp(seats[seat-1].name,"\0") == 0) //if the requested for deletion seat is empty already, abort request
            {
                printf("Sorry, that seat is not reserved!");
                continue;
            }
            printf("OK! The reservation for seat %d is cancelled.\n\n", seat); //else free it, which practically means...
            strcpy(seats[seat-1].name, "\0");                                  //...set it's name field to be "\0".
        }
        break;
        //EPILOGH: ELEGXOS KATASTASHS THESHS****************
        case 3:
            ;
            {
                int temp;
                int choice = 0;
                char tmpn[40];
                unsigned long tmpnum;
                printf("Search with name, or phone? ('1' = NAME, '2' = PHONE): ");
                scanf("%d", &choice); //take user input
                while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
                if (choice == 1) //if user wants to search by name,
                {
                    printf("Give the name you are searching for:");
                    scanf("%s %s", tempName1, tempName2); //get the name he wants in 2 variables...
                    strcpy(tmpn, tempName1);
                    strcat(tmpn, " ");
                    strcat(tmpn, tempName2); //and merge them into one string with a space between them.
                    while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
                    for (int i = 0; i<numberOfSeats; i++)
                    {
                        if (strcmp(seats[i].name, tmpn) == 0) //if that name is found
                        {
                            printf("The seat %d is reserved by %s with the phone number \n\n", i+1, tmpn); //tell the user...
                            for (int k = 0; k<10; k++)
                            {
                                printf("%u ", seats[i].phone[k]); //...and print the phone
                            }
                            printf("\n");
                            continue;
                        }
                    }
                    printf("No such person found!\n\n");
                    continue;
                }
                else if (choice == 2)
                {
                    unsigned short tempnum[10];
                    printf("Give the phone of the passenger you are searching for:");
                    scanf("%lu", &tmpnum);
                    phoneAssign(tempnum, tmpnum);
                    while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
                    for (int i = 0; i<numberOfSeats; i++)
                    {
                        //We'll compare the array containing the given number with all phones in the passenger list
                        temp = 0; //it starts from 0 in each comparisson
                        for (int j = 0; j<10; j++)
                        {
                            if (tempnum[j]!=seats[i].phone[j]) temp = 1; //if at least one digit is different make it =1
                        }
                        if (strcmp(seats[i].name, "\0")!=0 && temp == 0) //if it's still 0, the phone was found...
                        {
                            printf("The seat %d is reserved by %s with the phone number ", i+1, seats[i].name); //...so print it.
                            for (int k = 0; k<10; k++)
                            {
                                printf("%u ", seats[i].phone[k]);
                            }
                            printf("\n\n");
                            break;
                        }
                    }
                    if (temp==0) break;
                    printf("No such person found!\n\n");
                    continue;
                }
                printf("No such person has a ticket!\n\n");
            }
            break;
        //EPILOGH: EMFANISH KRATHMENWN THESEWN****************
        case 5:
            printf("The seats that are already reserved are seats:\n");
            for(int i = 0; i<numberOfSeats; i++)
            {
                if ((strcmp(seats[i].name,"\0") != 0) && seats[i].seatNo<=numberOfSeats && seats[i].seatNo>=0)
                {
                    printf("Seat: %d, Name: %s, phone: ", seats[i].seatNo, seats[i].name);
                    for (int k = 0; k<10; k++) printf("%u ", seats[i].phone[k]);
                    printf("\n");
                }
            }
            break;

        case 0:
            printf("\n\nClosing program. . .\nAuthor: Vasilis Anastasiadis\nAM:123533\n\n");
            return 0;
        }
    }
    return 0;
}