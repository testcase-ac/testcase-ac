#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 97, 101, 1009, 65537, 99999989
    };

    int datasets = rnd.next(8, 18);
    for (int tc = 0; tc < datasets; ++tc) {
        int mode = tc < 6 ? tc : rnd.next(0, 6);
        int n;
        int s;
        int w;
        int q;

        if (mode == 0) {
            n = rnd.next(1, 3);
            s = rnd.next(1, 30);
            w = rnd.next(1, 30);
            q = rnd.any(vector<int>{2, 3, 5});
        } else if (mode == 1) {
            n = rnd.next(4, 15);
            s = rnd.next(1, 1000);
            w = rnd.next(1, 1000);
            q = rnd.any(vector<int>{2, 5});
        } else if (mode == 2) {
            n = rnd.next(8, 35);
            s = rnd.next(1, 100000);
            w = rnd.next(1, 100000);
            q = rnd.any(vector<int>{3, 7, 11, 13, 17});
        } else if (mode == 3) {
            n = rnd.next(20, 120);
            s = rnd.next(1, 1000000000);
            w = rnd.next(1, 1000000000);
            q = rnd.any(vector<int>{97, 101, 1009, 65537});
        } else if (mode == 4) {
            n = rnd.next(1, 40);
            s = rnd.any(vector<int>{1, 7, 10, 1000000000});
            w = rnd.any(vector<int>{1, 2, 999999937, 1000000000});
            q = rnd.any(primes);
        } else {
            n = rnd.next(30, 180);
            s = rnd.next(1, 1000000000);
            w = rnd.next(1, 1000000000);
            q = rnd.any(primes);
        }

        println(n, s, w, q);
    }

    println(0, 0, 0, 0);
    return 0;
}
