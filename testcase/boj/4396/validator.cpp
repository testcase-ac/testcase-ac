#include "testlib.h"
#include <vector>
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    // 2. Read mine map
    vector<string> mine(n);
    set<pair<int,int>> mine_pos;
    int mine_cnt = 0;
    for (int i = 0; i < n; ++i) {
        mine[i] = inf.readLine("[.*]{"+to_string(n)+","+to_string(n)+"}", "mine_row");
        ensuref((int)mine[i].size() == n, "Mine row %d has length %d, expected %d", i+1, (int)mine[i].size(), n);
        for (int j = 0; j < n; ++j) {
            ensuref(mine[i][j] == '.' || mine[i][j] == '*', "Invalid character '%c' in mine map at (%d,%d)", mine[i][j], i+1, j+1);
            if (mine[i][j] == '*') {
                ensuref(!mine_pos.count({i,j}), "Duplicate mine at (%d,%d)", i+1, j+1);
                mine_pos.insert({i,j});
                mine_cnt++;
            }
        }
    }

    // 3. Read opened map
    vector<string> opened(n);
    for (int i = 0; i < n; ++i) {
        opened[i] = inf.readLine("[.x]{"+to_string(n)+","+to_string(n)+"}", "opened_row");
        ensuref((int)opened[i].size() == n, "Opened row %d has length %d, expected %d", i+1, (int)opened[i].size(), n);
        for (int j = 0; j < n; ++j) {
            ensuref(opened[i][j] == '.' || opened[i][j] == 'x', "Invalid character '%c' in opened map at (%d,%d)", opened[i][j], i+1, j+1);
        }
    }

    // 4. Check that all mines are on different cells (already checked above)
    // 5. Check that number of mines <= n*n
    ensuref(mine_cnt <= n*n, "Too many mines: %d > %d", mine_cnt, n*n);

    // 6. Check that all opened cells are not mines (i.e., no 'x' on a mine)
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (opened[i][j] == 'x') {
            ensuref(mine[i][j] != '*', "Opened cell at (%d,%d) is a mine", i+1, j+1);
        }
    }

    // 7. Check that all mines are on different cells (already checked above)
    // 8. Check that all unopened cells are not required to be mines (problem does not require this in input)

    // 9. Check that the number of unopened cells is at least the number of mines (otherwise, game cannot be won)
    int unopened = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
        if (opened[i][j] == '.') unopened++;
    ensuref(unopened >= mine_cnt, "Number of unopened cells (%d) less than number of mines (%d)", unopened, mine_cnt);

    inf.readEof();
}
