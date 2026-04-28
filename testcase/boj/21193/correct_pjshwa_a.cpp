#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>
using namespace std;
using ll=long long;
set<ll> mp[1001];
set<ll> ans;
int arr[1001];
priority_queue<pair<ll,int>> q;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        arr[i]=-arr[i];
    }
    sort(arr,arr+n);
    q.push({0,1});
    ll pre=-1;
    int kk=k;
    while(k){
        ll t=-q.top().first;
        int idx=-q.top().second;
        q.pop();
        if(pre==t)continue;
        cout<<t<<": ";k--;
        pre=t;
        ll p=t;
        for(int i=idx;i>=0;i--){
            if(mp[i].count(p)){
                p+=arr[i];
                cout<<-arr[i]<<' ';
            }
            if(!p)break;
        }
        cout<<'\n';
        for(int i=idx+1;i<n;i++){
            ans.insert(t-arr[i]);
            if(ans.size()>kk)ans.erase(prev(ans.end()));
            if(*prev(ans.end())<t-arr[i])continue;
            q.push({-t+arr[i],-i});
            mp[i].insert({t-arr[i]});
        }
    }

}
