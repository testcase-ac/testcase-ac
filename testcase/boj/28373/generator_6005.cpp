#include "testlib.h"
#include <algorithm>
#include <vector>
#include <string>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Sample length N: mix small and medium sizes for variability
    int N;
    if (rnd.next() < 0.4) {
        // small string
        N = rnd.next(1, min(5, 20));
    } else {
        // medium string
        N = rnd.next(1, 20);
    }
    // At most 3 occurrences of 'S'
    int maxS = min(3, N);
    // Choose number of 'S' occurrences with weighted probabilities
    int k;
    double r = rnd.next();
    if (r < 0.3) k = 0;
    else if (r < 0.6) k = 1;
    else if (r < 0.85) k = min(2, maxS);
    else k = maxS;

    // Prepare positions 0..N-1
    vector<int> pos(N);
    iota(pos.begin(), pos.end(), 0);
    vector<bool> isS(N, false);

    // Place the 'S's either contiguously or at random distinct positions
    if (k > 0) {
        if (k >= 2 && rnd.next() < 0.5) {
            int start = rnd.next(0, N - k);
            for (int i = 0; i < k; i++)
                isS[start + i] = true;
        } else {
            shuffle(pos.begin(), pos.end());
            for (int i = 0; i < k; i++)
                isS[pos[i]] = true;
        }
    }

    // Build the uppercase string
    string s;
    s.resize(N);
    for (int i = 0; i < N; i++) {
        if (isS[i]) {
            s[i] = 'S';
        } else {
            char c;
            do {
                c = char(rnd.next('A', 'Z'));
            } while (c == 'S');
            s[i] = c;
        }
    }

    // Output the generated test case
    println(s);
    return 0;
}
