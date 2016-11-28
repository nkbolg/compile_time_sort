#include <array>
#include <iostream>
#include <utility>

template <typename T, size_t N, std::size_t... I>
constexpr std::array<T, N> compiletime_sort_impl(const std::array<T, N> elems_in, std::index_sequence<I...>)
{
    T elems[N] = { elems_in[I]...};
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N - 1 - i; j++)
        {
            if (elems[j] > elems[j+1])
            {
                T t = elems[j + 1];
                elems[j + 1] = elems[j];
                elems[j] = t;
            }
        }
    }
    return{ elems[I]... };
}

template <typename T, size_t N, typename Indices = std::make_index_sequence<N>>
constexpr std::array<T, N> compiletime_sort(const std::array<T, N> elems_in)
{
    return compiletime_sort_impl(elems_in, Indices());
}

int main() {
    constexpr std::array<int, 10> sample_arr2 = { 10,9,8,100500,6,5,4,3,2,1 };
    constexpr auto rr = compiletime_sort(sample_arr2);
    for (auto &elem : rr)
    {
        std::cout << elem << std::endl;
    }
    return 0;
}