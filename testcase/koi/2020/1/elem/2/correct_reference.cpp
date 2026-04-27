#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0);
    int T;
    cin >> T;
    int n,a,b,c,d,e;
    while(T--){
        cin >> n;
        a = b = c = d = e = 0;
        a += n/60;
        n%=60;
        if(n>35){
            a++;
            c = 6-(n+5)/10;
            n %= 10;
            if(n>=5){
                e += 10-n;
            }
            else{
                d += n;
            }
        }
        else{
            b = (n+4)/10;
            n %= 10;
            if(n>=6){
                e += 10-n;
            }
            else{
                d += n;
            }
        }
        cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << '\n';
    }
}