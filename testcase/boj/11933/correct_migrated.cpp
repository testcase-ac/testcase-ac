/* ---------- PosixIO start ---------- */
// Template by hyper1423
// Last Update: 20260413

#include <unistd.h>
#include <cstring>
#include <array>
#include <algorithm>
#include <cassert>

namespace posix_io {

using namespace std;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

template <int IN_SZ, int OUT_SZ, bool MANUAL_LOAD = false>
struct PosixIO {
    array<u8, IN_SZ> inbuf;
    int insz = 0, inpos = 0;
    bool is_eof = false;
   
    array<u8, OUT_SZ> outbuf;
    int outsz = 0;

    void flush() {
        if (outsz > 0) { int _ = write(STDOUT_FILENO, outbuf.data(), outsz); }
        outsz = 0;
    }

    constexpr bool is_digit(u8 ch) { return '0' <= ch && ch <= '9'; }

    void refill_append() {
        if (is_eof) { return; }

        // shrink buffer
        memcpy(inbuf.data(), inbuf.data()+inpos, insz-inpos);
        fill(inbuf.data()+insz-inpos, inbuf.data()+insz, 0);
        insz -= inpos; inpos = 0;

        // append
        int len = ::read(STDIN_FILENO, inbuf.data()+insz, inbuf.size()-insz);
        is_eof = len < inbuf.size()-insz;
        insz += len;
    }

    void skip(int cnt=1) {
        if constexpr (!MANUAL_LOAD) {
            if (!is_eof && inpos + cnt > insz) { refill_append(); }
        }
        inpos += cnt;
    }

    // Peek raw bytes as type T
    template <class T = u8>
    T peek() {
        if constexpr (!MANUAL_LOAD) {
            if (!is_eof && inpos + sizeof(T) > insz) { refill_append(); }
        }
        T res;
        memcpy(&res, inbuf.data() + inpos, sizeof(T));
        return res;
    }

    // Read raw bytes as type T
    template <class T = u8>
    T read() {
        T val = peek<T>();
        skip(sizeof(T));
        return val;
    }

    void skip_until_numeric() {
        while (!is_digit(peek()) && peek() != '-') {
            inpos++;
        }
    }

    template <class T, bool skip_next = true>
    T read_num() {
        T x = 0;
        bool neg = peek() == '-';
        if (neg) { skip(); }
        while (true) {
            char ch = peek();
            if (!is_digit(ch)) { break; }
            skip();
            x = 10*x + ch-'0';
        }

        if constexpr (skip_next) { skip(); }
        return neg ? -x : x;
    }

    // NOTE: This assumes 0 <= x <= 99999999
    template <bool skip_next = true>
    u32 read_num_8d() {
        u64 bytes = peek<u64>(); // load little endian
        int len = __builtin_ctzll(~bytes & 0x1010101010101010) / 8; // all digit chars have the bit 0x10; ' ' and '\n' don't
        bytes <<= 8 * (8-len); // truncate after the delimiter
        bytes &= 0x0F0F0F0F0F0F0F0F; // the lower nibble of a digit char == the digit they represent
        
        // instead of repeating x = 10x + bytes[i], parallelize the process with bit ops

        // bytes[2i..2i+2] = bytes[2i] + 10*bytes[2i+1] for i in 0..4
        bytes += (bytes << 8) * 10;
        bytes = (bytes >> 8) & 0x00FF00FF00FF00FF; // zero out used slots

        // bytes[4i..4i+4] = bytes[4i..4i+2] + 100*bytes[4i+2..4i+4] for i in 0..2
        bytes += (bytes << 16) * 100;
        bytes = (bytes >> 16) & 0x0000FFFF0000FFFF; // zero out used slots

        // bytes[8i..8i+8] = bytes[8i..8i+4] + 10000*bytes[8i+4..8i+8] for i in 0..1
        bytes += (bytes << 32) * 10000;
        bytes = (bytes >> 32) & 0x00000000FFFFFFFF; // zero out used slots

        skip(len + skip_next);
        return u32(bytes);
    }

    void write_char(char ch) {
        outbuf[outsz++] = ch;
    }

    template <class T>
    void write_num(T x) {
        if (x < 0) {
            outbuf[outsz++] = '-';
            x = -x;
        }

        int begin = outsz;
        if (x == 0) {
            outbuf[outsz++] = '0';
            return;
        }
        while (x > 0) {
            outbuf[outsz++] = '0' + x % 10;
            x /= 10;
        }
        reverse(outbuf.begin()+begin, outbuf.begin()+outsz);
    }
};

}
using posix_io::PosixIO;

/* ----------- PosixIO end ----------- */



#include <array>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

struct Edge { int v; i64 w; };

struct LCATree {
    // no prefix: indexed by node
    array<int, 500000> par, sz, depth, heavy, tin;
    array<i64, 500000> w_heavy;

