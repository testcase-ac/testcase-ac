#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomDigits(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    s.push_back(rnd.next('1', '9'));
    for (int i = 1; i < n; ++i) {
        s.push_back(rnd.any(alphabet));
    }
    return s;
}

string fromCounts(vector<int> counts, bool ascending) {
    string s;
    for (int d = ascending ? 0 : 9; ascending ? d <= 9 : d >= 0; ascending ? ++d : --d) {
        s.append(counts[d], char('0' + d));
    }

    if (!s.empty() && s[0] == '0') {
        for (int i = 1; i < (int)s.size(); ++i) {
            if (s[i] != '0') {
                swap(s[0], s[i]);
                break;
            }
        }
    }
    return s;
}

string shuffledFromCounts(vector<int> counts) {
    string s = fromCounts(counts, true);
    shuffle(s.begin(), s.end());
    if (s[0] == '0') {
        for (int i = 1; i < (int)s.size(); ++i) {
            if (s[i] != '0') {
                swap(s[0], s[i]);
                break;
            }
        }
    }
    return s;
}

vector<int> randomCounts(int n, int mode) {
    vector<int> counts(10, 0);

    if (mode == 0) {
        int digit = rnd.next(1, 9);
        counts[digit] = n;
    } else if (mode == 1) {
        counts[rnd.next(1, 9)] = 1;
        counts[0] = n - 1;
    } else if (mode == 2) {
        int first = rnd.next(1, 9);
        int second = rnd.next(0, 9);
        while (second == first) second = rnd.next(0, 9);
        for (int i = 0; i < n; ++i) {
            ++counts[rnd.next(0, 2) == 0 ? first : second];
        }
        if (counts[0] == n) {
            --counts[0];
            ++counts[first];
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(0, 9);
            if (i == 0 && d == 0) d = rnd.next(1, 9);
            ++counts[d];
        }
    }

    return counts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    string a;
    string b;

    if (mode == 0) {
        n = 1;
        a = string(1, char('1' + rnd.next(0, 8)));
        b = string(1, char('1' + rnd.next(0, 8)));
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        vector<int> counts = randomCounts(n, rnd.next(0, 2));
        a = fromCounts(counts, rnd.next(0, 1) == 0);
        b = shuffledFromCounts(counts);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        vector<int> counts = randomCounts(n, 1);
        b = shuffledFromCounts(counts);
        a = rnd.next(0, 1) == 0 ? fromCounts(counts, true) : fromCounts(counts, false);
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        string alphabet = rnd.any(vector<string>{"0123456789", "0011223344", "5556677889"});
        a = randomDigits(n, alphabet);
        b = randomDigits(n, alphabet);
    } else if (mode == 4) {
        n = rnd.next(10, 30);
        vector<int> counts = randomCounts(n, rnd.next(2, 3));
        b = shuffledFromCounts(counts);
        a = fromCounts(counts, true);
        int changes = rnd.next(1, min(4, n));
        for (int i = 0; i < changes; ++i) {
            int pos = rnd.next(0, n - 1);
            char delta = rnd.next(0, 1) == 0 ? -1 : 1;
            if (a[pos] + delta >= '0' && a[pos] + delta <= '9') {
                a[pos] = char(a[pos] + delta);
            }
        }
        if (a[0] == '0') a[0] = char('1' + rnd.next(0, 8));
    } else if (mode == 5) {
        n = rnd.next(31, 60);
        vector<int> counts = randomCounts(n, rnd.next(0, 3));
        b = shuffledFromCounts(counts);
        a = randomDigits(n, rnd.any(vector<string>{"0123456789", "000111222999"}));
    } else {
        n = 60;
        vector<int> counts = randomCounts(n, rnd.next(1, 3));
        b = shuffledFromCounts(counts);
        a = rnd.next(0, 1) == 0 ? string(n, '9') : string(n, '1');
    }

    println(a);
    println(b);
    return 0;
}
