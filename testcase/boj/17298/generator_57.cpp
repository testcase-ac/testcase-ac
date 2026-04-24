#include "testlib.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Constants for bounds
const int N_MIN = 1;
const int N_MAX = 12; // Adjust as needed for easy verification

const int A_MIN = 1;
const int A_MAX = 10; // Adjust as needed

const int TYPE_MIN = 1;
const int TYPE_MAX = 6;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate N within the specified bounds
    const int N = rnd.next(N_MIN, N_MAX);

    // Randomly select a test case type
    const int type = rnd.next(TYPE_MIN, TYPE_MAX);

    vector<int> A(N);

    switch (type) {
        case 1:
            // Type 1: Random sequence
            for (int i = 0; i < N; ++i) {
                A[i] = rnd.next(A_MIN, A_MAX);
            }
            break;

        case 2:
            // Type 2: Increasing sequence
            {
                int current = rnd.next(A_MIN, A_MAX);
                A[0] = current;
                for (int i = 1; i < N; ++i) {
                    int increment = rnd.next(0, (A_MAX - current) / max(1, N - i));
                    current += increment;
                    A[i] = current;
                }
            }
            break;

        case 3:
            // Type 3: Decreasing sequence
            {
                int current = rnd.next(A_MIN, A_MAX);
                A[0] = current;
                for (int i = 1; i < N; ++i) {
                    int decrement = rnd.next(0, (current - A_MIN) / max(1, N - i));
                    current -= decrement;
                    A[i] = current;
                }
            }
            break;

        case 4:
            // Type 4: All elements equal
            {
                int val = rnd.next(A_MIN, A_MAX);
                for (int i = 0; i < N; ++i) {
                    A[i] = val;
                }
            }
            break;

        case 5:
            // Type 5: Zig-zag sequence
            {
                int mid = (A_MIN + A_MAX) / 2;
                for (int i = 0; i < N; ++i) {
                    if (i % 2 == 0) {
                        A[i] = rnd.next(A_MIN, mid);
                    } else {
                        A[i] = rnd.next(mid + 1, A_MAX);
                    }
                }
            }
            break;

        case 6:
            // Type 6: Repeating patterns
            {
                int pattern_length = rnd.next(1, max(1, N / 2));
                vector<int> pattern(pattern_length);
                for (int i = 0; i < pattern_length; ++i) {
                    pattern[i] = rnd.next(A_MIN, A_MAX);
                }
                for (int i = 0; i < N; ++i) {
                    A[i] = pattern[i % pattern_length];
                }
            }
            break;
    }

    // Output the generated test case
    cout << N << endl;
    for (int i = 0; i < N; ++i) {
        cout << A[i];
        if (i != N - 1) cout << ' ';
    }
    cout << endl;

    return 0;
}
