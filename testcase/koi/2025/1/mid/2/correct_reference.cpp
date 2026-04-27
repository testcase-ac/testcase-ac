#include <iostream>
#include <cstring>
using namespace std;

const int INF = 1E9;
const int MAXN = 2001;

int ticket_price[6];
int pair_ticket_price;
int n;

bool a_schedule[MAXN+1];
bool b_schedule[MAXN+1];

int memo[MAXN+2][5 + 1][5 + 1][4 + 1];

// day 에 a 티켓 ra일, b 티켓 rb일, 2인권 rp일 (이상) 들고있을 때의 나머지 일정 처리 최소 비용
int dfs(int day, int ra, int rb, int rp)
{
    if (day == n + 1)
        return memo[day][ra][rb][rp] = 0;
    if (memo[day][ra][rb][rp] != -1)
        return memo[day][ra][rb][rp];

    int ans = INF;
    bool need_a = a_schedule[day];
    bool need_b = b_schedule[day];

    for (int add_pair : {0, 4})
    {
        int cost_pair = (add_pair ? pair_ticket_price : 0);
        for (int add_a : {0, 1, 3, 5})
        {
            int cost_a = ticket_price[add_a];
            for (int add_b : {0, 1, 3, 5})
            {
                int cost_b = ticket_price[add_b];

                int next_ra = max(ra, add_a); // 나중에 -1
                int next_rb = max(rb, add_b);
                int next_rp = max(rp, add_pair);

                bool a_covered = (next_ra >= 1 || next_rp >= 1);
                bool b_covered = (next_rb >= 1 || next_rp >= 1);

                if (need_a && !a_covered) // impossible
                    continue;
                if (need_b && !b_covered) // impossible
                    continue;

                int next_day = day + 1;
                next_ra = max(0, next_ra - 1);
                next_rb = max(0, next_rb - 1);
                next_rp = max(0, next_rp - 1);

                int cost = cost_pair + cost_a + cost_b + dfs(next_day, next_ra, next_rb, next_rp);
                ans = min(ans, cost);
            }
        }
    }
    return memo[day][ra][rb][rp] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    string a, b;
    cin >> a >> b;
    for (int i = 0; i < n; i++)
    {
        a_schedule[i + 1] = (a[i] == '1');
        b_schedule[i + 1] = (b[i] == '1');
    }
    cin >> ticket_price[1];
    cin >> ticket_price[3];
    cin >> ticket_price[5];
    cin >> pair_ticket_price;
    memset(memo, -1, sizeof(memo));

    int ans = dfs(0, 0, 0, 0);
    cout << ans << endl;
}