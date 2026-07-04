#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Test {
    long long n;
    long long l;
    long long r;
    long long x;
    long long y;
    long long z;
    long long b1;
    long long b2;
};

long long rndU32() {
    return rnd.next(0LL, 4294967295LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Test> tests;
    int randomTests = rnd.next(6, 14);
    for (int tc = 0; tc < randomTests; ++tc) {
        int mode = rnd.next(0, 5);
        Test cur{};

        if (mode == 0) {
            cur.n = rnd.next(2LL, 8LL);
            cur.l = rnd.next(-10LL, 10LL);
            cur.r = cur.l;
            cur.x = rnd.next(0LL, 3LL);
            cur.y = rnd.next(0LL, 3LL);
            cur.z = rnd.next(0LL, 7LL);
            cur.b1 = rndU32();
            cur.b2 = rndU32();
        } else if (mode == 1) {
            cur.n = rnd.next(2LL, 12LL);
            cur.l = rnd.next(-30LL, -1LL);
            cur.r = rnd.next(1LL, 30LL);
            cur.x = rnd.next(0LL, 20LL);
            cur.y = rnd.next(0LL, 20LL);
            cur.z = rnd.next(0LL, 50LL);
            cur.b1 = rnd.next(0LL, 1000LL);
            cur.b2 = rnd.next(0LL, 1000LL);
        } else if (mode == 2) {
            cur.n = rnd.next(2LL, 16LL);
            cur.l = rnd.next(-2000000000LL, -1999999950LL);
            cur.r = rnd.next(1999999950LL, 2000000000LL);
            cur.x = rndU32();
            cur.y = rndU32();
            cur.z = rndU32();
            cur.b1 = rndU32();
            cur.b2 = rndU32();
        } else if (mode == 3) {
            cur.n = rnd.next(2LL, 10LL);
            cur.l = rnd.next(-5LL, 5LL);
            cur.r = cur.l + rnd.next(0LL, 8LL);
            cur.x = 0;
            cur.y = rnd.next(0LL, 2LL);
            cur.z = rnd.next(0LL, 5LL);
            cur.b1 = rnd.next(0LL, 20LL);
            cur.b2 = rnd.next(0LL, 20LL);
        } else if (mode == 4) {
            cur.n = rnd.next(2LL, 20LL);
            cur.l = rnd.next(-100LL, 0LL);
            cur.r = cur.l + rnd.next(1LL, 200LL);
            cur.x = rnd.any(vector<long long>{0LL, 1LL, 4294967295LL});
            cur.y = rnd.any(vector<long long>{0LL, 1LL, 4294967295LL});
            cur.z = rnd.any(vector<long long>{0LL, 1LL, 4294967295LL});
            cur.b1 = rnd.any(vector<long long>{0LL, 1LL, 4294967295LL});
            cur.b2 = rnd.any(vector<long long>{0LL, 1LL, 4294967295LL});
        } else {
            cur.n = rnd.next(2LL, 14LL);
            long long width = rnd.next(1LL, 50LL);
            cur.l = rnd.next(-1000LL, 1000LL - width);
            cur.r = cur.l + width;
            cur.x = rnd.next(0LL, 100000LL);
            cur.y = rnd.next(0LL, 100000LL);
            cur.z = rnd.next(0LL, 100000LL);
            cur.b1 = rnd.next(0LL, 100000LL);
            cur.b2 = rnd.next(0LL, 100000LL);
        }

        tests.push_back(cur);
    }

    tests.push_back({2, -2000000000LL, -2000000000LL, 0, 0, 0, 0, 4294967295LL});
    tests.push_back({2, 2000000000LL, 2000000000LL, 4294967295LL, 4294967295LL, 4294967295LL, 4294967295LL, 0});
    tests.push_back({rnd.next(6LL, 18LL), -1, 1, 1, 1, 1, rnd.next(0LL, 3LL), rnd.next(0LL, 3LL)});

    shuffle(tests.begin(), tests.end());

    println(static_cast<int>(tests.size()));
    for (const Test& cur : tests) {
        printf("%lld %lld %lld %lld %lld %lld %lld %lld\n",
               cur.n, cur.l, cur.r, cur.x, cur.y, cur.z, cur.b1, cur.b2);
    }

    return 0;
}
