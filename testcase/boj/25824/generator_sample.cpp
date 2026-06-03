#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    constexpr int studentCount = 12;
    vector<vector<int>> time(studentCount, vector<int>(studentCount, 0));

    int mode = rnd.next(0, 4);
    int low = 1;
    int high = 1000;

    if (mode == 0) {
        high = rnd.next(1, 12);
    } else if (mode == 1) {
        low = rnd.next(1, 200);
        high = rnd.next(low, min(1000, low + rnd.next(0, 80)));
    } else if (mode == 2) {
        low = rnd.next(850, 1000);
    }

    for (int i = 0; i < studentCount; ++i) {
        for (int j = i + 1; j < studentCount; ++j) {
            int value;
            if (mode == 3) {
                int groupDistance = abs(i / 2 - j / 2);
                int base = 1 + groupDistance * rnd.next(20, 90);
                value = min(1000, base + rnd.next(0, 30));
            } else if (mode == 4) {
                value = rnd.next(0, 3) == 0 ? rnd.next(1, 20) : rnd.next(700, 1000);
            } else {
                value = rnd.next(low, high);
            }
            time[i][j] = time[j][i] = value;
        }
    }

    for (int i = 0; i < studentCount; ++i) {
        println(time[i]);
    }

    return 0;
}
