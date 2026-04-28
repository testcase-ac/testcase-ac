#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define all(v) v.begin(), v.end()
#pragma gcc optimize("O3")
#pragma gcc optimize("Ofast")
#pragma gcc optimize("unroll-loops")
using namespace std;
const int INF = 1e9;
const int TMX = 1 << 18;
const long long llINF = 2e18;
const int mod = 1e9 + 7;
const long long hashmod = 100003;
const int MAXV = 20001;
const int MAXE = 1000000;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vec;
typedef vector<pi> vecpi;
int dp[85][85], a[85];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, k, x;
    cin >> n >> k >> x;
    for (int i = 0; i < n; i++)
    {
        int p, q;
        cin >> p >> q;
        a[i] = p;
        if (i == 0)
            dp[0][1] = a[0];
        if (i > 0)
        {
            if (a[i] * (x - a[i]) > dp[i - 1][1] * (x - dp[i - 1][1]))
                dp[i][1] = a[i];
            else
                dp[i][1] = dp[i - 1][1];
        }
    }

    for (int j = 2; j <= k; j++)
    {
        for (int i = j - 1; i < n; i++)
        {

            if ((dp[i - 1][j - 1] + a[i]) * (x * j - dp[i - 1][j - 1] - a[i]) > dp[i - 1][j] * (x * j - dp[i - 1][j]))
                dp[i][j] = dp[i - 1][j - 1] + a[i];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[n - 1][k] * (x * k - dp[n - 1][k]);
}
