#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Total number of seats
    int N = rnd.next(1, 10);
    // Probability to place a couple seat pair
    double coupleProb = rnd.next(0.0, 1.0);

    string seats;
    seats.reserve(N);
    for (int i = 0; i < N; ) {
        // If at least two seats remain, we may place a couple
        if (i <= N - 2 && rnd.next() < coupleProb) {
            seats += "LL";
            i += 2;
        } else {
            seats += 'S';
            i += 1;
        }
    }

    // Output
    println(N);
    printf("%s\n", seats.c_str());
    return 0;
}
