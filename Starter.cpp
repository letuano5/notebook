#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include<bits/stdc++.h>
using namespace std;

#define           fi    first
#define           se    second
#define           pb    push_back
#define           ep    emplace
#define           eb    emplace_back
#define           lb    lower_bound
#define           ub    upper_bound
#define       all(x)    x.begin(), x.end()
#define      rall(x)    x.rbegin(), x.rend()
#define   uniquev(v)    sort(all(v)), (v).resize(unique(all(v)) - (v).begin())
#define     mem(f,x)    memset(f , x , sizeof(f))
#define        sz(x)    (int32_t)(x).size()
#define  __lcm(a, b)    (1ll * ((a) / __gcd((a), (b))) * (b))
#define          mxx    *max_element
#define          mnn    *min_element
#define         left    Kurumi_Tokisaki
#define        right    Kei_Karuizawa
#define         next    Mai_Sakurajima
#define          div    Yume_Irido
#define         prev    Chizuru_Mizuhara
#define    cntbit(x)    __builtin_popcountll(x)
#define      MASK(x)    ( 1ll << (x) )
#define          Yes    cout << "Yes"
#define          YES    cout << "YES"
#define           No    cout << "No"
#define           NO    cout << "NO"
#define           AA    cout << "Alice"
#define           BB    cout << "Bob"

/// TASK
/// -----------------------------
#ifdef LMQZZZ
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
void _print() {cerr << " ]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

#define deb(x...) cerr << "[ in " <<__func__<< "() : line " <<__LINE__<< " ] : [ " << #x << " ] = [ "; _print(x); cerr << '\n';
#define TASK "C"
#else
#define deb(x...) 3326
#define TASK "lmqzzz"
#endif
///------------------------------

void lmqzzz();
void init();
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);      cout.tie(0);
  if (fopen(TASK ".inp", "r")) {
    freopen(TASK ".inp", "r", stdin);
    freopen(TASK ".out", "w", stdout);
  }
  /// =================================
          constexpr bool MULTITEST = 0;
  /// ================================
  init();
  int32_t TT = 1;
  if ( MULTITEST ) cin >> TT;
  for(int32_t TTT = 1; TTT <= TT; TTT ++) {
    lmqzzz();
    cout << '\n';
  }
}

template <class T> inline T min(const T &a, const T &b, const T &c) { return min(a, min(b, c)); }
template <class T> inline T max(const T &a, const T &b, const T &c) { return max(a, max(b, c)); }
template <class T, class U> inline bool mini(T &a, const U &b) { if (a > b) { a = b; return 1; } return 0; }
template <class T, class U> inline bool maxi(T &a, const U &b) { if (a < b) { a = b; return 1; } return 0; }

constexpr     int16_t dr[]  =  {0, 0, -1, 1};
constexpr     int16_t dc[]  =  {1, -1, 0, 0};
constexpr      int64_t MOD  =  998244353;
constexpr     int32_t MAXN  =  1e6 + 10;
