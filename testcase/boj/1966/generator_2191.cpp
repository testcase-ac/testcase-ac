#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Hyperparameters
    int testcase_count = rnd.next(1, 5);  // 1-5 test cases
    double high_priority_prob = rnd.next(0.0, 1.0);  // Probability of having high priority documents
    double duplicate_priority_prob = rnd.next(0.0, 1.0);  // Probability of duplicate priorities
    
    println(testcase_count);
    
    for (int tc = 0; tc < testcase_count; tc++) {
        int N = rnd.next(1, 10);  // Small number of documents (1-10)
        int M = rnd.next(0, N-1);  // Position of interest (0 to N-1)
        
        vector<int> priorities;
        
        // Decide if we want some high priority documents
        bool has_high_priority = rnd.next() < high_priority_prob;
        int max_priority = has_high_priority ? rnd.next(5, 9) : rnd.next(1, 4);
        
        // Generate priorities
        for (int i = 0; i < N; i++) {
            // Sometimes duplicate priorities
            if (i > 0 && rnd.next() < duplicate_priority_prob) {
                priorities.push_back(priorities[rnd.next(0, (int)priorities.size()-1)]);
            } else {
                priorities.push_back(rnd.next(1, max_priority));
            }
        }
        
        // Randomly shuffle to create more interesting cases
        shuffle(priorities.begin(), priorities.end());
        
        // Print test case
        println(N, M);
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << " ";
            cout << priorities[i];
        }
        cout << endl;
    }
    
    return 0;
}
