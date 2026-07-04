#include "testlib.h"
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const long long LIM = 1000000000000000000LL;

vector<long long> uniqueSorted(vector<long long> values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    return values;
}

vector<long long> randomSpikes(long long n, int x) {
    set<long long> chosen;
    while ((int)chosen.size() < x) {
        chosen.insert(rnd.next(1LL, n - 1));
    }
    return vector<long long>(chosen.begin(), chosen.end());
}

vector<long long> buildSpikes(long long n, int mode) {
    vector<long long> p;
    if (mode == 0) {
        long long start = rnd.next(1LL, max(1LL, n - 4));
        int len = (int)min<long long>(rnd.next(1, 4), n - start);
        for (int i = 0; i < len; ++i) p.push_back(start + i);
    } else if (mode == 1) {
        long long start = rnd.next(1LL, max(1LL, n - 8));
        for (int i = 0; i < 8 && start + i * 2 <= n - 1; ++i) p.push_back(start + i * 2);
    } else if (mode == 2) {
        long long offset = rnd.next(1LL, min(30LL, n - 1));
        long long start = max(1LL, n - offset);
        int len = (int)min<long long>(rnd.next(1, 6), n - start);
        for (int i = 0; i < len; ++i) p.push_back(start + i);
    } else if (mode == 3) {
        int x = (int)min<long long>(rnd.next(1, 12), n - 1);
        p = randomSpikes(n, x);
    } else {
        long long block = rnd.next(1LL, max(1LL, n - 12));
        p.push_back(1);
        p.push_back(block);
        p.push_back(min(n - 1, block + 1));
        p.push_back(min(n - 1, block + 2));
        p.push_back(n - 1);
    }
    return uniqueSorted(p);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(0, 4);
        long long n;
        if (sizeMode == 0) {
            n = rnd.next(2LL, 12LL);
        } else if (sizeMode == 1) {
            n = rnd.next(13LL, 80LL);
        } else if (sizeMode == 2) {
            n = rnd.next(1000LL, 1000000LL);
        } else {
            n = LIM - rnd.next(0LL, 1000LL);
        }

        vector<long long> p = buildSpikes(n, rnd.next(0, 4));
        if (p.empty()) p.push_back(1);

        println(n);
        println((int)p.size());
        println(p);
    }

    return 0;
}
