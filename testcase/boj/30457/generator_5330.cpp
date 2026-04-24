#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int N = rnd.next(1, 10);        // number of students
    int H = rnd.next(1, 10);        // maximum possible height
    int t = rnd.next(-2, 2);        // bias for height distribution

    // Generate the heights
    vector<int> A;
    A.reserve(N);
    for (int i = 0; i < N; i++) {
        // rnd.wnext(H, t) gives in [0, H-1] with bias t
        int h = 1 + rnd.wnext(H, t);
        A.push_back(h);
    }

    // Output
    println(N);
    println(A);

    return 0;
}
