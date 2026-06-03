#include "testlib.h"

#include <string>

using namespace std;

string randomBinaryString(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(char('0' + rnd.next(0, 1)));
    }
    return s;
}

string periodicBinaryString(int n, int period) {
    string base = randomBinaryString(period);
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(base[i % period]);
    }
    return s;
}

string rotateLeft(const string& s, int shift) {
    return s.substr(shift) + s.substr(0, shift);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);

    string a;
    string b;

    if (mode == 0) {
        a = randomBinaryString(n);
        b = randomBinaryString(n);
    } else if (mode == 1) {
        a = string(n, char('0' + rnd.next(0, 1)));
        b = string(n, char('0' + rnd.next(0, 1)));
    } else if (mode == 2) {
        int period = rnd.next(1, n);
        a = periodicBinaryString(n, period);
        b = periodicBinaryString(n, period);
    } else if (mode == 3) {
        b = randomBinaryString(n);
        a = rotateLeft(b, rnd.next(0, n - 1));
    } else if (mode == 4) {
        b = periodicBinaryString(n, rnd.next(1, n));
        a = rotateLeft(b, rnd.next(0, n - 1));
    } else {
        b = randomBinaryString(n);
        a = rotateLeft(b, rnd.next(0, n - 1));
        int flips = rnd.next(1, n);
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] = char('0' + '1' - a[pos]);
        }
    }

    println(a);
    println(b);

    return 0;
}
