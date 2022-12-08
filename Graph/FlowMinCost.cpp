/*
Bai toan nguoi dua thu trung hoa co huong

Dinh thua: dinh co degin < degout
Dinh thieu: dinh co degin > degout

Thuat toan: tim duong di tu 1 dinh thua -> 1 dinh thieu, nhan doi cac canh tren duong di

Luong mincost:
Them 2 dinh s t
Noi s -> cac dinh thua:
    suc chua = luong thua
    trong so = 0
Noi cac dinh thieu -> t:
    suc chua = luong thieu
    trong so = 0
Cac canh co san:
    suc chua = + vo cung
    trong so = trong so da cho

=> tim luong min cost
*/

long long get_wp(TEdge edge) {
  int u = edge.u,
      v = edge.v,
      w = edge.w;

  return w + p[u] - p[v];
}

void ijk(int s, int t, int n) {
  fill(d + 1, d + n + 1, INF);

  priority_queue <TPQ_Item> pq;

  d[s] = 0;
  pq.push({s, 0});

  while (pq.empty() == false) {
    TPQ_Item item = pq.top();
    pq.pop();

    if (item.valid() == false)
      continue;

    int u = item.u;

    for (int i : adj[u]) {
      int v = edges[i].v;

      if (get_cf(edges[i]) == 0)
        continue;

      if (minimize(d[v], d[u] + get_wp(edges[i])))
        trace[v] = i,
        pq.push({v, d[v]});
    }
  }

  for (int u = 1; u <= n; u++)
    p[u] += d[u];
}
