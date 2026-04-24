#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Dimensions
    int n = rnd.next(1, 10);
    int m = rnd.next(1, 10);
    // Scenario: 0 = hotspot row, 1 = hotspot column, 2 = uniform
    int scenario = rnd.next(0, 2);
    int hotspotRow = rnd.next(0, n - 1);
    int hotspotCol = rnd.next(0, m - 1);

    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            double p;
            if (scenario == 0) {
                p = (i == hotspotRow ? 0.8 : 0.1);
            } else if (scenario == 1) {
                p = (j == hotspotCol ? 0.8 : 0.1);
            } else {
                p = 0.2;
            }
            bool wantNine = rnd.next() < p;
            vector<char> digits;
            if (wantNine) {
                int len = rnd.next(1, 4);
                int k = rnd.next(1, len);
                digits.resize(len);
                // place k nines
                for (int t = 0; t < k; t++) digits[t] = '9';
                // other digits 0-8
                for (int t = k; t < len; t++) digits[t] = char('0' + rnd.next(0, 8));
            } else {
                int len = rnd.next(1, 4);
                digits.resize(len);
                for (int t = 0; t < len; t++) {
                    digits[t] = char('0' + rnd.next(0, 8));
                }
            }
            // shuffle and fix leading zero
            shuffle(digits.begin(), digits.end());
            if (!digits.empty() && digits[0] == '0') {
                bool fixed = false;
                for (int t = 1; t < (int)digits.size(); t++) {
                    if (digits[t] != '0') {
                        swap(digits[0], digits[t]);
                        fixed = true;
                        break;
                    }
                }
                if (!fixed) {
                    // all zeros -> make first a '1'
                    digits[0] = '1';
                }
            }
            // convert to integer
            int v = 0;
            for (char c : digits) {
                v = v * 10 + (c - '0');
            }
            a[i][j] = v;
        }
    }

    // Output
    println(n, m);
    for (int i = 0; i < n; i++) {
        println(a[i]);
    }
    return 0;
}
