#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ll maxN = 1000000000000000000LL;
    int mode = rnd.next(0, 6);

    ll n;
    if (mode == 0) {
        n = rnd.next(1LL, 5LL);
    } else if (mode == 1) {
        n = rnd.next(6LL, 40LL);
    } else if (mode == 2) {
        n = rnd.next(41LL, 500LL);
    } else if (mode == 3) {
        n = maxN - rnd.next(0LL, 1000LL);
    } else if (mode == 4) {
        ll block = rnd.next(1LL, 200000000000000000LL);
        n = 5 * block + rnd.next(0LL, 4LL);
    } else {
        n = rnd.next(1LL, maxN);
    }

    int m;
    if (mode == 3) {
        m = rnd.next(2, 8);
    } else if (mode == 6) {
        m = rnd.next(20, 60);
    } else {
        m = rnd.next(2, 20);
    }

    vector<int> songs;
    songs.reserve(m);

    int durationMode = rnd.next(0, 5);
    if (durationMode == 0) {
        int value = rnd.next(1, 5);
        songs.assign(m, value);
    } else if (durationMode == 1) {
        vector<int> choices = {2, 4};
        for (int i = 0; i < m; ++i) songs.push_back(rnd.any(choices));
    } else if (durationMode == 2) {
        vector<int> choices = {3, 5};
        for (int i = 0; i < m; ++i) songs.push_back(rnd.any(choices));
    } else if (durationMode == 3) {
        for (int i = 1; i <= 5 && (int)songs.size() < m; ++i) songs.push_back(i);
        while ((int)songs.size() < m) songs.push_back(rnd.next(1, 5));
    } else if (durationMode == 4) {
        int heavy = rnd.next(1, 5);
        for (int i = 0; i < m; ++i) {
            songs.push_back(rnd.next(0, 3) == 0 ? rnd.next(1, 5) : heavy);
        }
    } else {
        for (int i = 0; i < m; ++i) songs.push_back(rnd.next(1, 5));
    }

    shuffle(songs.begin(), songs.end());

    println(n, m);
    for (int song : songs) println(song);

    return 0;
}
