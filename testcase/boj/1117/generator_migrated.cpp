//GPT가 짠 코드
#include <bits/stdc++.h>
using namespace std;

int main(){
	mt19937 rng(random_device{}());

	int w=uniform_int_distribution<int>(1,1000000000)(rng);

	int c,h;
	while(1){
		c=uniform_int_distribution<int>(0,1000)(rng);
		int k=c+1;
		int mx=1000000000/k;
		if(mx==0) continue;
		h=uniform_int_distribution<int>(1,mx)(rng)*k;
		break;
	}

	int f=uniform_int_distribution<int>(0,w)(rng);
	int mx=max(f,w-f);

	int x1=uniform_int_distribution<int>(0,mx-1)(rng);
	int x2=uniform_int_distribution<int>(x1+1,mx)(rng);

	int hh=h/(c+1);
	int y1=uniform_int_distribution<int>(0,hh-1)(rng);
	int y2=uniform_int_distribution<int>(y1+1,hh)(rng);

	cout<<w<<' '<<h<<' '<<f<<' '<<c<<' '
	    <<x1<<' '<<y1<<' '<<x2<<' '<<y2<<'\n';
}
