struct TLine_Segtree {
  struct TLine {
    long long a, b;

    long long operator () (long long x) {
      return a * x + b;
    }
  };

  inline static vector <long long> point;

  TLine_Segtree *cl, *cr;
  long long l, r;
  TLine line;

  TLine_Segtree (int _l = 0, int _r = point.size() - 1) {
    cl = cr = NULL;
    l = point[_l];
    r = point[_r];
    line = {0, INF};

    if (l == r)
      return;

    int _m = (_l + _r) / 2;

    cl = new TLine_Segtree(_l, _m);
    cr = new TLine_Segtree(_m + 1, _r);
  }

  void update(TLine new_line, long long u, long long v) {
    if (v < l || r < u)
      return;

    if (u <= l && r <= v) {
      bool better_l = (new_line(l) <= line(l)),
           better_r = (new_line(r) <= line(r));

      if (better_l && better_r) {
        line = new_line;
        return;
      }

      if (better_l == false && better_r == false)
        return;
    }

    if (l == r)
      return;

    cl -> update(new_line, u, v);
    cr -> update(new_line, u, v);
  }

  long long get(long long x) {
    if (x < l || r < x)
      return INF;

    if (l == r)
      return line(x);

    return min({line(x),
                cl -> get(x),
                cr -> get(x)});
  }
};
