class trie_t {
public:
  trie_t* g[2];
  int cnt;

  trie_t() : g{nullptr, nullptr}, cnt(0) {}

  static void add (trie_t* root, int num, int d) {
    for (int i = 15; i >= 0; i --) {
      const int b = num >> i & 1;
      if (root->g[b] == nullptr) {
        root->g[b] = new trie_t();
      }
      root = root->g[b];
      root->cnt += d;
    }
  }

  static int findk (trie_t* root, int k) {
    int res = 0;
    for (int i = 15; i >= 0; i --) {
      if (root->g[0] && root->g[0]->cnt >= k) {
        root = root->g[0];
      } else {
        if (root->g[0]) {
          k -= root->g[0]->cnt;
        }
        root = root->g[1];
        res |= MASK(i);
      }
    }
    return res;
  }
};
