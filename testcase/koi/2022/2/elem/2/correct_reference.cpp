#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 5e2+10;

int A[MAXN];

int main()
{
    int n;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;

    for(int i=1;i<=n;i++)
    {
        cin>>A[i];
    }

    int res = n-2;
    int curd = 0;
    int k = 0,d = 0;
    int cnt = 0;
    int cur;

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){

            curd = max(A[j]-A[i],A[i]-A[j]);
            k = j-i;

            if(curd%k)continue;

            d = (A[j]-A[i])/k;

            cnt = 0;
            for(int t=1;t<=n;t++){
                cur = A[i]+d*(t-i);
                if(cur==A[t])cnt++;
            }

            res = min(res,n-cnt);
        }
    }

    cout<<res<<"\n";

    return 0;
}
