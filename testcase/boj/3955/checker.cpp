#include "testlib.h"
#include <cstdio>
using namespace std;

int K, C;

// Reads and validates an answer from the stream
// Returns the number of bags if valid, -1 if IMPOSSIBLE
long long readAns(InStream& stream) {
    string token = stream.readToken();
    if (token == "IMPOSSIBLE") {
        return -1;
    }
    
    // Try to parse as integer using sscanf
    long long bags;
    if (sscanf(token.c_str(), "%lld", &bags) != 1) {
        stream.quitf(_wa, "invalid format: expected integer or IMPOSSIBLE, got '%s'", token.c_str());
    }
    
    if (bags <= 0 || bags > 1000000000LL) {
        stream.quitf(_wa, "number of bags out of range: %lld (must be between 1 and 10^9)", bags);
    }
    
    // Check if this number of bags gives a valid solution
    long long total_candies = bags * (long long)C;
    
    // We need total_candies = K*X + 1 for some positive integer X
    // So (total_candies - 1) must be divisible by K and the result must be positive
    if (total_candies <= 1) {
        stream.quitf(_wa, "bags = %lld gives only %lld candies, need at least 2", bags, total_candies);
    }
    
    if ((total_candies - 1) % K != 0) {
        stream.quitf(_wa, "bags = %lld gives total = %lld candies, but (total-1) = %lld is not divisible by K = %d", 
                     bags, total_candies, total_candies - 1, K);
    }
    
    long long X = (total_candies - 1) / K;
    if (X <= 0) {
        stream.quitf(_wa, "bags = %lld gives X = %lld, but X must be positive", bags, X);
    }
    
    return bags;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    
    int t = inf.readInt();
    for (int test = 0; test < t; test++) {
        setTestCase(test + 1);
        K = inf.readInt();
        C = inf.readInt();
        
        long long jans = readAns(ans);
        long long pans = readAns(ouf);
        
        if (jans == -1 && pans == -1) {
            // Both say IMPOSSIBLE - accept this
            continue;
        }
        
        if (jans == -1 && pans != -1) {
            quitf(_wa, "jury says IMPOSSIBLE but participant claims solution exists");
        }
        
        if (jans != -1 && pans == -1) {
            quitf(_wa, "participant says IMPOSSIBLE but jury found a solution");
        }
        
        // Both found solutions - both should be valid (already verified in readAns)
        // Any valid solution is acceptable according to problem statement
    }
    
    quitf(_ok, "all test cases passed");
}
