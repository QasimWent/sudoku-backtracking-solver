#include <QAbstractTableModel>
#include <QString>
#include "IndexPair.h"

const size_t COLS = 9;
const size_t ROWS = 9;

class SudokuModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    SudokuModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override; 
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    

signals:
    void editCompleted(const QString&);

public slots:
    void changeTable();
    
private:
    int m_board[ROWS][COLS] = {
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

    // To let user solve board themselves
    int sol_m_board[ROWS][COLS] = {
        {7, 8, 5, 4, 3, 9, 1, 2, 6},
        {6, 1, 2, 8, 7, 5, 3, 4, 9},
        {4, 9, 3, 6, 2, 1, 5, 7, 8},
        {8, 5, 7, 9, 4, 3, 2, 6, 1},
        {2, 6, 1, 7, 5, 8, 9, 3, 4},
        {9, 3, 4, 1, 6, 2, 7, 8, 5},
        {5, 7, 8, 3, 9, 4, 6, 1, 2},
        {1, 2, 6, 5, 8, 7, 4, 9, 3},
        {3, 4, 9, 2, 1, 6, 8, 5, 7}
    };
    IndexPair* findEmpty();
    bool isValid(int number, const IndexPair& position);
    void delay(int millisecondsWait);
    bool solve();
};
