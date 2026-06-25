#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> p;

    if (mode == 0) {
        int n = rnd.next(1, 20);
        int hi = rnd.next(8, 80);
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.next(1, hi));
        }
    } else if (mode == 1) {
        int n = rnd.next(2, 36);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            int x = 2 * rnd.next(0, base) + 1;
            p.push_back(min(x, 9999999));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 36);
        int base = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            p.push_back(2 * rnd.next(1, base));
        }
    } else if (mode == 3) {
        int pairs = rnd.next(1, 14);
        vector<int> odd = {1, 3, 5, 7, 9, 11, 13, 15, 21, 25};
        vector<int> even = {2, 4, 6, 8, 10, 12, 18, 24, 30, 36};
        for (int i = 0; i < pairs; ++i) {
            p.push_back(rnd.any(odd));
            p.push_back(rnd.any(even));
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 45);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) p.push_back(1);
            else if (pick == 1) p.push_back(2);
            else if (pick == 2) p.push_back(9999999);
            else if (pick == 3) p.push_back(9999998);
            else p.push_back(rnd.next(1, 50));
        }
    } else {
        int n = rnd.next(20, 60);
        int low = rnd.next(1, 500);
        int width = rnd.next(10, 300);
        for (int i = 0; i < n; ++i) {
            p.push_back(rnd.next(low, min(9999999, low + width)));
        }
    }

    shuffle(p.begin(), p.end());
    println((int)p.size());
    println(p);
    return 0;
}
