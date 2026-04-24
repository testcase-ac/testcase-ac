#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of elements between 3 and 10
    int N = rnd.next(3, 10);
    // Hyper-parameter for bias: positive favours larger digits, negative favours smaller
    int bias = rnd.next(-2, 2);
    vector<int> a(N);
    // Generate each digit in [0,9] with weighted bias
    for (int i = 0; i < N; ++i) {
        a[i] = rnd.wnext(10, bias);
    }
    // Output
    println(N);
    println(a);
    return 0;
}
