#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<int> Ns(T);

    // Predefined sets to guarantee both win/lose cases
    vector<int> losing = {4, 8, 12, 16, 20};
    vector<int> winning = {1, 5, 9, 13, 17};

    // Ranges for random generation
    vector<pair<int,int>> ranges = {
        {1, 1},    // trivial
        {2, 5},    // small
        {6, 10},   // medium
        {11, 20}   // larger
    };

    if (T == 1) {
        // Single case: randomly pick win or lose scenario
        if (rnd.next() < 0.5)
            Ns[0] = rnd.any(losing);
        else
            Ns[0] = rnd.any(winning);
    } else {
        // Ensure at least one losing and one winning case
        Ns[0] = rnd.any(losing);
        Ns[1] = rnd.any(winning);
        // Fill the rest randomly
        for (int i = 2; i < T; ++i) {
            double p = rnd.next();
            int idx;
            if (p < 0.1) idx = 0;
            else if (p < 0.4) idx = 1;
            else if (p < 0.8) idx = 2;
            else idx = 3;
            auto pr = ranges[idx];
            Ns[i] = rnd.next(pr.first, pr.second);
        }
    }

    // Output
    println(T);
    for (int x : Ns) println(x);

    return 0;
}
