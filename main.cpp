#include <iostream>
#include <string>
#include <cmath>

struct IndexPair
{
    int row_index;
    int col_index;

    IndexPair() = default;
    IndexPair(int r, int c) : row_index(r), col_index(c) {};

    bool operator!=(const IndexPair& rhs) const
    {
        if (this->row_index != rhs.row_index || this->col_index != rhs.col_index)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

void print_board(const int (&board)[9][9])
{
    int rows = sizeof(board) / sizeof(board[0]);
    int cols = sizeof(board[0]) / sizeof(int);
    for (size_t i = 0; i != rows; ++i)
    {
        if (i % 3 == 0 && i != 0)
        {
            std::cout << "--------------------" << std::endl;
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

IndexPair* find_empty(int (&board)[9][9])
{
    int rows = sizeof(board) / sizeof(board[0]);
    int cols = sizeof(board[0]) / sizeof(int);
    for (size_t i = 0; i != rows; ++i)
    {
        for (size_t j = 0; j != cols; ++j)
        {
            if (board[i][j] == 0)
            {
                return new IndexPair(i, j);
            }
        }
    }
    return nullptr;
}

bool is_valid(const int (&board)[9][9], int number, const IndexPair& position)
{
    int rows = sizeof(board) / sizeof(board[0]);
    int cols = sizeof(board[0]) / sizeof(int);

    // Check the row - loop through each column in given row
    for (size_t i = 0; i != cols; ++i)
    {
        if (board[position.row_index][i] == number && position.col_index != i)
        {
            return false;
        }
    }

    // Check the column - loop through each row in given column
    for (size_t i = 0; i != rows; ++i)
    {
        if (board[i][position.col_index] == number && position.row_index != i)
        {
            return false;
        }
    }

    // Determine 3x3 cube
    int box_x = position.col_index / 3;
    int box_y = position.row_index / 3;

    // Check 3x3 cube - loop through each element in cube
    IndexPair pair;
    for (size_t i = box_y * 3; i != box_y * 3 + 3; ++i)
    {
        for (size_t j = box_x * 3; j != box_x * 3 + 3; ++j)
        {
            pair.row_index = i;
            pair.col_index = j;
            if (board[i][j] == number && pair != position)
            {
                return false;
            }
        }
    }

    return true;
}

bool solve_board(int (&board)[9][9])
{
    IndexPair* pair = find_empty(board);
    int row, col;
    
    if (pair == nullptr)
    {
        return true;
    }
    else
    {
        row = pair->row_index;
        col = pair->col_index;
    }

    // Attempt to insert number into empty position
    for (int num = 1; num <= 9; num++)
    {
        if (is_valid(board, num, *pair))
        {
            board[row][col] = num;
            if (solve_board(board))
            {
                return true;
            }
            board[row][col] = 0;
        }
    }
    return false;
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
    solve_board(board);
    std::cout << "_____________________________AFTER___________________________" << std::endl;
    print_board(board);
}