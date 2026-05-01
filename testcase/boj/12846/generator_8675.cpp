#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int lenType = rnd.next(0, 9);
    int n;
    if (lenType <= 3) n = rnd.next(1, 6);        // very small
    else if (lenType <= 7) n = rnd.next(4, 15);  // small / medium
    else n = rnd.next(10, 30);                   // medium

    int pattern = rnd.next(0, 9);

    // Adjust pattern if n is too small for it
    if (n < 2 && (pattern == 1 || pattern == 2 || pattern == 6))
        pattern = 0;
    if (n < 3 && (pattern == 3 || pattern == 4 || pattern == 5 || pattern == 7 || pattern == 8))
        pattern = 0;

    vector<int> t(n, 1);

    switch (pattern) {
        case 0: {
            // Fully random small/medium values
            int choice = rnd.next(0, 3);
            int maxVal;
            if (choice == 0) maxVal = 3;
            else if (choice == 1) maxVal = 10;
            else if (choice == 2) maxVal = 100;
            else maxVal = 1000000;
            for (int i = 0; i < n; ++i)
                t[i] = rnd.next(1, maxVal);
            break;
        }
        case 1: {
            // Strictly increasing
            int start = rnd.next(1, 1000000 / max(1, n));
            int denom = max(1, n - 1);
            int maxStep = max(1, (1000000 - start) / denom);
            int step = rnd.next(1, maxStep);
            for (int i = 0; i < n; ++i)
                t[i] = start + i * step;
            break;
        }
        case 2: {
            // Strictly decreasing
            int start = rnd.next(n, 1000000);
            int denom = max(1, n - 1);
            int maxStep = max(1, (start - 1) / denom);
            int step = rnd.next(1, maxStep);
            for (int i = 0; i < n; ++i)
                t[i] = start - i * step;
            break;
        }
        case 3: {
            // Valley: high - low - high
            int left = rnd.next(1, n - 2);
            int right = n - 1 - left;
            int low = rnd.next(1, 1000);
            int high = rnd.next(low + 1, low + 1000);
            for (int i = 0; i < left; ++i)
                t[i] = rnd.next(low + 1, high);
            t[left] = low;
            for (int i = left + 1; i < n; ++i)
                t[i] = rnd.next(low + 1, high);
            break;
        }
        case 4: {
            // Mountain: low - high - low
            int peakPos = rnd.next(1, n - 2);
            int low = rnd.next(1, 1000);
            int high = rnd.next(low + 1, low + 1000);
            for (int i = 0; i < n; ++i) {
                if (i == peakPos) t[i] = high;
                else t[i] = rnd.next(low, high - 1);
            }
            break;
        }
        case 5: {
            // Plateaus: several constant segments
            int segments = rnd.next(1, min(5, n));
            vector<int> lens;
            int rem = n;
            for (int i = 0; i < segments; ++i) {
                int len;
                if (i == segments - 1) {
                    len = rem;
                } else {
                    int maxLen = rem - (segments - i - 1);
                    len = rnd.next(1, maxLen);
                }
                lens.push_back(len);
                rem -= len;
            }
            vector<int> vals(segments);
            for (int i = 0; i < segments; ++i)
                vals[i] = rnd.next(1, 1000);

            // Sometimes make segments non-decreasing to create large monotone areas
            if (rnd.next(0, 1) == 1)
                sort(vals.begin(), vals.end());

            int idx = 0;
            for (int s = 0; s < segments; ++s) {
                for (int k = 0; k < lens[s]; ++k)
                    t[idx++] = vals[s];
            }
            break;
        }
        case 6: {
            // Alternating high / low
            int low = rnd.next(1, 1000);
            int high = rnd.next(low + 1, low + 1000);
            bool startHigh = rnd.next(0, 1);
            for (int i = 0; i < n; ++i) {
                bool highHere = (i % 2 == 0 ? startHigh : !startHigh);
                t[i] = highHere ? high : low;
            }
            break;
        }
        case 7: {
            // One deep hole in otherwise high area
            int low = rnd.next(1, 500000);
            int high = rnd.next(low + 1, 1000000);
            for (int i = 0; i < n; ++i)
                t[i] = high;
            int pos = rnd.next(0, n - 1);
            t[pos] = low;
            break;
        }
        case 8: {
            // One very tall bar in otherwise low area
            int low = rnd.next(1, 500000);
            int high = rnd.next(low + 1, 1000000);
            for (int i = 0; i < n; ++i)
                t[i] = low;
            int pos = rnd.next(0, n - 1);
            t[pos] = high;
            break;
        }
        case 9: {
            // All equal
            int upper;
            int c = rnd.next(0, 3);
            if (c == 0) upper = 10;
            else if (c == 1) upper = 1000;
            else upper = 1000000;
            int val = rnd.next(1, upper);
            for (int i = 0; i < n; ++i)
                t[i] = val;
            break;
        }
    }

    println(n);
    println(t);

    return 0;
}
