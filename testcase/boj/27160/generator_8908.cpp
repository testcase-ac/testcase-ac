#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> fruits = {"STRAWBERRY", "BANANA", "LIME", "PLUM"};
    vector<pair<int,int>> cards; // (fruitIndex, count)
    int sums[4] = {0, 0, 0, 0};

    // Choose scenario type for diversity
    // 0: NO, no fruit totals 5
    // 1: YES, single card with 5 of a fruit, no other of that fruit
    // 2: YES, multiple cards of same fruit sum to 5 (no individual 5 for that fruit)
    // 3: NO, there is a card with 5 but same fruit total > 5, and no other fruit totals 5
    // 4: Random medium case (YES or NO)
    int scenario = rnd.next(0, 4);

    if (scenario == 0) {
        // Small NO case: no fruit totals 5
        int N = rnd.next(1, 4);
        for (int i = 0; i < N; i++) {
            int f = rnd.next(0, 3);
            int x = rnd.next(1, 5);
            while (sums[f] + x == 5) {
                x = rnd.next(1, 5);
            }
            sums[f] += x;
            cards.push_back({f, x});
        }
    } else if (scenario == 1) {
        // YES case: exactly one fruit has a card with 5, and no other card of that fruit
        int N = rnd.next(1, 6);
        int ft = rnd.next(0, 3);
        int pos = rnd.next(0, N - 1);

        for (int i = 0; i < N; i++) {
            int f, x;
            if (i == pos) {
                f = ft;
                x = 5;
                sums[f] += x;
            } else {
                do {
                    f = rnd.next(0, 3);
                } while (f == ft); // no other card of this fruit
                x = rnd.next(1, 5);
                // Optional: avoid other fruits totalling 5 to keep focus on the single 5-card
                while (sums[f] + x == 5) {
                    x = rnd.next(1, 5);
                }
                sums[f] += x;
            }
            cards.push_back({f, x});
        }
    } else if (scenario == 2) {
        // YES case: multiple cards of same fruit sum to 5, none individually 5
        int ft = rnd.next(0, 3);
        int k = rnd.next(2, 4); // number of cards for this fruit
        int remain = 5;

        // Build k positive integers <=4 that sum to 5 (k >= 2 guarantees each < 5)
        for (int i = 0; i < k; i++) {
            int x;
            if (i == k - 1) {
                x = remain;
            } else {
                int max_x = min(4, remain - (k - i - 1) * 1);
                x = rnd.next(1, max_x);
            }
            remain -= x;
            sums[ft] += x;
            cards.push_back({ft, x});
        }

        int extra = rnd.next(0, 3);
        for (int i = 0; i < extra; i++) {
            int f;
            do {
                f = rnd.next(0, 3);
            } while (f == ft); // keep total of ft exactly 5

            int x = rnd.next(1, 5);
            // Avoid making other fruits sum exactly 5 too often
            while (sums[f] + x == 5) {
                x = rnd.next(1, 5);
            }
            sums[f] += x;
            cards.push_back({f, x});
        }
    } else if (scenario == 3) {
        // NO case: there is a 5-card, but total for that fruit > 5, and no fruit totals 5
        int N = rnd.next(2, 7);
        int ft = rnd.next(0, 3);

        // First card: the 5-card
        cards.push_back({ft, 5});
        sums[ft] = 5;

        // Second card: same fruit, pushes total > 5
        int x2 = rnd.next(1, 5);
        // sums[ft] is 5, any positive x2 makes it >5, no need for while but keep it safe
        while (sums[ft] + x2 == 5) {
            x2 = rnd.next(1, 5);
        }
        sums[ft] += x2;
        cards.push_back({ft, x2});

        // Remaining cards: ensure no other fruit totals 5
        for (int i = 2; i < N; i++) {
            int f = rnd.next(0, 3);
            int x = rnd.next(1, 5);
            while (sums[f] + x == 5) {
                x = rnd.next(1, 5);
            }
            sums[f] += x;
            cards.push_back({f, x});
        }
    } else {
        // Random medium case
        int N = rnd.next(5, 25);
        for (int i = 0; i < N; i++) {
            int f = rnd.next(0, 3);
            int x = rnd.next(1, 5);
            cards.push_back({f, x});
        }
    }

    // Shuffle card order to avoid patterns
    shuffle(cards.begin(), cards.end());

    int N = (int)cards.size();
    println(N);
    for (auto &p : cards) {
        println(fruits[p.first], p.second);
    }

    return 0;
}
