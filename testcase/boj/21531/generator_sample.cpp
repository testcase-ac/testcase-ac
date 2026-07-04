#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static string randomDigits(int n) {
    string c;
    c += char('1' + rnd.next(9));
    for (int i = 1; i < n; ++i) {
        c += char('0' + rnd.next(10));
    }
    return c;
}

static string repeatedDigit(int n) {
    char d = char('1' + rnd.next(9));
    return string(n, d);
}

static string alternatingDigits(int n) {
    char a = char('1' + rnd.next(9));
    char b = char('0' + rnd.next(10));
    if (b == a) {
        b = char('0' + ((b - '0' + rnd.next(1, 9)) % 10));
    }

    string c;
    for (int i = 0; i < n; ++i) {
        c += (i % 2 == 0 ? a : b);
    }
    return c;
}

static string carryHeavy(int n) {
    vector<string> motifs = {"9", "90", "99", "109", "190", "909", "990"};
    string motif = rnd.any(motifs);
    string c;
    while ((int)c.size() < n) {
        c += motif;
    }
    c.resize(n);
    if (c[0] == '0') {
        c[0] = char('1' + rnd.next(9));
    }
    return c;
}

static string powerOfTenLike(int n) {
    string c(n, '0');
    c[0] = '1';
    if (n > 1 && rnd.next(2) == 1) {
        int pos = rnd.next(1, n - 1);
        c[pos] = char('1' + rnd.next(9));
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (rnd.next(100) < 75) {
        n = rnd.next(1, 25);
    } else {
        n = rnd.next(26, 120);
    }

    string c;
    if (mode == 0) {
        c = randomDigits(n);
    } else if (mode == 1) {
        c = repeatedDigit(n);
    } else if (mode == 2) {
        c = alternatingDigits(n);
    } else if (mode == 3) {
        c = carryHeavy(n);
    } else if (mode == 4) {
        c = powerOfTenLike(n);
    } else {
        vector<string> small = {"1", "2", "9", "10", "11", "18", "19", "20", "21", "22", "99", "100"};
        c = rnd.any(small);
    }

    println(c);
    return 0;
}
