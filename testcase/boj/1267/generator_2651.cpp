#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of calls: 1 to 10
    int N = rnd.next(1, 10);
    vector<int> durations;
    durations.reserve(N);

    // Generate each call duration with occasional boundary values
    for (int i = 0; i < N; i++) {
        int x;
        if (rnd.next(0, 4) == 0) {
            // pick a boundary around 30s or 60s
            vector<int> b = {29, 30, 31, 59, 60, 61};
            x = rnd.any(b);
        } else {
            // general call length
            x = rnd.next(1, 200);
        }
        durations.push_back(x);
    }

    // Output
    println(N);
    for (int i = 0; i < N; i++) {
        if (i) printf(" ");
        printf("%d", durations[i]);
    }
    printf("\n");
    return 0;
}
