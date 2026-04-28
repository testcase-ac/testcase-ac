/******************************
Author: jhnah917(Justice_Hui)
g++ -std=c++17 -DLOCAL
******************************/

#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define IDX(v, x) lower_bound(all(v), x) - v.begin()
using namespace std;

using uint = unsigned;
using ll = long long;
using ull = unsigned long long;

int N, M;
vector<int> G[2020], R[2020], DFN;
int Check[2020];

void AddEdge(int s, int e){
    G[s].push_back(e); R[e].push_back(s);
}
void AddEdge(int s, int e, int x){
    if(x == 1) AddEdge(s, e);
    else AddEdge(s, e), AddEdge(e, s);
}
void DFS(int v){
    Check[v] = 1;
    for(const auto &i : G[v]) if(!Check[i]) DFS(i);
    DFN.push_back(v);
}
void DFS2(int v, int color){
    Check[v] = color;
    for(const auto &i : R[v]) if(!Check[i]) DFS2(i, color);
}
bool GetSCC(){
    memset(Check, 0, sizeof Check);
    DFN.clear();
    for(int i=1; i<=N; i++) if(!Check[i]) DFS(i);
    reverse(all(DFN));
    memset(Check, 0, sizeof Check);
    int pv = 0;
    for(const auto &i : DFN) if(!Check[i]) DFS2(i, ++pv);
    return pv == 1;
}

void Solve(){
    for(int i=1; i<=M; i++){
        int s, e, x; cin >> s >> e >> x;
        AddEdge(s, e, x);
    }
    cout << GetSCC() << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    while(1){
        cin >> N >> M; if(!N) break;
        for(int i=1; i<=N; i++) G[i].clear(), R[i].clear();
        Solve();
    }
}