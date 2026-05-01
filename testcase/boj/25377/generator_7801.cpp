#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a subtask scenario for diversity
    int scenario = rnd.next(1, 6);

    int N;
    if (scenario == 1) {
        // Subtask 1: N = 1
        N = 1;
    } else {
        // Other subtasks: small N for manual verification
        N = rnd.next(2, 10);
    }

    vector<pair<int,int>> stores;
    stores.reserve(N);

    for (int i = 0; i < N; i++) {
        int A, B;
        switch (scenario) {
            case 1:
                // Single store, arbitrary times
                A = rnd.next(0, 1000);
                B = rnd.next(0, 1000);
                break;
            case 2:
                // Subtask 2: all A = 0
                A = 0;
                B = rnd.next(0, 1000);
                break;
            case 3:
                // Subtask 3: all B = 10
                A = rnd.next(0, 1000);
                B = 10;
                break;
            case 4:
                // Subtask 4: all A > B (impossible to get bread)
                A = rnd.next(1, 1000);
                B = rnd.next(0, A - 1);
                break;
            case 5:
                // Subtask 5: all A <= B (always possible)
                A = rnd.next(0, 1000);
                B = rnd.next(A, 1000);
                break;
            case 6:
            default:
                // General case
                A = rnd.next(0, 1000);
                B = rnd.next(0, 1000);
                break;
        }
        stores.emplace_back(A, B);
    }

    // Shuffle to avoid ordered patterns
    shuffle(stores.begin(), stores.end());

    // Output
    println(N);
    for (auto &p : stores) {
        println(p.first, p.second);
    }

    return 0;
}
