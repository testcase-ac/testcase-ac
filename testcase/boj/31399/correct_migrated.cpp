// https://codio.tistory.com/entry/백준-31399-아리스-청소합니Hard-C

#include<iostream>
#include<vector>
#include<tuple>
#include<numeric>
#define lint long long
using namespace std;

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

inline int stateID(int x, int y, int d, int n, int m){
  return (x*m+y)*4+d;
}

inline tuple<int,int,int> statePos(int id, int n, int m){
  int d = id%4; id /= 4;
  int y = id%m; id /= m;
  int x = id;
  return {x,y,d};
}

struct DSU {
  vector<int> parent;
  vector<lint> w;

  DSU(int N = 0) {init(N);}
  void init(int N){
    parent.resize(N);
    w.assign(N,0);
    iota(parent.begin(),parent.end(),0);
  }

  int find(int x){
    if(parent[x] == x) return x;
    int p = parent[x];
    int r = find(p);
    w[x] += w[p];
    parent[x] = r;
    return r;
  }

  void link(int x, int y){
    parent[x] = y;
    w[x] = 1;
  }
};

int main(){
  ios::sync_with_stdio(0); 
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  int sx, sy, sd;
  cin >> sx >> sy >> sd;

  vector<string> a(n), b(n);
  for(auto& v:a) cin >> v;
  for(auto& v:b) cin >> v;

  vector<vector<char>> cleaned(n,vector<char>(m,0));

  const int T = n*m*4;
  DSU uf(T);

  auto inside = [&](int x, int y){
    return (0 <= x && x < n && 0 <= y && y < m);
  };

  auto nextState = [&](int x, int y, int d) -> tuple<int,int,int> {
    int rot = (cleaned[x][y] ? b[x][y] : a[x][y]) - '0';
    int nd = (d+rot) % 4;
    int nx = x + dx[nd];
    int ny = y + dy[nd];
    return {nx,ny,nd};
  };

  auto jumpOver = [&](int x, int y, int d) -> tuple<int,int,int,lint>{
    lint dist = 0;
    while(true){
      int cur = stateID(x,y,d,n,m);
      int r = uf.find(cur);
      dist += uf.w[cur];

      auto[rx,ry,rd] = statePos(r,n,m);
      auto [nx,ny,nd] = nextState(rx,ry,rd);

      if(!inside(nx,ny)) return make_tuple(-1,-1,-1,-1);
      if(!cleaned[nx][ny]) return make_tuple(nx,ny,nd,dist+1);

      int nxt = stateID(nx,ny,nd,n,m);
      if(uf.find(nxt) == uf.find(r)){
        return make_tuple(-1,-1,-1,-1);
      }
      uf.link(r,nxt);
      x = nx; y = ny; d = nd;
      dist++;
    }
  };

  lint ans = 0;
  while(inside(sx,sy)){
    if(cleaned[sx][sy]){
      auto [nx,ny,nd,dist] = jumpOver(sx,sy,sd);
      if(nx < 0) break;
      ans += dist;
      sx = nx; sy = ny; sd = nd;
    }

    auto [nx,ny,nd] = nextState(sx,sy,sd);
    cleaned[sx][sy] = 1;
    ans++;
    sx = nx; sy = ny; sd = nd;
  }

  cout << ans;
}
