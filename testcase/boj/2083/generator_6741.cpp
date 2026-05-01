#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of members (excluding sentinel)
    int N = rnd.next(1, 10);

    // Probabilities to focus on boundary cases
    double ageBoundaryProb = rnd.next(0.0, 1.0);
    double weightBoundaryProb = rnd.next(0.0, 1.0);

    // Boundary values for classification thresholds
    vector<int> ageBounds = {17, 18};
    vector<int> weightBounds = {79, 80};

    for (int i = 0; i < N; i++) {
        // Generate a random name of length 1..10, letters only
        int len = rnd.next(1, 10);
        string name;
        name.reserve(len);
        for (int j = 0; j < len; j++) {
            if (rnd.next(0, 1) == 0) {
                // lowercase
                name.push_back(char(rnd.next('a', 'z')));
            } else {
                // uppercase
                name.push_back(char(rnd.next('A', 'Z')));
            }
        }

        // Generate age, favoring boundary ages sometimes
        int age;
        if (rnd.next() < ageBoundaryProb) {
            age = rnd.any(ageBounds);
        } else {
            age = rnd.next(1, 100);
        }

        // Generate weight, favoring boundary weights sometimes
        int weight;
        if (rnd.next() < weightBoundaryProb) {
            weight = rnd.any(weightBounds);
        } else {
            weight = rnd.next(1, 200);
        }

        // Output member
        println(name, age, weight);
    }

    // Sentinel line
    println("#", 0, 0);

    return 0;
}
