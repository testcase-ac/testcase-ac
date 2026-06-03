#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int n = 12;
    vector<vector<int>> time(n, vector<int>(n, 0));

    int mode = rnd.next(0, 4);
    int low = rnd.next(1, 20);
    int high = rnd.next(50, 1000);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int gi = i / 2;
            int gj = j / 2;
            int value;

            if (mode == 0) {
                value = rnd.next(1, 1000);
            } else if (mode == 1) {
                value = (gi == gj) ? rnd.next(1, low) : rnd.next(high / 2, high);
            } else if (mode == 2) {
                value = (gi == gj) ? rnd.next(high / 2, high) : rnd.next(1, low);
            } else if (mode == 3) {
                int groupDistance = abs(gi - gj);
                int base = 1 + groupDistance * rnd.next(3, 40);
                value = min(1000, base + rnd.next(0, 30));
            } else {
                value = rnd.next(0, 3) == 0 ? rnd.next(1, low) : rnd.next(high / 2, high);
            }

            time[i][j] = time[j][i] = value;
        }
    }

    for (int i = 0; i < n; ++i) {
        println(time[i]);
    }

    return 0;
}
