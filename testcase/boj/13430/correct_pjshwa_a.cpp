#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<utility>
#include<tuple>
#include<compare>
using namespace std;

template<class T, size_t md>
struct Z
{
	T value;
	static inline size_t phi=md-1;
	Z() = default;
	Z(T val):value{val}{}
	operator T(){return value;}
	Z& operator=(T val){value=val;return *this;}
	Z& operator=(Z z){value=z.value;return *this;}
	void fixmodulo(){value%=md;value+=md;value%=md;}
	Z& operator+=(Z oth)
	{
		value+=oth.value;fixmodulo();return *this;
	}
	Z& operator-=(Z oth)
	{
		value+=(md-oth.value);fixmodulo();return *this;
	}
	Z& operator*=(Z oth)
	{
		value*=oth.value;fixmodulo();return *this;
	}
	Z& operator+=(T oth)
	{
		value+=oth;fixmodulo();return *this;
	}
	Z& operator-=(T oth)
	{
		value+=(md-oth);fixmodulo();return *this;
	}
	Z& operator*=(T oth)
	{
		value*=oth;fixmodulo();return *this;
	}
	Z& operator^=(size_t exp)
	{
		T res{1};
		while(exp)
		{
			if(exp&1)res=((res*value)%md+md)%md;
			value*=value;
			fixmodulo();
			exp>>=1;
		}
		value=res;
		return *this;
	}
	Z& operator/=(Z oth)
	{
		oth^=(phi-1);
		return (*this*=oth);
	}
	Z& operator/=(T val)
	{
		Z oth=val;
		return (*this/=oth);
	}
	Z& operator++(){value++;return *this;}
	Z operator++(int){Z temp=*this;value++;return temp;}
	auto operator<=>(Z& oth){return value<=>oth.value;}
};

template<class T, size_t md>
istream& operator>>(istream& is,Z<T,md> z)
{
	is>>z.value;return is;
}

using mod_t=Z<long,1000000007>;

int main()
{
	//n+kCk+1
	mod_t a=1;
	long n,k;cin>>k>>n;
	for(long i=n;i<=n+k;i++)a*=i;
	for(long i=1;i<=k+1;i++)a/=i;
	cout<<a;
}
