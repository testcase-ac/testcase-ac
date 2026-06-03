#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000LL;
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 12);
    long long k = rnd.next(1LL, 1000000000LL);
    long long m = rnd.next(1LL, 1000000000LL);
    vector<long long> lengths;

    if (mode == 0) {
        k = rnd.next(1LL, 30LL);
        n = rnd.next(4, 10);
        long long maxLen = min(LIM, 3 * k + 40);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 5);
            if (pick == 0) lengths.push_back(rnd.next(1LL, k));
            else if (pick == 1) lengths.push_back(min(LIM, k + rnd.next(1LL, k)));
            else if (pick == 2) lengths.push_back(min(LIM, 2 * k));
            else if (pick == 3) lengths.push_back(min(LIM, 2 * k + rnd.next(1LL, 20LL)));
            else lengths.push_back(rnd.next(1LL, maxLen));
        }
        m = rnd.next(1LL, 80LL);
    } else if (mode == 1) {
        k = rnd.next(1LL, 20LL);
        n = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(1LL, k));
        }
        m = rnd.next(1LL, 20LL);
    } else if (mode == 2) {
        k = rnd.next(2LL, 100LL);
        n = rnd.next(3, 9);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(k + 1, min(LIM, 2 * k - 1)));
        }
        m = rnd.next(1LL, 60LL);
    } else if (mode == 3) {
        k = rnd.next(1LL, 100LL);
        n = rnd.next(3, 9);
        for (int i = 0; i < n; ++i) {
            long long base = 2 * k + rnd.next(0LL, 300LL);
            lengths.push_back(min(LIM, base));
        }
        m = rnd.next(1LL, 200LL);
    } else if (mode == 4) {
        k = rnd.next(1LL, 10LL);
        n = rnd.next(3, 8);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(rnd.next(900000000LL, LIM));
        }
        m = rnd.next(900000000LL, LIM);
    } else {
        k = rnd.next(400000000LL, 500000000LL);
        n = rnd.next(4, 10);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 3);
            if (pick == 0) lengths.push_back(k);
            else if (pick == 1) lengths.push_back(min(LIM, k + 1));
            else if (pick == 2) lengths.push_back(min(LIM, 2 * k));
            else lengths.push_back(min(LIM, 2 * k + rnd.next(1LL, 1000LL)));
        }
        m = rnd.next(1LL, 1000LL);
    }

    shuffle(lengths.begin(), lengths.end());

    println(n, k, m);
    for (long long length : lengths) {
        println(length);
    }

    return 0;
}
