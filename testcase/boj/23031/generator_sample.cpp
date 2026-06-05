#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string randomCommands(int length, const string& alphabet) {
    string commands;
    commands.reserve(length);
    for (int i = 0; i < length; ++i) {
        commands.push_back(rnd.any(alphabet));
    }
    return commands;
}

string routeCommands(int length) {
    string pattern = rnd.any(vector<string>{
        "FFFFFFR",
        "FFFFLFFR",
        "FLFRFR",
        "RRFFFFL",
        "LFFFFFFR",
    });

    string commands;
    while ((int)commands.size() < length) {
        commands += pattern;
        if (rnd.next(3) == 0) {
            commands += rnd.any(string("LR"));
        }
    }
    commands.resize(length);
    return commands;
}

vector<pair<int, int>> allCells(int n) {
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != 0 || j != 0) {
                cells.push_back({i, j});
            }
        }
    }
    shuffle(cells.begin(), cells.end());
    return cells;
}

void placeCells(vector<string>& board, char mark, int count, vector<pair<int, int>>& cells) {
    while (count > 0 && !cells.empty()) {
        auto [r, c] = cells.back();
        cells.pop_back();
        if (board[r][c] == 'O') {
            board[r][c] = mark;
            --count;
        }
    }
}

void placeLine(vector<string>& board, char mark, int count, bool horizontal) {
    int n = board.size();
    int line = rnd.next(1, n - 1);
    vector<pair<int, int>> cells;
    for (int i = 0; i < n; ++i) {
        int r = horizontal ? line : i;
        int c = horizontal ? i : line;
        if (r != 0 || c != 0) {
            cells.push_back({r, c});
        }
    }
    shuffle(cells.begin(), cells.end());

    for (auto [r, c] : cells) {
        if (count == 0) {
            break;
        }
        if (board[r][c] == 'O') {
            board[r][c] = mark;
            --count;
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(10, 15);
    if (mode == 4) {
        n = 15;
    }

    int commandLength = rnd.next(10, 50);
    string commands;
    if (mode == 0) {
        commands = routeCommands(commandLength);
    } else if (mode == 1) {
        commands = randomCommands(commandLength, "FFFFFLR");
    } else if (mode == 2) {
        commands = randomCommands(commandLength, "FFLLRR");
    } else if (mode == 3) {
        commands = randomCommands(commandLength, "FLR");
    } else {
        commands = routeCommands(50);
    }

    vector<string> board(n, string(n, 'O'));
    vector<pair<int, int>> cells = allCells(n);

    int maxCount = 2 * n;
    int zombies = 0;
    int switches = 0;
    if (mode == 0) {
        zombies = rnd.next(n / 2, maxCount);
        switches = rnd.next(0, n);
        placeLine(board, 'Z', zombies / 2, rnd.next(2) == 0);
        zombies -= zombies / 2;
    } else if (mode == 1) {
        zombies = rnd.next(0, n);
        switches = rnd.next(n, maxCount);
        placeLine(board, 'S', switches / 2, rnd.next(2) == 0);
        switches -= switches / 2;
    } else if (mode == 2) {
        zombies = rnd.next(0, maxCount);
        switches = rnd.next(0, maxCount);
    } else if (mode == 3) {
        zombies = rnd.next(0, 3);
        switches = rnd.next(0, 3);
    } else {
        zombies = maxCount;
        switches = maxCount;
    }

    placeCells(board, 'Z', zombies, cells);
    placeCells(board, 'S', switches, cells);

    board[0][0] = 'O';

    println(n);
    println(commands);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
