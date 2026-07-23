#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

// Function to display the board
void draw()
{
    printf("\n\n");
    printf("\t\t\t\t %c %c %c %c %c\n", board[0][0], 186, board[0][1], 186, board[0][2]);
    printf("\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c\n",
           205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);
    printf("\t\t\t\t %c %c %c %c %c\n", board[1][0], 186, board[1][1], 186, board[1][2]);
    printf("\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c\n",
           205, 205, 205, 206, 205, 205, 205, 206, 205, 205, 205);
    printf("\t\t\t\t %c %c %c %c %c\n", board[2][0], 186, board[2][1], 186, board[2][2]);
}

// Function to check if a player has won
int check()
{
    // Check rows
    if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X')
        return 1;

    if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X')
        return 1;

    if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X')
        return 1;

    // Check columns
    if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X')
        return 1;

    if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X')
        return 1;

    if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X')
        return 1;

    // Check diagonals
    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
        return 1;

    if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
        return 1;


    // Check rows for O
    if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O')
        return 1;

    if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O')
        return 1;

    if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O')
        return 1;

    // Check columns for O
    if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O')
        return 1;

    if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O')
        return 1;

    if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O')
        return 1;

    // Check diagonals for O
    if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
        return 1;

    if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
        return 1;

    return 0;
}

// Function to put X or O on the board
void inputValue(int input, int player)
{
    char ch;

    if (player == 1)
    {
        ch = 'X';
    }
    else
    {
        ch = 'O';
    }

    if (input == 1)
        board[0][0] = ch;
    else if (input == 2)
        board[0][1] = ch;
    else if (input == 3)
        board[0][2] = ch;
    else if (input == 4)
        board[1][0] = ch;
    else if (input == 5)
        board[1][1] = ch;
    else if (input == 6)
        board[1][2] = ch;
    else if (input == 7)
        board[2][0] = ch;
    else if (input == 8)
        board[2][1] = ch;
    else if (input == 9)
        board[2][2] = ch;
}

// Function to check if the move is valid
int isValidMove(int input)
{
    if (input < 1 || input > 9)
    {
        return 0;
    }

    int row = (input - 1) / 3;
    int column = (input - 1) % 3;

    // If the position still contains a number, it is available
    if (board[row][column] >= '1' && board[row][column] <= '9')
    {
        return 1;
    }

    return 0;
}


int main()
{
    int input;
    int player = 1;

    printf("\n\t\t\t\tTIC TAC TOE\n\n");

    draw();

    printf("\n\nPress any key to start the game...");
    getch();

    system("cls");

    // Maximum 9 moves
    for (int i = 0; i < 9; i++)
    {
        draw();

        if (player == 1)
        {
            printf("\nPlayer 1 (X), enter a number from 1 to 9: ");
        }
        else
        {
            printf("\nPlayer 2 (O), enter a number from 1 to 9: ");
        }

        scanf("%d", &input);

        // Check whether the move is valid
        while (!isValidMove(input))
        {
            printf("\nInvalid move! The position is already occupied or the number is invalid.");
            printf("\nPlease enter another number from 1 to 9: ");

            scanf("%d", &input);
        }

        // Put X or O on the board
        inputValue(input, player);

        // Clear screen
        system("cls");

        // Display updated board
        draw();

        // Check if the current player has won
        if (check())
        {
            if (player == 1)
            {
                printf("\nPlayer 1 (X) wins!\n");
            }
            else
            {
                printf("\nPlayer 2 (O) wins!\n");
            }

            return 0;
        }

        // Switch player
        if (player == 1)
        {
            player = 2;
        }
        else
        {
            player = 1;
        }
    }

    // If all 9 moves are completed and nobody wins
    printf("\nIt's a draw!\n");

    return 0;
}