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
    // Check rows
    if (board[0][0] == 'X' &&
        board[0][1] == 'X' &&
        board[0][2] == 'X')
        return 1;

    if (board[1][0] == 'X' &&
        board[1][1] == 'X' &&
        board[1][2] == 'X')
        return 1;

    if (board[2][0] == 'X' &&
        board[2][1] == 'X' &&
        board[2][2] == 'X')
        return 1;


    // Check columns
    if (board[0][0] == 'X' &&
        board[1][0] == 'X' &&
        board[2][0] == 'X')
        return 1;

    if (board[0][1] == 'X' &&
        board[1][1] == 'X' &&
        board[2][1] == 'X')
        return 1;

    if (board[0][2] == 'X' &&
        board[1][2] == 'X' &&
        board[2][2] == 'X')
        return 1;


    // Check diagonals
    if (board[0][0] == 'X' &&
        board[1][1] == 'X' &&
        board[2][2] == 'X')
        return 1;

    if (board[0][2] == 'X' &&
        board[1][1] == 'X' &&
        board[2][0] == 'X')
        return 1;


    // Check rows for O
    if (board[0][0] == 'O' &&
        board[0][1] == 'O' &&
        board[0][2] == 'O')
        return 1;

    if (board[1][0] == 'O' &&
        board[1][1] == 'O' &&
        board[1][2] == 'O')
        return 1;

    if (board[2][0] == 'O' &&
        board[2][1] == 'O' &&
        board[2][2] == 'O')
        return 1;


    // Check columns for O
    if (board[0][0] == 'O' &&
        board[1][0] == 'O' &&
        board[2][0] == 'O')
        return 1;

    if (board[0][1] == 'O' &&
        board[1][1] == 'O' &&
        board[2][1] == 'O')
        return 1;

    if (board[0][2] == 'O' &&
        board[1][2] == 'O' &&
        board[2][2] == 'O')
        return 1;


    // Check diagonals for O
    if (board[0][0] == 'O' &&
        board[1][1] == 'O' &&
        board[2][2] == 'O')
        return 1;

    if (board[0][2] == 'O' &&
        board[1][1] == 'O' &&
        board[2][0] == 'O')
        return 1;


    // Nobody has won
    return 0;
}


// Function to place X or O on the board
void inputValue(int input, char player)
{
    int row = (input - 1) / 3;
    int column = (input - 1) % 3;

    board[row][column] = player;
}


// Function to check if a move is valid
int isValidMove(int input)
{
    // Check if input is between 1 and 9
    if (input < 1 || input > 9)
    {
        return 0;
    }

    int row = (input - 1) / 3;
    int column = (input - 1) % 3;

    // Check if the position is still available
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
        // Generate random number between 1 and 9
        move = (rand() % 9) + 1;

    } while (!isValidMove(move));

    return move;
}


int main()
{
    int input;
    char player = 'X';

    // Start random number generator
    srand(time(0));

    printf("\n\t\t\t\tTIC TAC TOE\n");
    printf("\n\t\t\tYou are X");
    printf("\n\t\t\tComputer is O\n");

    draw();

    printf("\n\nPress any key to start the game...");
    getch();

    system("cls");


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

            // Check if player's move is valid
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

            // Wait for 2 seconds
            Sleep(2000);

            // Generate computer's move
            input = computerMove();

            printf("\nComputer chooses position: %d\n", input);
        }


        // Put X or O on the board
        inputValue(input, player);

        // Clear screen
        system("cls");

        // Display updated board
        draw();


        // Check if someone won
        if (check())
        {
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


    // If all 9 moves are completed
    printf("\nIt's a draw!\n");

    return 0;
}