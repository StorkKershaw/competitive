#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>

using namespace std;
using namespace std::string_literals;
using namespace std::complex_literals;
using namespace __gnu_pbds;
using namespace atcoder;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using usize = size_t;
using f32 = float;
using f64 = double;
using f80 = long double;

template <typename T>
using twin = tuple<T, T>;

template <typename T>
using triplet = tuple<T, T, T>;

template <typename T>
using quadruplet = tuple<T, T, T, T>;

template <typename T>
using quintuplet = tuple<T, T, T, T, T>;

template <typename T, typename Compare = less<T>>
using statistic_set = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

template <typename K, typename V, typename Compare = less<K>>
using statistic_map = tree<K, V, Compare, rb_tree_tag, tree_order_statistics_node_update>;

struct point
{
    i64 x, y;

    auto operator<=>(const point &other) const -> weak_ordering
    {
        auto half = lower_half() <=> other.lower_half();
        return half != 0 ? half : 0 <=> (x * other.y - y * other.x);
    }

private:
    auto lower_half() const -> bool
    {
        return pair(y, x) < pair(0ll, 0ll);
    }
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto v = vector(n, point());
    for (auto &[x, y] : v)
    {
        cin >> x >> y;
    }

    sort(v.begin(), v.end());

    for (auto [x, y] : v)
    {
        cout << x << ' ' << y << '\n';
    }

    return 0;
}
