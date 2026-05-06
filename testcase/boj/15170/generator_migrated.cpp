//GPT 코드
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rd(ll l,ll r){
	return uniform_int_distribution<ll>(l,r)(rng);
}

int main(){
	int n=rd(1,100);
	cout<<n<<'\n';

	int t=rd(0,1);

	if(t==0){
		ll cx=rd(-200,200);
		ll cy=rd(-200,200);
		ll r=rd(20,150);

		set<pair<ll,ll>>s;

		for(int i=0;i<n;i++){
			ll x,y;
			do{
				x=rd(-250,250);
				y=rd(-250,250);
			}while(s.count({x,y}));
			s.insert({x,y});

			ll dx=x-cx;
			ll dy=y-cy;
			ll d=dx*dx+dy*dy;

			if(d<=r*r) cout<<x<<' '<<y<<' '<<'I'<<'\n';
			else cout<<x<<' '<<y<<' '<<'N'<<'\n';
		}
	}
	else{
		ll cx1=rd(-150,-50);
		ll cy1=rd(-150,-50);
		ll cx2=rd(50,150);
		ll cy2=rd(50,150);
		ll r=rd(20,60);

		set<pair<ll,ll>>s;

		for(int i=0;i<n;i++){
			ll x,y;
			do{
				x=rd(-250,250);
				y=rd(-250,250);
			}while(s.count({x,y}));
			s.insert({x,y});

			ll d1=(x-cx1)*(x-cx1)+(y-cy1)*(y-cy1);
			ll d2=(x-cx2)*(x-cx2)+(y-cy2)*(y-cy2);

			if(d1<=r*r||d2<=r*r) cout<<x<<' '<<y<<' '<<'I'<<'\n';
			else cout<<x<<' '<<y<<' '<<'N'<<'\n';
		}
	}
}
