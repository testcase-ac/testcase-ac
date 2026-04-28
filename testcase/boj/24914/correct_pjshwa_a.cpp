#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 200002;
ll N, M, Q;
map<int, int> child[MAX];           //child[u][v] = u를 부모, v를 자식으로 잇는 간선의 색
map<int, int> child_color_cnt[MAX]; // child_color_cnt[i][c] = i번 노드의 자식 중 색깔이 c개인 것의 개수
int parent_color[MAX];              // parent_color[i] = i번 노드의 부모와 연결된 길의 색
pii roads[MAX];                     // roads[i] = i번 길이 잇고 있는 두 노드 번호
bool visit[MAX];
int sum;                            // 전체 연결 요소 개수

// number_of_child_cc(idx): idx의 자식들을 루트로 하는 연결요소의 개수
int number_of_child_cc(int idx) {
    // 부모랑 같지 않은 자식색의 종류 수와 같다
    int ret = child_color_cnt[idx].size();  // 자식 색의 종류
    
    // 부모와 같은 색은 카운트하지 않음
    int pc = parent_color[idx];
    if (child_color_cnt[idx].find(pc) != child_color_cnt[idx].end()) ret--;
    
    return ret;
}

void change_road_color(int par, int chd, int color) {
    int original_color = parent_color[chd];
    child_color_cnt[par][original_color]--;
    if (child_color_cnt[par][original_color] == 0) child_color_cnt[par].erase(original_color);
    
    child_color_cnt[par][color]++;
    parent_color[chd] = color;
}

int paint(int p, int t) {
    int par = roads[p].first, chd = roads[p].second;
    if (child[par].find(chd) == child[par].end()) swap(par, chd);
    
    sum -= number_of_child_cc(par);
    sum -= number_of_child_cc(chd);
    change_road_color(par, chd, t);
    sum += number_of_child_cc(par);
    sum += number_of_child_cc(chd);
    
    return sum;
}

void dfs(int idx) {
    visit[idx] = true;

    for (auto iter=child[idx].begin(); iter != child[idx].end(); iter++) {
        int next = iter->first;
        int color = iter->second;
        
        child[next].erase(idx);
        if (visit[next]) continue;
        
        if (child_color_cnt[idx].find(color) == child_color_cnt[idx].end())
            child_color_cnt[idx][color] = 0;
        child_color_cnt[idx][color]++;
        parent_color[next] = color;
        
        dfs(next);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> Q;
    
    int u, v, w;
    for (int i=0; i<N-1; i++) {
        cin >> u >> v >> w;
        roads[i+1] = {u, v};
        child[u][v] = w;
        child[v][u] = w;
    }
    
    // 1을 루트로 하는 트리로 만들기
    // 연결요소의 개수는 루트에서만 카운트한다
    dfs(1);
    for (int i=1; i<=N; i++) sum += number_of_child_cc(i);
    
    int p, t;
    for (int i=0; i<Q; i++) {
        cin >> p >> t;
        cout << paint(p, t) << "\n";
    }

    return 0;
}
