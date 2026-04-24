#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose a small number of students between 3 and 10.
    int N = rnd.next(3, 10);
    println(N);
    
    // Hyperparameter: favored candidate (1, 2, or 3) that might be slightly preferred.
    int favoredCandidate = rnd.next(1, 3);
    // Hyperparameter: bias percentage in favor of favoredCandidate (0 to 100%).
    int biasPercent = rnd.next(20, 80); // choose a bias percentage between 20 and 80
    // For each student decide whether to favor the biased candidate or use a uniformly random vote.
    for (int i = 0; i < N; i++) {
        int candidateForThree;
        // Decide using bias: With probability biasPercent%, the student gives 3 points to favoredCandidate.
        if(rnd.next(0, 99) < biasPercent) {
            candidateForThree = favoredCandidate;
        } else {
            candidateForThree = rnd.next(1, 3);
        }
        // Prepare a vote array for candidates 1~3
        // vote[0] -> score for candidate 1, vote[1] -> candidate 2, vote[2] -> candidate 3.
        vector<int> vote(3, 0);
        vote[candidateForThree - 1] = 3;
        
        // Determine the remaining two candidates.
        vector<int> remain;
        for (int candidate = 1; candidate <= 3; candidate++) {
            if (candidate != candidateForThree) remain.push_back(candidate);
        }
        // Randomize the ordering for assigning scores 2 and 1.
        shuffle(remain.begin(), remain.end());
        vote[remain[0] - 1] = 2;
        vote[remain[1] - 1] = 1;
        
        println(vote[0], vote[1], vote[2]);
    }
    
    return 0;
}
