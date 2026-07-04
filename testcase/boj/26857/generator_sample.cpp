#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static vector<string> emptyBoard(int r, int c) {
    return vector<string>(r, string(c, '.'));
}

static vector<pair<int, int>> shuffledCells(int r, int c) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());
    return cells;
}

static void placeTokens(vector<string>& board, const string& tokens) {
    vector<pair<int, int>> cells = shuffledCells((int)board.size(), (int)board[0].size());
    for (int i = 0; i < (int)tokens.size(); ++i) {
        board[cells[i].first][cells[i].second] = tokens[i];
    }
}

static string randomTokens(int count, int colors) {
    string tokens;
    for (int i = 0; i < count; ++i) {
        tokens.push_back(char('a' + rnd.next(0, colors - 1)));
    }
    return tokens;
}

static string unevenTokens(int colors, int count) {
    string tokens;
    for (int color = 0; color < colors && (int)tokens.size() < count; ++color) {
        int copies = color == 0 ? rnd.next(2, max(2, count / 2)) : rnd.next(1, 4);
        for (int i = 0; i < copies && (int)tokens.size() < count; ++i) {
            tokens.push_back(char('a' + color));
        }
    }
    while ((int)tokens.size() < count) {
        tokens.push_back(char('a' + rnd.next(0, colors - 1)));
    }
    shuffle(tokens.begin(), tokens.end());
    return tokens;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int r = 1;
    int c = 2;
    string tokens;

    if (mode == 0) {
        r = 1;
        c = rnd.next(2, 18);
        int tokenCount = rnd.next(1, c);
        int colors = rnd.next(1, min(6, tokenCount));
        tokens = randomTokens(tokenCount, colors);
    } else if (mode == 1) {
        r = rnd.next(2, 18);
        c = 1;
        int tokenCount = rnd.next(1, r);
        int colors = rnd.next(1, min(6, tokenCount));
        tokens = randomTokens(tokenCount, colors);
    } else if (mode == 2) {
        r = rnd.next(2, 4);
        c = rnd.next(2, 5);
        int tokenCount = rnd.next(1, r * c);
        int colors = rnd.next(1, min(4, tokenCount));
        tokens = unevenTokens(colors, tokenCount);
    } else if (mode == 3) {
        r = rnd.next(3, 7);
        c = rnd.next(3, 7);
        int tokenCount = rnd.next(1, min(r * c, 10));
        tokens = string(tokenCount, char('a' + rnd.next(0, 3)));
    } else if (mode == 4) {
        r = rnd.next(2, 8);
        c = rnd.next(2, 8);
        int tokenCount = min(r * c, rnd.next(6, 20));
        int colors = rnd.next(2, min(8, tokenCount));
        tokens = randomTokens(tokenCount, colors);
    } else if (mode == 5) {
        r = rnd.next(5, 12);
        c = rnd.next(5, 12);
        int tokenCount = rnd.next(1, min(12, r * c));
        int colors = rnd.next(1, min(5, tokenCount));
        tokens = randomTokens(tokenCount, colors);
    } else {
        r = rnd.any(vector<int>{1, 2, 3, 10, 25});
        c = rnd.any(vector<int>{1, 2, 3, 10, 25});
        if (r * c < 2) c = 2;
        int tokenCount = rnd.next(1, min(r * c, 26));
        tokens = randomTokens(tokenCount, min(26, tokenCount));
    }

    vector<string> board = emptyBoard(r, c);
    placeTokens(board, tokens);

    println(r, c);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
