#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;

const int N=1e6+1;

int not_prime[N], biggest_prime[N];
vi primes;

void crivo() {
	for (int i = 2; i<N; i++)
		if (!not_prime[i]) {
			for (int j = i*i; j<N; j+=i) 
				not_prime[j]=1;
			primes.push_back(i);
		}
	for (int i = 2; i<N; i++)
		if (biggest_prime[i]==0)
			for(int j = i; j<N; j+=i)
				biggest_prime[j]=i;
}

vector<ii> fatora(int n) {
	int last_prime = -1;

	vector<ii> ret;

	while (n>1) {
		int p = biggest_prime[n];

		if (last_prime != p) {
			ret.push_back(make_pair(p, 1));
			last_prime = p;
		}
		else {
			ret[ret.size()-1].se++;
		}

		n/=biggest_prime[n];
	}

	return ret;
}

int main() {
	return 0;
}
