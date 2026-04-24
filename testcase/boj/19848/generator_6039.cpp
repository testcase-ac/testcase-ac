#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // half length between 1 and 15, total length is even between 2 and 30
    int n2 = rnd.next(1, 15);
    int n = 2 * n2;

    // Depending on n2, pick modes; only simple modes if n2==1
    int max_mode = (n2 >= 2 ? 6 : 3);
    int mode = rnd.next(0, max_mode);

    vector<char> s;
    switch (mode) {
        // 0: block 0s then 1s
        case 0: {
            for (int i = 0; i < n2; i++) s.push_back('0');
            for (int i = 0; i < n2; i++) s.push_back('1');
            break;
        }
        // 1: block 1s then 0s
        case 1: {
            for (int i = 0; i < n2; i++) s.push_back('1');
            for (int i = 0; i < n2; i++) s.push_back('0');
            break;
        }
        // 2: alternating
        case 2: {
            char b = rnd.next(0,1) ? '1' : '0';
            char o = (b == '0' ? '1' : '0');
            for (int i = 0; i < n; i++) {
                s.push_back((i % 2 == 0) ? b : o);
            }
            break;
        }
        // 3: fully random shuffle
        case 3: {
            s.reserve(n);
            for (int i = 0; i < n2; i++) s.push_back('0');
            for (int i = 0; i < n2; i++) s.push_back('1');
            shuffle(s.begin(), s.end());
            break;
        }
        // 4: block + random remainder
        case 4: {
            // choose a small inner block, either 0->1 or 1->0
            char a = rnd.next(0,1) ? '1' : '0';
            char b = (a == '0' ? '1' : '0');
            int k = rnd.next(1, n2-1);
            for (int i = 0; i < k; i++) s.push_back(a);
            for (int i = 0; i < k; i++) s.push_back(b);
            int rem = n2 - k;
            vector<char> tmp;
            tmp.reserve(2*rem);
            for (int i = 0; i < rem; i++) tmp.push_back('0');
            for (int i = 0; i < rem; i++) tmp.push_back('1');
            shuffle(tmp.begin(), tmp.end());
            for (char c : tmp) s.push_back(c);
            break;
        }
        // 5: random prefix + block suffix
        case 5: {
            char a = rnd.next(0,1) ? '1' : '0';
            char b = (a == '0' ? '1' : '0');
            int k = rnd.next(1, n2-1);
            int rem = n2 - k;
            vector<char> tmp;
            tmp.reserve(2*rem);
            for (int i = 0; i < rem; i++) tmp.push_back('0');
            for (int i = 0; i < rem; i++) tmp.push_back('1');
            shuffle(tmp.begin(), tmp.end());
            for (char c : tmp) s.push_back(c);
            for (int i = 0; i < k; i++) s.push_back(a);
            for (int i = 0; i < k; i++) s.push_back(b);
            break;
        }
        // 6: interleaved blocks of equal sizes summing to n2
        case 6: {
            int t = rnd.next(1, n2);
            vector<int> parts(t, 1);
            int rem = n2 - t;
            for (int i = 0; i < rem; i++) {
                int idx = rnd.next(0, t-1);
                parts[idx]++;
            }
            for (int x : parts) {
                for (int i = 0; i < x; i++) s.push_back('0');
                for (int i = 0; i < x; i++) s.push_back('1');
            }
            break;
        }
    }

    // Output the string S
    string out;
    out.reserve(n);
    for (char c : s) out.push_back(c);
    printf("%s\n", out.c_str());
    return 0;
}
