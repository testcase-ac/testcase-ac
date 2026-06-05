#include "testlib.h"

#include <array>
#include <set>
#include <string>
#include <vector>

using namespace std;

string makeToken(const string& prefix, int group, int index, int salt) {
    return prefix + to_string(group) + "x" + to_string(index) + "x" + to_string(salt);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1},
    };
    const vector<pair<int, int>> cells = {
        {0, 0}, {0, 1}, {0, 2},
        {1, 0},         {1, 2},
        {2, 0}, {2, 1}, {2, 2},
    };

    const int mode = rnd.next(0, 4);
    const int salt = rnd.next(0, 9999);
    const array<string, 5> middlePrefixes = {"M", "a", "Z", "9", "Aa"};
    const array<string, 5> detailPrefixes = {"s", "B", "0", "zz", "A0"};

    set<string> used;
    vector<string> middle(8);
    vector<vector<string>> detail(8, vector<string>(8));

    string finalGoal = makeToken("Final", mode, 0, salt);
    used.insert(finalGoal);

    for (int g = 0; g < 8; ++g) {
        string prefix = middlePrefixes[(mode + g) % middlePrefixes.size()];
        middle[g] = makeToken(prefix, g + 1, rnd.next(0, 99), salt);
        while (used.count(middle[g])) {
            middle[g] += "X";
        }
        used.insert(middle[g]);

        for (int k = 0; k < 8; ++k) {
            string detailPrefix = detailPrefixes[(mode + k + g) % detailPrefixes.size()];
            if (mode == 1 && k % 2 == 0) {
                detailPrefix = middlePrefixes[(g + k) % middlePrefixes.size()] + "Prefix";
            } else if (mode == 2) {
                detailPrefix += string(rnd.next(1, 4), char('A' + rnd.next(0, 25)));
            } else if (mode == 3) {
                detailPrefix += to_string(rnd.next(0, 9));
            } else if (mode == 4 && k >= 4) {
                detailPrefix = "sameStart" + to_string(g);
            }

            detail[g][k] = makeToken(detailPrefix, g + 1, k + 1, salt);
            while (used.count(detail[g][k])) {
                detail[g][k] += "Y";
            }
            used.insert(detail[g][k]);
        }
        shuffle(detail[g].begin(), detail[g].end());
    }

    vector<vector<string>> board(9, vector<string>(9));
    board[4][4] = finalGoal;

    for (int g = 0; g < 8; ++g) {
        const auto [dr, dc] = directions[g];
        board[4 + dr][4 + dc] = middle[g];

        const int blockRow = 3 + dr * 3;
        const int blockCol = 3 + dc * 3;
        board[blockRow + 1][blockCol + 1] = middle[g];

        for (int k = 0; k < 8; ++k) {
            const auto [r, c] = cells[k];
            board[blockRow + r][blockCol + c] = detail[g][k];
        }
    }

    for (const auto& row : board) {
        println(row);
    }

    return 0;
}
