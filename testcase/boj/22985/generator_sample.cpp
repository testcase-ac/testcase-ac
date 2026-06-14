#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long sumCapacity(const string& s) {
    long long total = 0;
    for (char c : s) total += 25 - (c - 'a');
    return total;
}

long long minCapacity(const string& s) {
    int best = 25;
    for (char c : s) best = min(best, 25 - (c - 'a'));
    return best;
}

long long chooseM(const string& s) {
    const long long maxM = 1000000000000000000LL;
    long long sum = sumCapacity(s);
    long long mn = minCapacity(s);

    vector<long long> candidates = {
        0,
        1,
        mn,
        min(maxM, mn + 1),
        sum,
        min(maxM, sum + 1),
        maxM,
    };

    if (sum > 0) candidates.push_back(rnd.next(0LL, min(sum, 200LL)));
    if (sum < maxM) candidates.push_back(rnd.next(sum, min(maxM, sum + 200LL)));
    return rnd.any(candidates);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 5);
        string alphabet = "az";
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        s = string(n, 'z');
    } else if (mode == 2) {
        n = rnd.next(1, 30);
        char c = rnd.next('a', 'd');
        s = string(n, c);
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        string alphabet = "ayz";
        for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        char hi = rnd.next('a', 'z');
        for (int i = 0; i < n; ++i) s += char(rnd.next('a', hi));
    } else if (mode == 5) {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                s += rnd.any(string("xyz"));
            } else {
                s += char(rnd.next('a', 'w'));
            }
        }
    } else if (mode == 6) {
        n = 300;
        char c = rnd.any(string("az"));
        s = string(n, c);
    } else {
        n = rnd.next(100, 300);
        for (int i = 0; i < n; ++i) s += char(rnd.next('a', 'z'));
    }

    long long m = chooseM(s);
    println(n, m);
    println(s);

    return 0;
}
