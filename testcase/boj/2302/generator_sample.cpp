#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int N = 1;
    vector<int> vip;

    if (mode == 0) {
        N = rnd.next(1, 5);
    } else if (mode == 1) {
        N = rnd.next(25, 40);
    } else if (mode == 2) {
        N = rnd.next(1, 40);
        for (int seat = 1; seat <= N; seat++) {
            vip.push_back(seat);
        }
    } else if (mode == 3) {
        N = rnd.next(8, 40);
        int start = rnd.next(1, N);
        int length = rnd.next(1, min(6, N - start + 1));
        for (int seat = start; seat < start + length; seat++) {
            vip.push_back(seat);
        }
    } else if (mode == 4) {
        N = rnd.next(10, 40);
        int stride = rnd.next(2, 5);
        int offset = rnd.next(1, stride);
        for (int seat = offset; seat <= N; seat += stride) {
            vip.push_back(seat);
        }
    } else {
        N = rnd.next(1, 40);
        int M = rnd.next(0, N);
        set<int> chosen;
        while ((int)chosen.size() < M) {
            chosen.insert(rnd.next(1, N));
        }
        vip.assign(chosen.begin(), chosen.end());
    }

    println(N);
    println((int)vip.size());
    for (int seat : vip) {
        println(seat);
    }

    return 0;
}
