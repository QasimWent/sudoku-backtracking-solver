#include "SudokuModel.h"
#include <QBrush>
#include <QColor>
#include <QEventLoop>
#include <QFont>
#include <QTimer>

SudokuModel::SudokuModel(QObject* parent) : QAbstractTableModel(parent)
{
    
}

int SudokuModel::rowCount(const QModelIndex&) const
{
    return ROWS;
}

int SudokuModel::columnCount(const QModelIndex&) const
{
    return COLS;
}

QVariant SudokuModel::data(const QModelIndex& index, int role) const 
{
    int row = index.row();
    int col = index.column();

    QFont font;
    switch (role)
    {
        case Qt::DisplayRole:
            if (m_board[row][col] == 0)
            {
                return "";
            }
            return m_board[row][col];
        case Qt::BackgroundRole:
            if (m_board[row][col] != 0)
            {
               return QBrush(QColor(210, 180, 140));
            }
            break;
        case Qt::FontRole:
            font.setPixelSize(28);
            return font;
            break;
        case Qt::ForegroundRole:
            return QBrush(Qt::white);
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
    }
    return QVariant();
}

bool SudokuModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole)
    {
        
        if (value.toInt() == sol_m_board[index.row()][index.column()])
        {
            m_board[index.row()][index.column()] = value.toInt();
        }
        
        /*
        QString result;
	    for(int row= 0; row < ROWS; row++)
	    {
            for(int col= 0; col < COLS; col++)
	        {
	            result += m_board[row][col] + " ";
	        }
        }
        */
    }
    return true;
}

Qt::ItemFlags SudokuModel::flags(const QModelIndex &index) const
{
    if (m_board[index.row()][index.column()] == 0)
    {
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    }
    return Qt::ItemIsEnabled;
}



IndexPair* SudokuModel::findEmpty()
{
    for (size_t i = 0; i != ROWS; ++i)
    {
        for (size_t j = 0; j != COLS; ++j)
        {
            if (m_board[i][j] == 0)
            {
                return new IndexPair(i, j);
            }
        }
    }
    return nullptr;
}

bool SudokuModel::isValid(int number, const IndexPair& position)
{
    // Check the row - loop through each column in given row
    for (size_t i = 0; i != COLS; ++i)
    {
        if (m_board[position.row_index][i] == number && position.col_index != i)
        {
            return false;
        }
    }

    // Check the column - loop through each row in given column
    for (size_t i = 0; i != ROWS; ++i)
    {
        if (m_board[i][position.col_index] == number && position.row_index != i)
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
            if (m_board[i][j] == number && pair != position)
            {
                return false;
            }
        }
    }

    return true;
}

void SudokuModel::delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

bool SudokuModel::solve()
{
    IndexPair* pair = findEmpty();
    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(9, 9);
    int row, col;
    
    if (pair == nullptr)
    {
        delete pair;
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
        delay(100);
        if (isValid(num, *pair))
        {
            m_board[row][col] = num;
            emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
            if (solve())
            {
                return true;
            }
            m_board[row][col] = 0;
            emit dataChanged(topLeft, bottomRight, {Qt::DisplayRole});
        }
    }
    delete pair;
    return false;
}

void SudokuModel::changeTable()
{
    solve();
}