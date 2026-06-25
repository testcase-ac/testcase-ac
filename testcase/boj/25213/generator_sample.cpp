#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> c;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 24);
        for (int i = 0; i < n; ++i) c.push_back(rnd.next(2, 25));
    } else if (mode == 1) {
        int n = rnd.next(4, 45);
        int primary = rnd.next(2, 25);
        int secondary = rnd.next(2, 25);
        for (int i = 0; i < n; ++i) {
            c.push_back(rnd.next(0, 99) < 75 ? primary : secondary);
        }
    } else if (mode == 2) {
        vector<vector<int>> exact = {
            {2, 2},
            {3, 3, 3},
            {4, 4, 4, 4},
            {2, 3, 6},
            {2, 4, 4},
            {3, 4, 12},
            {5, 5, 5, 5, 5},
            {6, 6, 6, 6, 6, 6},
        };
        c = rnd.any(exact);
        int extra = rnd.next(0, 20);
        for (int i = 0; i < extra; ++i) c.push_back(rnd.next(2, 25));
    } else if (mode == 3) {
        int n = rnd.next(10, 60);
        vector<int> smallPieces = {18, 19, 20, 21, 22, 23, 24, 25};
        for (int i = 0; i < n; ++i) c.push_back(rnd.any(smallPieces));
    } else if (mode == 4) {
        int n = rnd.next(8, 50);
        vector<int> divisors = {2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24};
        for (int i = 0; i < n; ++i) c.push_back(rnd.any(divisors));
    } else {
        int n = rnd.next(20, 70);
        for (int i = 0; i < n; ++i) {
            int band = rnd.next(0, 2);
            if (band == 0) c.push_back(rnd.next(2, 6));
            else if (band == 1) c.push_back(rnd.next(7, 14));
            else c.push_back(rnd.next(15, 25));
        }
    }

    shuffle(c.begin(), c.end());
    println((int)c.size());
    println(c);

    return 0;
}
