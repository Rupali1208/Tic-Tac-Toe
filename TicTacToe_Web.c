#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Check if a move is valid
int isValidMove(char board[], int position)
{
    if (position < 1 || position > 9)
    {
        return 0;
    }

    if (board[position - 1] >= '1' &&
        board[position - 1] <= '9')
    {
        return 1;
    }

    return 0;
}


// Put player symbol on board
void makeMove(char board[], int position, char player)
{
    board[position - 1] = player;
}


// Check if someone has won
int checkWin(char board[], char player)
{
    int winningCombinations[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    int i;

    for (i = 0; i < 8; i++)
    {
        if (board[winningCombinations[i][0]] == player &&
            board[winningCombinations[i][1]] == player &&
            board[winningCombinations[i][2]] == player)
        {
            return 1;
        }
    }

    return 0;
}


// Check if game is a draw
int checkDraw(char board[])
{
    int i;

    for (i = 0; i < 9; i++)
    {
        if (board[i] >= '1' &&
            board[i] <= '9')
        {
            return 0;
        }
    }

    return 1;
}


// Generate computer move
int computerMove(char board[])
{
    int availableMoves[9];
    int count = 0;
    int i;

    for (i = 0; i < 9; i++)
    {
        if (board[i] >= '1' &&
            board[i] <= '9')
        {
            availableMoves[count] = i + 1;
            count++;
        }
    }

    if (count == 0)
    {
        return 0;
    }

    return availableMoves[rand() % count];
}


int main(int argc, char *argv[])
{
    char board[9];
    char player;
    int position;
    int computerPosition;
    int i;

    srand((unsigned int)time(NULL));


    /*
        Arguments:

        argv[1] = board
        argv[2] = action
        argv[3] = position
        argv[4] = player

        Example:

        TicTacToe_Web.exe "123456789" move 5 X
    */


    if (argc < 3)
    {
        printf("ERROR");
        return 1;
    }


    // Copy board from Flask
    for (i = 0; i < 9; i++)
    {
        board[i] = argv[1][i];
    }


    // -----------------------------------------
    // PLAYER MOVE
    // -----------------------------------------

    if (strcmp(argv[2], "move") == 0)
    {
        if (argc < 5)
        {
            printf("ERROR");
            return 1;
        }


        position = atoi(argv[3]);

        player = argv[4][0];


        // Check valid move
        if (!isValidMove(board, position))
        {
            printf("INVALID");
            return 0;
        }


        // Make move
        makeMove(board, position, player);


        // Check winner
        if (checkWin(board, player))
        {
            printf("WIN|%c|", player);

            for (i = 0; i < 9; i++)
            {
                printf("%c", board[i]);
            }

            return 0;
        }


        // Check draw
        if (checkDraw(board))
        {
            printf("DRAW|%c|", player);

            for (i = 0; i < 9; i++)
            {
                printf("%c", board[i]);
            }

            return 0;
        }


        // Normal move
        printf("CONTINUE|%c|", player);

        for (i = 0; i < 9; i++)
        {
            printf("%c", board[i]);
        }

        return 0;
    }


    // -----------------------------------------
    // COMPUTER MOVE
    // -----------------------------------------

    if (strcmp(argv[2], "computer") == 0)
    {
        computerPosition = computerMove(board);


        if (computerPosition == 0)
        {
            printf("DRAW|O|");

            for (i = 0; i < 9; i++)
            {
                printf("%c", board[i]);
            }

            return 0;
        }


        // Computer plays O
        makeMove(board, computerPosition, 'O');


        // Check computer win
        if (checkWin(board, 'O'))
        {
            printf("WIN|O|%d|", computerPosition);

            for (i = 0; i < 9; i++)
            {
                printf("%c", board[i]);
            }

            return 0;
        }


        // Check draw
        if (checkDraw(board))
        {
            printf("DRAW|O|%d|", computerPosition);

            for (i = 0; i < 9; i++)
            {
                printf("%c", board[i]);
            }

            return 0;
        }


        // Normal computer move
        printf("CONTINUE|O|%d|", computerPosition);

        for (i = 0; i < 9; i++)
        {
            printf("%c", board[i]);
        }

        return 0;
    }


    printf("ERROR");

    return 1;
}