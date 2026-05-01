#include <iostream>
#include <array>
#include <vector>
#include <span>
#include <queue>
#include <utility>
#include <cassert>

using namespace std;
using u8 = unsigned char;

template <class T, int SIGMA, int OFFSET, int PATSZ, int ALLOC>
struct AhoCorasick {
    struct Node {
        array<int, SIGMA> go;
        int fail;
        vector<int> pat;
    };
    
    array<Node, ALLOC+1> nodes;
    array<int, PATSZ+1> patsz;
    int root = 0;
    
    int size = 1, pat_id = 1;
    int alloc() { return size++; }
    int patalloc() { return pat_id++; }
    
    void init() {
        size = 1;
        pat_id = 1;
        root = 0;
        nodes[root] = { { 0, }, root, vector<int>() };
        nodes[root].go.fill(root);
    }
    
    int insert(span<T> s) {
        int n = s.size();
        int cur = root;
        for (int i = 0; i < n; i++) {
            int& nxt = nodes[cur].go[s[i] - OFFSET];
            if (nxt == root) { nxt = alloc(); }
            cur = nxt;
        }
        
        auto& pat = nodes[cur].pat;
        if (pat.empty()) {
            pat = { patalloc() };
            patsz[pat.back()] = n;
        }
        return pat.back();
    }
    
    deque<int> que;
    void build() {
        for (int i = 0; i < SIGMA; i++) {
            int subroot = nodes[root].go[i];
            if (subroot != root) {
                que.push_back(subroot);
            }
        }
        
        while (!que.empty()) {
            int u = que.front(); que.pop_front();
            auto& nu = nodes[u];
            for (int i = 0; i < SIGMA; i++) {
                int v = nu.go[i];
                if (v == root) { continue; }
                
                auto& nv = nodes[v];
                int& f = nv.fail;
                f = nu.fail;
                while (f != root && nodes[f].go[i] == root) { f = nodes[f].fail; }
                if (nodes[f].go[i] != root) { f = nodes[f].go[i]; }
                
                auto& pat = nv.pat;
                pat.insert(pat.end(), nodes[f].pat.begin(), nodes[f].pat.end());
                
                que.push_back(v);
            }
        }
    }
    
    void match(span<T> s, span<int> res) {
        int n = s.size();
        int cur = root;

        for (int i = 0; i < n; i++) {
            while (cur != root && nodes[cur].go[s[i] - OFFSET] == root) {
                cur = nodes[cur].fail;
            }
            if (nodes[cur].go[s[i] - OFFSET] != root) {
                cur = nodes[cur].go[s[i] - OFFSET];
                for (int p : nodes[cur].pat) {
                    res[i - patsz[p] + 1] = p;
                }
            }
        }
    }
};

constexpr int MAX_N = 2000;

array<array<bool, MAX_N>, MAX_N> p, t;
array<int, MAX_N> p_comp, fail;
array<array<int, MAX_N>, MAX_N> t_comp;
AhoCorasick<bool, 2, 0, MAX_N, MAX_N*MAX_N> alg;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int hp, wp, ht, wt;
    cin >> hp >> wp >> ht >> wt >> ws; // ws trims whitespace
    alg.init();

    for (int y = 0; y < hp; y++) {
        string s;
        getline(cin, s);
        for (int x = 0; x < wp; x++) {
            p[y][x] = s[x] == 'o';
        }
        p_comp[y] = alg.insert(span(p[y].data(), wp));
    }

    for (int y = 0; y < ht; y++) {
        string s;
        getline(cin, s);
        for (int x = 0; x < wt; x++) {
            t[y][x] = s[x] == 'o';
        }
    }

    alg.build();
    for (int y = 0; y < ht; y++) {
        alg.match(span(t[y].data(), wt), t_comp[y]);
    }

    // transpose for better cache
    for (int y = 0; y < ht; y++) {
        for (int x = 0; x < y; x++) {
            swap(t_comp[y][x], t_comp[x][y]);
        }
    }

    // fail.fill(0); // not needed
    int j = 0;
    for (int i = 1; i < hp; i++) {
        while (j > 0 && p_comp[i] != p_comp[j]) {
            j = fail[j-1];
        }
        if (p_comp[i] == p_comp[j]) {
            fail[i] = ++j;
        }
    }

    int res = 0;
    for (int x = 0; x < wt; x++) {
        int j = 0;
        for (int i = 0; i < ht; i++) {
            while (j > 0 && t_comp[x][i] != p_comp[j]) {
                j = fail[j-1];
            }
            if (t_comp[x][i] == p_comp[j]) {
                j++;
                if (j == hp) {
                    res++;
                    j = fail[j-1];
                }
            }
        }
    }

    cout << res << "\n";

    return 0;
}
