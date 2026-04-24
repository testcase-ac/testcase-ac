#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small K and N
    int K = rnd.next(1, 10);
    int N = rnd.next(K, min(20, K + 10));
    // Number of unique values U
    int U = rnd.next(1, K);
    vector<string> uniques;
    // Some tricky prefixes to catch comparator bugs
    vector<string> tricky = {"9", "98", "91", "7", "72", "73", "111", "12"};
    for (int i = 0; i < U; ++i) {
        string s;
        if (rnd.next() < 0.3) {
            // pick a tricky value
            s = rnd.any(tricky);
        } else {
            // generate a random 1-3 digit number (no leading zero)
            int len = rnd.next(1, 3);
            s.push_back(char('1' + rnd.next(0, 8)));
            for (int j = 1; j < len; ++j)
                s.push_back(char('0' + rnd.next(0, 9)));
        }
        uniques.push_back(s);
    }
    // Ensure each unique appears at least once, distribute the rest
    vector<int> count(U, 1);
    for (int i = 0; i < K - U; ++i) {
        int idx = rnd.next(0, U - 1);
        count[idx]++;
    }
    // Build the input list and shuffle
    vector<string> inputVals;
    for (int i = 0; i < U; ++i)
        for (int j = 0; j < count[i]; ++j)
            inputVals.push_back(uniques[i]);
    shuffle(inputVals.begin(), inputVals.end());
    // Output
    println(K, N);
    for (auto &s : inputVals)
        println(s);
    return 0;
}
