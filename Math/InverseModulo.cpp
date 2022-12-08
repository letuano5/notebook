gcd(a, m) = 1
a^-1 = a^phi(m)-2
inv[1] = 1;
for(int i = 2; i < m; ++i)
    inv[i] = m - (m/i) * inv[m%i] % m;
