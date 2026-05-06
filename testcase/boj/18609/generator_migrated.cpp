//GPT 코드
#include <bits/stdc++.h>
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device


mt19937_64 r;

string add(string a,string b) {
	if(a.size()<b.size()) swap(a,b);
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	string s="";
	int c=0;
	for(int i=0;i<a.size();i++) {
		int x=a[i]-'0'+c;
		if(i<b.size()) x+=b[i]-'0';
		s.push_back(x%10+'0');
		c=x/10;
	}
	if(c) s.push_back(c+'0');
	reverse(s.begin(),s.end());
	return s;
}

string sub(string a,string b) {
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	string s="";
	int c=0;
	for(int i=0;i<a.size();i++) {
		int x=a[i]-'0'-c;
		if(i<b.size()) x-=b[i]-'0';
		if(x<0) x+=10,c=1;
		else c=0;
		s.push_back(x+'0');
	}
	while(s.size()>1&&s.back()=='0') s.pop_back();
	reverse(s.begin(),s.end());
	return s;
}

string mul(string a,string b) {
	int n=a.size(),m=b.size();
	vector<int>v(n+m);
	for(int i=n-1;i>=0;i--) for(int j=m-1;j>=0;j--)
		v[i+j+1]+=(a[i]-'0')*(b[j]-'0');
	for(int i=n+m-1;i>0;i--) v[i-1]+=v[i]/10,v[i]%=10;
	string s="";
	int i=0;
	while(i<n+m-1&&v[i]==0)i++;
	for(;i<n+m;i++) s.push_back(v[i]+'0');
	return s;
}

string mul_int(string a,int d) {
	int n=a.size();
	vector<int>v(n+10);
	for(int i=n-1;i>=0;i--) v[i+10]+=(a[i]-'0')*d;
	for(int i=n+9;i>0;i--) v[i-1]+=v[i]/10,v[i]%=10;
	string s="";
	int i=0;
	while(i<n+9&&v[i]==0)i++;
	for(;i<n+10;i++) s.push_back(v[i]+'0');
	return s;
}

string rnd(int l) {
	string s="";
	s.push_back('1'+r()%9);
	for(int i=1;i<l;i++) s.push_back('0'+r()%10);
	return s;
}

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
    r.seed(seedRng());
	int n=r()%18*2+2;
	cout<<n<<'\n';

	int d=2;

	int mx=450/n;

	vector<string>k(n);

	string L="0",R="0";

	for(int i=0;i<n-1;i++) {
		int len=r()%mx+1;
		k[i]=rnd(len);
		if(i<n/2) L=add(L,k[i]);
		else R=add(R,k[i]);
	}

	if(L>=R) k[n-1]=sub(L,R);
	else k[n-1]=sub(R,L);

	vector<string>a(n);

	for(int i=0;i<n;i++) {
		string sq=mul(k[i],k[i]);
		a[i]=mul_int(sq,d);
	}

	shuffle(a.begin(),a.end(),r);

	for(int i=0;i<n;i++)
		cout<<a[i]<<(i+1<n?' ':'\n');
}
