#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n = 1;
    string s;

    if (mode == 0) {
        n = rnd.next(1, 12);
        s.resize(n);
        for (char& c : s) c = rnd.next(2) == 0 ? 's' : 't';
    } else if (mode == 1) {
        n = rnd.next(13, 40);
        s.resize(n);
        double tProb = rnd.next(0.15, 0.85);
        for (char& c : s) c = rnd.next() < tProb ? 't' : 's';
    } else if (mode == 2) {
        n = rnd.next(1, 40);
        s.assign(n, 's');
        for (int i = 0; i < (n + 1) / 2; ++i) {
            char c = rnd.next(2) == 0 ? 's' : 't';
            s[i] = c;
            s[n - 1 - i] = c;
        }
    } else if (mode == 3) {
        n = rnd.next(2, 50);
        s.assign(n, 's');
        for (int i = 0; i < (n + 1) / 2; ++i) {
            char c = rnd.next(2) == 0 ? 's' : 't';
            s[i] = c;
            s[n - 1 - i] = c;
        }
        int flips = rnd.next(1, (n + 1) / 2);
        for (int i = 0; i < flips; ++i) {
            int pos = rnd.next(n);
            s[pos] = s[pos] == 's' ? 't' : 's';
        }
    } else if (mode == 4) {
        n = rnd.next(2, 60);
        char first = rnd.next(2) == 0 ? 's' : 't';
        s.resize(n);
        for (int i = 0; i < n; ++i) s[i] = (i % 2 == 0) ? first : (first == 's' ? 't' : 's');
    } else if (mode == 5) {
        n = rnd.next(2, 70);
        s.clear();
        while ((int)s.size() < n) {
            char c = rnd.next(2) == 0 ? 's' : 't';
            int len = rnd.next(1, 8);
            while (len-- > 0 && (int)s.size() < n) s.push_back(c);
        }
    } else {
        n = rnd.next(80, 100);
        s.resize(n);
        double tProb = rnd.next(0.05, 0.95);
        for (char& c : s) c = rnd.next() < tProb ? 't' : 's';
    }

    println(n);
    println(s);

    return 0;
}
