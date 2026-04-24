#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    
    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameters for small but diverse sizes
        int C, D;
        if (rnd.next() < 0.2) C = 1;
        else C = rnd.next(1, 10);
        if (rnd.next() < 0.2) D = 1;
        else D = rnd.next(1, 10);
        
        // Maximum distinct votes: two types for each cat-dog pair
        int maxVotes = 2 * C * D;
        int v;
        double p = rnd.next();
        if (p < 0.1) {
            // edge case: no votes
            v = 0;
        } else if (p < 0.3) {
            // edge case: maximum distinct votes
            v = maxVotes;
        } else {
            // a moderate random number of votes
            v = rnd.next(1, min(20, maxVotes));
        }
        
        println(C, D, v);
        
        // Probability that a voter likes cats (and thus dislikes a dog)
        double likeCatProb = rnd.next();
        
        // Generate votes
        for (int i = 0; i < v; ++i) {
            bool likeCat = rnd.next() < likeCatProb;
            if (likeCat) {
                int ci = rnd.next(1, C);
                int di = rnd.next(1, D);
                // Format: like cat, dislike dog
                println(string("C") + to_string(ci), string("D") + to_string(di));
            } else {
                int di = rnd.next(1, D);
                int ci = rnd.next(1, C);
                // Format: like dog, dislike cat
                println(string("D") + to_string(di), string("C") + to_string(ci));
            }
        }
    }
    
    return 0;
}
