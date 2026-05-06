//GPT 코드
#include <bits/stdc++.h>
using namespace std;

const int m[3][3][4]={
	{{0,14,20,4},{13,23,7,3},{19,18,17,16}},
	{{7,19,15,11},{18,14,10,6},{23,22,21,20}},
	{{0,9,22,19},{1,10,23,16},{15,14,13,12}}
};

const int mp[24]={
	0,1,3,2,4,5,8,9,12,13,16,17,
	7,6,11,10,15,14,19,18,20,21,23,22
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct C {
	array<char,24> s;

	C(){
		for(int i=0;i<6;i++)
			for(int j=0;j<4;j++)
				s[4*i+j]=i;
	}

	void rot(int a,int b,int c,int d){
		char t=s[a];
		s[a]=s[b];
		s[b]=s[c];
		s[c]=s[d];
		s[d]=t;
	}

	void move(int mm){
		auto&p=m[mm%3];
		if(mm<3)
			for(int i=0;i<3;i++)
				rot(p[i][0],p[i][1],p[i][2],p[i][3]);
		else
			for(int i=0;i<3;i++)
				rot(p[i][3],p[i][2],p[i][1],p[i][0]);
	}

	void print(){
		string col="GROBYW";
		shuffle(col.begin(),col.end(),rng);
		char out[24];

		for(int i=0;i<24;i++)
			out[i]=col[s[mp[i]]];

		cout<<out[0]<<out[1]<<'\n';
		cout<<out[2]<<out[3]<<'\n';

		cout<<out[4]<<out[5]<<' '
		    <<out[6]<<out[7]<<' '
		    <<out[8]<<out[9]<<' '
		    <<out[10]<<out[11]<<'\n';

		cout<<out[12]<<out[13]<<' '
		    <<out[14]<<out[15]<<' '
		    <<out[16]<<out[17]<<' '
		    <<out[18]<<out[19]<<'\n';

		cout<<out[20]<<out[21]<<'\n';
		cout<<out[22]<<out[23]<<'\n';
	}
};

int main(){

	int T=rng()%10+1;
	cout<<T<<'\n';

	while(T--){
		C c;

		int k=20+rng()%4;
		while(k--) c.move(rng()%6);

		c.print();
		cout<<'\n';
	}
}
