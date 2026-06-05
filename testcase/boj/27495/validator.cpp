#include "testlib.h"

#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<vector<string>> a(9, vector<string>(9));
    map<string, int> count;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            a[i][j] = inf.readToken("[0-9A-Za-z]{1,100}", "goal");
            ++count[a[i][j]];
        }
        inf.readEoln();
    }
    inf.readEof();

    vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1},
    };

    vector<string> middleGoals;
    for (auto [dr, dc] : directions) {
        int centerRow = 4 + dr;
        int centerCol = 4 + dc;
        int blockRow = 3 + dr * 3 + 1;
        int blockCol = 3 + dc * 3 + 1;

        string middle = a[centerRow][centerCol];
        middleGoals.push_back(middle);

        ensuref(a[blockRow][blockCol] == middle,
                "middle goal at central direction (%d,%d) must match outer block center",
                dr, dc);
    }

    for (const string& middle : middleGoals) {
        ensuref(count[middle] == 2,
                "middle goal must appear exactly twice: %s appears %d times",
                middle.c_str(), count[middle]);
    }

    string finalGoal = a[4][4];
    ensuref(count[finalGoal] == 1,
            "final goal must appear exactly once: %s appears %d times",
            finalGoal.c_str(), count[finalGoal]);

    for (const auto& [goal, occurrences] : count) {
        if (goal == finalGoal) {
            continue;
        }

        bool isMiddle = false;
        for (const string& middle : middleGoals) {
            if (goal == middle) {
                isMiddle = true;
                break;
            }
        }

        if (!isMiddle) {
            ensuref(occurrences == 1,
                    "non-middle goal must appear exactly once: %s appears %d times",
                    goal.c_str(), occurrences);
        }
    }
}
