#include "testlib.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate a random size of the sequence N within the allowed range
    int N = rnd.next(1, 10); // Keeping N small for human verification

    // Print N
    println(N);

    // Generate and print the sequence A with values between 1 and 1,000
    for (int i = 0; i < N; i++) {
        cout << rnd.next(1, 10);
        if (i != N - 1) {
            cout << " ";
        }
    }
    cout << '\n';

    return 0;
}
