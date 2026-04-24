#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    for (int tc = 0; tc < T; tc++) {
        // Number of candy types
        int n = rnd.next(1, 10);
        // Total money in cents, skewed sometimes
        int m_cents;
        if (rnd.next(1) == 0) {
            // uniform
            m_cents = rnd.next(1, 2000);
        } else {
            // skew to high
            m_cents = rnd.wnext(2000, 1);
            if (m_cents < 1) m_cents = 1;
        }
        double m = m_cents / 100.0;
        // Choose price max for candies: either <= m or may exceed
        int priceMaxCents;
        if (rnd.next(2) == 0) {
            priceMaxCents = rnd.next(1, m_cents);
        } else {
            priceMaxCents = rnd.next(m_cents, 2000);
        }
        // Calorie bounds
        int c_lo = rnd.next(1, 2000);
        int c_hi = rnd.next(c_lo, 5000);
        // Generate candies
        vector<pair<int,int>> candies;
        vector<int> Tvals = {-1, 0, 1};
        for (int i = 0; i < n; i++) {
            // price
            int t_p = rnd.any(Tvals);
            int off_p = rnd.wnext(priceMaxCents, t_p);
            int p_cents = off_p + 1;
            // calories
            int range = c_hi - c_lo + 1;
            int t_c = rnd.any(Tvals);
            int off_c = rnd.wnext(range, t_c);
            int c = c_lo + off_c;
            candies.emplace_back(c, p_cents);
        }
        // Shuffle to avoid any order
        shuffle(candies.begin(), candies.end());
        // Output this test case
        printf("%d %.2f\n", n, m);
        for (auto &pr : candies) {
            printf("%d %.2f\n", pr.first, pr.second / 100.0);
        }
    }
    // Termination line
    printf("0 0.00\n");
    return 0;
}
