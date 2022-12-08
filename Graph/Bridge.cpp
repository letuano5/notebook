/**
  Counting bridges in multi-graph.
  adj[u] = {v, i} - node and id of edge.
**/

void dfs(int u){
  long long s = 0, s2 = 0;

  low[u] = num[u] = ++timeDfs;
  child[u] = 1;

  for(auto [v, i] : g[u]){
    if(used[i])
      continue;

    used[i] = true;

    if(!num[v]){
      tr[v] = u;
      dfs(v);
      low[u] = min(low[u], low[v]);
      child[u] += child[v];

      if(low[v] >= num[v]){
        // current edge is bridge
      }

      if(low[v] >= num[u]){
        // u is joint
      }
    }
    else
      low[u] = min(low[u], num[v]);
  }

}

void solve(){
  for(int i = 1; i <= n; i++)
    if(num[i] == 0){
      dfs(i);
    }
}
