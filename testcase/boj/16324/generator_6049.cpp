#include "testlib.h"
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 6);
    string s;
    int64_t a = 0, b = 0, c = 0, d = 0;

    if (mode == 1) {
        // pure string of zeros or ones
        int n = rnd.next(1, 30);
        char ch = rnd.next(0, 1) ? '1' : '0';
        s = string(n, ch);
    } else if (mode == 2) {
        // random bit string
        int n = rnd.next(1, 30);
        s.resize(n);
        for (int i = 0; i < n; i++)
            s[i] = rnd.next(0, 1) ? '1' : '0';
    } else if (mode == 3) {
        // small alternating blocks
        int k = rnd.next(2, 6);
        char cur = rnd.next(0, 1) ? '1' : '0';
        for (int i = 0; i < k; i++) {
            int len = rnd.next(1, 10);
            s += string(len, cur);
            cur = (cur == '0' ? '1' : '0');
        }
    } else if (mode == 4) {
        // fixed counts then shuffle
        int z = rnd.next(1, 20);
        int o = rnd.next(1, 20);
        s.reserve(z + o);
        for (int i = 0; i < z; i++) s.push_back('0');
        for (int i = 0; i < o; i++) s.push_back('1');
        shuffle(s.begin(), s.end());
    } else if (mode == 5) {
        // periodic pattern
        int p = rnd.next(1, 5);
        int p0 = rnd.next(1, p);
        int n = rnd.next(1, 30);
        s.resize(n);
        for (int i = 0; i < n; i++) {
            s[i] = (i % p < p0 ? '0' : '1');
        }
    } else {
        // large block counts (do not build string)
        int64_t z = rnd.next(20000, 31622);
        int64_t o = rnd.next(20000, 31622);
        // ensure within bounds
        a = z * (z - 1) / 2;
        b = z * o;
        c = 0;
        d = o * (o - 1) / 2;
        println(a, b, c, d);
        return 0;
    }

    // compute subsequence counts for small s
    int64_t cnt0 = 0, cnt1 = 0;
    for (char ch : s) {
        if (ch == '0') {
            a += cnt0;
            c += cnt1;
            cnt0++;
        } else {
            b += cnt0;
            d += cnt1;
            cnt1++;
        }
    }
    println(a, b, c, d);
    return 0;
}
