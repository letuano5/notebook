namespace Matrix_Exponentiation {

  const int MAX_ROW = |; // Change Max_row here
  const int MAX_COL = |; // Change Max_col here
  int64_t mod = 1e9 + 7; // Change MOD here
  int64_t mxmod = (int64_t)(7e18 / mod) * mod;

  void change_mod(int _mod) {
    mod = _mod;
    mxmod = (int64_t)(7e18 / mod) * mod;
  }

  int64_t multi(int64_t a, int64_t b) {
    int64_t ret = 0;
    for(int i = 0 ; MASK(i) <= b ; i ++, a = (a + a) % mod) {
      if(MASK(i) & b) ret = (ret + a) % mod;
    }
    return ret;
  }

  struct Matrix {
    int r,c;
    int64_t a[MAX_ROW][MAX_COL];
    void Resize(int _r,int _c) {
      for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
                a[i][j] = 0;
        }
      }
    }

    auto & operator [] (int i) { return a[i]; }

    const auto & operator[] (int i) const { return a[i]; }

    Matrix operator *(const Matrix& other) {
      Matrix product, tmp;
      product.Resize(r, other.c);
      tmp.Resize(r, other.c);
      for (int i = 0; i < product.r; i ++) {
        for (int j = 0; j < c; j ++) {
          for (int k = 0; k < product.c; k ++) {
            //product[i][k] += multi(a[i][j] , other.a[j][k]);
            tmp[i][k] += a[i][j] * other[j][k];
            if(tmp[i][k] >= mxmod)
                    tmp[i][k] -= mxmod;
          }
        }
      }
      for (int i = 0; i < product.r; i ++) {
        for (int j = 0; j < product.c; j ++) {
                product[i][j] = tmp[i][j] % mod;
        }
      }
      return product;
    }

    void operator *= (const Matrix& other) {
      *this = *this * other;
    }

    Matrix operator ^ (const int64_t& b) {
      Matrix ret;
      Matrix m = *this;
      ret.Resize(m.r, m.c);
      for (int i = 0; i < ret.r; i ++) {
              ret[i][i] = 1;
      }
      for(int i = 0 ; MASK(i) <= b ; i ++, m *= m) {
        if (b & MASK(i)) {
          ret*=m;
        }
      }
      return ret;
    }

    void operator ^= (const int64_t& b) {
      *this = *this ^ b;
    }

    friend ostream& operator << (ostream& os, const Matrix& M) {
      for (int i = 0; i < M.r; i ++) {
        for (int j = 0; j < M.c; j ++) {
          os << M.a[i][j] << " \n"[j == M.c - 1];
        }
      }
      return os;
    }
  };
}

using namespace Matrix_Exponentiation;
