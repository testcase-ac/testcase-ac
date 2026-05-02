#pragma GCC optimize("O3")
#pragma GCC target("avx,avx2")

#include <unistd.h>
#include <array>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

array<char, 1 << 25> inbuf;
int insz, inpos;

array<char, 16> outbuf;
int outsz;

constexpr bool is_digit(char ch) { return '0' <= ch && ch <= '9'; }

char peek_char() {
    return inbuf[inpos];
}
char read_char() {
    return inbuf[inpos++];
}

bool skip_nondigit() {
    if (!is_digit(peek_char())) {
        inpos++;
        return true;
    }
    return false;
}

int read_int() {
    int x = 0;
    while (true) {
        char ch = peek_char();
        if (!is_digit(ch)) { break; }
        inpos++;
        x = 10*x + ch-'0';
    }
    return x;
}

void write_int(int x) {
    if (x == 0) {
        outbuf[outsz++] = '0';
        return;
    }
    while (x > 0) {
        outbuf[outsz++] = '0' + x % 10;
        x /= 10;
    }
    for (int i = 0; i < (outsz >> 1); i++) {
        swap(outbuf[i], outbuf[outsz-1 - i]);
    }
}

array<array<int, 4000>, 4000> cost; // cost[end][start] inclusive
array<int, 4000> dp, ndp;
int main() {
    insz = read(STDIN_FILENO, inbuf.data(), inbuf.size());
    inpos = 0;

    outsz = 0;
    
    int n = read_int(); inpos++;
    int k = read_int(); inpos++;
    
    // idea by brandonzhang
    // https://www.acmicpc.net/source/35938771
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cost[i][j] = read_char()-'0';
            inpos++;
        }
        inpos += 2*(n - i);
        for (int j = i-2; j >= 0; j--) {
            cost[i][j] += cost[i][j+1];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cost[i][j] += cost[i-1][j];
        }
    }

    auto dnc = [&](auto self, int k, int il, int ir, int jl, int jr) -> void {
        if (ir < il) { return; }
        int i = (il + ir) >> 1;

        int jopt = jl;
        int jopt_val = INF;
        for (int j = jl; j <= min(jr, i-1); j++) {
            int val = dp[j] + cost[i][j+1];
            if (val < jopt_val) {
                jopt = j;
                jopt_val = val;
            }
        }

        ndp[i] = jopt_val;
        self(self, k, il, i-1, jl, jopt);
        self(self, k, i+1, ir, jopt, jr);
    };

    for (int i = 0; i < n; i++) {
        dp[i] = cost[i][0];
    }
    for (int q = 2; q <= k; q++) {
        dnc(dnc, q, 0, n-1, 0, n-1);
        swap(dp, ndp);
    }

    int res = dp[n-1];
    write_int(res);
    outbuf[outsz++] = '\n';
    write(STDOUT_FILENO, outbuf.data(), outsz);

    return 0;
}
