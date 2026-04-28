#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <bitset>
#include <unordered_set>
#include <cstring>
#include <chrono>
#include <random>
//#define x first
//#define y second
#define all(x)x.begin(),x.end()
#define pack(x)sort(all(x));x.erase(unique(all(x)),x.end())
#define gi(x,v)lower_bound(all(x),v)-x.begin()
#define REP(i,a,b) for (int i = (a); i <= (b); ++i)
#define rREP(i,a,b) for (int i = (a); i >= (b); --i)
using namespace std;
using ll=long long;
using ld=long double;
//#define int ll
using pii=pair<ll,pair<int,int>>;
using pi=pair<int,int>;
using vi=vector<int>;
#define pp pair
using tu=array<int,3>;
int arr[5010];
vector<int> v[5010];
bool er[15010]={1,1};
vector<int> prm;
int N;
vector<int> tt;
vector<int> my[5010];
vector<int>& dfs(int n,int p){
    vector<int>&tmp=my[n];
    tmp.resize(N+1);
    iota(all(tmp),0);
//    for(int j=2;j<=N;j++)tmp[j]=j;
    tmp[arr[n]]=0;
    for(auto i:v[n]){
        if(i==p)continue;
        auto w=dfs(i,n);
        fill(all(tt),1e9);
        for(auto j:prm){////n log log n
            int mn=1e9;
            for(int k=j;k<=N;k+=j)mn=min(mn,w[k]);
            for(int k=j;k<=N;k+=j)tt[k]=min(tt[k],min(mn,w[k]));
        }for(int j=2;j<=N;j++)tmp[j]+=tt[j];
        w.clear();
    }return tmp;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,a,b;
    cin>>n;N=max(102,n*2);
    for(int i=2;i<=N;i++){
        if(er[i])continue;
        prm.push_back(i);
        for(int j=i*i;j<=N;j+=i)er[j]=1;
    }tt.resize(N+1);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }for(int i=1;i<n;i++){
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }auto w=dfs(1,0);
    cout<<*min_element(w.begin()+2,w.end());
}
