#include "testlib.h"

#include <vector>
using namespace std;

vector<int> permutedCycle(int n) {
    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = i + 1;
    }
    shuffle(nodes.begin(), nodes.end());

    vector<int> f(n + 1);
    for (int i = 0; i < n; ++i) {
        f[nodes[i]] = nodes[(i + 1) % n];
    }
    return f;
}

vector<int> twoCycleWithTrees(int n) {
    vector<int> f(n + 1, 0);
    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = i + 1;
    }
    shuffle(nodes.begin(), nodes.end());

    int a = nodes[0];
    int b = nodes[1];
    f[a] = b;
    f[b] = a;

    vector<int> available = {a, b};
    for (int i = 2; i < n; ++i) {
        int v = nodes[i];
        f[v] = rnd.any(available);
        available.push_back(v);
    }
    return f;
}

vector<int> chainIntoCycle(int n) {
    vector<int> f(n + 1, 0);
    vector<int> nodes(n);
    for (int i = 0; i < n; ++i) {
        nodes[i] = i + 1;
    }
    shuffle(nodes.begin(), nodes.end());

    int cycleSize = rnd.next(2, n);
    for (int i = 0; i < cycleSize; ++i) {
        f[nodes[i]] = nodes[(i + 1) % cycleSize];
    }
    for (int i = cycleSize; i < n; ++i) {
        f[nodes[i]] = nodes[i - 1];
    }
    return f;
}

vector<int> randomFunctionalGraph(int n) {
    vector<int> f(n + 1);
    for (int i = 1; i <= n; ++i) {
        f[i] = rnd.next(1, n - 1);
        if (f[i] >= i) {
            ++f[i];
        }
    }
    return f;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n = rnd.next(2, 10);
        int mode = rnd.next(0, 3);

        vector<int> f;
        if (mode == 0) {
            f = permutedCycle(n);
        } else if (mode == 1) {
            f = twoCycleWithTrees(n);
        } else if (mode == 2) {
            f = chainIntoCycle(n);
        } else {
            f = randomFunctionalGraph(n);
        }

        vector<int> line;
        for (int i = 1; i <= n; ++i) {
            line.push_back(f[i]);
        }

        println(n);
        println(line);
    }

    return 0;
}
