#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Generate number of test cases T (1 ≤ T ≤ 3, kept small for human verification)
    int T = rnd.next(1, 3);
    println(T);
    
    for (int t = 0; t < T; t++) {
        // Generate number of applicants N (1 ≤ N ≤ 10)
        int N = rnd.next(1, 10);
        println(N);
        
        // Generate document ranks (1..N, no duplicates)
        vector<int> doc_ranks(N);
        for (int i = 0; i < N; i++) doc_ranks[i] = i + 1;
        shuffle(doc_ranks.begin(), doc_ranks.end());
        
        // Hyperparameters for interview rank generation
        double correlation = rnd.next(-1.0, 1.0); // correlation between doc and interview ranks
        bool reverse_order = (rnd.next(0, 1) == 1); // sometimes reverse the order
        
        // Generate interview ranks with some correlation to document ranks
        vector<int> interview_ranks(N);
        for (int i = 0; i < N; i++) interview_ranks[i] = i + 1;
        
        if (abs(correlation) > 0.7) {
            // Strong correlation: keep similar order
            if (correlation > 0) {
                // Positive correlation
                sort(interview_ranks.begin(), interview_ranks.end(), [&](int a, int b) {
                    return doc_ranks[a-1] < doc_ranks[b-1];
                });
            } else {
                // Negative correlation
                sort(interview_ranks.begin(), interview_ranks.end(), [&](int a, int b) {
                    return doc_ranks[a-1] > doc_ranks[b-1];
                });
            }
        } else {
            // Weak correlation: shuffle randomly
            shuffle(interview_ranks.begin(), interview_ranks.end());
        }
        
        if (reverse_order) {
            reverse(interview_ranks.begin(), interview_ranks.end());
        }
        
        // Output the applicants
        for (int i = 0; i < N; i++) {
            println(doc_ranks[i], interview_ranks[i]);
        }
    }
    
    return 0;
}
