#include "testlib.h"
using namespace std;

vector<int> randomGraphDegrees(int N, double density) {
    vector<int> deg(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (rnd.next() < density) {
                deg[i]++;
                deg[j]++;
            }
        }
    }
    return deg;
}

vector<int> generateParityInvalid(int N) {
    vector<int> deg(N);
    for (int i = 0; i < N; ++i)
        deg[i] = rnd.next(0, N - 1);

    int sum = 0;
    for (int x : deg) sum += x;

    if (sum % 2 == 0) {
        int idx = rnd.next(0, N - 1);
        if (deg[idx] == N - 1)
            deg[idx]--;
        else
            deg[idx]++;
    }
    return deg;
}

vector<int> baseInvalidWithZeros(const vector<int>& core, int N) {
    vector<int> deg = core;
    deg.resize(N, 0); // append zeros
    return deg;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 9); // 0..5 valid, 6..9 invalid
    int N;
    vector<int> deg;

    if (type <= 5) {
        // VALID degree sequences
        if (type == 0) {
            // Random moderately dense graph
            N = rnd.next(2, 10);
            vector<double> dens = {0.3, 0.5, 0.7, 0.9};
            double p = rnd.any(dens);
            deg = randomGraphDegrees(N, p);
        } else if (type == 1) {
            // Random sparse / medium graph
            N = rnd.next(5, 15);
            vector<double> dens = {0.05, 0.1, 0.2, 0.35};
            double p = rnd.any(dens);
            deg = randomGraphDegrees(N, p);
        } else if (type == 2) {
            // Path or cycle
            N = rnd.next(2, 15);
            deg.assign(N, 0);
            bool makeCycle = (N >= 3 && rnd.next(0, 1) == 1);
            if (makeCycle) {
                // Simple cycle: all degree 2
                for (int i = 0; i < N; ++i) deg[i] = 2;
            } else {
                // Path
                if (N == 2) {
                    deg[0] = deg[1] = 1;
                } else {
                    deg[0] = deg[N - 1] = 1;
                    for (int i = 1; i < N - 1; ++i) deg[i] = 2;
                }
            }
        } else if (type == 3) {
            // Star plus possible isolates
            N = rnd.next(3, 15);
            deg.assign(N, 0);
            int center = rnd.next(0, N - 1);
            int leaves = rnd.next(1, N - 1);
            deg[center] = leaves;
            vector<int> idxs;
            for (int i = 0; i < N; ++i)
                if (i != center) idxs.push_back(i);
            shuffle(idxs.begin(), idxs.end());
            for (int i = 0; i < leaves; ++i)
                deg[idxs[i]] = 1;
            // remaining vertices stay 0
        } else if (type == 4) {
            // Complete graph or clique + isolates
            bool full = (rnd.next(0, 1) == 0);
            if (full) {
                N = rnd.next(2, 12);
                deg.assign(N, N - 1);
            } else {
                N = rnd.next(3, 15);
                int k = rnd.next(2, min(7, N));
                deg.assign(N, 0);
                for (int i = 0; i < k; ++i)
                    deg[i] = k - 1;
                // others remain 0
            }
        } else if (type == 5) {
            // Two cliques connected by a single bridge edge
            N = rnd.next(4, 16);
            int a = rnd.next(2, N - 2);
            int b = N - a; // b >= 2
            deg.assign(N, 0);
            // clique A: vertices [0, a-1]
            // clique B: vertices [a, N-1]
            for (int i = 0; i < a; ++i)
                deg[i] = a - 1;
            for (int i = a; i < N; ++i)
                deg[i] = b - 1;
            int u = rnd.next(0, a - 1);
            int v = rnd.next(a, N - 1);
            deg[u]++; // bridge
            deg[v]++;
        }

        // Optionally shuffle order to test solutions that assume sorted input
        if (N > 1 && rnd.next(0, 1) == 1)
            shuffle(deg.begin(), deg.end());

    } else {
        // INVALID degree sequences
        if (type == 6) {
            // Handshake lemma violation: odd sum
            N = rnd.next(2, 20);
            deg = generateParityInvalid(N);
        } else if (type == 7) {
            // Even-sum non-graphical: core [2,2,0] + zeros
            N = rnd.next(3, 20);
            vector<int> core = {2, 2, 0};
            deg = baseInvalidWithZeros(core, N);
        } else if (type == 8) {
            // Even-sum non-graphical: core [3,3,1,1] + zeros
            N = rnd.next(4, 20);
            vector<int> core = {3, 3, 1, 1};
            deg = baseInvalidWithZeros(core, N);
        } else { // type == 9
            // Even-sum non-graphical: core [3,3,0,0] + zeros
            N = rnd.next(4, 20);
            vector<int> core = {3, 3, 0, 0};
            deg = baseInvalidWithZeros(core, N);
        }
        // Shuffle invalid sequences as well for diversity
        shuffle(deg.begin(), deg.end());
    }

    // Output the generated test case
    println(N);
    println(deg);

    return 0;
}
