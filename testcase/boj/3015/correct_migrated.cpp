#include <iostream>
#include <stack>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    stack<pair<int,int>> s;
    int a,same=0;
    long long pair=0;
    for(int i=0;i<n;i++) {
        cin>>a;
        same=1;
        while(!s.empty() && s.top().first<a) {
            pair+=s.top().second;
            s.pop();
        } if(!s.empty()) {
            if(s.top().first==a) {
                pair+=s.top().second;
                same=s.top().second+1;
                if(s.size() >1) {
                    pair+=1;
                } s.pop();
            } else {
                pair+=1;;
            }
        } s.push(make_pair(a,same));
    }
    cout<<pair<<endl;
}
