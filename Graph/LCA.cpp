int euler[MAXN * 4];
int l[MAXN * 4][20];
int d[MAXN];
int pos[MAXN];
int par[MAXN];

////////////////////////////////////////////////////////////////////
/// in main :
d[1] = 0;
int N = 0;

function<void(int, int)> dfslca = [&](int u, int p) {
  par[u] = p;
  euler[++N] = u;
  for (const int &v : adj[u]) {
    if (v == p) continue;
    d[v] = d[u] + 1;
    dfslca(v, u);
    euler[++N] = u;
  }
};

dfslca(1, 1);

for (int i = 1; i <= N; i ++) {
  pos[euler[i]] = i;
}

for (int i = 1; i <= N; i ++) {
  l[i][0] = euler[i];
}

int lim = log2(N);
for (int i = 1; i <= lim; i ++) {
  for (int j = 1; j + MASK(i) - 1 <= N; j ++) {
    l[j][i] = (d[l[j][i - 1]] <= d[l[j + MASK(i - 1)][i - 1]]) ? l[j][i - 1] : l[j + MASK(i - 1)][i - 1];
  }
}

function<int(int, int)> lca = [=](int u, int v) {
  u = pos[u];
  v = pos[v];
  if(u > v) {
    u ^= v;
    v ^= u;
    u ^= v;
  }
  int lg = log2(v - u + 1);
  return (d[l[u][lg]] <= d[l[v - MASK(lg) + 1][lg]])
          ? l[u][lg] : l[v - MASK(lg) + 1][lg];
};
