#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(1, 5);
    for (int tc = 0; tc < caseCount; ++tc) {
        int r = rnd.next(4, 10);
        int c = rnd.next(4, 12);
        vector<string> board(r, string(c, '.'));

        for (int i = 0; i < r; ++i) {
            board[i][0] = '#';
            board[i][c - 1] = '#';
        }
        for (int j = 0; j < c; ++j) {
            board[0][j] = '#';
            board[r - 1][j] = '#';
        }

        vector<pair<int, int>> cells;
        for (int i = 1; i + 1 < r; ++i) {
            for (int j = 1; j + 1 < c; ++j) {
                cells.push_back({i, j});
            }
        }
        shuffle(cells.begin(), cells.end());

        int wallLimit = max(0, (int)cells.size() - 4);
        int wallCount = rnd.next(0, min(wallLimit, (int)cells.size() / 5));
        int cursor = 0;
        for (int i = 0; i < wallCount; ++i) {
            auto [x, y] = cells[cursor++];
            board[x][y] = '#';
        }

        vector<pair<int, int>> open;
        for (int i = cursor; i < (int)cells.size(); ++i) {
            open.push_back(cells[i]);
        }
        shuffle(open.begin(), open.end());

        int maxBoxes = min(4, ((int)open.size() - 1) / 2);
        int boxCount = rnd.next(1, maxBoxes);

        set<pair<int, int>> boxCells;
        for (int i = 0; i < boxCount; ++i) {
            boxCells.insert(open.back());
            open.pop_back();
        }

        set<pair<int, int>> targetCells;
        int boxesAlreadyOnTargets = boxCount == 1 ? 0 : rnd.next(0, boxCount - 1);
        vector<pair<int, int>> boxes(boxCells.begin(), boxCells.end());
        shuffle(boxes.begin(), boxes.end());
        for (int i = 0; i < boxesAlreadyOnTargets; ++i) {
            targetCells.insert(boxes[i]);
        }
        while ((int)targetCells.size() < boxCount) {
            targetCells.insert(open.back());
            open.pop_back();
        }

        pair<int, int> worker = open.back();
        open.pop_back();
        bool workerOnTarget = rnd.next(0, 4) == 0 && !targetCells.count(worker);
        if (workerOnTarget) {
            if (!targetCells.empty()) {
                targetCells.erase(targetCells.begin());
            }
            targetCells.insert(worker);
        }

        for (auto [x, y] : targetCells) {
            board[x][y] = '+';
        }
        for (auto [x, y] : boxCells) {
            board[x][y] = targetCells.count({x, y}) ? 'B' : 'b';
        }
        board[worker.first][worker.second] = targetCells.count(worker) ? 'W' : 'w';

        string moves;
        string alphabet = "UDLR";
        int moveCount = rnd.next(1, 50);
        for (int i = 0; i < moveCount; ++i) {
            moves += alphabet[rnd.next(0, 3)];
        }

        println(r, c);
        for (const string& row : board) {
            println(row);
        }
        println(moves);
    }

    println(0, 0);
    return 0;
}
