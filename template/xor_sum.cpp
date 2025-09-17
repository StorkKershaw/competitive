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

template <typename T, i32 D = 60>
struct xor_sum
{
    static_assert(is_integral_v<T> || is_base_of_v<internal::static_modint_base, T>, "T must be an integral or modint type");

    xor_sum(vector<i64> &v) : zero(), one()
    {
        for (auto x : v)
        {
            for (auto d = 0; d < D; ++d)
            {
                if (x & 1)
                {
                    ++one[d];
                }
                else
                {
                    ++zero[d];
                }
                x >>= 1;
            }
        }
    }

    /**
     * @brief Computes the sum of (v[i] ^ v[j]) where i < j in constant time.
     *
     * @return The total sum of all pairwise XORs of the elements in the vector.
     */
    auto pairwise_sum() const -> T
    {
        auto r = T();
        for (auto d = 0; d < D; ++d)
        {
            r += pow2(d) * (one[d] * zero[d]);
        }
        return r;
    }

    /**
     * @brief Computes (v[0] XOR x) + (v[1] XOR x) + ... + (v[n-1] XOR x) in constant time.
     *
     * @param x The value to XOR with each element of the vector.
     * @return The computed sum as a value of type T.
     */
    auto apply_sum(i64 x) const -> T
    {
        auto r = T();
        for (auto d = 0; d < D; ++d)
        {
            if (x & 1)
            {
                r += pow2(d) * zero[d];
            }
            else
            {
                r += pow2(d) * one[d];
            }
            x >>= 1;
        }
        return r;
    }

    auto one_hot_sum(i64 d, bool invert) const -> T
    {
        return pow2(d) * (invert ? zero[d] : one[d]);
    }

private:
    template <typename U = T>
    auto pow2(i64 k) const -> enable_if_t<is_integral_v<U>, U>
    {
        return U(1) << k;
    }

    template <typename U = T>
    auto pow2(i64 k) const -> enable_if_t<is_base_of_v<internal::static_modint_base, U>, U>
    {
        return U(2).pow(k);
    }

    array<i64, D> zero, one;
};

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0;
    cin >> n;

    auto v = vector(n, 0ll);
    for (auto &x : v)
    {
        cin >> x;
    }

    auto s = xor_sum<i64, 30>(v);
    auto r = s.apply_sum(0);
    for (auto x : v)
    {
        r = max(r, s.apply_sum(x));
    }
    cout << r << '\n';

    return 0;
}
