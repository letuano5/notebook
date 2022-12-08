int n, m, A[N][N], B[N][N][4];
void upd(int x, int y, int v) {
  for(int i = x ; i <= n ; i += lowbit(i)) {
    for(int j = y ; j <= m ; j += lowbit(j)) {
      B[i][j][0] += v;
      B[i][j][1] += x * v;
      B[i][j][2] += y * v;
      B[i][j][3] += x * y * v;
    }
  }
}
int qry(int x, int y) {
  int ans = 0;
  for(int i = x ; i > 0 ; i -= lowbit(i)) {
    for(int j = y ; j > 0 ; j -= lowbit(j)) {
      ans += (x + 1) * (y + 1) * B[i][j][0] - (y + 1) * B[i][j][1] - (x + 1) * B[i][j][2] + B[i][j][3];
    }
  }
  return ans;
}
void update(int x1, int y1, int x2, int y2, int v) {
  upd(x1, y1, v);
  upd(x1, y2 + 1, -v);
  upd(x2 + 1, y1, -v);
  upd(x2 + 1, y2 + 1, v);
}
int query(int x1, int y1, int x2, int y2) {
  return qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1);
}
void init() {
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= m ; ++j) {
      upd(i, j, A[i][j]);
    }
  }
}
