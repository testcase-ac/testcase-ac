#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int n;

    int scenario = rnd.next(0, 8);

    switch (scenario) {
        case 0: {
            // Very small n
            n = rnd.next(1, 3);
            a.resize(n);
            for (int i = 0; i < n; ++i)
                a[i] = rnd.next(1, 10);
            break;
        }
        case 1: {
            // Strictly increasing
            n = rnd.next(3, 40);
            int cur = rnd.next(1, 10);
            for (int i = 0; i < n; ++i) {
                a.push_back(cur);
                cur += rnd.next(1, 5);
                if (cur > 100000) cur = 100000; // clamp just in case
            }
            break;
        }
        case 2: {
            // Strictly decreasing
            n = rnd.next(3, 40);
            int start = rnd.next(n, 100000);
            for (int i = 0; i < n; ++i)
                a.push_back(start - i);
            break;
        }
        case 3: {
            // All equal
            n = rnd.next(3, 40);
            int val = rnd.next(1, 100000);
            a.assign(n, val);
            break;
        }
        case 4: {
            // Random with small value range and many duplicates
            n = rnd.next(5, 40);
            int lo = rnd.next(1, 5);
            int hi = lo + rnd.next(0, 5);
            hi = min(hi, 20);
            for (int i = 0; i < n; ++i)
                a.push_back(rnd.next(lo, hi));
            break;
        }
        case 5: {
            // Three segments: inc -> noisy low -> inc above first max
            n = rnd.next(8, 40);
            int len1 = rnd.next(2, n - 4);
            int len2 = rnd.next(2, n - len1 - 2);
            int len3 = n - len1 - len2; // >= 2

            int cur = rnd.next(1, 20);
            // first increasing segment
            for (int i = 0; i < len1; ++i) {
                a.push_back(cur);
                cur += rnd.next(1, 4);
                if (cur > 100000) cur = 100000;
            }
            int firstEnd = a.back();

            // middle noisy low segment (mostly below firstEnd)
            for (int i = 0; i < len2; ++i) {
                int val;
                if (rnd.next(0, 3) == 0)
                    val = rnd.next(1, firstEnd); // maybe equal or slightly below
                else
                    val = rnd.next(1, max(1, firstEnd - 1));
                a.push_back(val);
            }

            // last increasing segment above firstEnd
            cur = firstEnd + rnd.next(1, 5);
            if (cur > 100000) cur = 100000;
            for (int i = 0; i < len3; ++i) {
                a.push_back(cur);
                int step = rnd.next(1, 6);
                if (cur + step > 100000) step = max(1, 100000 - cur);
                cur += step;
            }
            break;
        }
        case 6: {
            // Zigzag high-low pattern
            n = rnd.next(5, 40);
            int baseLow = rnd.next(1, 40);
            int baseHigh = rnd.next(max(baseLow + 10, 50), 100000);
            for (int i = 0; i < n; ++i) {
                if (i % 2 == 0) {
                    // high
                    int delta = rnd.next(0, 10);
                    int val = baseHigh - delta;
                    if (val < 1) val = 1;
                    a.push_back(val);
                } else {
                    // low
                    int delta = rnd.next(0, 10);
                    int val = baseLow + delta;
                    if (val > 100000) val = 100000;
                    a.push_back(val);
                }
            }
            break;
        }
        case 7: {
            // Boundary-heavy: many 1s and 100000s with some mids
            n = rnd.next(5, 40);
            int c1 = rnd.next(1, max(1, n / 3));
            int c2 = rnd.next(1, max(1, n / 3));
            int remaining = n - c1 - c2;
            if (remaining < 0) {
                remaining = 0;
                c1 = n / 2;
                c2 = n - c1;
            }
            vector<int> tmp;
            tmp.insert(tmp.end(), c1, 1);
            tmp.insert(tmp.end(), c2, 100000);
            for (int i = 0; i < remaining; ++i)
                tmp.push_back(rnd.next(2, 99999));
            shuffle(tmp.begin(), tmp.end());
            a = tmp;
            break;
        }
        case 8: {
            // Medium n, fully random wide range
            n = rnd.next(20, 40);
            for (int i = 0; i < n; ++i)
                a.push_back(rnd.next(1, 100000));
            break;
        }
    }

    n = (int)a.size();
    println(n);
    println(a);

    return 0;
}
