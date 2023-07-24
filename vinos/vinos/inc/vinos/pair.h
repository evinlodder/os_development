#ifndef PAIR_H
#define PAIR_H



namespace vinos {

template <typename T1, typename T2>
class pair {
public:
    using first_type = T1;
    using second_type = T2;
    T1 first;
    T2 second;
    pair(const T1& f, const T2& s) : first(f), second(s) {}
    pair() : first(first_type{}), second(second_type{}) {}
};

template <size_t I, class T1, class T2>
struct pair_element
{
    static_assert(I == 1 || I == 0, "I is not 1 or 0...");
};

template <class T1, class T2>
struct pair_element <0, T1, T2>
{
    using type = T1;
};

template <class T1, class T2>
struct pair_element<1, T1, T2>
{
    using type = T2;
};


template <typename T1, typename T2>
vinos::pair<T1, T2> make_pair(const T1& first, const T2& second) {
    return vinos::pair<T1, T2>(first, second);
}

template <class T1, class T2>
constexpr T1& get(const vinos::pair<T1, T2>& p) noexcept {
    return p.first;
}

template <class T1, class T2>
constexpr T1& get(const vinos::pair<T2, T1>& p) noexcept {
    return p.second;
}

template <size_t I, class T1, class T2>
typename vinos::pair_element<I, T1, T2>::type& get(const vinos::pair<T1, T2>& p) {
    return vinos::get<vinos::pair_element<I, T1, T2>::type>(p);
}


}

#endif //PAIR_H
