#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of tasks
    int N = rnd.next(1, 10);

    // Hyper-parameters for deadline and weight distributions
    int Dmax = rnd.next(1, 15);
    int Wmax = rnd.next(1, 100);
    int t_dead = rnd.next(-2, 2);    // bias for deadlines: negative -> early, positive -> late
    int t_weight = rnd.next(-2, 2);  // bias for weights: negative -> small, positive -> large

    // Generate tasks
    vector<pair<int,int>> tasks;
    for (int i = 0; i < N; i++) {
        // Deadline d in [1, Dmax], biased by t_dead
        int d = rnd.wnext(Dmax, t_dead) + 1;
        // Weight w in [1, Wmax], biased by t_weight
        int w = rnd.wnext(Wmax, t_weight) + 1;
        tasks.emplace_back(d, w);
    }

    // Shuffle to randomize input order
    shuffle(tasks.begin(), tasks.end());

    // Output
    println(N);
    for (auto &p : tasks) {
        println(p.first, p.second);
    }

    return 0;
}
