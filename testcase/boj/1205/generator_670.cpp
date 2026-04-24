#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int P = rnd.next(10, 20);
    
    // Generate N (0 ≤ N ≤ P)
    int N = rnd.next() < 0.5 ? P : rnd.next(0, P);
    
    int maxScore = rnd.next(5, 40);
    // Generate new score (0 ≤ score ≤ 100)
    int newScore = rnd.next(0, maxScore);
    
    // First line: N newScore P
    println(N, newScore, P);
    
    if (N > 0) {
        // Generate N scores in non-ascending order
        int w = rnd.next(-2, 2);
        vector<int> scores;
        for (int i = 0; i < N; i++) {
            int score = rnd.wnext(0, maxScore, w);
            scores.push_back(score);
        }
        sort(scores.begin(), scores.end(), greater<int>());
        for (int i = 0; i < N; i++) {
            if (i > 0) printf(" ");
            printf("%d", scores[i]);
        }
        println("");
    }
    
    return 0;
}
