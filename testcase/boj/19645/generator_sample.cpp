#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> a;

    if (mode == 0) {
        int n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 50));
        }
    } else if (mode == 1) {
        int n = rnd.next(3, 18);
        int value = rnd.next(1, 50);
        a.assign(n, value);
    } else if (mode == 2) {
        int n = rnd.next(8, 30);
        int high = rnd.next(3, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, high));
        }
    } else if (mode == 3) {
        int n = rnd.next(6, 24);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                a.push_back(rnd.next(1, 8));
            } else {
                a.push_back(rnd.next(35, 50));
            }
        }
    } else if (mode == 4) {
        int groups = rnd.next(2, 10);
        for (int i = 0; i < groups; ++i) {
            int x = rnd.next(1, 25);
            int y = rnd.next(1, 25);
            int z = rnd.next(1, 25);
            a.push_back(x + y);
            a.push_back(x + z);
            a.push_back(y + z);
        }
    } else {
        int n = rnd.next(20, 50);
        int high = rnd.next(20, 50);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, high));
        }
    }

    shuffle(a.begin(), a.end());

    println(static_cast<int>(a.size()));
    println(a);

    return 0;
}
