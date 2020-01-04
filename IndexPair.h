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