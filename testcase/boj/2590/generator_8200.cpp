#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mode = rnd.next(0, 2);
    vector<int> n(6);
    int sum = 0;
    for (int i = 0; i < 6; i++) {
        if (mode == 0) {
            n[i] = rnd.next(0, 10);
        } else if (mode == 1) {
            n[i] = rnd.next(20, 100);
        } else {
            if (i == 2) { // emphasize size-3 cases for mod-4 edge
                if (rnd.next() < 0.7) n[i] = rnd.next(0, 7);
                else n[i] = rnd.next(8, 100);
            } else if (rnd.next() < 0.5) {
                n[i] = rnd.next(0, 100);
            } else {
                n[i] = rnd.next(0, 5);
            }
        }
        sum += n[i];
    }
    if (sum == 0) {
        int idx = rnd.next(0, 5);
        n[idx] = rnd.next(1, 10);
    }
    for (int x : n) println(x);
    return 0;
}
