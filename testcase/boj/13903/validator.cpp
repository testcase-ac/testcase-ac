#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int R = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 1000, "C");
    inf.readEoln();

    vector<vector<int>> grid(R, vector<int>(C));
    for (int i = 0; i < R; ++i) {
        string line = inf.readLine();
        if (line.find(' ') == string::npos) {
            ensuref((int)line.size() == C, "row %d length is %d, expected %d", i + 1, (int)line.size(), C);
            for (int j = 0; j < C; ++j) {
                char ch = line[j];
                ensuref(ch == '0' || ch == '1', "row %d contains non-binary character", i + 1);
                grid[i][j] = ch - '0';
            }
            continue;
        }

        ensuref((int)line.size() == 2 * C - 1, "space-separated row %d has invalid length", i + 1);
        for (int j = 0; j < C; ++j) {
            char ch = line[2 * j];
            ensuref(ch == '0' || ch == '1', "row %d contains non-binary character", i + 1);
            grid[i][j] = ch - '0';
            if (j + 1 < C) {
                ensuref(line[2 * j + 1] == ' ', "row %d must use single spaces between cells", i + 1);
            }
        }
    }

    int N = inf.readInt(0, 10, "N");
    inf.readEoln();

    vector<pair<int,int>> moves;
    for (int i = 0; i < N; ++i) {
        int r = inf.readInt(-R, R, "r");
        inf.readSpace();
        int c = inf.readInt(-C, C, "c");
        inf.readEoln();
        moves.push_back({r,c});
    }

    inf.readEof();
}
