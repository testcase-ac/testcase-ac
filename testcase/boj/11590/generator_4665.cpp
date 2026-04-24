#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of strings
    int N = rnd.next(2, 10);
    // Alphabet size (from 'A')
    int K = rnd.next(1, 4);
    // Base string max length
    int Lmax = rnd.next(1, 3);
    // Probabilities for special constructions
    double embedP = rnd.next();
    double palinP = rnd.next();

    // Build alphabet
    string alpha;
    for (int i = 0; i < K; i++) alpha.push_back(char('A' + i));

    vector<string> xs;
    xs.reserve(N);
    for (int i = 0; i < N; i++) {
        double p = rnd.next();
        string s;
        if (i > 0 && p < embedP) {
            // Embed a prior string as prefix and suffix
            int j = rnd.next(0, int(xs.size()) - 1);
            string base = xs[j];
            int midLen = rnd.next(0, Lmax);
            string mid;
            for (int t = 0; t < midLen; t++)
                mid.push_back(alpha[rnd.next(0, K - 1)]);
            s = base + mid + base;
        } else if (p < embedP + palinP) {
            // Create a palindrome
            int halfLen = rnd.next(1, Lmax);
            string half;
            for (int t = 0; t < halfLen; t++)
                half.push_back(alpha[rnd.next(0, K - 1)]);
            string rev = half;
            reverse(rev.begin(), rev.end());
            s = half + rev;
        } else {
            // Pure random string
            int len = rnd.next(1, Lmax);
            for (int t = 0; t < len; t++)
                s.push_back(alpha[rnd.next(0, K - 1)]);
        }
        xs.push_back(s);
    }

    // Output
    println(N);
    for (auto &str : xs)
        println(str);

    return 0;
}
