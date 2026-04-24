#include "testlib.h"
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    // Register the generator; the seed is the third argument (default 1 if not provided)
    registerGen(argc, argv, 1);
    
    // Hyperparameter: number of test cases.
    // We choose T randomly between 1 and 5.
    int T = rnd.next(1, 5);
    println(T);
    
    for (int tc = 0; tc < T; tc++) {
        // Generate number of computers, n, in range [2, 10] so that the test instance is small.
        int n = rnd.next(2, 10);
        
        // Maximum number of dependency edges possible (directed, no self-dependencies).
        int maxEdges = n * (n - 1);
        
        // Generate number of dependencies d, in range [1, maxEdges].
        int d = rnd.next(1, maxEdges);
        
        // Choose the hacked computer c.
        int c = rnd.next(1, n);
        
        // Print first line of the test case: n, d, c
        println(n, d, c);
        
        // Build a list of all possible dependencies (a,b) where computer a depends on computer b.
        // To ensure that no dependency appears twice.
        vector<tuple<int, int>> allDeps;
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                if(a == b) continue;
                // a depends on b.
                allDeps.push_back({a, b});
            }
        }
        
        // Shuffle the complete list of dependencies.
        shuffle(allDeps.begin(), allDeps.end());
        
        // Hyperparameter: maximum delay time.
        // For a small and human-verifiable test, we choose delays between 0 and 10 seconds.
        // (The problem allows delays up to 1000 seconds.)
        int maxDelay = 10;
        
        // Print exactly d dependency lines.
        for (int i = 0; i < d; i++) {
            int a, b;
            tie(a, b) = allDeps[i];
            int s = rnd.next(0, maxDelay);
            println(a, b, s);
        }
    }
    
    return 0;
}
