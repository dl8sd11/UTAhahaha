#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000006;
bool sieve[MAXC];
vector<int> prime;

void linear_sieve() {
    for (int i=2; i<MAXC; i++) {
        if (!sieve[i]) prime.emplace_back(i);
        for (int j=0; i*prime[j]<MAXC; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

int main () {
    linear_sieve();
    for (int i=0; i<20; i++) {
        cout << prime[i] << " \n"[i==19];
    }
}