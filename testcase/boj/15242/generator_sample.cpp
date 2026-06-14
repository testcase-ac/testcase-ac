#include "testlib.h"
#include <string>
#include <utility>
#include <vector>

using namespace std;

string squareName(pair<int, int> square) {
    string result;
    result += char('a' + square.first);
    result += char('1' + square.second);
    return result;
}

bool inside(int x, int y) {
    return 0 <= x && x < 8 && 0 <= y && y < 8;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> allSquares;
    vector<pair<int, int>> edgeSquares;
    vector<pair<int, int>> cornerSquares = {{0, 0}, {0, 7}, {7, 0}, {7, 7}};
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            allSquares.push_back({x, y});
            if (x == 0 || x == 7 || y == 0 || y == 7) {
                edgeSquares.push_back({x, y});
            }
        }
    }

    pair<int, int> start;
    pair<int, int> finish;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        start = rnd.any(allSquares);
        finish = start;
    } else if (mode == 1) {
        const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
        const int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};

        vector<pair<pair<int, int>, pair<int, int>>> moves;
        for (auto from : allSquares) {
            for (int k = 0; k < 8; ++k) {
                int nx = from.first + dx[k];
                int ny = from.second + dy[k];
                if (inside(nx, ny)) {
                    moves.push_back({from, {nx, ny}});
                }
            }
        }

        auto move = rnd.any(moves);
        start = move.first;
        finish = move.second;
    } else if (mode == 2) {
        start = rnd.any(cornerSquares);
        finish = rnd.any(allSquares);
    } else if (mode == 3) {
        start = rnd.any(edgeSquares);
        finish = rnd.any(edgeSquares);
    } else if (mode == 4) {
        start = rnd.any(cornerSquares);
        finish = {7 - start.first, 7 - start.second};
    } else {
        start = rnd.any(allSquares);
        finish = rnd.any(allSquares);
    }

    println(squareName(start));
    println(squareName(finish));

    return 0;
}
