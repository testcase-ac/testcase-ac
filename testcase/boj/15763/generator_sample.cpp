#include "testlib.h"

#include <array>
#include <string>
#include <vector>
using namespace std;

using Board = array<string, 3>;

const vector<array<pair<int, int>, 3>> LINES = {
    {{{0, 0}, {0, 1}, {0, 2}}},
    {{{1, 0}, {1, 1}, {1, 2}}},
    {{{2, 0}, {2, 1}, {2, 2}}},
    {{{0, 0}, {1, 0}, {2, 0}}},
    {{{0, 1}, {1, 1}, {2, 1}}},
    {{{0, 2}, {1, 2}, {2, 2}}},
    {{{0, 0}, {1, 1}, {2, 2}}},
    {{{0, 2}, {1, 1}, {2, 0}}},
};

char pickLetter(int alphabetSize) {
    return char('A' + rnd.next(0, alphabetSize - 1));
}

Board randomBoard(int alphabetSize) {
    Board board;
    for (int r = 0; r < 3; ++r) {
        board[r].resize(3);
        for (int c = 0; c < 3; ++c) {
            board[r][c] = pickLetter(alphabetSize);
        }
    }
    return board;
}

void forceSingleWin(Board& board, char cow) {
    auto line = rnd.any(LINES);
    for (auto [r, c] : line) {
        board[r][c] = cow;
    }
}

void forceTeamWin(Board& board, char a, char b) {
    auto line = rnd.any(LINES);
    vector<char> cells = {a, a, b};
    shuffle(cells.begin(), cells.end());
    for (int i = 0; i < 3; ++i) {
        board[line[i].first][line[i].second] = cells[i];
    }
}

Board uniqueBoard() {
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector<char> cells(letters.begin(), letters.end());
    shuffle(cells.begin(), cells.end());

    Board board;
    int at = 0;
    for (int r = 0; r < 3; ++r) {
        board[r].resize(3);
        for (int c = 0; c < 3; ++c) {
            board[r][c] = cells[at++];
        }
    }
    return board;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    Board board;

    if (mode == 0) {
        int alphabetSize = rnd.next(1, 4);
        board = randomBoard(alphabetSize);
    } else if (mode == 1) {
        int alphabetSize = rnd.next(2, 6);
        board = randomBoard(alphabetSize);
        forceSingleWin(board, pickLetter(alphabetSize));
    } else if (mode == 2) {
        int alphabetSize = rnd.next(2, 8);
        board = randomBoard(alphabetSize);
        char a = pickLetter(alphabetSize);
        char b = pickLetter(alphabetSize);
        while (b == a) {
            b = pickLetter(alphabetSize);
        }
        forceTeamWin(board, a, b);
    } else if (mode == 3) {
        int alphabetSize = rnd.next(2, 5);
        board = randomBoard(alphabetSize);
        forceSingleWin(board, pickLetter(alphabetSize));
        char a = pickLetter(alphabetSize);
        char b = pickLetter(alphabetSize);
        while (b == a) {
            b = pickLetter(alphabetSize);
        }
        forceTeamWin(board, a, b);
    } else if (mode == 4) {
        board = uniqueBoard();
    } else {
        char cow = pickLetter(26);
        board = {{{cow, cow, cow}, {cow, cow, cow}, {cow, cow, cow}}};
    }

    for (const string& row : board) {
        println(row);
    }

    return 0;
}
