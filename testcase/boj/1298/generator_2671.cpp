#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students / notebooks
    int N = rnd.next(1, 10);
    // Maximum possible person-laptop guesses is N * N, but cap it to 20 for handiness
    int maxEdges = N * N;
    int M = rnd.next(0, min(maxEdges, 20));

    // Build all possible guesses (person i thinks laptop j is theirs)
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            edges.emplace_back(i, j);

    // Shuffle and take the first M guesses
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Output in the required format
    println(N, M);
    for (auto &e : edges)
        println(e.first, e.second);

    return 0;
}
