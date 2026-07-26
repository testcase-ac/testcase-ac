#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int k = rnd.next(2, n);
    int mode = rnd.next(0, 3);
    vector<int> colors;
    for (int color = 1; color <= k; ++color) colors.push_back(color);
    while ((int)colors.size() < n) colors.push_back(rnd.next(1, k));
    shuffle(colors.begin(), colors.end());

    int baseX = rnd.next(1, 249990);
    int baseY = rnd.next(1, 249990);
    println(n, k);
    for (int i = 0; i < n; ++i) {
        int x, y;
        if (mode == 0) {
            x = rnd.next(1, 25);
            y = rnd.next(1, 25);
        } else if (mode == 1) {
            x = baseX + rnd.next(0, 10);
            y = baseY + rnd.next(0, 10);
        } else if (mode == 2) {
            x = baseX;
            y = baseY;
        } else {
            x = rnd.any(vector<int>{1, 250000, rnd.next(1, 250000)});
            y = rnd.any(vector<int>{1, 250000, rnd.next(1, 250000)});
        }
        println(x, y, colors[i]);
    }

    return 0;
}
