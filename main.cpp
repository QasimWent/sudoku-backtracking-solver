#include <iostream>
#include <string>

void print_board(const int (&board)[9][9])
{
    int rows = sizeof(board) / sizeof(board[0]);
    int cols = sizeof(board[0]) / sizeof(int);
    for (size_t i = 0; i != rows; ++i)
    {
        if (i % 3 == 0 && i != 0)
        {
            std::cout << "--------------" << std::endl;
        }
        for (size_t j = 0; j != cols; ++j)
        {
            if (j % 3 == 0 && j != 0)
            {
                std::cout << "|";
            }
            if (j == 8)
            {
                std::cout << board[i][j] << std::endl;
            }
            else
            {
                std::cout << board[i][j] << " ";
            }
            
        }
    }
}

int main()
{
    int board[9][9] = {
        {7, 8, 0, 4, 0, 0, 1, 2, 0},
        {6, 0, 0, 0, 7, 5, 0, 0, 9},
        {0, 0, 0, 6, 0, 1, 0, 7, 8},
        {0, 0, 7, 0, 4, 0, 2, 6, 0},
        {0, 0, 1, 0, 5, 0, 9, 3, 0},
        {9, 0, 4, 0, 6, 0, 0, 0, 5},
        {0, 7, 0, 3, 0, 0, 0, 1, 2},
        {1, 2, 0, 0, 0, 7, 4, 0, 0},
        {0, 4, 9, 2, 0, 6, 0, 0, 7}
    };
    print_board(board);
}