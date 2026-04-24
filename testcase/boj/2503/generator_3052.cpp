#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

// Count strikes and balls between guess g and secret s
pair<int,int> countSB(int g, int s) {
    int ga[3] = { g/100, (g/10)%10, g%10 };
    int sa[3] = { s/100, (s/10)%10, s%10 };
    int strikes = 0, balls = 0;
    for (int i = 0; i < 3; i++) {
        if (ga[i] == sa[i]) {
            strikes++;
        } else {
            for (int j = 0; j < 3; j++) {
                if (i != j && ga[i] == sa[j]) {
                    balls++;
                }
            }
        }
    }
    return {strikes, balls};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Build all valid numbers: 3 distinct digits from 1..9
    vector<int> candidates;
    for (int d1 = 1; d1 <= 9; d1++) {
        for (int d2 = 1; d2 <= 9; d2++) if (d2 != d1) {
            for (int d3 = 1; d3 <= 9; d3++) if (d3 != d1 && d3 != d2) {
                candidates.push_back(d1*100 + d2*10 + d3);
            }
        }
    }

    // Pick the secret number
    int secret = rnd.any(candidates);

    // Build available guesses (exclude the secret)
    vector<int> avail = candidates;
    avail.erase(find(avail.begin(), avail.end(), secret));

    // Number of questions
    int N = rnd.next(1, 6);

    // Hyper-parameters for diversity
    int w_high = rnd.next(1, 5); // weight for high-similarity guesses (>=2 strikes)
    int w_mid  = rnd.next(1, 5); // weight for medium-similarity guesses (1 ball/strike)
    int w_low  = rnd.next(1, 5); // weight for low-similarity guesses (0 matches)
    int sumw = w_high + w_mid + w_low;

    vector<tuple<int,int,int>> queries;
    for (int qi = 0; qi < N; qi++) {
        // Partition available guesses by similarity to secret
        vector<int> pool_high, pool_mid, pool_low;
        for (int g : avail) {
            auto sb = countSB(g, secret);
            int s = sb.first, b = sb.second;
            if (s >= 2) {
                pool_high.push_back(g);
            } else if (s + b >= 1) {
                pool_mid.push_back(g);
            } else {
                pool_low.push_back(g);
            }
        }

        // Choose a pool according to weights
        int r = rnd.next(sumw - 1);
        vector<int>* pool;
        if (r < w_high) {
            pool = &pool_high;
        } else if (r < w_high + w_mid) {
            pool = &pool_mid;
        } else {
            pool = &pool_low;
        }
        // Fallback if chosen pool is empty
        if (pool->empty()) {
            if (!pool_mid.empty()) pool = &pool_mid;
            else if (!pool_low.empty()) pool = &pool_low;
            else pool = &pool_high;
        }

        // Pick a guess and compute its feedback
        int guess = rnd.any(*pool);
        auto sb = countSB(guess, secret);
        queries.emplace_back(guess, sb.first, sb.second);

        // Remove the chosen guess from avail
        avail.erase(find(avail.begin(), avail.end(), guess));
    }

    // Output the generated test case
    println(N);
    for (auto &t : queries) {
        int g, s, b;
        tie(g, s, b) = t;
        println(g, s, b);
    }

    return 0;
}
