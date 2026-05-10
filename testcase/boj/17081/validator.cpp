#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N, M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readEoln();
    long long cells = 1LL * N * M;
    ensuref(cells >= 2, "N*M must be at least 2, got %d*%d = %lld", N, M, cells);

    // Read grid
    vector<string> grid(N);
    int cntStart = 0, cntBoss = 0;
    int cntMonGrid = 0; // '&' + 'M'
    int cntBoxGrid = 0; // 'B'

    for (int i = 0; i < N; ++i) {
        grid[i] = inf.readLine("[.#@&MB^]{1,100}", "grid_row");
        ensuref((int)grid[i].size() == M,
                "Row %d length mismatch: expected %d, got %d",
                i + 1, M, (int)grid[i].size());
        for (int j = 0; j < M; ++j) {
            char ch = grid[i][j];
            if (ch == '@') {
                cntStart++;
            } else if (ch == 'M') {
                cntBoss++;
                cntMonGrid++;
            } else if (ch == '&') {
                cntMonGrid++;
            } else if (ch == 'B') {
                cntBoxGrid++;
            }
        }
    }

    ensuref(cntStart == 1, "There must be exactly one '@', found %d", cntStart);
    ensuref(cntBoss == 1, "There must be exactly one 'M', found %d", cntBoss);

    // Command string S
    string S = inf.readToken("[LRUD]{1,5000}", "commands");
    inf.readEoln();

    // Now K lines of monsters follow directly (no explicit K in input).
    // K is the number of monsters in the grid, including boss.
    int K = cntMonGrid;
    ensuref(K >= 1, "There must be at least one monster including boss, found %d", K);

    map<pair<int,int>, int> monPosCount;
    set<string> monNames;

    for (int i = 0; i < K; ++i) {
        int R = inf.readInt(1, N, "monster_R");
        inf.readSpace();
        int C = inf.readInt(1, M, "monster_C");
        inf.readSpace();
        string name = inf.readToken("[A-Za-z]{1,10}", "monster_name");
        inf.readSpace();
        int W = inf.readInt(1, 20, "monster_W");
        inf.readSpace();
        int A = inf.readInt(1, 20, "monster_A");
        inf.readSpace();
        int H = inf.readInt(1, 20, "monster_H");
        inf.readSpace();
        int E = inf.readInt(1, 20, "monster_E");
        inf.readEoln();

        pair<int,int> pos = {R - 1, C - 1};
        ensuref(grid[pos.first][pos.second] == '&' || grid[pos.first][pos.second] == 'M',
                "Monster info line %d refers to cell (%d,%d) which is not '&' or 'M' in grid",
                i + 1, R, C);
        monPosCount[pos]++;

        ensuref(!monNames.count(name),
                "Duplicate monster name '%s'", name.c_str());
        monNames.insert(name);
    }

    // Check monster coverage and uniqueness per cell
    int countedMon = 0;
    int bossCounted = 0;
    for (auto &p : monPosCount) {
        int r = p.first.first;
        int c = p.first.second;
        char ch = grid[r][c];
        ensuref(p.second == 1,
                "Monster at (%d,%d) has %d info lines (must be exactly 1)",
                r + 1, c + 1, p.second);
        if (ch == 'M') bossCounted++;
        countedMon++;
    }
    ensuref(countedMon == cntMonGrid,
            "Number of monsters in info (%d) does not match number of '&' and 'M' in grid (%d)",
            countedMon, cntMonGrid);
    ensuref(bossCounted == 1,
            "Boss cell 'M' must appear exactly once in monster info, found %d",
            bossCounted);

    // After all monsters, we have exactly L lines of box info,
    // where L is the number of 'B' in the grid (cntBoxGrid).
    int Lbox = cntBoxGrid;
    map<pair<int,int>, int> boxPosCount;

    for (int i = 0; i < Lbox; ++i) {
        int R = inf.readInt(1, N, "box_R");
        inf.readSpace();
        int C = inf.readInt(1, M, "box_C");
        inf.readSpace();
        char T = inf.readChar();
        ensuref(T == 'W' || T == 'A' || T == 'O',
                "Box type at info line %d must be 'W','A','O', got '%c'",
                i + 1, T);
        inf.readSpace();

        pair<int,int> pos = {R - 1, C - 1};
        ensuref(grid[pos.first][pos.second] == 'B',
                "Box info line %d refers to cell (%d,%d) which is not 'B' in grid",
                i + 1, R, C);
        boxPosCount[pos]++;

        if (T == 'W' || T == 'A') {
            int val = inf.readInt(1, 10, "equip_value");
            (void)val;
        } else { // T == 'O'
            string eff = inf.readToken("[A-Z]{2}", "accessory_type");
            ensuref(
                eff == "HR" || eff == "RE" || eff == "CO" ||
                eff == "EX" || eff == "DX" || eff == "HU" ||
                eff == "CU",
                "Invalid accessory type '%s' at line %d",
                eff.c_str(), i + 1
            );
        }
        inf.readEoln();
    }

    int countedBoxes = 0;
    for (auto &p : boxPosCount) {
        int r = p.first.first;
        int c = p.first.second;
        ensuref(p.second == 1,
                "Box at (%d,%d) has %d info lines (must be exactly 1)",
                r + 1, c + 1, p.second);
        countedBoxes++;
    }
    ensuref(countedBoxes == cntBoxGrid,
            "Number of boxes in info (%d) does not match number of 'B' in grid (%d)",
            countedBoxes, cntBoxGrid);

    inf.readEof();
}
