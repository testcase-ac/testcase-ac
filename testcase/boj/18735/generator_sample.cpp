#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int freshColor(int& nextColor) {
    return nextColor++;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 40);
    vector<int> c(n);
    int nextColor = rnd.next(1, 1000000000 - 1000);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) c[i] = freshColor(nextColor);
    } else if (mode == 1) {
        int colors = rnd.next(1, min(n, 8));
        vector<int> palette;
        for (int i = 0; i < colors; ++i) palette.push_back(freshColor(nextColor));
        for (int i = 0; i < n; ++i) c[i] = rnd.any(palette);
    } else if (mode == 2) {
        n = max(n, 2);
        c.assign(n, 0);
        for (int i = 0; i < n; ++i) c[i] = freshColor(nextColor);
        int pos = rnd.next(0, n - 2);
        c[pos + 1] = c[pos];
    } else if (mode == 3) {
        n = max(n, 3);
        c.assign(n, 0);
        for (int i = 0; i < n; ++i) c[i] = freshColor(nextColor);
        int pos = rnd.next(0, n - 3);
        c[pos + 2] = c[pos];
    } else if (mode == 4) {
        n = max(n, 4);
        c.assign(n, 0);
        for (int i = 0; i < n; ++i) c[i] = freshColor(nextColor);
        int pos = rnd.next(0, n - 4);
        c[pos + rnd.next(3, min(8, n - pos - 1))] = c[pos];
    } else {
        n = max(n, 2);
        c.assign(n, 0);
        int colors = rnd.next(2, min(n, 10));
        vector<int> palette;
        for (int i = 0; i < colors; ++i) palette.push_back(freshColor(nextColor));
        for (int i = 0; i < n; ++i) {
            if (i > 0 && rnd.next(0, 3) == 0) {
                c[i] = c[i - 1];
            } else if (i > 1 && rnd.next(0, 4) == 0) {
                c[i] = c[i - 2];
            } else {
                c[i] = rnd.any(palette);
            }
        }
    }

    println(n);
    println(c);
    return 0;
}
