#include <bits/stdc++.h>
using namespace std;
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int N, cl, cr;
	cin>>N>>cl>>cr;
	int D[2][2][12];
	auto X=D[0], Y=D[1];
	memset(D, 0x3f, sizeof(D));
	X[0][0]=0;
	for(int k=0, p=2, x; k<N; k++) {
		swap(X, Y);
		memset(X, 0x3f, sizeof(D[0]));
		cin>>x; --x;
		int d=abs(x/3-p/3)+abs(x%3-p%3);
		for(int i=0; i<12; i++) X[0][i]=Y[0][i]+cr+d, X[1][i]=Y[1][i]+cl+d;
		for(int i=0; i<12; i++) {
			X[0][p]=min(X[0][p], Y[1][i]+cr+abs(i/3-x/3)+abs(i%3-x%3));
			X[1][p]=min(X[1][p], Y[0][i]+cl+abs(i/3-x/3)+abs(i%3-x%3));
		}
		p=x;
	}
	int ans=1e9;
	for(int i=0; i<2; i++) ans=min(ans, *min_element(X[i], X[i]+12));
	cout<<ans<<'\n';
}
