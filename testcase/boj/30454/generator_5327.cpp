#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small sizes for hand-checkability
    int N = rnd.next(1, 10);
    int L = rnd.next(1, 20);

    // Hyper-parameter to skew density of '1's
    int t = rnd.next(-2, 2);
    int densInt = rnd.wnext(1001, t); // in [0..1000], skewed by t
    double p = densInt / 1000.0;      // probability of '1'

    // Prepare strings with some edge patterns
    vector<string> vs;
    if (N >= 1) vs.push_back(string(L, '0')); // all zeros
    if (N >= 2) vs.push_back(string(L, '1')); // all ones
    if (N >= 3) {
        string alt;
        for (int i = 0; i < L; i++)
            alt.push_back((i % 2) ? '1' : '0');
        vs.push_back(alt);                     // alternating
    }
    // Fill the rest randomly
    for (int i = vs.size(); i < N; i++) {
        string s;
        for (int j = 0; j < L; j++) {
            s.push_back(rnd.next() < p ? '1' : '0');
        }
        vs.push_back(s);
    }
    // Shuffle to mix special and random cases
    shuffle(vs.begin(), vs.end());

    // Output
    println(N, L);
    for (auto &s : vs)
        println(s);

    return 0;
}
