#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Four scenarios: equal, obvious bus faster, tricky bus faster, subway faster
    int scenario = rnd.next(0, 3);
    int N, A, B;
    switch (scenario) {
        case 0: {
            // equal times
            B = rnd.next(1, 1000000);
            N = rnd.next(1, B);
            A = B;
            break;
        }
        case 1: {
            // obvious bus faster: A < B - N
            B = rnd.next(3, 1000000);
            N = rnd.next(1, B - 2);           // ensures B - N >= 2
            int maxA = B - N - 1;             // so A <= B - N - 1
            A = rnd.next(1, maxA);
            break;
        }
        case 2: {
            // tricky bus faster: B-N < A < B
            B = rnd.next(2, 1000000);
            N = rnd.next(2, B);               // ensures N >= 2
            int lowA = B - N + 1;
            int highA = B - 1;
            A = rnd.next(lowA, highA);
            break;
        }
        case 3: {
            // subway faster: A > B
            B = rnd.next(1, 1000000);
            N = rnd.next(1, B);
            int minA = B + 1;
            A = rnd.next(minA, 1000000);
            break;
        }
    }
    // Output N, A, B
    println(N, A, B);
    return 0;
}
