#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 12);

    vector<vector<int>> score(n, vector<int>(m, 0));

    if (mode == 0) {
        for (int j = 0; j < m; ++j) score[0][j] = 0;
    } else if (mode == 1) {
        for (int j = 0; j < m; ++j) score[0][j] = 100;
    } else {
        int solved = rnd.next(0, m);
        vector<int> tasks(m);
        for (int j = 0; j < m; ++j) tasks[j] = j;
        shuffle(tasks.begin(), tasks.end());
        for (int k = 0; k < solved; ++k) score[0][tasks[k]] = 100;
    }

    for (int i = 1; i < n; ++i) {
        if (mode == 2 && rnd.next(0, 2) == 0) {
            score[i] = score[0];
            continue;
        }

        for (int j = 0; j < m; ++j) {
            bool dymowkaSolved = score[0][j] == 100;
            int value = 0;

            if (mode == 3) {
                value = dymowkaSolved ? 100 : (rnd.next(0, 3) == 0 ? 100 : 0);
            } else if (mode == 4) {
                value = dymowkaSolved ? (rnd.next(0, 3) == 0 ? 0 : 100)
                                      : (rnd.next(0, 1) == 0 ? 0 : 100);
            } else {
                int probability = dymowkaSolved ? rnd.next(35, 85) : rnd.next(10, 70);
                value = rnd.next(0, 99) < probability ? 100 : 0;
            }

            score[i][j] = value;
        }
    }

    println(n, m);
    for (const auto& row : score) {
        println(row);
    }

    return 0;
}
