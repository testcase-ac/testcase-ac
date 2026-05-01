#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of commands
    int N = rnd.next(1, 20);
    println(N);

    // Hyper-parameters for diversity
    double pushProb = rnd.next(0.0, 1.0);     // Probability to generate a push
    double frontProb = rnd.next(0.0, 1.0);    // Given a push, prob for front vs back
    int maxX = rnd.next(1, 1000);             // Upper bound for X in pushes

    vector<string> nonPushOps = {
        "pop_front", "pop_back", "size", "empty", "front", "back"
    };

    for (int i = 0; i < N; i++) {
        if (rnd.next() < pushProb) {
            int X = rnd.next(1, maxX);
            if (rnd.next() < frontProb) {
                println("push_front " + to_string(X));
            } else {
                println("push_back " + to_string(X));
            }
        } else {
            // pick any non-push operation
            string op = rnd.any(nonPushOps);
            println(op);
        }
    }

    return 0;
}
