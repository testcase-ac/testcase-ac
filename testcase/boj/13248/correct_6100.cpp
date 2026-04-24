#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int A, B, C, D, E;
    cin >> A >> B >> C >> D >> E;
    if(A >= A+B-C) {
        return !(cout << 0);
    }
    int sti = D / (A+B), stmod = D % (A+B), edi = E / (A+B), edmod = E % (A+B);
    //printf("sti = %d, stmod = %d, edi = %d, edmod = %d\n", sti, stmod, edi, edmod);
    int notok = 0;
    if(edi > sti + 1) {
        notok += (edi - sti - 1) * (B-C);
    }
    if(edi > sti) {
        notok += max(0ll, min(A+B-C-stmod, B-C));
        notok += max(0ll, min(edmod - A, B-C));
    }
    if(edi == sti) {
        if(edmod == stmod) {
            if(A <= stmod && stmod <= A+B-C) {
                return !(cout << "1");
            } else {
                return !(cout << "0");
            }
        }
        notok += max(0ll, min(A+B-C, edmod) - max(A, stmod));
    }
    //printf("notok = %d\n", notok);
    cout << fixed << setprecision(17) << ((long double)notok / (E - D));

}
