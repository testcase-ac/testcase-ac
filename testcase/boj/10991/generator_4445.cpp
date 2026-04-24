#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: bias strength for weighted sampling of N
    // t > 0 biases towards larger N, t < 0 towards smaller N, t = 0 uniform
    int t = rnd.next(-2, 2);
    // Generate N in [1,10] using weighted next
    int N = rnd.wnext(10, t) + 1;
    println(N);
    return 0;
}
