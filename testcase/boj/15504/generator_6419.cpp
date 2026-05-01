#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with variability: small, medium, or larger (but <=20 for manual readability)
    int mode = rnd.next(0, 2);
    int N;
    if (mode == 0) {
        N = rnd.next(3, 5);
    } else if (mode == 1) {
        N = rnd.next(6, 12);
    } else {
        N = rnd.next(13, 20);
    }

    // Generate distinct skills A_i
    vector<int> A(N);
    int rawAmaxChoices[] = {20, 100, 1000000};
    vector<int> aPool(rawAmaxChoices, rawAmaxChoices + 3);
    int Amax = rnd.any(aPool);
    Amax = max(Amax, N + 1);
    set<int> used;
    for (int i = 0; i < N; i++) {
        int x;
        do {
            x = rnd.next(1, Amax);
        } while (used.count(x));
        used.insert(x);
        A[i] = x;
    }
    // Shuffle to avoid sorted order
    shuffle(A.begin(), A.end());

    // Generate fatigue H_i with variable scale
    int rawHmaxChoices[] = {5, 100, 1000000};
    vector<int> hPool(rawHmaxChoices, rawHmaxChoices + 3);
    int Hmax = rnd.any(hPool);
    Hmax = max(Hmax, 1);
    vector<int> H(N);
    for (int i = 0; i < N; i++) {
        H[i] = rnd.next(1, Hmax);
    }

    // Generate match limits L_i (2 <= L_i <= N-1)
    vector<int> L(N);
    for (int i = 0; i < N; i++) {
        L[i] = rnd.next(2, N - 1);
    }

    // Output in required format
    println(N);
    println(A);
    println(H);
    println(L);

    return 0;
}
