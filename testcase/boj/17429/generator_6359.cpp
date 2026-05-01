#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter: size of tree
    int N = rnd.next(2, 10);
    // Hyperparameter: tree shape (0=random, 1=chain, 2=star)
    int shape = rnd.next(0, 2);
    vector<pair<int,int>> edges;
    if (shape == 1) {
        // chain 1-2-3-...-N
        for (int i = 2; i <= N; i++)
            edges.emplace_back(i - 1, i);
    } else if (shape == 2) {
        // star centered at c
        int c = rnd.next(1, N);
        for (int i = 1; i <= N; i++)
            if (i != c)
                edges.emplace_back(c, i);
    } else {
        // random tree
        for (int i = 2; i <= N; i++)
            edges.emplace_back(rnd.next(1, i - 1), i);
    }
    shuffle(edges.begin(), edges.end());
    // Number of queries
    int Q = rnd.next(6, 15);
    // Output N, Q and edges
    println(N, Q);
    for (auto &e : edges)
        println(e.first, e.second);
    // Ensure we cover all command types at least once
    set<int> missing = {1, 2, 3, 4, 5, 6};
    for (int i = 1; i <= Q; i++) {
        int cmd;
        int remain = Q - i + 1;
        if (remain == (int)missing.size()) {
            // must use one of the missing types
            vector<int> v(missing.begin(), missing.end());
            int idx = rnd.next(0, (int)v.size() - 1);
            cmd = v[idx];
        } else {
            cmd = rnd.next(1, 6);
        }
        missing.erase(cmd);
        int X, Y;
        long long V;
        switch (cmd) {
            case 1:
                X = rnd.next(1, N);
                V = rnd.next(1, 100);
                println(1, X, V);
                break;
            case 2:
                X = rnd.next(1, N);
                Y = rnd.next(1, N);
                V = rnd.next(1, 100);
                println(2, X, Y, V);
                break;
            case 3:
                X = rnd.next(1, N);
                V = rnd.next(0, 5);
                println(3, X, V);
                break;
            case 4:
                X = rnd.next(1, N);
                Y = rnd.next(1, N);
                V = rnd.next(0, 5);
                println(4, X, Y, V);
                break;
            case 5:
                X = rnd.next(1, N);
                println(5, X);
                break;
            case 6:
                X = rnd.next(1, N);
                Y = rnd.next(1, N);
                println(6, X, Y);
                break;
        }
    }
    return 0;
}
