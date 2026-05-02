#include <iostream>
#include <array>
#include <cassert>

using namespace std;
using u32 = unsigned int;

constexpr int MAX_N = 200'000;

struct Trie {
    array<array<int, 2>, MAX_N*32> nodes;
    array<int, MAX_N*32> cnt;

    int root = 0;
    int nsz = 1;
    int alloc() { return nsz++; }

    void insert(u32 x) {
        int cur = root;

        for (int i = 31; i >= 0; i--) {
            bool bit = x & (1u << i);
            if (nodes[cur][bit] == 0) { nodes[cur][bit] = alloc(); }

            cur = nodes[cur][bit];
            cnt[cur]++;
        }
    }

    u32 closest(u32 x) {
        u32 res = 0;
        int cur = root;

        for (int i = 31; i >= 0; i--) {
            bool bit = x & (1u << i);
            if (nodes[cur][bit] == 0) { bit = !bit; }
            if (bit) { res |= 1u << i; }

            cur = nodes[cur][bit];
        }

        return res;
    }

    void remove(u32 x) {
        int cur = root;

        for (int i = 31; i >= 0; i--) {
            bool bit = x & (1u << i);
            if (nodes[cur][bit] == 0) { assert(false); }

            int nxt = nodes[cur][bit];
            cnt[nxt]--;
            if (cnt[nxt] == 0) {
                nodes[cur][bit] = 0;
                return;
            }
            cur = nxt;
        }
    }
};

Trie trie;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    trie.insert(0);

    int n;
    cin >> n;
    while (n--) {
        int t;
        u32 x;
        cin >> t >> x;
        if (t == 1) {
            trie.insert(x);
        } else if (t == 2) {
            trie.remove(x);
        } else {
            cout << (trie.closest(~x) ^ x) << "\n";
        }
    }

    return 0;
}
