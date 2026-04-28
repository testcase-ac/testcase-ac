#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
using namespace std;
using ll=long long;
ll arr[100'010];
priority_queue<pair<ll,int>> pq;
priority_queue<ll> ans;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll n,s;
    cin>>n>>s;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        pq.push({-arr[i],i});
    }
    ll res=-pq.top().first;
    int cnt=0;
    for(int i=n-1;i>0;i--){
        ans.push(-arr[i]);
        while(pq.top().second>=i)pq.pop();
        cnt++;
        res=max(res,min(-pq.top().first+cnt*s,-ans.top()+(cnt-1)*s-(n-1)*s));
    }
    cout<<res;
}

