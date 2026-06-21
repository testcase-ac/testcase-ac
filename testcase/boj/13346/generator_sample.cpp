#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomWord(int n, int q) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('0' + rnd.next(0, q - 1)));
    }
    return s;
}

string mutateWord(const string& base, int q, int changes) {
    int n = int(base.size());
    vector<int> positions(n);
    for (int i = 0; i < n; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());

    string result = base;
    for (int i = 0; i < changes; ++i) {
        int pos = positions[i];
        int oldDigit = result[pos] - '0';
        int delta = rnd.next(1, q - 1);
        result[pos] = char('0' + (oldDigit + delta) % q);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int q;
    int n;
    int d;
    string f1;
    string f2;

    if (mode == 0) {
        q = rnd.next(2, 10);
        n = rnd.next(1, 4);
        d = rnd.next(1, 2 * n);
        f1 = randomWord(n, q);
        f2 = randomWord(n, q);
    } else if (mode == 1) {
        q = rnd.next(2, 10);
        n = rnd.next(1, 20);
        f1 = randomWord(n, q);
        f2 = f1;
        d = 2 * rnd.next(1, n);
    } else if (mode == 2) {
        q = rnd.next(2, 10);
        n = rnd.next(2, 20);
        f1 = randomWord(n, q);
        f2 = mutateWord(f1, q, n);
        d = rnd.any(vector<int>{n - 1, n, n + 1, 2 * n});
        if (d < 1) d = 1;
    } else if (mode == 3) {
        q = rnd.next(3, 10);
        n = rnd.next(3, 25);
        int focusDistance = rnd.next(1, n - 1);
        f1 = randomWord(n, q);
        f2 = mutateWord(f1, q, focusDistance);
        d = rnd.next(1, 2 * n);
    } else if (mode == 4) {
        q = 2;
        n = rnd.next(5, 32);
        f1 = randomWord(n, q);
        int focusDistance = rnd.next(0, n);
        f2 = mutateWord(f1, q, focusDistance);
        d = rnd.next(1, 2 * n);
    } else if (mode == 5) {
        q = rnd.next(2, 10);
        n = rnd.next(8, 30);
        f1 = randomWord(n, q);
        int focusDistance = rnd.next(0, n);
        f2 = mutateWord(f1, q, focusDistance);
        d = rnd.any(vector<int>{1, focusDistance, focusDistance + 1, 2 * n - 1, 2 * n});
        if (d < 1) d = 1;
        if (d > 2 * n) d = 2 * n;
    } else {
        q = rnd.any(vector<int>{2, 3, 10});
        n = rnd.next(25, 40);
        f1 = randomWord(n, q);
        int focusDistance = rnd.next(0, min(n, 12));
        f2 = mutateWord(f1, q, focusDistance);
        d = rnd.next(max(1, focusDistance - 2), min(2 * n, focusDistance + 20));
    }

    println(q, n, d);
    println(f1);
    println(f2);
    return 0;
}
