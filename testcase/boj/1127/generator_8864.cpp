#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 5);
    int N, K;

    switch (scenario) {
        case 0:
            N = rnd.next(1, 3);
            K = rnd.next(1, 3);
            break;
        case 1:
            N = rnd.next(4, 7);
            K = rnd.next(2, min(6, N + 2));
            break;
        case 2: {
            N = rnd.next(4, 7);
            int maxK2 = min(8, N + 3);
            int minK2 = max(1, N / 2);
            if (minK2 > maxK2) minK2 = maxK2;
            K = rnd.next(minK2, maxK2);
            break;
        }
        case 3:
            N = rnd.next(5, 10);
            K = rnd.next(1, min(7, N));
            break;
        case 4:
            N = rnd.next(5, 10);
            K = rnd.next(2, min(8, N + 2));
            break;
        case 5: {
            N = rnd.next(3, 8);
            int maxK5 = min(10, N + 2);
            int minK5 = max(1, N / 2);
            if (minK5 > maxK5) minK5 = maxK5;
            K = rnd.next(minK5, maxK5);
            break;
        }
        default:
            N = 3;
            K = 2;
    }

    // Build adjacency matrix
    vector<string> adj(N, string(N, '0'));

    if (N > 1) {
        switch (scenario) {
            case 0: {
                double d = 0.2 + 0.6 * rnd.next(); // density between 0.2 and 0.8
                for (int i = 0; i < N; ++i) {
                    for (int j = i + 1; j < N; ++j) {
                        if (rnd.next() < d) {
                            adj[i][j] = adj[j][i] = '1';
                        }
                    }
                }
                break;
            }
            case 1:
            case 2: { // clique
                for (int i = 0; i < N; ++i) {
                    for (int j = i + 1; j < N; ++j) {
                        adj[i][j] = adj[j][i] = '1';
                    }
                }
                break;
            }
            case 3: { // path or star
                if (rnd.next(0, 1) == 0) { // path
                    for (int i = 0; i + 1 < N; ++i) {
                        adj[i][i + 1] = adj[i + 1][i] = '1';
                    }
                } else { // star
                    int c = rnd.next(0, N - 1);
                    for (int i = 0; i < N; ++i) {
                        if (i == c) continue;
                        adj[c][i] = adj[i][c] = '1';
                    }
                }
                break;
            }
            case 4: { // random with chosen density
                double densArr[3] = {0.2, 0.5, 0.8};
                double d = densArr[rnd.next(0, 2)];
                for (int i = 0; i < N; ++i) {
                    for (int j = i + 1; j < N; ++j) {
                        if (rnd.next() < d) {
                            adj[i][j] = adj[j][i] = '1';
                        }
                    }
                }
                break;
            }
            case 5: { // complete bipartite between halves
                int mid = N / 2;
                for (int i = 0; i < mid; ++i) {
                    for (int j = mid; j < N; ++j) {
                        adj[i][j] = adj[j][i] = '1';
                    }
                }
                break;
            }
        }
    }

    // Build offices
    vector<vector<int>> offices(N);
    vector<vector<bool>> hasOffice(N, vector<bool>(K, false));

    auto addOffice = [&](int city, int comp) {
        if (!hasOffice[city][comp]) {
            hasOffice[city][comp] = true;
            offices[city].push_back(comp);
        }
    };

    switch (scenario) {
        case 0: {
            for (int i = 0; i < N; ++i) {
                double p = 0.3 + 0.4 * rnd.next(); // between 0.3 and 0.7
                for (int c = 0; c < K; ++c) {
                    if (rnd.next() < p) addOffice(i, c);
                }
            }
            break;
        }
        case 1: {
            for (int i = 0; i < N; ++i) {
                int minS = max(1, K / 2);
                int maxS = K;
                if (minS > maxS) minS = maxS;
                int s = rnd.next(minS, maxS);
                vector<int> all(K);
                iota(all.begin(), all.end(), 0);
                shuffle(all.begin(), all.end());
                for (int j = 0; j < s; ++j) addOffice(i, all[j]);
            }
            break;
        }
        case 2: {
            for (int i = 0; i < N; ++i) {
                for (int c = 0; c < K; ++c) addOffice(i, c);
            }
            break;
        }
        case 3: {
            for (int i = 0; i < N; ++i) {
                int s = rnd.next(0, K);
                vector<int> all(K);
                iota(all.begin(), all.end(), 0);
                shuffle(all.begin(), all.end());
                for (int j = 0; j < s; ++j) addOffice(i, all[j]);
            }
            break;
        }
        case 4: {
            for (int i = 0; i < N; ++i) {
                if (i < N / 3) {
                    // likely no offices here
                    if (rnd.next(0, 4) == 0) { // small chance to still have some offices
                        int s = rnd.next(1, K);
                        vector<int> all(K);
                        iota(all.begin(), all.end(), 0);
                        shuffle(all.begin(), all.end());
                        for (int j = 0; j < s; ++j) addOffice(i, all[j]);
                    }
                } else {
                    int s = rnd.next(1, K);
                    vector<int> all(K);
                    iota(all.begin(), all.end(), 0);
                    shuffle(all.begin(), all.end());
                    for (int j = 0; j < s; ++j) addOffice(i, all[j]);
                }
            }
            break;
        }
        case 5: {
            for (int i = 0; i < N; ++i) {
                for (int c = 0; c < K; ++c) addOffice(i, c);
            }
            break;
        }
    }

    // Optionally ensure each company has at least one office somewhere
    if (rnd.next(0, 1) == 1) {
        for (int c = 0; c < K; ++c) {
            bool present = false;
            for (int i = 0; i < N && !present; ++i) {
                if (hasOffice[i][c]) present = true;
            }
            if (!present) {
                int city = rnd.next(0, N - 1);
                addOffice(city, c);
            }
        }
    }

    // Build existing guards (subset of offices per city)
    vector<vector<int>> guards(N);

    for (int i = 0; i < N; ++i) {
        const vector<int>& oc = offices[i];
        if (oc.empty()) continue;

        switch (scenario) {
            case 0: {
                for (int comp : oc) {
                    if (rnd.next() < 0.5) guards[i].push_back(comp);
                }
                break;
            }
            case 1: {
                if (rnd.next(0, 3) == 0) {
                    // all zero guards in this city
                } else {
                    for (int comp : oc) {
                        if (rnd.next() < 0.25) guards[i].push_back(comp);
                    }
                }
                break;
            }
            case 2: {
                for (int comp : oc) {
                    if (rnd.next() < 0.8) guards[i].push_back(comp);
                }
                if (guards[i].empty() && !oc.empty() && rnd.next(0, 1) == 1) {
                    int idx = rnd.next(0, (int)oc.size() - 1);
                    guards[i].push_back(oc[idx]);
                }
                break;
            }
            case 3: {
                double p = 0.3 + 0.4 * rnd.next(); // 0.3-0.7
                for (int comp : oc) {
                    if (rnd.next() < p) guards[i].push_back(comp);
                }
                break;
            }
            case 4: {
                if (rnd.next(0, 1) == 0) {
                    // none
                } else {
                    for (int comp : oc) guards[i].push_back(comp);
                }
                break;
            }
            case 5: {
                int pat = rnd.next(0, 3);
                if (pat == 0) {
                    // none
                } else if (pat == 1) {
                    double p = 0.3;
                    for (int comp : oc) if (rnd.next() < p) guards[i].push_back(comp);
                } else if (pat == 2) {
                    double p = 0.6;
                    for (int comp : oc) if (rnd.next() < p) guards[i].push_back(comp);
                } else {
                    for (int comp : oc) guards[i].push_back(comp);
                }
                break;
            }
        }
    }

    // Output
    println(N);
    for (int i = 0; i < N; ++i) {
        println(adj[i]);
    }

    println(K);

    auto printList = [&](const vector<int>& v) {
        printf("%d", (int)v.size());
        for (int x : v) printf(" %d", x);
        printf("\n");
    };

    for (int i = 0; i < N; ++i) {
        printList(guards[i]);
    }
    for (int i = 0; i < N; ++i) {
        printList(offices[i]);
    }

    return 0;
}
