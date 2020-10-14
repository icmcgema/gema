//Miller - Rabin: Algoritmo probabilístico 
//para descobrir se um número é primo ou não.
#include <bits/stdc++.h>
using namespace std;
#define ll long long

//Gerador seguro de números aleatórios
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll a, ll b){
	return uniform_int_distribution<ll>(a, b)(rng);
}

//Retorna a*b % mod. é necessário pra multiplicar 
//dois long long sem dar overflow. 
//Se os números que vc quer testar são menores que 2*10^9, 
//pode deixar o return (a*b)%mod.
ll mod_mul(ll a, ll b, ll mod){ 
	//return (a*b)%mod; 
	ll cur_mod = a;
	ll ans = 0;
	for (int i=0; i<63; i++){
		if ((b>>i)&1) ans = (ans + cur_mod)%mod;
		cur_mod = (2*cur_mod) % mod;
	}
	return ans;
}

//Exponenciação rápida - calcula (a^e)%mod em O(log(e)).
ll fexp(ll a, ll e, ll mod){
	if (e == 0) return 1;
	ll p = fexp(a, e/2, mod);
	p = mod_mul(p, p, mod);
	if (e%2 == 1) 
		p = mod_mul(p, a, mod);
	return p;
}

//Miller-Rabin. Checa se o número p é fortemente pseudoprimo na base a.
//Complexidade: O(log(p)) sem modmul, O(log²(p)) com modmul.
bool miller_rabin (ll p, ll a){

	ll q = p-1, k=0;
	while(q % 2 == 0){
		q /= 2;
		k++;
	}

	ll cur = fexp(a, q, p);
	if (cur == 1 or cur == p-1) return true;

	for (int i=0; i<k; i++){
		if (cur == p-1) return true;
		if (cur == 1) return false;
		cur = mod_mul(cur, cur, p);
	}

	return false;
}

//Testa o algoritmo de miller rabin pra várias bases. 
//p => número testado, k => número de bases.
//A probabilidade de erro (identificar que um 
//número é primo quando na vdd é composto) é de (1/4)^k
//k = 40 é uma boa opção, se o TL apertar vc pode diminuir isso aí
bool is_probably_prime(ll p, int k){
	if (p == 0 or p == 1) return false;
	if (p == 2 or p == 3) return true;
	if (p%2 == 0) return false;

	for (int i=0; i<k; i++) {
		if (!miller_rabin(p, rnd(1, p-1))) return false;
	}

	return true;
}

//Só pra conferir
bool is_prime(ll p){
	if (p == 0 or p == 1) return false;
	if (p == 2 or p == 3) return true;
	for (ll i=2; i*i<=p; i++) if (p%i==0) return false;
	return true;
}

int main(){
	int t = 0;
	while(1){
		ll p = rnd(0, 1e18);
		cout << "testing for p = " << p << endl;
		assert(is_probably_prime(p, 40) == is_prime(p));
		cout << "(tested " << ++t << " numbers)" << endl;
	}
}
