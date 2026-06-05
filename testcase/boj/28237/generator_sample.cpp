#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 5000;
    int mode = rnd.next(6);
    int n;

    if (mode == 0) {
        vector<int> edge = {1, 2, 3, 4, 4999, 5000};
        n = rnd.any(edge);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
    } else if (mode == 2) {
        n = rnd.next(maxN - 200, maxN);
    } else if (mode == 3) {
        vector<int> factorable = {1, 5, 65, 901};
        n = rnd.any(factorable);
    } else if (mode == 4) {
        int base = rnd.next(1, 70);
        n = min(maxN, base * base);
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
