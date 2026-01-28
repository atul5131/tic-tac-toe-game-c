#include <stdio.h>
#include <ctype.h>

char board[9];

void init_board()
{
    for (int i = 0; i < 9; ++i)
        board[i] = ' ';
}

void print_board()
{
    printf("\n");
    for (int r = 0; r < 3; ++r)
    {
        printf(" %c | %c | %c \n", board[r * 3], board[r * 3 + 1], board[r * 3 + 2]);
        if (r < 2)
            printf("---+---+---\n");
    }
    printf("\n");
    printf("Cells: 1 2 3 4 5 6 7 8 9\n");
}

int check_winner()
{
    int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; ++i)
    {
        char a = board[lines[i][0]];
        if (a != ' ' && a == board[lines[i][1]] && a == board[lines[i][2]])
            return a;
    }
    return 0;
}

int is_full()
{
    for (int i = 0; i < 9; ++i)
        if (board[i] == ' ')
            return 0;
    return 1;
}

int main()
{
    init_board();
    printf("Tic-Tac-Toe (manual placements)\n");
    printf("Enter moves by specifying a cell number (1-9) and symbol X or O.\n");
    printf("Example: 5 X\n");
    printf("Enter 0 to finish and evaluate the final board.\n");

    while (1)
    {
        print_board();
        printf("Move (cell symbol) or 0 to finish: ");

        int cell;
        if (scanf("%d", &cell) != 1)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            printf("Invalid input. Try again.\n");
            continue;
        }
        if (cell == 0)
            break;
        if (cell < 1 || cell > 9)
        {
            printf("Cell must be 1..9\n");
            continue;
        }

        char sym;
        if (scanf(" %c", &sym) != 1)
        {
            printf("Missing symbol. Try again.\n");
            continue;
        }
        sym = toupper((unsigned char)sym);
        if (sym != 'X' && sym != 'O')
        {
            printf("Symbol must be X or O\n");
            continue;
        }

        int idx = cell - 1;
        if (board[idx] != ' ')
        {
            printf("Cell already occupied\n");
            continue;
        }
        board[idx] = sym;

        int winner = check_winner();
        if (winner)
        {
            print_board();
            printf("Winner: %c\n", winner);
            return 0;
        }
        if (is_full())
        {
            print_board();
            printf("Draw\n");
            return 0;
        }
    }

    print_board();
    int winner = check_winner();
    if (winner)
        printf("Winner: %c\n", winner);
    else if (is_full())
        printf("Draw\n");
    else
        printf("No winner yet.\n");
    return 0;
}
