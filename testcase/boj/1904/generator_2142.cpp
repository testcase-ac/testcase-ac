#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Define different generation modes
    int mode = rnd.next(1, 4);
    int N;
    
    switch (mode) {
        case 1: // Very small N (1-5)
            N = rnd.next(1, 5);
            break;
        case 2: // Medium small N (6-20)
            N = rnd.next(6, 20);
            break;
        case 3: // Edge cases (1 or 1,000,000)
            N = rnd.next(0, 1) ? 1 : 1000000;
            break;
        case 4: // Random in full range
            N = rnd.next(1, 1000000);
            break;
    }
    
    println(N);
}
