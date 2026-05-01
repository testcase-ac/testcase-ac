#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of patterns and required matches
    int N = rnd.next(1, 15);
    int K = rnd.next(1, N);
    // Length of each pattern
    int L = rnd.next(1, 12);
    // Probability of placing a question mark
    vector<double> qList = {0.0, 0.2, 0.5, 0.8, 1.0};
    double qProb = rnd.any(qList);
    // Probability to duplicate an existing pattern
    vector<double> dList = {0.0, 0.2, 0.5};
    double dupProb = rnd.any(dList);

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<string> patterns;
    patterns.reserve(N);

    for (int i = 0; i < N; ++i) {
        // Occasionally duplicate a previous pattern
        if (i > 0 && rnd.next() < dupProb) {
            int j = rnd.next(0, (int)patterns.size() - 1);
            patterns.push_back(patterns[j]);
        } else {
            // Generate a fresh pattern
            string s;
            s.reserve(L);
            for (int p = 0; p < L; ++p) {
                if (rnd.next() < qProb)
                    s.push_back('?');
                else
                    s.push_back(alphabet[rnd.next(0, 25)]);
            }
            patterns.push_back(s);
        }
    }
    // Shuffle to randomize order
    shuffle(patterns.begin(), patterns.end());

    // Output
    println(N, K);
    for (auto &s : patterns)
        println(s);

    return 0;
}
