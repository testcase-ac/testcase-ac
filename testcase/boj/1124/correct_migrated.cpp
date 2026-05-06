#include <bits/stdc++.h>
using namespace std;
int main() {
    bool isp[100001];
    memset(isp,1,sizeof(isp));
    isp[0]=0;
    isp[1]=0;
    for(int i=2;i<100001;i++) if(isp[i]) for(int j=i*2;j<100001;j+=i) isp[j]=0;
    vector<int> pr;
    for(int i=2;i<100001;i++) if(isp[i]) pr.push_back(i);
    int a,b,k,n=0,x;
    cin>>a>>b;
    for(int i=a;i<=b;i++) {
        x=i;k=0;
        for(int p:pr) {
            while(x%p==0) {
                x/=p;
                k++;
            } if(isp[x]) {
                k++;
                break;
            }
        } if(isp[k]) n++;
    } cout<<n;
}
