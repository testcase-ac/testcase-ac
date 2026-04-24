#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for K and N diversity: bias towards small or large
    vector<int> bias = {-2, -1, 0, 1, 2};
    int bK = rnd.any(bias);
    int bN = rnd.any(bias);

    // Generate price K (1 to 20) and count N (1 to 20)
    int K = rnd.wnext(20, bK) + 1;
    int N = rnd.wnext(20, bN) + 1;

    // Total cost
    int total = K * N;

    // Decide if Dongsoo needs money (1) or has enough (0)
    int need = rnd.next(0, 1);

    int M;
    if (need == 1 && total > 1) {
        // Not enough money: M < total
        M = rnd.next(1, total - 1);
    } else {
        // Enough money or total==1: M >= total
        // Add a small random margin up to 20
        M = rnd.next(total, total + 20);
    }

    // Print K, N, M
    println(K, N, M);

    return 0;
}
