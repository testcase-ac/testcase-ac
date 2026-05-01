#include "testlib.h"
using namespace std;

string randomGear(int len, double pTwo) {
    string s;
    s.reserve(len);
    int threshold = int(pTwo * 1000 + 0.5);
    for (int i = 0; i < len; i++) {
        int x = rnd.next(0, 999);
        s += (x < threshold ? '2' : '1');
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s1, s2;

    int type = rnd.next(1, 7);

    // helper lambdas
    auto computeWidths = [](const string& a, const string& b,
                            int& ansAll, int& ansNeg, int& ansNonNeg) {
        int n = (int)a.size();
        int m = (int)b.size();
        const int INF = 1e9;
        ansAll = ansNeg = ansNonNeg = INF;

        for (int shift = -m; shift <= n; ++shift) {
            bool ok = true;
            for (int i = 0; i < m && ok; ++i) {
                int j = i + shift;
                if (0 <= j && j < n) {
                    if (a[j] == '2' && b[i] == '2') ok = false;
                }
            }
            if (!ok) continue;
            int left = min(0, shift);
            int right = max(n, shift + m);
            int width = right - left;
            if (width < ansAll) ansAll = width;
            if (shift < 0 && width < ansNeg) ansNeg = width;
            if (shift >= 0 && width < ansNonNeg) ansNonNeg = width;
        }
    };

    if (type == 1) {
        // Tiny random
        int n1 = rnd.next(1, 5);
        int n2 = rnd.next(1, 5);
        s1 = randomGear(n1, 0.5);
        s2 = randomGear(n2, 0.5);
    } else if (type == 2) {
        // Medium random, more '1's
        int n1 = rnd.next(5, 25);
        int n2 = rnd.next(5, 25);
        double pTwo1 = 0.3;
        double pTwo2 = 0.4;
        s1 = randomGear(n1, pTwo1);
        s2 = randomGear(n2, pTwo2);
    } else if (type == 3) {
        // One all '1', other random and heavy on '2'
        int n1 = rnd.next(3, 20);
        int n2 = rnd.next(3, 20);
        bool firstAllOnes = rnd.next(0, 1);
        if (firstAllOnes) {
            s1 = string(n1, '1');
            s2 = randomGear(n2, 0.7);
        } else {
            s1 = randomGear(n1, 0.7);
            s2 = string(n2, '1');
        }
    } else if (type == 4) {
        // Alternating patterns
        int n1 = rnd.next(5, 20);
        int n2 = rnd.next(5, 20);
        char start1 = rnd.any(string("12"));
        char start2;
        bool sameStart = rnd.next(0, 1);
        if (sameStart) start2 = start1;
        else start2 = (start1 == '1' ? '2' : '1');

        s1.resize(n1);
        s2.resize(n2);
        for (int i = 0; i < n1; i++) {
            if (i % 2 == 0) s1[i] = start1;
            else s1[i] = (start1 == '1' ? '2' : '1');
        }
        for (int i = 0; i < n2; i++) {
            if (i % 2 == 0) s2[i] = start2;
            else s2[i] = (start2 == '1' ? '2' : '1');
        }
    } else if (type == 5) {
        // Containment: s2 fits entirely inside s1 without collision
        int n1 = rnd.next(5, 25);
        int n2 = rnd.next(2, n1);
        s1 = randomGear(n1, rnd.next(0, 1) ? 0.3 : 0.6);

        int offset = rnd.next(0, n1 - n2);
        s2.assign(n2, '1');
        for (int i = 0; i < n2; i++) {
            char c = s1[offset + i];
            if (c == '2') {
                s2[i] = '1';
            } else {
                s2[i] = (rnd.next(0, 1) ? '1' : '2');
            }
        }
    } else if (type == 6) {
        // Best alignment requires negative shift
        bool built = false;
        for (int tries = 0; tries < 500 && !built; ++tries) {
            int n1 = rnd.next(3, 15);
            int n2 = rnd.next(3, 15);
            double p1 = 0.3 + 0.4 * rnd.next(0, 1000) / 1000.0;
            double p2 = 0.3 + 0.4 * rnd.next(0, 1000) / 1000.0;
            string a = randomGear(n1, p1);
            string b = randomGear(n2, p2);

            int allW, negW, nonNegW;
            computeWidths(a, b, allW, negW, nonNegW);
            if (allW < 1000000000 && negW < 1000000000 && allW == negW &&
                (nonNegW == 1000000000 || allW < nonNegW)) {
                s1 = a;
                s2 = b;
                built = true;
            }
        }
        if (!built) {
            // Fallback to medium random
            int n1 = rnd.next(5, 25);
            int n2 = rnd.next(5, 25);
            s1 = randomGear(n1, 0.5);
            s2 = randomGear(n2, 0.5);
        }
    } else if (type == 7) {
        // Any overlapping shift causes collision -> only disjoint placement works
        bool built = false;
        for (int tries = 0; tries < 500 && !built; ++tries) {
            int n1 = rnd.next(3, 12);
            int n2 = rnd.next(3, 12);
            string a = randomGear(n1, 0.7);
            string b = randomGear(n2, 0.7);

            bool validOverlapExists = false;
            int n = n1, m = n2;
            for (int shift = -m + 1; shift <= n - 1 && !validOverlapExists; ++shift) {
                bool ok = true;
                for (int i = 0; i < m && ok; ++i) {
                    int j = i + shift;
                    if (0 <= j && j < n) {
                        if (a[j] == '2' && b[i] == '2') ok = false;
                    }
                }
                if (ok) validOverlapExists = true;
            }
            if (!validOverlapExists) {
                s1 = a;
                s2 = b;
                built = true;
            }
        }
        if (!built) {
            int n1 = rnd.next(5, 20);
            int n2 = rnd.next(5, 20);
            s1 = randomGear(n1, 0.6);
            s2 = randomGear(n2, 0.6);
        }
    }

    println(s1);
    println(s2);

    return 0;
}
