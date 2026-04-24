#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N in [3,30], biased to extremes
    int biasN = rnd.next(0,1) ? +rnd.next(1,3) : -rnd.next(1,3);
    int N = rnd.wnext(28, biasN) + 3;
    // Choose K in [1,N], biased to extremes
    int biasK = rnd.next(0,1) ? +rnd.next(1,3) : -rnd.next(1,3);
    int K = rnd.wnext(N, biasK) + 1;
    // Probability to extend runs of equal lengths
    double pSame = rnd.next(0.0, 1.0);
    // Maximum name length
    vector<int> opts = {5, 10, 15, 20};
    int Lmax = rnd.any(opts);

    // Generate lengths with clustering
    vector<int> len(N);
    len[0] = rnd.next(2, Lmax);
    for (int i = 1; i < N; i++) {
        if (rnd.next() < pSame) {
            len[i] = len[i-1];
        } else {
            len[i] = rnd.next(2, Lmax);
        }
    }
    // Generate names of given lengths
    vector<string> names(N);
    for (int i = 0; i < N; i++) {
        string s;
        for (int j = 0; j < len[i]; j++) {
            s.push_back(char(rnd.next('A', 'Z')));
        }
        names[i] = s;
    }
    // Output
    println(N, K);
    for (auto &s : names) println(s);
    return 0;
}
