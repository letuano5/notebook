bool composite(LL n, int a, LL d, int s) {
  LL x = power(a, d, n);

  if (x == 1 || x == n - 1)
    return false;

  for (int r = 1; r <= s - 1; r++) {
    x = multiply(x, x, n);

    if (x == n - 1)
      return false;
  }

  return true;
}

  if (n < 5)
    return (n == 2 || n == 3 ? "YES" : "NO");

  int s = 0;
  long long d = n - 1;

  while (d % 2 == 0)
    s++,
    d /= 2;

  vector <int> prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

  for (int p : prime) {
    if (p == n)
      return "YES";

    if (p > n - 2)
      return "YES";

    if (composite(n, p, d, s))
      return "NO";
  }

  return "YES";
