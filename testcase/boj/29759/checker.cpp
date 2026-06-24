#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int n;
int boardSize;
vector<vector<int>> inputBoard;

struct Answer {
    vector<vector<int>> board;
};

void checkPairwiseCoprime(InStream& stream, const vector<int>& values, const char* groupName, int groupIndex) {
    for (int i = 0; i < int(values.size()); ++i) {
        for (int j = i + 1; j < int(values.size()); ++j) {
            if (gcd(values[i], values[j]) != 1) {
                stream.quitf(_wa,
                             "%s %d has non-coprime values %d and %d",
                             groupName,
                             groupIndex,
                             values[i],
                             values[j]);
            }
        }
    }
}

Answer readAnswer(InStream& stream) {
    Answer answer;
    answer.board.assign(boardSize, vector<int>(boardSize));

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            answer.board[i][j] = stream.readInt(2,
                                                1000000,
                                                format("b_%d_%d", i + 1, j + 1).c_str());
            if (inputBoard[i][j] != 0 && answer.board[i][j] != inputBoard[i][j]) {
                stream.quitf(_wa,
                             "cell (%d, %d) changed from %d to %d",
                             i + 1,
                             j + 1,
                             inputBoard[i][j],
                             answer.board[i][j]);
            }
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after board");
    }

    for (int i = 0; i < boardSize; ++i) {
        checkPairwiseCoprime(stream, answer.board[i], "row", i + 1);
    }

    for (int j = 0; j < boardSize; ++j) {
        vector<int> column;
        column.reserve(boardSize);
        for (int i = 0; i < boardSize; ++i) {
            column.push_back(answer.board[i][j]);
        }
        checkPairwiseCoprime(stream, column, "column", j + 1);
    }

    for (int blockRow = 0; blockRow < n; ++blockRow) {
        for (int blockCol = 0; blockCol < n; ++blockCol) {
            vector<int> block;
            block.reserve(boardSize);
            for (int i = blockRow * n; i < (blockRow + 1) * n; ++i) {
                for (int j = blockCol * n; j < (blockCol + 1) * n; ++j) {
                    block.push_back(answer.board[i][j]);
                }
            }
            checkPairwiseCoprime(stream, block, "block", blockRow * n + blockCol + 1);
        }
    }

    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    boardSize = n * n;
    inputBoard.assign(boardSize, vector<int>(boardSize));

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            inputBoard[i][j] = inf.readInt();
        }
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid coprime sudoku completion");
}
