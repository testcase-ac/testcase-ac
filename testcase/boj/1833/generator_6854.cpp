#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cities
    int N = rnd.next(2, 10);
    int maxE = N*(N-1)/2;
    // Hyperparameter for number of pre-installed edges
    int t = rnd.next(-2, 2);
    int K = rnd.wnext(maxE+1, t);
    // All possible edges
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; i++)
        for (int j = i+1; j <= N; j++)
            edges.emplace_back(i, j);
    shuffle(edges.begin(), edges.end());
    vector<vector<int>> a(N+1, vector<int>(N+1));
    // Choose cost scales
    vector<int> scales = {10, 100, 1000};
    int scaleOld = rnd.any(scales);
    int scaleNew = rnd.any(scales);
    // Mark pre-installed edges
    vector<bool> installed(maxE, false);
    for (int i = 0; i < K; i++) {
        installed[i] = true;
    }
    // Fill matrix
    for (int idx = 0; idx < maxE; idx++) {
        int u = edges[idx].first;
        int v = edges[idx].second;
        if (installed[idx]) {
            int c = rnd.next(1, scaleOld);
            a[u][v] = a[v][u] = -c;
        } else {
            int c = rnd.next(1, scaleNew);
            a[u][v] = a[v][u] = c;
        }
    }
    // Diagonal zeros
    for (int i = 1; i <= N; i++) a[i][i] = 0;
    // Output
    println(N);
    for (int i = 1; i <= N; i++) {
        vector<int> row;
        row.reserve(N);
        for (int j = 1; j <= N; j++) row.push_back(a[i][j]);
        println(row);
    }
    return 0;
}
