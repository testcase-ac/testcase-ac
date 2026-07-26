#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    long long l = rnd.next(1LL, 50LL);
    long long r = rnd.next(1LL, 60LL);
    vector<long long> positions(n);

    int mode = rnd.next(0, 2);
    for (long long& position : positions) {
        if (mode == 0) {
            position = rnd.next(0LL, l);
        } else if (mode == 1) {
            position = rnd.any(vector<long long>{0, l, l / 2});
        } else {
            position = rnd.next(0LL, std::min(l, 5LL));
        }
    }
    sort(positions.begin(), positions.end());

    println(n, l, r);
    println(positions);
}
