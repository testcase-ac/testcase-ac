#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 40);
    string s;

    if (mode == 0) {
        n = rnd.next(1, 100);
        char c = rnd.next(0, 1) ? '1' : '0';
        s.assign(n, c);
    } else if (mode == 1) {
        n = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            s += char('0' + (i % 2));
        }
        if (rnd.next(0, 1)) {
            for (char& c : s) c = (c == '0' ? '1' : '0');
        }
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        int zeros = rnd.next(1, n - 1);
        s.assign(zeros, '0');
        s.append(n - zeros, '1');
    } else if (mode == 3) {
        n = rnd.next(2, 80);
        int ones = rnd.next(1, n - 1);
        s.assign(ones, '1');
        s.append(n - ones, '0');
    } else if (mode == 4) {
        string block;
        int blockLen = rnd.next(1, 8);
        for (int i = 0; i < blockLen; ++i) {
            block += char('0' + rnd.next(0, 1));
        }
        int reps = rnd.next(1, 100 / blockLen);
        for (int i = 0; i < reps; ++i) s += block;
    } else if (mode == 5) {
        n = rnd.next(1, 100);
        double oneProb = rnd.next(0.1, 0.9);
        for (int i = 0; i < n; ++i) {
            s += (rnd.next() < oneProb ? '1' : '0');
        }
    } else if (mode == 6) {
        vector<string> parts;
        int partCount = rnd.next(2, 8);
        int remaining = rnd.next(partCount, 60);
        for (int i = 0; i < partCount; ++i) {
            int len = (i + 1 == partCount) ? remaining : rnd.next(1, remaining - (partCount - i - 1));
            remaining -= len;
            string part;
            for (int j = 0; j < len; ++j) {
                part += (j == 0 || rnd.next(0, 3) == 0) ? '0' : '1';
            }
            parts.push_back(part);
        }
        sort(parts.rbegin(), parts.rend());
        for (const string& part : parts) s += part;
    } else {
        n = rnd.next(1, 100);
        s.reserve(n);
        char c = rnd.next(0, 1) ? '1' : '0';
        while ((int)s.size() < n) {
            int run = min(rnd.next(1, 8), n - (int)s.size());
            s.append(run, c);
            c = (c == '0' ? '1' : '0');
        }
    }

    println(s);
    return 0;
}
