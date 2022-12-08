class trie_t {
public:
  trie_t* g[2];
  int cnt;
  static constexpr int lim = 30;

  trie_t() : g{nullptr, nullptr}, cnt(0) {}

  static bool add (trie_t* root, int num, int bit = lim) {
    if (bit == -1) {
      return 0;
    }
    const int b = num >> bit & 1;
    if (root->g[b] == nullptr) {
      root->g[b] = new trie_t();
      add(root->g[b], num, bit - 1);
      root->g[b]->cnt ++;
      return 1;
    } else if (add(root->g[b], num, bit - 1)) {
      root->g[b]->cnt ++;
      return 1;
    } else {
      return 0;
    }
  }

  static bool rmv (trie_t* root, int num, int bit = lim) {
    if (bit == -1) {
      return 1;
    }
    const int b = num >> bit & 1;
    if (root->g[b] == nullptr) {
      return 0;
    } else if (rmv(root->g[b], num, bit - 1)) {
      root->g[b]->cnt --;
      if (root->g[b]->cnt == 0) {
        root->g[b] = nullptr;
      }
      return 1;
    } else {
      return 0;
    }
  }

  static int findk (trie_t* root, int k) {
    int res = 0;
    for (int i = lim; i >= 0; i --) {
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

  static int countx (trie_t* root, int num) {
    int res = 0;
    for (int i = lim; i >= 0; i --) {
      if (num >= MASK(i)) {
        if (root->g[0]) {
          res += root->g[0]->cnt;
        }
        num -= MASK(i);
        if (root->g[1]) {
          root = root->g[1];
        } else {
          return res;
        }
      } else {
        if (root->g[0]) {
          root = root->g[0];
        } else {
          return res;
        }
      }
    }
    return res;
  }
};
