#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for distribution of N: bias towards small or large
    int biasSign = rnd.next(-1, 1); // -1, 0, or 1
    int weight = biasSign * 3;      // -3 (small), 0 (uniform), 3 (large)
    // Generate N in [1..20]
    int rawN = rnd.wnext(20, weight); // [0..19] biased as per weight
    int N = rawN + 1;

    // Hyper-parameter: probability to repeat a previous seat
    double dupProb = rnd.next(0.0, 1.0);

    vector<int> requests;
    requests.reserve(N);
    for (int i = 0; i < N; i++) {
        int seat;
        if (!requests.empty() && rnd.next() < dupProb) {
            // With probability dupProb, pick a duplicate request
            seat = rnd.any(requests);
        } else {
            // Otherwise pick a random seat 1..100
            seat = rnd.next(1, 100);
        }
        requests.push_back(seat);
    }

    // Output
    println(N);
    println(requests);

    return 0;
}
