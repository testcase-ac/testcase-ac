#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000000000000LL;

    // Precompute factorials up to limit (including 0! and 1!)
    vector<long long> fact;
    fact.push_back(1); // 0!
    for (int i = 1; ; ++i) {
        long long nxt = fact.back() * i;
        if (nxt > LIM) break;
        fact.push_back(nxt); // i!
    }

    // Small DP to know which numbers up to MAXDP are representable
    const int MAXDP = 50000;
    vector<int> smallFacts;
    for (long long f : fact)
        if (f <= MAXDP)
            smallFacts.push_back((int)f); // include both 0! and 1! separately

    vector<char> can(MAXDP + 1, 0);
    can[0] = 1;
    for (int w : smallFacts) {
        for (int s = MAXDP; s >= w; --s) {
            if (can[s - w])
                can[s] = 1;
        }
    }

    // Numbers in [1..MAXDP] that are NOT representable (0 is special: M>=1)
    vector<int> noList;
    for (int i = 1; i <= MAXDP; ++i)
        if (!can[i])
            noList.push_back(i);

    // Precomputed tricky YES-cases that need both 0! and 1!
    // (correct answer YES, but treating 0! and 1! as one coin of value 1 gives NO)
    vector<long long> extras = {
        4, 10, 28, 34,
        124, 130, 148, 154,
        724, 730, 748, 754,
        844, 850, 868, 874
    };

    long long N = 0;
    int type = rnd.next(0, 99);

    if (type < 15) {
        // Very small / hand-checkable, mixed YES/NO
        if (type < 5) {
            N = rnd.next(0, 20);          // tiny numbers including 0
        } else if (type < 10) {
            // Some small tricky YES (first few extras)
            vector<long long> smallExtras = {4, 10, 28, 34};
            N = rnd.any(smallExtras);
        } else {
            // Random up to 40
            N = rnd.next(0, 40);
        }
    } else if (type < 30) {
        // Tricky YES where 0! and 1! must both be available
        N = rnd.any(extras);
    } else if (type < 55) {
        // Guaranteed YES: sum of random non-empty subset of all factorials
        while (true) {
            long long sum = 0;
            bool used = false;
            for (int i = 0; i < (int)fact.size(); ++i) {
                if (rnd.next(0, 1)) {
                    sum += fact[i];
                    used = true;
                }
            }
            if (!used) continue; // avoid empty subset (N=0 not allowed as YES)
            N = sum;
            break;
        }
    } else if (type < 75) {
        // Guaranteed NO with relatively small numbers
        int choice = rnd.next(0, 9);
        if (!noList.empty()) {
            if (choice < 3) {
                // Any NO up to MAXDP
                N = rnd.any(noList);
            } else if (choice < 6) {
                // Prefer small NOs up to 100 if possible
                vector<int> cand;
                for (int x : noList)
                    if (x <= 100)
                        cand.push_back(x);
                if (!cand.empty())
                    N = rnd.any(cand);
                else
                    N = rnd.any(noList);
            } else {
                // NOs close to factorial boundaries (f-1 where that is NO)
                vector<long long> picks;
                for (long long f : fact) {
                    long long x = f - 1;
                    if (1 <= x && x <= MAXDP && !can[(int)x])
                        picks.push_back(x);
                }
                if (!picks.empty())
                    N = rnd.any(picks);
                else
                    N = rnd.any(noList);
            }
        } else {
            // Fallback (should not happen): known small NO
            N = 5;
        }
    } else {
        // Edge / boundary and large values
        int sub = rnd.next(0, 4);
        if (sub == 0) {
            // Explicit impossible: N = 0 (M >= 1)
            N = 0;
        } else if (sub == 1) {
            // Single factorial
            N = fact[rnd.next(0, (int)fact.size() - 1)];
        } else if (sub == 2) {
            // Sum of all factorials
            long long sum = 0;
            for (long long f : fact) sum += f;
            N = sum;
        } else if (sub == 3) {
            // Near the upper limit
            long long offset = rnd.next(0, 1000);
            if (offset > LIM) offset = LIM;
            N = LIM - offset;
        } else {
            // Around the largest factorial <= LIM
            long long f = fact.back();
            long long delta = rnd.next(-5, 5);
            long long cand = f + delta;
            if (cand < 0) cand = 0;
            if (cand > LIM) cand = LIM;
            N = cand;
        }
    }

    println(N);
    return 0;
}
