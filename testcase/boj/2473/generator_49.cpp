#include "testlib.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
// comment?
using namespace std;

// Constants for bounds
const int MIN_N = 3;
const int MAX_N = 12;
const int MIN_VALUE = -12;
const int MAX_VALUE = 12;

int main(int argc, char* argv[]) {
    // Initialize the random seed based on the system time
    registerGen(argc, argv, 1);

    // Randomly determine the size of the test case
    int N = rnd.next(MIN_N, MAX_N);
    
    // Use a set to store unique solutions
    set<int> unique_solutions;

    // Decide the type of test case to generate
    int testType = rnd.next(0, 3); // Randomly choose one of the types (0 to 3)

    if (testType == 0) {
        // Case 1: All positive (acidic) solutions
        while (unique_solutions.size() < N) {
            int value = rnd.next(1, MAX_VALUE);
            unique_solutions.insert(value);
        }
    } else if (testType == 1) {
        // Case 2: All negative (alkaline) solutions
        while (unique_solutions.size() < N) {
            int value = rnd.next(MIN_VALUE, -1);
            unique_solutions.insert(value);
        }
    } else if (testType == 2) {
        // Case 3: Random mixture of positive and negative values
        while (unique_solutions.size() < N) {
            int value = rnd.next(MIN_VALUE, MAX_VALUE);
            while(!value) {
              value = rnd.next(MIN_VALUE, MAX_VALUE);
            }
            unique_solutions.insert(value);
        }
    } else {
        // Case 4: Special case with extreme values
        unique_solutions.insert(MIN_VALUE);
        unique_solutions.insert(MAX_VALUE);
        while (unique_solutions.size() < N) {
            int value = rnd.next(MIN_VALUE / 2, MAX_VALUE / 2);
            while(!value) {
              value = rnd.next(MIN_VALUE / 2, MAX_VALUE / 2);
            }
            unique_solutions.insert(value);
        }
    }

    // Convert the set to a vector for shuffling
    vector<int> solutions(unique_solutions.begin(), unique_solutions.end());

    // Shuffle the solutions to avoid any predictable order
    shuffle(solutions.begin(), solutions.end());

    // Output the test case
    cout << N << endl;
    for (int i = 0; i < N; i++) {
        cout << solutions[i];
        if (i < N - 1) cout << " ";
    }
    cout << endl;

    return 0;
}
