#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(1, 8);

    int N = 0;
    vector<long long> price;
    vector<long long> value;
    long long K = 0;
    vector<int> owned;

    if (mode == 1) {
        // Mode 1: K = 0, random holdings
        N = rnd.next(1, 8);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(1, 20);
            value[i] = rnd.next(1, 20);
        }
        K = 0;
        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        int M = rnd.next(0, N);
        owned.assign(all.begin(), all.begin() + M);
    } else if (mode == 2) {
        // Mode 2: Already satisfied by initial holdings (answer = 0, K > 0)
        N = rnd.next(3, 10);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(1, 30);
            value[i] = rnd.next(1, 30);
        }
        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        int M = rnd.next(1, N);
        owned.assign(all.begin(), all.begin() + M);
        long long sumVal = 0;
        for (int idx : owned) sumVal += value[idx];
        K = rnd.next(1LL, sumVal); // 1 <= K <= current value sum
    } else if (mode == 3) {
        // Mode 3: Impossible case (K > total value)
        N = rnd.next(2, 10);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(1, 30);
            value[i] = rnd.next(1, 30);
        }
        long long sumAll = 0;
        for (int i = 0; i < N; ++i) sumAll += value[i];
        K = sumAll + rnd.next(1, 30); // strictly larger than total value
        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        int M = rnd.next(0, N);
        owned.assign(all.begin(), all.begin() + M);
    } else if (mode == 4) {
        // Mode 4: Simple beneficial trade, one bad owned, one good to buy (answer = 0)
        N = 2;
        price.assign(N, 0);
        value.assign(N, 0);
        price[0] = 5; value[0] = 1;
        price[1] = 5; value[1] = rnd.next(10, 20);
        K = value[1]; // need the good sticker
        owned.clear();
        owned.push_back(0); // own the bad one, can sell and buy the good one with 0 initial money
    } else if (mode == 5) {
        // Mode 5: Need to sell multiple low-value stickers to buy one high-value (answer = 0)
        N = 3;
        price.assign(N, 0);
        value.assign(N, 0);
        price[0] = 5;  value[0] = 1;
        price[1] = 5;  value[1] = 1;
        price[2] = 10; value[2] = rnd.next(15, 30);
        K = value[2];
        owned.clear();
        owned.push_back(0);
        owned.push_back(1); // sell both to buy sticker 2
    } else if (mode == 6) {
        // Mode 6: No initial stickers (M = 0), random solvable / impossible
        N = rnd.next(1, 8);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(1, 50);
            value[i] = rnd.next(1, 50);
        }
        long long sumAll = 0;
        for (int i = 0; i < N; ++i) sumAll += value[i];
        bool solvable = rnd.next(0, 1);
        if (solvable) {
            K = rnd.next(0LL, sumAll); // possible, maybe already K=0
        } else {
            K = sumAll + rnd.next(1, 50);
        }
        owned.clear(); // M = 0
    } else if (mode == 7) {
        // Mode 7: Medium random instance, some structure
        N = rnd.next(8, 15);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(1, 100);
            value[i] = rnd.next(1, 100);
        }
        long long sumAll = 0;
        for (int i = 0; i < N; ++i) sumAll += value[i];
        if (rnd.next(0, 1)) {
            K = rnd.next(0LL, sumAll); // solvable
        } else {
            K = sumAll + rnd.next(1, 50); // impossible
        }
        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        int M = rnd.next(0, N);
        owned.assign(all.begin(), all.begin() + M);
    } else { // mode == 8
        // Mode 8: Large prices/values near constraints, K possibly near 1e9
        N = rnd.next(1, 5);
        price.assign(N, 0);
        value.assign(N, 0);
        for (int i = 0; i < N; ++i) {
            price[i] = rnd.next(20000000, 30000000);
            value[i] = rnd.next(20000000, 30000000);
        }
        long long sumAll = 0;
        for (int i = 0; i < N; ++i) sumAll += value[i];

        if (rnd.next(0, 1)) {
            // Impossible high K, close to upper bound
            K = 1000000000LL;
        } else {
            // Solvable with large values
            K = rnd.next(0LL, min(sumAll, 1000000000LL));
        }

        vector<int> all(N);
        for (int i = 0; i < N; ++i) all[i] = i;
        shuffle(all.begin(), all.end());
        int M = rnd.next(0, N);
        owned.assign(all.begin(), all.begin() + M);
    }

    println(N);
    println(price);
    println(value);
    println(K);
    println((int)owned.size());
    if (!owned.empty()) {
        println(owned);
    }

    return 0;
}
