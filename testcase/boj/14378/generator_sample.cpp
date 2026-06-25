#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 5);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 2;
        } else {
            n = rnd.next(2, 8);
        }

        int mode = rnd.next(0, 3);
        int maxStart = mode == 0 ? 20 : (mode == 1 ? 200 : 2300);
        int rowStepLimit = mode == 2 ? 8 : 25;
        int colStepLimit = mode == 2 ? 8 : 25;

        vector<int> rowBase(n), colBase(n);
        rowBase[0] = rnd.next(0, maxStart);
        colBase[0] = rnd.next(1, maxStart);

        for (int i = 1; i < n; ++i) {
            rowBase[i] = rowBase[i - 1] + rnd.next(1, rowStepLimit);
            colBase[i] = colBase[i - 1] + rnd.next(1, colStepLimit);
        }

        int highest = rowBase.back() + colBase.back();
        if (highest > 2500) {
            int shift = highest - 2500;
            for (int& value : rowBase) {
                value -= shift;
            }
        }

        vector<vector<int>> lists;
        for (int r = 0; r < n; ++r) {
            vector<int> row;
            for (int c = 0; c < n; ++c) {
                row.push_back(rowBase[r] + colBase[c]);
            }
            lists.push_back(row);
        }
        for (int c = 0; c < n; ++c) {
            vector<int> column;
            for (int r = 0; r < n; ++r) {
                column.push_back(rowBase[r] + colBase[c]);
            }
            lists.push_back(column);
        }

        lists.erase(lists.begin() + rnd.next(0, 2 * n - 1));
        shuffle(lists.begin(), lists.end());

        println(n);
        for (const vector<int>& list : lists) {
            println(list);
        }
    }

    return 0;
}
