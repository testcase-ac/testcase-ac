#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <numeric>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n): p(n) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        p[b] = a; return true;
    }
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of variables: biased to be somewhat large
    int nVar = rnd.wnext(10, 2) + 1;  // 1..10
    // Number of constants: biased to be small
    int nConst = rnd.wnext(6, -1);    // 0..5

    // Generate unique variable names
    string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    set<string> used;
    vector<string> atoms;
    while ((int)atoms.size() < nVar) {
        int L = rnd.next(1, 5);
        string s;
        for (int i = 0; i < L; i++) s += rnd.any(letters);
        if (!used.count(s)) {
            used.insert(s);
            atoms.push_back(s);
        }
    }
    // Generate constant strings
    set<long long> cused;
    for (int i = 0; i < nConst; i++) {
        long long x;
        do {
            x = rnd.next(-100, 100);
        } while (cused.count(x));
        cused.insert(x);
        atoms.push_back(to_string(x));
    }
    int N = atoms.size();

    // Build equality constraints: acyclic spanning-like edges
    DSU dsu(N);
    vector<pair<int,int>> eqs;
    // generate all possible pairs
    vector<pair<int,int>> pairs;
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            pairs.emplace_back(i, j);
    shuffle(pairs.begin(), pairs.end());
    int maxEqs = N > 1 ? rnd.next(0, N-1) : 0;
    for (auto &pr : pairs) {
        if ((int)eqs.size() >= maxEqs) break;
        int u = pr.first, v = pr.second;
        if (dsu.unite(u, v)) {
            eqs.emplace_back(u, v);
        }
    }

    // Build inequality constraints: between different components
    vector<pair<int,int>> ineqs;
    vector<pair<int,int>> canIneq;
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            if (dsu.find(i) != dsu.find(j))
                canIneq.emplace_back(i, j);
    shuffle(canIneq.begin(), canIneq.end());
    int maxIneq = !canIneq.empty() ? rnd.next(0, (int)canIneq.size()) : 0;
    for (int i = 0; i < maxIneq; i++) {
        ineqs.push_back(canIneq[i]);
    }

    // Collect clause strings
    vector<string> clauses;
    for (auto &e : eqs) {
        int u = e.first, v = e.second;
        if (rnd.next(0,1)) swap(u, v);
        clauses.push_back(atoms[u] + "==" + atoms[v]);
    }
    for (auto &e : ineqs) {
        int u = e.first, v = e.second;
        if (rnd.next(0,1)) swap(u, v);
        clauses.push_back(atoms[u] + "!=" + atoms[v]);
    }
    // Ensure at least one clause
    if (clauses.empty()) {
        // trivial self-equality
        clauses.push_back(atoms[0] + "==" + atoms[0]);
    }
    // Shuffle clause order
    shuffle(clauses.begin(), clauses.end());

    // Build output string
    string res;
    for (int i = 0; i < (int)clauses.size(); i++) {
        if (i) res += "&&";
        res += clauses[i];
    }
    // Print
    printf("%s\n", res.c_str());
    return 0;
}
