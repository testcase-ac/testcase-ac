#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> angles = {-360, -315, -270, -225, -180, -135, -90, -45,
                          0,    45,   90,   135,  180,  225,  270, 315, 360};
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int n;
        if (tc == 0 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = 2 * rnd.next(1, 6) + 1;
        }

        int d;
        if (tc == 0) {
            d = rnd.any(vector<int>{-360, 0, 360});
        } else {
            d = rnd.any(angles);
        }

        int pattern = rnd.next(4);
        int base = rnd.next(1, 1000000);
        int step = rnd.next(1, 97);

        println(n, d);
        for (int row = 0; row < n; ++row) {
            vector<int> values;
            for (int col = 0; col < n; ++col) {
                int value;
                if (pattern == 0) {
                    value = (row * n + col + 1);
                } else if (pattern == 1) {
                    value = 1000000 - ((row + col) % 17);
                } else if (pattern == 2) {
                    value = 1 + ((base + row * step + col * (step + 3)) % 1000000);
                } else {
                    bool onMain = row == col;
                    bool onAnti = row + col == n - 1;
                    bool onMiddle = row == n / 2 || col == n / 2;
                    value = onMain || onAnti || onMiddle ? rnd.next(1, 40) : rnd.next(41, 120);
                }
                values.push_back(value);
            }
            println(values);
        }
    }

    return 0;
}
