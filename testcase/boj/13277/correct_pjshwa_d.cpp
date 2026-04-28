#include <bits/stdc++.h>

#define ll long long
using namespace std;

using cdouble = complex<double>;

void fft(vector <cdouble> &a, int sgn)
{
	int n = a.size();
	for (int i=1,j=0,t; i<n; i++){
		for (t=n>>1; j>=t; j-=t, t>>=1);
		j += t;
		if (i < j) swap(a[i],a[j]);
	}

	double ang = sgn*2*acos(-1);
	for (int i=2; i<=n; i<<=1){
		cdouble wi(cos(ang/i),sin(ang/i));

		for (int j=0; j<n; j+=i){
			cdouble w(1);
			for (int k=0; k<i/2; k++){
				cdouble u = a[j+k];
				cdouble v = a[j+k+i/2]*w;
				a[j+k] = u+v;
				a[j+k+i/2] = u-v;
				w *= wi;
			}
		}
	}
}

vector<ll> multiply(vector<ll> &v, vector<ll> &w)
{
	int n;
	for(n=1; n<v.size()+w.size(); n<<=1);

	vector<cdouble> fv(v.begin(), v.end());
	vector<cdouble> fw(w.begin(), w.end());
	fv.resize(n);
	fw.resize(n);
	fft(fv, 1);
	fft(fw, 1);

	for (int i=0; i<n; i++) 
		fv[i] *= fw[i];
	
	fft(fv, -1);
	
	vector<ll> res(n);
	for (int i=0;i<n;i++) 
		res[i] = fv[i].real()>0 ? fv[i].real()/n+0.5 : fv[i].real()/n-0.5;

	return res;
}

void print(vector<double> a){	
	for(int i=0; i<a.size(); i++)
		cout << a[i] << " ";

	cout << endl;
}

void print(vector<ll> a){	
	for(int i=0; i<a.size(); i++)
		cout << a[i] << " ";

	cout << endl;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	string s1, s2;
	cin >> s1 >> s2;

	const ll d[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
	int nd = 3, md = d[nd];

	int n1 = s1.size(), n2 = s2.size();
	vector<ll> v1((n1-1)/nd+1), v2((n2-1)/nd+1);
	for(int i=0; i<n1; i++)
		v1[i/nd] += d[i%nd] * (s1[n1-i-1]-'0');

	for(int i=0; i<n2; i++)
		v2[i/nd] += d[i%nd] * (s2[n2-i-1]-'0');

	vector<ll> v3;
	v3 = multiply(v1, v2);

	//print(v1);
	//print(v2);
	//print(v3);

	for(int i=0; i<v3.size()-1; i++){
		v3[i+1] += v3[i]/md;
		v3[i] %= md;
	}

	for(int i=v3.size()-1; v3[i]>=md; i++){
		v3.push_back(v3[i]/md);
		v3[i] %= md;
	}
	
	//print(v3);

	bool leadingzero = true;
	for(int i=v3.size()-1; i>=0; i--){
		if(leadingzero){
			if(v3[i]==0)
				continue;

			leadingzero = false;
			cout << to_string(v3[i]);
		}
		else{
			string s = to_string(v3[i]), t;
			for(int j=s.size(); j<nd; j++)
				t += '0';

			cout << t << s;
		}
	}
		
	if(leadingzero) cout << '0';
	cout << endl;

	return 0;
}

// https://www.acmicpc.net/source/9993762
