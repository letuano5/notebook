#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

/* k-th: find_by_order() (0-indexed)
   the number of items in a set that are strictly smaller than our item: order_of_key()
*/
/*
multiset: less<int> -> less_equal<int>
for searching, lower_bound and upper_bound work oppositely. Also, let's say you want to erase x, use s.erase(s.upper_bound(x)) (as upper bound is considered as lower bound)
*/

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct chash {
    int operator()(pair<int, int> x) const { return x.first* 31 + x.second; }
};

gp_hash_table<int, int, custom_hash> mp;
gp_hash_table<pair<int, int>, int, chash> mp1;
