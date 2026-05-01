#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Define generation strategies for variability
    vector<string> types = {
        "random", "increasing", "decreasing",
        "alternating", "ones", "max_first",
        "max_last", "plateaus"
    };
    string tp = rnd.any(types);
    // Choose N small enough for manual verification
    int N = rnd.next(1, 15);
    vector<int> A(N);
    if (tp == "random") {
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1, N);
    } else if (tp == "increasing") {
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(i + 1, N);
    } else if (tp == "decreasing") {
        for (int i = 0; i < N; i++)
            A[i] = rnd.next(1, N - i);
    } else if (tp == "alternating") {
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0)
                A[i] = rnd.next(max(1, N/2), N);
            else
                A[i] = rnd.next(1, 2);
        }
    } else if (tp == "ones") {
        for (int i = 0; i < N; i++)
            A[i] = 1;
    } else if (tp == "max_first") {
        A[0] = N;
        for (int i = 1; i < N; i++)
            A[i] = rnd.next(1, max(1, N/2));
    } else if (tp == "max_last") {
        for (int i = 0; i < N - 1; i++)
            A[i] = rnd.next(1, max(1, N/2));
        A[N-1] = N;
    } else if (tp == "plateaus") {
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, min(5, N - i));
            int val = rnd.next(1, N);
            for (int j = 0; j < len; j++)
                A[i++] = val;
        }
    }
    // Output the test case
    println(N);
    println(A);
    return 0;
}
