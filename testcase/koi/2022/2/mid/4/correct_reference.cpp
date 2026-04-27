#include <algorithm>
#include <cstdio>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, M, K, S;
ll A[101010];

pii f(int lft, int tot, int k, int m) {
    ll t = (tot - lft) + (ll)k * m;
    return {t / tot, tot - t % tot};
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%lld", &A[i]);
    scanf("%d%d%d", &M, &K, &S);
    
    sort(A + 1, A + N + 1);
    int lb, rb;
    for (lb = K - 1; lb > 0 && A[lb] == A[K]; lb--);
    for (rb = K + 1; rb <= N && A[rb] <= A[K] + 1; rb++);

    int lcnt = count(A + 1, A + N + 1, A[K]);
    int tot = rb - lb - 1;
    int tm = M;
    ll st = A[K];

    while (lb > 0 || rb <= N) {
        if (!M) break;

        int lm = M + 1, rm = M + 1;
        if (lb) {
            int l = 0, r = M;
            while (l <= r) {
                int m = l + r >> 1;
                pii t = f(lcnt, tot, K - lb, m);
                if (A[lb] + (tm - M) + m >= st + t.first) r = m - 1;
                else l = m + 1;
            }
            lm = l;
        }
        if (rb <= N) {
            int l = 0, r = M;
            while (l <= r) {
                int m = l + r >> 1;
                pii t = f(lcnt, tot, K - lb, m);
                if (st + t.first + (t.second < tot) >= A[rb]) r = m - 1;
                else l = m + 1;
            }
            rm = l;
        }

        if (lm > M && rm > M) {
            pii t = f(lcnt, tot, K - lb, M);
            st += t.first;
            lcnt = t.second;
            M = 0;
            break;
        }

        pii t = f(lcnt, tot, K - lb, min(lm, rm));
        st += t.first; lcnt = t.second;
        M -= min(lm, rm);
        if (lm >= rm) {
            rb++;
            if (lcnt == tot) lcnt++;
        }
        else { lb--; lcnt++; }
        tot++;
    }

    pii t = f(lcnt, tot, K - lb, M);
    st += t.first; lcnt = t.second;

    for (int i = 1; i <= lb; i++) A[i] += tm;
    for (int i = lb + 1; i < rb; i++) {
        if (i - lb <= lcnt) A[i] = st;
        else A[i] = st + 1;
    }

    for (int i = 1; i <= N; i++) printf("%lld ", A[i]); puts("");
    return 0;
}