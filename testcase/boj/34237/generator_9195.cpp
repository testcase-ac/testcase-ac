#include "testlib.h"
using namespace std;

struct Match {
    int g, x, y;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3); // 4 modes: 0,1,2,3

    int N = 0, M = 0;
    vector<pair<int,int>> bets;
    vector<Match> matches;

    if (mode == 0) {
        // Hand-crafted small case with various edge situations
        N = 5;
        M = 7;

        bets.push_back({0, 0});
        bets.push_back({1, 0});
        bets.push_back({2, 0});
        bets.push_back({2, 1});
        bets.push_back({3, 2});

        matches.push_back({0, 0, 0});
        matches.push_back({1, 0, 0});
        matches.push_back({2, 1, 0});
        matches.push_back({3, 2, 1});
        matches.push_back({3, 0, 0});
        matches.push_back({5, 3, 1});
        matches.push_back({10, 0, 0});
    }
    else if (mode == 1) {
        // Structured grid of bets with small max sum
        int maxSum = rnd.next(4, 10);

        vector<pair<int,int>> cand;
        for (int a = 0; a <= maxSum; ++a) {
            int bMax = min(a, maxSum - a);
            for (int b = 0; b <= bMax; ++b) {
                cand.push_back({a, b});
            }
        }

        shuffle(cand.begin(), cand.end());

        int maxN = min(15, (int)cand.size());
        int minN = min(5, maxN);
        N = rnd.next(minN, maxN);

        bets.assign(cand.begin(), cand.begin() + N);

        M = rnd.next(5, 15);

        // Query 1: all bets potentially winning (g = maxSum, start 0:0)
        if (M >= 1) {
            matches.push_back({maxSum, 0, 0});
        }

        // Query 2: smaller g to cut by sum constraint
        if (M >= 2) {
            int g2 = maxSum / 2;
            matches.push_back({g2, 0, 0});
        }

        // Query 3: equality query on a random bet
        if (M >= 3) {
            auto bet = rnd.any(bets);
            int a = bet.first;
            int b = bet.second;
            matches.push_back({a + b, a, b});
        }

        // Remaining queries: random but respecting constraints
        while ((int)matches.size() < M) {
            int g = rnd.next(0, min(100, maxSum + 5));
            int s = rnd.next(0, g);
            int y = 0;
            if (s > 0) y = rnd.next(0, s / 2);
            int x = s - y; // x >= y, x + y = s <= g
            matches.push_back({g, x, y});
        }
    }
    else if (mode == 2) {
        // Random bets with sum >= 1 to allow a guaranteed 0-answer query
        N = rnd.next(3, 10);
        int maxSum = rnd.next(3, 20);

        for (int i = 0; i < N; ++i) {
            while (true) {
                int a = rnd.next(0, maxSum);
                int bMax = min(a, maxSum - a);
                int b = rnd.next(0, bMax);
                if (a + b > 0) {
                    bets.push_back({a, b});
                    break;
                }
            }
        }

        M = rnd.next(5, 15);

        // First query: g = 0, x = 0, y = 0 -> no winner because all sums >= 1
        matches.push_back({0, 0, 0});

        // Remaining random queries
        while ((int)matches.size() < M) {
            int g = rnd.next(0, 100);
            int s = rnd.next(0, g);
            int y = 0;
            if (s > 0) y = rnd.next(0, s / 2);
            int x = s - y;
            matches.push_back({g, x, y});
        }
    }
    else { // mode == 3
        // Random medium-sized case with wide value range
        N = rnd.next(10, 20);
        int maxSum = rnd.next(20, 100);

        int maxSumBets = 0;

        bool forceZero = (rnd.next(0, 1) == 0);
        for (int i = 0; i < N; ++i) {
            int a, b;
            if (i == 0 && forceZero) {
                a = 0; b = 0;
            } else {
                a = rnd.next(0, maxSum);
                int bMax = min(a, maxSum - a);
                b = rnd.next(0, bMax);
            }
            bets.push_back({a, b});
            maxSumBets = max(maxSumBets, a + b);
        }

        M = rnd.next(10, 20);

        // Random queries first
        for (int i = 0; i < M; ++i) {
            int g = rnd.next(0, 100);
            int s = rnd.next(0, g);
            int y = 0;
            if (s > 0) y = rnd.next(0, s / 2);
            int x = s - y;
            matches.push_back({g, x, y});
        }

        // Ensure first query allows all bets to win (x=y=0, g large enough)
        int gAll = min(100, maxSumBets + rnd.next(0, 100 - maxSumBets));
        matches[0] = {gAll, 0, 0};
    }

    // Optional shuffling for extra variability
    if (!bets.empty() && rnd.next(0, 1) == 1) {
        shuffle(bets.begin(), bets.end());
    }
    if (!matches.empty() && rnd.next(0, 1) == 1) {
        shuffle(matches.begin(), matches.end());
    }

    // Output
    println(N, M);
    for (int i = 0; i < N; ++i) {
        println(bets[i].first, bets[i].second);
    }
    for (int j = 0; j < M; ++j) {
        println(matches[j].g, matches[j].x, matches[j].y);
    }

    return 0;
}
