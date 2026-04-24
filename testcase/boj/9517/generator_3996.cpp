#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Initial holder of the bomb
    int K = rnd.next(1, 8);
    // Number of questions: ensure we can exceed 210 seconds
    int N = rnd.next(3, 20);

    vector<int> T(N);
    vector<char> Z(N);

    // Hyper-parameter for correctness bias
    vector<int> biases = {-3, -1, 0, 1, 3};
    int cbias = rnd.any(biases);
    double correctProb = rnd.wnext(101, cbias) / 100.0;

    // Hyper-parameters for time-weight biases
    vector<int> timeBiases = {-2, -1, 0, 1, 2};
    vector<int> lastBiases = {-1, 0, 1};

    // Generate times so that sum of first N-1 < 210 and total sum > 210
    while (true) {
        int sum = 0;
        bool ok = true;
        int tb = rnd.any(timeBiases);

        // First N-1 times
        for (int i = 0; i < N - 1; i++) {
            int ti = rnd.wnext(100, tb) + 1; // [1,100]
            sum += ti;
            if (sum >= 210) {
                ok = false;
                break;
            }
            T[i] = ti;
        }
        if (!ok) continue;

        // Compute lower bound for last time to exceed 210
        int lb = 211 - sum;
        if (lb < 1) lb = 1;
        if (lb > 100) continue; // impossible to exceed 210 with last ≤100

        // Sample last time with its own bias
        int eb = rnd.any(lastBiases);
        int range = 100 - lb + 1; // number of choices
        int last = (range == 1 ? lb : rnd.wnext(range, eb) + lb);
        sum += last;
        if (sum > 210) {
            T[N - 1] = last;
            break;
        }
    }

    // Generate answer results
    for (int i = 0; i < N; i++) {
        if (rnd.next() < correctProb) {
            Z[i] = 'T';
        } else {
            Z[i] = rnd.any(vector<char>{'N', 'P'});
        }
    }

    // Output the test case
    println(K);
    println(N);
    for (int i = 0; i < N; i++) {
        println(T[i], Z[i]);
    }

    return 0;
}
