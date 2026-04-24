#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for weight bias
    int tA = rnd.next(-2, 2);
    int tB = rnd.next(-2, 2);
    int tC = rnd.next(-2, 2);
    int tD = rnd.next(-2, 2);
    
    // Generate small counts (0 to 20) with some bias
    int A = rnd.wnext(21, tA);
    int B = rnd.wnext(21, tB);
    int C = rnd.wnext(21, tC);
    int D = rnd.wnext(21, tD);

    // Output the test case
    println(A, B);
    println(C, D);

    return 0;
}
