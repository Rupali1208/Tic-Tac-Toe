#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};


// Function to display the board
void draw()
{
    printf("\n\n");

    printf("\t\t\t\t %c %c %c %c %c\n",
           board[0][0], 186, board[0][1], 186, board[0][2]);

    printf("\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c\n",
           205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);

    printf("\t\t\t\t %c %c %c %c %c\n",
           board[1][0], 186, board[1][1], 186, board[1][2]);

    printf("\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c\n",
           205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);

    printf("\t\t\t\t %c %c %c %c %c\n",
           board[2][0], 186, board[2][1], 186, board[2][2]);
}


// Function to check if someone has won
int check()
{
    int i;

    // Check rows
    for (i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
        {
            return 1;
        }
    }

    // Check columns
    for (i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
        {
            return 1;
        }
    }

    // Check first diagonal
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        return 1;
    }

    // Check second diagonal
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        return 1;
    }

    return 0;
}


// Function to check if the game is a draw
int isDraw()
{
    int i;
    int j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] >= '1' &&
                board[i][j] <= '9')
            {
                return 0;
            }
        }
    }

    return 1;
}


// Function to put X or O on the board
void inputValue(int input, char player)
{
    int row;
    int column;

    row = (input - 1) / 3;
    column = (input - 1) % 3;

    board[row][column] = player;
}


// Function to check if the move is valid
int isValidMove(int input)
{
    int row;
    int column;

    // Check if input is between 1 and 9
    if (input < 1 || input > 9)
    {
        return 0;
    }

    row = (input - 1) / 3;
    column = (input - 1) % 3;

    // Check if position is available
    if (board[row][column] >= '1' &&
        board[row][column] <= '9')
    {
        return 1;
    }

    return 0;
}


// Function to generate computer's move
int computerMove()
{
    int move;

    do
    {
        move = (rand() % 9) + 1;

    } while (!isValidMove(move));

    return move;
}


// Function to reset the board
void resetBoard()
{
    board[0][0] = '1';
    board[0][1] = '2';
    board[0][2] = '3';

    board[1][0] = '4';
    board[1][1] = '5';
    board[1][2] = '6';

    board[2][0] = '7';
    board[2][1] = '8';
    board[2][2] = '9';
}


// Main function
int main()
{
    int mode;
    int input;

    char player;

    // Start random number generator
    srand(time(0));


    printf("\n");
    printf("\t\t\t\tTIC TAC TOE\n");

    printf("\n\t\t\tSelect Game Mode\n");

    printf("\n\t\t\t1. Player VS Player");

    printf("\n\t\t\t2. Player VS Computer");

    printf("\n\t\t\tEnter your choice: ");

    scanf("%d", &mode);


    // Check if mode is valid
    while (mode != 1 && mode != 2)
    {
        printf("\nInvalid choice!");

        printf("\nPlease select 1 or 2: ");

        scanf("%d", &mode);
    }


    // Reset board
    resetBoard();


    system("cls");


    // =====================================================
    // PLAYER VS PLAYER
    // =====================================================

    if (mode == 1)
    {
        player = 'X';


        printf("\n\t\t\t\tTIC TAC TOE");

        printf("\n\n\t\t\tPlayer 1 = X");

        printf("\n\t\t\tPlayer 2 = O\n");


        // Maximum 9 moves
        for (int i = 0; i < 9; i++)
        {
            draw();


            // Ask for player's move
            if (player == 'X')
            {
                printf("\nPlayer 1 (X), enter a number from 1 to 9: ");
            }
            else
            {
                printf("\nPlayer 2 (O), enter a number from 1 to 9: ");
            }


            scanf("%d", &input);


            // Check if move is valid
            while (!isValidMove(input))
            {
                printf("\nInvalid move!");

                printf("\nPlease enter an available number from 1 to 9: ");

                scanf("%d", &input);
            }


            // Put X or O on board
            inputValue(input, player);


            system("cls");


            // Check if someone won
            if (check())
            {
                draw();


                if (player == 'X')
                {
                    printf("\nPlayer 1 (X) wins!\n");
                }
                else
                {
                    printf("\nPlayer 2 (O) wins!\n");
                }

                return 0;
            }


            // Check for draw
            if (isDraw())
            {
                draw();

                printf("\nIt's a draw!\n");

                return 0;
            }


            // Switch player
            if (player == 'X')
            {
                player = 'O';
            }
            else
            {
                player = 'X';
            }
        }
    }


    // =====================================================
    // PLAYER VS COMPUTER
    // =====================================================

    else if (mode == 2)
    {
        player = 'X';


        printf("\n\t\t\t\tTIC TAC TOE");

        printf("\n\n\t\t\tYou are X");

        printf("\n\t\t\tComputer is O\n");


        // Maximum 9 moves
        for (int i = 0; i < 9; i++)
        {
            draw();


            // Human player's turn
            if (player == 'X')
            {
                printf("\nYour turn!");

                printf("\nEnter a number from 1 to 9: ");

                scanf("%d", &input);


                // Check if move is valid
                while (!isValidMove(input))
                {
                    printf("\nInvalid move!");

                    printf("\nPlease enter an available number from 1 to 9: ");

                    scanf("%d", &input);
                }
            }


            // Computer's turn
            else
            {
                printf("\nComputer is thinking...");

                Sleep(1000);


                // Generate computer's move
                input = computerMove();

                printf("\nComputer chooses position: %d\n", input);

                Sleep(1000);
            }


            // Put X or O on board
            inputValue(input, player);


            system("cls");


            // Check if someone won
            if (check())
            {
                draw();


                if (player == 'X')
                {
                    printf("\nCongratulations! You win!\n");
                }
                else
                {
                    printf("\nComputer wins!\n");
                }

                return 0;
            }


            // Check for draw
            if (isDraw())
            {
                draw();

                printf("\nIt's a draw!\n");

                return 0;
            }


            // Switch player
            if (player == 'X')
            {
                player = 'O';
            }
            else
            {
                player = 'X';
            }
        }
    }


    return 0;
}