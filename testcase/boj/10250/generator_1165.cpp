#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int T = rnd.next(1, 5); // Generate between 1 to 5 test cases
    cout << T << endl;
    
    for (int t = 0; t < T; t++) {
        int H = rnd.next(1, 10); // Generate H between 1 and 10
        int W = rnd.next(1, 10); // Generate W between 1 and 10
        int maxN = H * W;
        int N = rnd.next(1, maxN); // Ensure N is within valid range
        
        cout << H << " " << W << " " << N << endl;
    }
    
    return 0;
}
