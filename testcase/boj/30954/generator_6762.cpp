#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of stacks and cards
    int k = rnd.next(3, 8);
    int n = rnd.next(1, 30);
    // Generate capacities Ci such that sum(C) - max(C) >= n
    vector<int> C(k);
    while (true) {
        for (int i = 0; i < k; i++) {
            C[i] = rnd.next(1, n);
        }
        int sumC = accumulate(C.begin(), C.end(), 0);
        int maxC = *max_element(C.begin(), C.end());
        if (sumC - maxC >= n) break;
    }
    // Distribute n cards into stacks respecting capacities
    vector<int> suffixCap(k);
    suffixCap[k-1] = 0;
    for (int i = k - 2; i >= 0; i--) {
        suffixCap[i] = suffixCap[i+1] + C[i+1];
    }
    vector<int> a(k);
    int rem = n;
    for (int i = 0; i < k; i++) {
        if (i == k - 1) {
            a[i] = rem;
        } else {
            int minCards = max(0, rem - suffixCap[i]);
            int maxCards = min(C[i], rem);
            a[i] = rnd.next(minCards, maxCards);
            rem -= a[i];
        }
    }
    // Prepare a random permutation of cards
    vector<int> cards(n);
    for (int i = 0; i < n; i++) cards[i] = i + 1;
    shuffle(cards.begin(), cards.end());
    // Output
    println(n, k);
    int ptr = 0;
    for (int i = 0; i < k; i++) {
        // Print capacity and contents (bottom to top, zeros for empty)
        printf("%d", C[i]);
        for (int j = 0; j < a[i]; j++) {
            printf(" %d", cards[ptr++]);
        }
        for (int j = a[i]; j < C[i]; j++) {
            printf(" 0");
        }
        printf("\n");
    }
    return 0;
}
