#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomRow(int n, int aPercent) {
    string row;
    row.reserve(n);
    for (int i = 0; i < n; ++i) {
        row.push_back(rnd.next(1, 100) <= aPercent ? 'a' : 'b');
    }
    return row;
}

string runRow(int n) {
    string row;
    row.reserve(n);

    char cur = rnd.next(0, 1) == 0 ? 'a' : 'b';
    while (static_cast<int>(row.size()) < n) {
        int remaining = n - static_cast<int>(row.size());
        int run = rnd.next(1, min(remaining, rnd.next(2, 8)));
        row.append(run, cur);
        cur = cur == 'a' ? 'b' : 'a';
    }

    return row;
}

string alternatingRow(int n) {
    string row;
    row.reserve(n);
    char first = rnd.next(0, 1) == 0 ? 'a' : 'b';
    for (int i = 0; i < n; ++i) {
        row.push_back((i % 2 == 0) == (first == 'a') ? 'a' : 'b');
    }
    return row;
}

string blockRow(int n) {
    string row;
    row.reserve(n);

    int left = rnd.next(0, n);
    int right = n - left;
    char first = rnd.next(0, 1) == 0 ? 'a' : 'b';
    row.append(left, first);
    row.append(right, first == 'a' ? 'b' : 'a');

    return row;
}

string mirroredRow(int n) {
    string half;
    half.reserve((n + 1) / 2);
    for (int i = 0; i < (n + 1) / 2; ++i) {
        half.push_back(rnd.next(0, 1) == 0 ? 'a' : 'b');
    }

    string row = half;
    for (int i = n / 2 - 1; i >= 0; --i) {
        row.push_back(half[i] == 'a' ? 'b' : 'a');
    }
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    string row;

    if (mode == 0) {
        n = rnd.next(1, 20);
        row.assign(n, rnd.next(0, 1) == 0 ? 'a' : 'b');
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        row = alternatingRow(n);
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        row = runRow(n);
    } else if (mode == 3) {
        n = rnd.next(1, 50);
        row = randomRow(n, rnd.any(vector<int>{20, 35, 50, 65, 80}));
    } else if (mode == 4) {
        n = rnd.next(2, 50);
        row = blockRow(n);
    } else if (mode == 5) {
        n = rnd.next(3, 60);
        row = mirroredRow(n);
    } else {
        n = rnd.next(80, 180);
        row = randomRow(n, rnd.next(30, 70));
    }

    if (rnd.next(0, 4) == 0) {
        reverse(row.begin(), row.end());
    }

    println(n);
    println(row);

    return 0;
}
