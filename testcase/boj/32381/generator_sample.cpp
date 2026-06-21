#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int64 n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 8) + 1;
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 500) + 1;
    } else if (mode == 3) {
        n = 1000000000LL - 2 * rnd.next(0, 50) - 1;
    } else {
        n = rnd.next(0, 1) ? 999999999LL : 987654321LL;
    }

    int q = rnd.next(1, 40);
    vector<int64> announced;
    announced.reserve(q);
    int64 maxBlack = n * n;

    if (mode <= 2) {
        int activeRows = 0;
        int activeCols = 0;
        int cappedN = static_cast<int>(min<int64>(n, 1000000LL));

        for (int i = 0; i < q; ++i) {
            bool flipRow = rnd.next(0, 1);
            if (flipRow) {
                if (activeRows == cappedN || (activeRows > 0 && rnd.next(0, 1))) {
                    --activeRows;
                } else {
                    ++activeRows;
                }
            } else {
                if (activeCols == cappedN || (activeCols > 0 && rnd.next(0, 1))) {
                    --activeCols;
                } else {
                    ++activeCols;
                }
            }

            int64 black = 1LL * activeRows * (n - activeCols) + 1LL * (n - activeRows) * activeCols;
            announced.push_back(black);
        }
    } else if (mode == 3) {
        for (int i = 0; i < q; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) {
                announced.push_back(0);
            } else if (pick == 1) {
                announced.push_back(maxBlack);
            } else if (pick == 2) {
                announced.push_back(n * rnd.next(0LL, min<int64>(n, 20)));
            } else if (pick == 3) {
                announced.push_back(maxBlack - rnd.next(0LL, min<int64>(maxBlack, 1000LL)));
            } else {
                announced.push_back(rnd.next(0LL, maxBlack));
            }
        }
    } else {
        int64 step = rnd.next(0, 1) ? n : rnd.next(1LL, min<int64>(n, 1000LL));
        int64 value = rnd.next(0LL, min<int64>(maxBlack, 1000LL));
        for (int i = 0; i < q; ++i) {
            int dir = rnd.next(0, 2) - 1;
            value = max<int64>(0, min<int64>(maxBlack, value + dir * step));
            announced.push_back(value);
        }
    }

    println(n, q);
    println(announced);

    return 0;
}
