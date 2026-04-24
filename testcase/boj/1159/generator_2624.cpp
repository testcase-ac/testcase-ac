/* generator code */
#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small N
    int N = rnd.next(1, 15);
    // If N < 5, always PREDAJA case, else randomize
    bool predajaCase = (N < 5) || (rnd.next() < 0.5);

    // Prepare alphabet
    vector<char> alphabet;
    for (char c = 'a'; c <= 'z'; ++c)
        alphabet.push_back(c);
    shuffle(alphabet.begin(), alphabet.end());

    vector<char> assigned;
    if (predajaCase) {
        // Ensure no letter appears 5+ times
        int Kmin = max(1, (N + 3) / 4);
        int Kmax = min(N, (int)alphabet.size());
        int K = rnd.next(Kmin, Kmax);
        vector<char> pool(alphabet.begin(), alphabet.begin() + K);
        // Distribute so each letter ≤4 times
        for (int i = 0; i < N; ++i)
            assigned.push_back(pool[i % K]);
        shuffle(assigned.begin(), assigned.end());
    } else {
        // Ensure at least one letter appears ≥5 times
        int F = rnd.next(5, min(N, 10));
        char c = rnd.any(alphabet);
        for (int i = 0; i < F; ++i)
            assigned.push_back(c);
        int rem = N - F;
        if (rem > 0) {
            vector<char> other;
            for (char x : alphabet)
                if (x != c) other.push_back(x);
            shuffle(other.begin(), other.end());
            int K2 = rnd.next(1, min(rem, 5));
            for (int i = 0; i < rem; ++i)
                assigned.push_back(other[i % K2]);
        }
        shuffle(assigned.begin(), assigned.end());
    }

    // Build random names (first letter fixed, suffix length ≤29 so total ≤30)
    vector<string> names;
    for (char c : assigned) {
        int sufLen = rnd.next(1, 29);
        string s;
        s.push_back(c);
        for (int i = 0; i < sufLen; ++i)
            s.push_back(char('a' + rnd.next(0, 25)));
        names.push_back(s);
    }

    // Output
    println(N);
    for (auto &s : names)
        println(s);

    return 0;
}
