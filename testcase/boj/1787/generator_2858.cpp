#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Length of string
    int N = rnd.next(1, 10);
    // Build small alphabet
    int alph_size = rnd.next(1, 5);
    string alphabet;
    for (int i = 0; i < alph_size; ++i)
        alphabet.push_back(char('a' + i));
    string s(N, 'a');
    // Decide whether to use a repeating pattern
    bool use_pattern = rnd.next() < 0.7;
    if (use_pattern) {
        // Hyperparameter for pattern length: bias small or large
        int maxP = min(N, 5);
        vector<int> ts = {-1, 0, 1};
        int t = rnd.any(ts);
        int p = rnd.wnext(maxP, t) + 1;  // p in [1..maxP]
        // Generate base pattern
        string pattern;
        for (int i = 0; i < p; ++i)
            pattern.push_back(rnd.any(alphabet));
        // Decide noise probability
        double noise_prob = (rnd.next() < 0.3 ? 0.0 : rnd.next() * 0.5);
        for (int i = 0; i < N; ++i) {
            if (rnd.next() < noise_prob)
                s[i] = rnd.any(alphabet);
            else
                s[i] = pattern[i % p];
        }
    } else {
        // Fully random string
        for (int i = 0; i < N; ++i)
            s[i] = rnd.any(alphabet);
    }
    // Output
    println(N);
    printf("%s\n", s.c_str());
    return 0;
}
