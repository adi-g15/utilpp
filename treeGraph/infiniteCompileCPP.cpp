//Try to compile it and see it yourself infinite

#include <iostream>
#include <utility>
#include <array>
#include <vector>

using namespace std;

template<typename T = unsigned short, typename indexType = size_t>
struct box{
    typedef pair<indexType, indexType> _coord;

    private:
        static indexType row, column, currIndex;   //currIndex is 0-based
        T value;
        T tmpVal;
        bool noModificationAllowed = false;
        _coord coordinate;

        // std::vector<T> possibilities;   //use it later, in combination with threads for marking the possibilities

    public:
        box(): 
            coordinate({currIndex/(row+1), currIndex%(row+1)}),
            noModificationAllowed(false)
            { //11 -> 1, 2
                ++currIndex;
        }
        box(const T& val, const _coord& coord = {currIndex/row, currIndex%row}): 
            value(val),
            coordinate(coord),
            noModificationAllowed(true){}

        auto assign(const T& val){ this->tmpVal = val; }
        auto finallize(){ this->value = this->tmpVal; }
        auto get(){ return this->value; }

    friend class sudoku;
};

class sudoku{
    typedef unsigned short ushort;
    typedef std::array< std::array< box<ushort, ushort>, 9 >, 9 > _board_9x9_;
    _board_9x9_ board;

    public:
        // sudoku() : board(sudokuGenerator()){}    //initialize with a sample board
        sudoku(const _board_9x9_& inputBoard) : board(inputBoard){
            if(!this->isValid())
                throw std::invalid_argument("ERROR: Sudoku board passed is invalid!");
        }
        sudoku(std::array<std::array<box<>, 9>, 9>&){
            
        }

        void solve();
        bool isValid() const;
        bool backTrackSolve(ushort row, ushort col);
};

int main(int argc, char const *argv[])
{
    std::array< std::array< box<>, 9 >, 9 > tmp{{
    // std::vector< std::vector< box<> > > tmp = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9},
    }};
    sudoku board(tmp);

    board.solve();

    return 0;
}

void sudoku::solve(){
    if(!this->isValid()){
        std::cerr<<"ERROR: Board passed is not valid\n";
        return;
    }
    if( !this->backTrackSolve(0,0) ){
        std::cerr<<"ERROR: Sudoku Couldn't be solved, verify the board given is right\n";
    }
    
}

bool sudoku::backTrackSolve(ushort r, ushort c){

}