#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    queue<int> q;
    int n,a;
    string s;
    cin>>n;
    while(n--) {
        cin>>s;
        if(s=="push") {
            cin>>a;
            q.push(a);
        } else if(s=="pop") {
            if(q.empty()) {
                cout<<"-1\n";
            } else { 
                cout<<q.front()<<"\n";
                q.pop();
            }
        } else if(s=="size") {
            cout<<q.size()<<"\n";
        } else if(s=="empty") {
            if(q.empty()) cout<<1<<"\n";
            else cout<<"0\n";
        } else if(s=="front") {
            if(q.empty()) cout<<-1<<"\n";
            else cout<<q.front()<<"\n";
        } else {
            if(q.empty()) cout<<"-1\n";
            else cout<<q.back()<<"\n";
        }
    }
}
