#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

//Struct representing a player (3 of those are created in main for each player)
typedef struct{
    char name[17];
    char id; //char is only one byte, and it's enough for the id
    unsigned char score;
} player;

//Struct representing a card - I would use enums for the characteristics, but some have identical values, so i went with char
typedef struct{
    char color;
    char shape;
    char number;
    char texture;
} card;

//Function that returns a random color
char randomColor(int i)
{
    if (i%3==0) return 'b';
    if (i%3==1) return 'g';
    if (i%3==2) return 'r';
    return 'g';
}

//Function that returns a random shape
char randomShape(int i)
{
    if (i%3==0) return 'c';
    if (i%3==1) return 'r';
    if (i%3==2) return 't';
    return 'r';
}

//Function that returns a random number
char randomNumber(int i)
{
    if (i%3==0) return 1;
    if (i%3==1) return 2;
    if (i%3==2) return 3;
    return 2;
}

//Function that returns a random texture
char randomTexture(int i)
{
    if (i%3==0) return 'b';
    if (i%3==1) return 'e';
    if (i%3==2) return 'h';
    return 'e';
}

//This returns a random card - the check to see if it exists is on the getNewBoard function.
card* getRandomCard()
{
    card* c = malloc(sizeof(card));
    c->color = randomColor(rand());
    c->number = randomNumber(rand());
    c->shape = randomShape(rand());
    c->texture = randomTexture(rand());
    return c;
}

//Struct for a board of 12 cards in a 3*4 grid
typedef struct{
    card hand[3][4];
}Board;

//Returns a new random board (3rows x 4columns), making sure that it contains no same cards
Board* getNewBoard()
{
    Board* board = malloc(sizeof(board));
    for(int i = 0; i<3; i++)
    {                               //this double for iterates through all grid spaces and fills them
        for(int j = 0; j<4; j++)
        {
            card* temp;
            temp = NULL;
            while(1) //This loop only exists to repeat the step if the card we get in the next command exists in the grid
            {
                temp = getRandomCard();
                char exists = 0; //to check if we already have this card in the board
                for(int k = 0; k<=i; k++) // and in this double for loop is the actual checking
                {                         //I iterate through previously filled places and compare the new card with the cards there
                    for(int l = 0; l<=j; l++)
                    {
                        if (board->hand[k][l].color == temp->color && board->hand[k][l].number == temp->number &&
                            board->hand[k][l].shape == temp->shape && board->hand[k][l].texture == temp->texture)
                        {
                            exists = 1;
                            free(temp);
                            temp = NULL;
                        }
                        if(exists == 1) break;
                    }
                    if(exists == 1) break;
                }

                if (exists == 1) continue; //if the card already exists, repeat that step and get a new one
                else break;
            }
                board->hand[i][j].color = temp->color;
                board->hand[i][j].number = temp->number;
                board->hand[i][j].shape = temp->shape;
                board->hand[i][j].texture = temp->texture;
        }
    }
    return board;
}
//Returns 1 if chosen cards are a SET or zero otherwise
char isSet(Board b, short cC[][2])
{
        if((b.hand[cC[0][0]][cC[0][1]].color == b.hand[cC[1][0]][cC[1][1]].color && b.hand[cC[0][0]][cC[0][1]].color == b.hand[cC[2][0]][cC[2][1]].color)
            ||
            (b.hand[cC[0][0]][cC[0][1]].color != b.hand[cC[1][0]][cC[1][1]].color && b.hand[cC[0][0]][cC[0][1]].color != b.hand[cC[2][0]][cC[2][1]].color
             && b.hand[cC[1][0]][cC[1][1]].color != b.hand[cC[2][0]][cC[2][1]].color))
        {
            if((b.hand[cC[0][0]][cC[0][1]].number == b.hand[cC[1][0]][cC[1][1]].number && b.hand[cC[0][0]][cC[0][1]].number == b.hand[cC[2][0]][cC[2][1]].number)
            ||
            (b.hand[cC[0][0]][cC[0][1]].number != b.hand[cC[1][0]][cC[1][1]].number && b.hand[cC[0][0]][cC[0][1]].number != b.hand[cC[2][0]][cC[2][1]].number
             && b.hand[cC[1][0]][cC[1][1]].number != b.hand[cC[2][0]][cC[2][1]].number))
             {
                 if((b.hand[cC[0][0]][cC[0][1]].shape == b.hand[cC[1][0]][cC[1][1]].shape && b.hand[cC[0][0]][cC[0][1]].shape == b.hand[cC[2][0]][cC[2][1]].shape)
                ||
                (b.hand[cC[0][0]][cC[0][1]].shape != b.hand[cC[1][0]][cC[1][1]].shape && b.hand[cC[0][0]][cC[0][1]].shape != b.hand[cC[2][0]][cC[2][1]].shape
                 && b.hand[cC[1][0]][cC[1][1]].shape != b.hand[cC[2][0]][cC[2][1]].shape))
                 {
                    if((b.hand[cC[0][0]][cC[0][1]].texture == b.hand[cC[1][0]][cC[1][1]].texture && b.hand[cC[0][0]][cC[0][1]].texture == b.hand[cC[2][0]][cC[2][1]].texture)
                    ||
                    (b.hand[cC[0][0]][cC[0][1]].texture != b.hand[cC[1][0]][cC[1][1]].texture && b.hand[cC[0][0]][cC[0][1]].texture != b.hand[cC[2][0]][cC[2][1]].texture
                     && b.hand[cC[1][0]][cC[1][1]].texture != b.hand[cC[2][0]][cC[2][1]].texture))
                     {
                         return 1;
                     }
                 }
             }
        }
        return 0;
}

