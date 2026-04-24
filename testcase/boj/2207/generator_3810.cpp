#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int M = rnd.next(1, 5);         // number of games
    int N = rnd.next(1, 10);        // number of students
    bool sat = rnd.next(0, 1) == 1;  // choose satisfiable or not

    if (!sat && N < 2) N = 2;  // need at least two for unsat core

    vector<pair<int,int>> choices;
    if (sat) {
        // Generate a hidden assignment: true = Rock, false = Scissor
        vector<bool> assign(M+1);
        for (int i = 1; i <= M; i++) {
            assign[i] = rnd.next(0,1);
        }
        // Generate each student's two guesses, ensuring at least one matches
        for (int i = 0; i < N; i++) {
            int goodPos = rnd.next(1, M);
            bool firstIsMatch = rnd.next(0,1);
            int x, y;
            if (firstIsMatch) {
                // First guess matches
                x = assign[goodPos] ? -goodPos : goodPos;
                int pos2 = rnd.next(1, M);
                y = (rnd.next(0,1) ? pos2 : -pos2);
            } else {
                // Second guess matches
                y = assign[goodPos] ? -goodPos : goodPos;
                int pos1 = rnd.next(1, M);
                x = (rnd.next(0,1) ? pos1 : -pos1);
            }
            choices.emplace_back(x, y);
        }
    } else {
        // Force an unsatisfiable core on a single position
        int corePos = rnd.next(1, M);
        // One student demands Rock,Rock at corePos
        choices.emplace_back(-corePos, -corePos);
        // Another demands Scissor,Scissor at corePos
        choices.emplace_back(corePos, corePos);
        // Fill the rest with random guesses
        for (int i = 2; i < N; i++) {
            int p1 = rnd.next(1, M), p2 = rnd.next(1, M);
            int x = rnd.next(0,1) ? p1 : -p1;
            int y = rnd.next(0,1) ? p2 : -p2;
            choices.emplace_back(x, y);
        }
    }

    // Shuffle students to conceal structure
    shuffle(choices.begin(), choices.end());

    // Output
    println(N, M);
    for (auto &pr : choices) {
        println(pr.first, pr.second);
    }
    return 0;
}