    // "t_" prefix: indexed by visit time (= tin)
    array<int, 500000> t_depth, t_head, t_tout, t_head_depth, t_head_par_tin;
    array<i64, 500000> t_dist;
    const vector<Edge>* adj;
    int n, rt;

    void init(const vector<Edge>* adj, int n, int rt) {
        this->adj = adj;
        this->n = n;
        this->rt = rt;
    }

    void build() {
        fill(heavy.begin(), heavy.begin()+n, -1);
        dfs_info(rt, rt);
        
        time = -1;
        t_head[0] = 0;
        dfs_hld(rt, rt);

        for (int i = 0; i < n; i++) { t_head_depth[i] = depth[t_head[i]]; }
        for (int i = 0; i < n; i++) { t_head_par_tin[i] = tin[par[t_head[i]]]; }
    }

    void dfs_info(int u, int p) {
        par[u] = p;
        sz[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (v == p) { continue; }

            depth[v] = depth[u] + 1;
            dfs_info(v, u);
            
            sz[u] += sz[v];
            if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) { heavy[u] = v; w_heavy[u] = w; }
        }
    }
    
    int time = -1;
    void dfs_hld(int u, int p) {
        tin[u] = ++time;
        
        if (heavy[u] == -1) {
            t_tout[time] = time;
            return;
        }

        t_depth[time+1] = t_depth[time]+1;
        t_head[time+1] = t_head[time];
        t_dist[time+1] = t_dist[time] + w_heavy[u];
        dfs_hld(heavy[u], u);
        
        for (auto [v, w] : adj[u]) {
            if (v == p || v == heavy[u]) { continue; }

            t_depth[time+1] = t_depth[tin[u]]+1;
            t_head[time+1] = v;
            t_dist[time+1] = t_dist[tin[u]] + w;
            dfs_hld(v, u);
        }

        t_tout[tin[u]] = time;
    }

    int t_lca(int t_u, int t_v) {
        while (t_head[t_u] != t_head[t_v]) {
            if (t_head_depth[t_u] < t_head_depth[t_v]) { swap(t_u, t_v); }
            t_u = t_head_par_tin[t_u];
        }

        return t_depth[t_u] < t_depth[t_v] ? t_u : t_v;
    }
};

PosixIO<27'400'100, 2'000'000, true> io;

array<vector<Edge>, 500000> adj;
LCATree tree;
array<int, 1000000> virt;
bitset<500000> t_is_x, t_is_y;
int main() {
    io.refill_append();

    int n = io.read_num_8d();
    int q = io.read_num_8d();

    for (int i = 0; i < n-1; i++) {
        int u = io.read_num_8d();
        int v = io.read_num_8d();
        int w = io.read_num<int>();

        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    tree.init(adj.data(), n, 0);
    tree.build();

    while (q--) {
        int xsz = io.read_num_8d();
        int ysz = io.read_num_8d();

        int vsz = 0;
        for (int i = 0; i < xsz; i++) {
            int x = io.read_num_8d();
            virt[vsz++] = tree.tin[x];
            t_is_x.set(tree.tin[x]);
        }
        for (int i = 0; i < ysz; i++) {
            int y = io.read_num_8d();
            virt[vsz++] = tree.tin[y];
            t_is_y.set(tree.tin[y]);
        }

        // keep only the relevant nodes
        // X nodes, Y nodes and the LCA of all pairs

        sort(virt.begin(), virt.begin()+vsz);
        int p_vsz = vsz;
        for (int i = 0; i < p_vsz-1; i++) {
            // Euler tour adjacent pairs give all distinct LCA
            virt[vsz++] = tree.t_lca(virt[i], virt[i+1]);
        }

        // dedup
        sort(virt.begin(), virt.begin()+vsz);
        vsz = unique(virt.begin(), virt.begin()+vsz) - virt.begin();

        i64 res = INF;
        int vi = 0;
        auto dp = [&](auto&& self, int t_u) -> pair<i64, i64> {
            i64 d_ux = t_is_x.test(t_u) ? 0 : INF;
            i64 d_uy = t_is_y.test(t_u) ? 0 : INF;
            t_is_x.reset(t_u); t_is_y.reset(t_u);
            
            // subtree ranges from tin to tout
            while (vi < vsz && virt[vi] <= tree.t_tout[t_u]) {
                int t_v = virt[vi++];
                auto [d_vx, d_vy] = self(self, t_v);
                
                i64 d_uv = tree.t_dist[t_v] - tree.t_dist[t_u];
                d_ux = min(d_ux, d_uv + d_vx);
                d_uy = min(d_uy, d_uv + d_vy);
            }
            
            res = min(res, d_ux + d_uy);
            return { d_ux, d_uy };
        };

        dp(dp, virt[0]);

        io.write_num<u64>(res);
        io.write_char('\n');
    }

    io.flush();
    return 0;
}
