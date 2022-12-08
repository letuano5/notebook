int pm[MAXN + 10];
vector<int> prime;

void eratosthenes(int N) {
  for (int i = 2 ; i <= N ; i ++) {
    if (pm[i] == 0) {
      pm[i] = i;
      prime.eb(i);
    }
    for (int j = 0 ; (j < sz(prime)) && (prime[j] <= pm[i]) && (i * prime[j] <= N) ; j ++) {
      pm[i * prime[j]] = prime[j];
    }
  }
}
