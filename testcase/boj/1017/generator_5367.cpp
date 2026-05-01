#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose an even N between 2 and 10
    int N2 = rnd.next(1, 5);
    int N = N2 * 2;
    // Choose a maximum value for the elements
    int low = 20;
    if (low < N + 5) low = N + 5;
    int maxval = rnd.next(low, 100);

    // Sieve primes up to 2*maxval
    int maxp = 2 * maxval;
    vector<bool> is_prime(maxp + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= maxp; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= maxp; j += i)
                is_prime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= maxp; ++i)
        if (is_prime[i])
            primes.push_back(i);

    // Build odd and even pools
    vector<int> odd_list, even_list;
    for (int i = 1; i <= maxval; ++i) {
        if (i & 1) odd_list.push_back(i);
        else       even_list.push_back(i);
    }

    bool solvable = rnd.next(0, 1);
    vector<int> result;

    if (solvable) {
        // Build N/2 pairs (odd, even) with prime sums
        set<int> used;
        vector<pair<int,int>> pairs;
        while (true) {
            used.clear();
            pairs.clear();
            bool fail = false;
            for (int k = 0; k < N2; ++k) {
                bool found = false;
                for (int it = 0; it < 1000; ++it) {
                    int o = rnd.any(odd_list);
                    int e = rnd.any(even_list);
                    if (used.count(o) || used.count(e)) continue;
                    int s = o + e;
                    if (s <= maxp && is_prime[s]) {
                        used.insert(o);
                        used.insert(e);
                        pairs.emplace_back(o, e);
                        found = true;
                        break;
                    }
                }
                if (!found) { fail = true; break; }
            }
            if (!fail) {
                for (auto &pr : pairs) {
                    result.push_back(pr.first);
                    result.push_back(pr.second);
                }
                break;
            }
        }
    } else {
        // Make it unsolvable by unbalancing odd/even count
        int cnt_odd = rnd.next(0, N);
        if (cnt_odd == N2) {
            if (cnt_odd > 0) cnt_odd--;
            else             cnt_odd++;
        }
        int cnt_even = N - cnt_odd;
        ::shuffle(odd_list.begin(), odd_list.end());
        ::shuffle(even_list.begin(), even_list.end());
        for (int i = 0; i < cnt_odd; ++i)  result.push_back(odd_list[i]);
        for (int i = 0; i < cnt_even; ++i) result.push_back(even_list[i]);
    }

    // Final shuffle and output
    ::shuffle(result.begin(), result.end());
    println(N);
    println(result);

    return 0;
}
