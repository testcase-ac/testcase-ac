#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: probability of low scores (<40)
    double pLow = rnd.next(0.0, 1.0);
    vector<int> scores;
    for (int i = 0; i < 5; i++) {
        if (rnd.next() < pLow) {
            // Low score: 0,5,...,35
            int idx = rnd.next(0, 7);
            scores.push_back(idx * 5);
        } else {
            // High score: 40,45,...,100
            int idx = rnd.next(8, 20);
            scores.push_back(idx * 5);
        }
    }

    // Output each score on its own line
    for (int s : scores) {
        println(s);
    }
    return 0;
}