//Prints a board in the screen
void printBoard(Board b)
{
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<4; j++)
        {
            printf("[%c%c%d%c] ", b.hand[i][j].color, b.hand[i][j].shape, b.hand[i][j].number, b.hand[i][j].texture);
        }
        printf("\n");
    }
}

int main()
{
    srand(time(NULL)); //random time seed
    //initializing the players
    player one; player two; player three;
    strcpy(one.name, "Marina Andreou");
    strcpy(two.name, "Kostas Grammenos");
    strcpy(three.name, "Maria Perdika");
    one.id = 'a';
    two.id = 'g';
    three.id = 'p';
    one.score = 0;
    two.score = 0;
    three.score = 0; //End of initialization

    //create the board for the game
    Board* board;
    //Enter the basic game loop
    while(1)
    {
        char tmpc; //used for emptying the input buffer
        char tmp = '0';
        player* activePlayer = NULL;
        board = getNewBoard();
        //printf("oh noooo");
        printBoard((*board));
        printf("Give the player id of the player that wants to play, give zero (0) to quit game or give anything else to refresh board.\n");
        printf("Your choice: ");
        while(scanf("%c", &tmp)!=1);
        while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
        if(tmp=='0') //'0' Input, quit game
        {
            printf("\n\n\nQuitting Game, Thank you for playing!\nAuthor: Anastasiadis Vasileios\n\n");
            printf("%s: %d\n%s: %d\n%s: %d\n\n", one.name, one.score, two.name, two.score, three.name, three.score);
            return 0;
        }
        //set the active player according to player input
        if(tmp == one.id) activePlayer = &one;
        else if(tmp == two.id) activePlayer = &two;
        else if(tmp == three.id) activePlayer = &three;
        //or give new random grid otherwise
        else continue;

        short chosenCards[3][2] = {{-1, -1},{-1, -1}, {-1, -1}}; //To store the coordinates of the 3 chosen cards
        for (int i = 0; i<3; i++) //loop for the active player to chose 3 cards
        {
            short a, b; //those will hold the x, y coordinates of the card
            while(1)
            {
                char postfix[3][8] = {{"first"}, {"second"}, {"third"}}; //Just for the printf bellow
                printf("Insert the X [range 0 to 2] and Y [range 0 to 3] coordinates of the %s card of your choice, SEPERATED BY A SPACE: ", postfix[i]);
                scanf("%hd %hd", &a, &b);
                while ((tmpc = getchar()) != '\n' && tmpc != EOF) { } //adeiasma buffer stdin
                chosenCards[i][0] = a;
                chosenCards[i][1] = b;
                char exists = 0;
                for (int j = 0; j<i; j++) //Checking if the player chose the card already
                {
                    if (a==chosenCards[j][0] && b==chosenCards[j][1])
                    {
                        printf("You have already chosen this card, chose another:\n");
                        exists = 1;
                    }
                    if (exists == 1) break;
                }
                if (exists==1) continue; //If he has, prompt him to chose another
                break;
            }
        }
        if (isSet((*board), chosenCards)) //if s/he got a set, give him/her 2 points
            {
                printf("\nYES! This was a set! %s, you gained 2 points!\n\n\n", activePlayer->name);
                activePlayer->score+=2;
            }
            else //if he didn't and his score is >0, take 1 point from him/her
            {
                printf("\nThis wasn't a set :/\n\n\n");
                if (activePlayer!= NULL && activePlayer->score>0) activePlayer->score-=1;
            }
            if (activePlayer->score>=10) //if someone has 10 points, he wins!
            {
                printf("Congratulations! Player %s, you WIN!\n", activePlayer->name);
                printf("Thank you for playing!\nAuthor: Anastasiadis Vasileios\n\n");
                return 0;
            }
    }

    return 0;
}
