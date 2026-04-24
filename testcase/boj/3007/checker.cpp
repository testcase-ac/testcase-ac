#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    // Read input
    int N = inf.readInt();
    vector<long long> b(N);
    for (int i = 0; i < N; i++) {
        b[i] = inf.readInt();
    }
    
    // Read participant's answer
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        // a[i] must be a positive integer
        a[i] = ouf.readLong(1, (long long)1e18, format("a[%d]", i+1).c_str());
    }
    // No extra tokens
    ouf.readEof();
    
    // Check the circular sum condition:
    // for each i (0-based), b[i] == a[i-1] + a[i+1], with indices modulo N
    for (int i = 0; i < N; i++) {
        int prev = (i - 1 + N) % N;
        int next = (i + 1) % N;
        long long sum = a[prev] + a[next];
        if (sum != b[i]) {
            quitf(_wa,
                  "At position %d: expected b[%d] = a[%d] + a[%d] = %lld + %lld = %lld, found %lld",
                  i+1, i+1, prev+1, next+1, a[prev], a[next], sum, b[i]);
        }
    }
    
    // All checks passed
    quitf(_ok, "correct sequence of length %d", N);
    return 0;
}
