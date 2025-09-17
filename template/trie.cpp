#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>

using namespace std;
using namespace std::literals::string_literals;
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

struct trie
{
    trie() : p(0), children() {}

    template <class F>
    auto insert(vector<i64> &key, F f, i32 i = 0, i32 d = 0) -> void
    {
        f(this, key, i, d);

        if (i + d == static_cast<i32>(key.size()))
        {
            return;
        }

        auto c = key[i + d];
        if (!children.contains(c))
        {
            children.emplace(c, trie());
        }

        children[c].insert(key, f, i, d + 1);
    }

    template <class F>
    auto find(vector<i64> &key, F f, i32 i = 0, i32 d = 0) -> void
    {
        f(this, key, i, d);

        if (i + d == static_cast<i32>(key.size()))
        {
            return;
        }

        auto c = key[i + d];
        if (!children.contains(c))
        {
            return;
        }

        children[c].find(key, f, i, d + 1);
    }

    i64 p;
    unordered_map<i64, trie> children;
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto root = trie();
    auto insert_fn = [](trie *t, vector<i64> &, i32, i32)
    {
        t->p++;
    };

    auto ans = 0ll;
    auto find_fn = [&](trie *t, vector<i64> &key, i32 i, i32 d)
    {
        auto c = i + d < static_cast<i32>(key.size()) ? key[i + d] : -1;
        auto q = t->children.contains(c) ? t->children[c].p : 0;
        auto diff = t->p - q;
        ans += diff * d;
    };

    for (auto i = 0; i < n; ++i)
    {
        auto s = ""s;
        cin >> s;

        auto v = vector<i64>(s.begin(), s.end());
        root.find(v, find_fn);
        root.insert(v, insert_fn);
    }

    cout << ans << '\n';
    return 0;
}
