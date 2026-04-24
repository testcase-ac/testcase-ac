#include <vector>
#include <iostream>
#include "testlib.h"

using namespace std;

vector<int> adj[100];
string names[100];
vector<vector<string>> res;
int use_complex_names = 0;
vector<string> make_name_cand(int N) {
    vector<string> name_cand;
    for (int i = 0; i < N; i++) {
        if (use_complex_names) {
            while (1) {
                string s = rnd.next("[A-Z]{1,5}");
                if (find(name_cand.begin(), name_cand.end(), s) == name_cand.end()) {
                    name_cand.push_back(s);
                    break;
                }
            }
        } else {
            name_cand.push_back(string(1, 'A' + i));
        }
    }
    shuffle(name_cand.begin(), name_cand.end());
    return name_cand;
}
void dfs(int u, int p, vector<string> acc) {
    bool is_leaf = true;
    vector<string> name_cand = make_name_cand(adj[u].size() - (p != -1));
    for (int v : adj[u]) {
        if (v == p) continue;
        is_leaf = false;
        acc.push_back(name_cand.back());
        name_cand.pop_back();
        dfs(v, u, acc);
        acc.pop_back();
    }
    if (is_leaf) {
        res.push_back(acc);
    }
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    use_complex_names = rnd.next(0, 1);
    int N = rnd.next(3, 10);
    vector<int> par(N);
    for (int i = 1; i < N; i++) {
        par[i] = rnd.next(0, i - 1);
        adj[par[i]].push_back(i);
        adj[i].push_back(par[i]);
    }
    dfs(0, -1, {});
    shuffle(res.begin(), res.end());
    println(res.size());
    for (auto v : res) {
        cout << v.size();
        for (auto s : v) {
            cout << " " << s;
        }
        cout << endl;
    }
    return 0;
}
