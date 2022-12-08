/**
  * Support: get sum in range, update position
**/

int update (int id, int l, int r, int pos, long long delta) {
  if (pos < l || pos > r)
    return 0;
  if (l == r) {
    n_nodes++;
    st[n_nodes] = Node(0, 0, delta);
    return n_nodes;
  }

  int mid = (l + r) >> 1;
  n_nodes++;
  int cur_id = n_nodes;

  if (pos <= mid) {
    st[cur_id].L = update(st[id].L, l, mid, pos, delta);
    st[cur_id].R = st[id].R;
  }

  else {
    st[cur_id].L = st[id].L;
    st[cur_id].R = update(st[id].R, mid + 1, r, pos, delta);
  }

  st[cur_id].sum = st[st[cur_id].L].sum + st[st[cur_id].R].sum;
  return cur_id;
}

long long get (int id, int l, int r, int u, int v) {
  if (u > v)
    return 0;
  if (v < l || r < u)
    return 0;
  if (u <= l && r <= v)
    return st[id].sum;
  int mid = (l + r) >> 1;
  return get(st[id].L, l, mid, u, v) + get(st[id].R, mid + 1, r, u, v);
}

// Update:
  ver[i] = update(ver[i - 1], 1, n, pos, delta);
// Get:
  long long ans = get(ver[L], 1, n, u, v) ;
