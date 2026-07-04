#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string randomString(int n, const string& alphabet) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(alphabet[rnd.next(int(alphabet.size()))]);
    }
    return s;
}

void forceDifferent(const string& a, string& b) {
    if (a != b) {
        return;
    }
    b[0] = char('a' + (b[0] - 'a' + 1) % 26);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    string a;
    string b;

    if (mode == 0) {
        n = 1;
        a = string(1, char('a' + rnd.next(26)));
        do {
            b = string(1, char('a' + rnd.next(26)));
        } while (a == b);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        a = randomString(n, "abc");
        b = a;

        for (int attempt = 0; attempt < 100 && a == b; ++attempt) {
            int l = rnd.next(n);
            int r = rnd.next(l, n - 1);
            b = a;
            reverse(b.begin() + l, b.begin() + r + 1);
        }
        forceDifferent(a, b);
    } else if (mode == 2) {
        n = rnd.next(4, 20);
        a = randomString(n, "abcd");

        int l = rnd.next(1, n / 2);
        int r = rnd.next(n / 2, n - 2);
        if (l > r) {
            swap(l, r);
        }

        a[l] = 'x';
        a[r] = 'y';
        b = a;
        reverse(b.begin() + l, b.begin() + r + 1);
    } else if (mode == 3) {
        n = rnd.next(2, 18);
        a = randomString(n, "ab");
        do {
            b = randomString(n, "cd");
        } while (a == b);
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        a = string(n, 'a');
        int l = rnd.next(1, n - 3);
        int r = rnd.next(l + 1, n - 2);
        a[l] = 'b';
        a[r] = 'c';
        b = a;
        reverse(b.begin() + l, b.begin() + r + 1);
    } else {
        n = rnd.next(25, 60);
        a = randomString(n, "abcdefghijklmnopqrstuvwxyz");
        b = a;
        int l = rnd.next(n);
        int r = rnd.next(l, n - 1);
        reverse(b.begin() + l, b.begin() + r + 1);
        forceDifferent(a, b);
    }

    forceDifferent(a, b);

    println(a);
    println(b);

    return 0;
}
