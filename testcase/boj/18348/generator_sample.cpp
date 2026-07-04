#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 888888;
    vector<int> boundaryNs = {2, 3, 4, 5, 6, 7, 8, 9, 10, MAX_N - 1, MAX_N};
    string s = rnd.next(0, 1) == 0 ? "order" : "chaos";
    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(2, 10);
    } else if (mode == 1) {
        n = rnd.any(boundaryNs);
    } else if (mode == 2) {
        n = rnd.next(11, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 5000);
    } else if (mode == 4) {
        int base = rnd.next(MAX_N - 1000, MAX_N);
        n = max(2, base - (base % 2));
    } else {
        int base = rnd.next(MAX_N - 1000, MAX_N);
        n = base | 1;
        if (n > MAX_N) n = MAX_N - 1;
    }

    println(s, n);
    return 0;
}
