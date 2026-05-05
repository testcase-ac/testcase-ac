#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
const int SOURCE = 0,SINK = 1,INF = 987654321;
int N,K,D;
int remain[302][302];
vector<int> edge[302], level;

bool BFS() {
	level = vector<int>(N + D + 2,-1);

    queue<int> q;
    level[SOURCE] = 0;
    q.push(SOURCE);

    while (!q.empty()) {
        int u = q.front();   q.pop();
        for (int v : edge[u]) {
            if (level[v] == -1 && remain[u][v] > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    return level[SINK] != -1;
}

int DFS(int u,int max_flow) {
	if (u == SINK)
		return max_flow;

	int ret = 0;
	for (int v : edge[u]) {
		if (level[v] == level[u] + 1 && remain[u][v] > 0) {
			int flow = DFS(v,min(max_flow,remain[u][v]));
			if (flow > 0) {
				remain[u][v] -= flow;
				remain[v][u] += flow;
				ret += flow;
				max_flow -= flow;
				if (max_flow == 0)
					break;
			}
		}
	}
	return ret;
}

int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> K >> D;
	int idx = SINK + 1;
	for (int i = 0; i < D; i++) {
		int n; cin >> n;
		edge[idx].push_back(SINK);
		edge[SINK].push_back(idx);
		remain[idx++][SINK] = n;
	}
	for (int i = 0; i < N; i++) {
		edge[idx].push_back(SOURCE);
		edge[SOURCE].push_back(idx);
		remain[SOURCE][idx] = K;
		int Z; cin >> Z;
		for (int j = 0; j < Z; j++) {
			int recipe; cin >> recipe;
			recipe++;
			edge[idx].push_back(recipe);
			edge[recipe].push_back(idx);
			remain[idx][recipe] = 1;
		}
		idx++;
	}

	int ans = 0;
	while (BFS())
		ans += DFS(SOURCE,987654321);
	cout << ans;

	return 0;
}
