#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <atcoder/all>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace std::literals::string_literals;
using namespace __gnu_pbds;
using namespace atcoder;
namespace ublas = boost::numeric::ublas;

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

template <typename T>
using statistic_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using mint = atcoder::modint1000000007;

template <typename T>
class mat : public ublas::matrix<T>
{
public:
    mat(i32 n, T init = T())
        : ublas::matrix<T>(n, n, init) {}

    mat(const ublas::matrix<T> &other)
        : ublas::matrix<T>(other) {}

    static auto id(i32 n) -> mat<T>
    {
        auto e = mat<T>(n);
        for (auto i = 0; i < n; ++i)
        {
            e(i, i) = 1;
        }
        return e;
    }

    auto pow(i64 k) const -> mat<T>
    {
        auto r = id(this->size1());
        auto base = *this;

        while (k)
        {
            if (k & 1)
            {
                r = mat<T>(prod(r, base));
            }
            base = mat<T>(prod(base, base));
            k >>= 1;
        }

        return r;
    }
};

auto traveling_salesperson(i32 n, vector<vector<i32>> &distances, i32 src) -> vector<mint>
{
    auto l = 1 << n;
    auto dp = vector(l, vector(n, mint()));
    dp[1 << src][src] = 1;

    for (auto s = 1; s < l; ++s)
    {
        for (auto i = 0, m = 1; i < n; ++i, m <<= 1)
        {
            if (s & m)
            {
                for (auto j = 0; j < n; ++j)
                {
                    if (!distances[j][i])
                    {
                        continue;
                    }
                    dp[s][i] += dp[s ^ m][j];
                }
            }
        }
    }

    auto w = vector(n, mint());
    for (auto &v : dp)
    {
        for (auto i = 0; i < n; ++i)
        {
            w[i] += v[i];
        }
    }

    return w;
}

auto main() -> i32
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    auto n = 0, k = 0;
    cin >> k >> n;

    auto distances = vector(n, vector(n, 0));
    for (auto i = 0; i < n; ++i)
    {
        for (auto j = 0; j < n; ++j)
        {
            cin >> distances[i][j];
        }
    }

    auto a = mat<mint>(n);
    for (auto i = 0; i < n; ++i)
    {
        auto v = traveling_salesperson(n, distances, i);
        for (auto j = 0; j < n; ++j)
        {
            a(i, j) = v[j];
        }
    }

    auto b = a.pow(k);
    cout << b(0, 0).val() << '\n';

    return 0;
}
