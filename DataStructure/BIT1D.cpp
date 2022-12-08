int A[N], B1[N], B2[N], n;
void upd(int* B, int x, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) B[i] += v;
}
int sum(int* B, int x) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) ans += B[i];
  return ans;
}
void update(int l, int r, int v) {
  upd(B1, r + 1, -v); upd(B1, l, v);
  upd(B2, r + 1, -(r + 1) * v); upd(B2, l, l * v);
}
int query(int l, int r) {
  return ((r + 1) * sum(B1, r) - sum(B2, r)) - (l * sum(B1, l - 1) - sum(B2, l - 1));
}
void init() {
  A[0] = 0;
  fill(B1, B1 + n + 1, 0);
  fill(B2, B2 + n + 1, 0);
  for(int i = 1 ; i <= n ; ++i) upd(i, A[i] - A[i - 1]);
}
