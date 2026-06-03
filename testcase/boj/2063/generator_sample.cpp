#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string formatRadius(long long scaled) {
    long long whole = scaled / 1000;
    int frac = scaled % 1000;

    if (frac == 0) return to_string(whole);
    if (whole > 0 && rnd.next(2) == 0) return to_string(whole);

    string suffix = to_string(1000 + frac).substr(1);
    while (suffix.size() > 1 && suffix.back() == '0' && rnd.next(2) == 0) {
        suffix.pop_back();
    }
    return to_string(whole) + "." + suffix;
}

vector<long long> makeSingleton() {
    return {rnd.next(1, 10000000) * 1000LL + rnd.next(0, 999)};
}

vector<long long> makeEqualPair() {
    long long value = rnd.next(1, 5000) * 1000LL + rnd.next(0, 999);
    return {value, value};
}

vector<long long> makeDominantNo(int n) {
    vector<long long> radii;
    long long sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        long long value = rnd.next(1, 20000);
        if (rnd.next(3) == 0) value *= 1000;
        radii.push_back(value);
        sum += value;
    }

    long long dominant = min(10000000LL * 1000LL, sum + rnd.next(1, 20000));
    radii.push_back(dominant);
    shuffle(radii.begin(), radii.end());
    return radii;
}

vector<long long> makePossible(int n) {
    vector<long long> radii;
    long long sum = 0;
    for (int i = 0; i < n - 1; ++i) {
        long long value = rnd.next(1, 15000);
        if (rnd.next(4) == 0) value *= 1000;
        radii.push_back(value);
        sum += value;
    }

    long long cap = min(sum, 10000000LL * 1000LL);
    long long last = rnd.next(1LL, cap);
    if (rnd.next(4) == 0) last = cap;
    radii.push_back(last);
    shuffle(radii.begin(), radii.end());
    return radii;
}

vector<long long> makeUpperBoundCase(int n) {
    vector<long long> radii;
    for (int i = 0; i < n; ++i) {
        long long value = 10000000LL * 1000LL - rnd.next(0, 5000);
        radii.push_back(max(1LL, value));
    }
    return radii;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(6);
        int n = rnd.next(1, 20);
        vector<long long> radii;

        if (mode == 0) {
            radii = makeSingleton();
        } else if (mode == 1) {
            radii = makeEqualPair();
        } else if (mode == 2) {
            n = rnd.next(2, 20);
            radii = makeDominantNo(n);
        } else if (mode == 3) {
            n = rnd.next(2, 20);
            radii = makePossible(n);
        } else if (mode == 4) {
            n = rnd.next(3, 20);
            radii = makePossible(n);
            radii[rnd.next((int)radii.size())] += rnd.next(1, 999);
            for (long long& value : radii) value = min(value, 10000000LL * 1000LL);
        } else {
            n = rnd.next(2, 20);
            radii = makeUpperBoundCase(n);
        }

        println((int)radii.size());
        for (int i = 0; i < (int)radii.size(); ++i) {
            if (i) cout << ' ';
            cout << formatRadius(radii[i]);
        }
        cout << '\n';
    }

    return 0;
}
