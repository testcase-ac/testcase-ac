#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 3 and 7 for variety
    int T = rnd.next(3, 7);
    vector<int> Ns;

    // Always include edge cases 1 and 100
    Ns.push_back(1);
    Ns.push_back(100);

    // Fill remaining cases with a mix of small and medium/large N
    for (int i = 2; i < T; i++) {
        if (rnd.next() < 0.5) {
            // small N for subtask1
            Ns.push_back(rnd.next(2, 20));
        } else {
            // medium to large N for full task
            Ns.push_back(rnd.next(21, 100));
        }
    }

    // Shuffle to randomize order
    shuffle(Ns.begin(), Ns.end());

    // Output
    println(T);
    for (int n : Ns) {
        println(n);
    }
    return 0;
}
