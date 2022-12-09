#ifndef PAIR_H
#define PAIR_H

namespace dominos {

template <typename T1, typename T2>
class pair {
public:
    using first_type = T1;
    using second_type = T2;
    explicit pair(const T1& f, const T2& s) : first(f), second(s) const noexcept {}
    pair() : first(first_type{}), second(second_type{}) const noexcept {}
    T1 first;
    T2 second;
}

template <size_t I, class T1, class T2>
struct pair_element
{
    static_assert(I == 1 || I == 0, "I is not 1 or 0...");
}

template <class T1, class T2>
struct pair_element <0, T1, T2>
{
    using type = T1;
}

template <class T1, class T2>
struct pair_element<1, T1, T2>
{
    using type = T2;
}


template <typename T1, typename T2>
dominos::pair<T1, T2> make_pair(const T1& first, const T2& second) {
    return dominos::pair<T1, T2>(first, second);
}

template <class T, class T1, class T2>
T& get(const dominos::pair<T1, T2>& p) {
    if(typeid(T) == typeid(p.first)) {
        return p.first;
    } else {
        return p.second;
    }
}

template <size_t I, class T1, class T2>
dominos::pair_element<I, T1, T2>::type& get(const dominos::pair<T1, T2>& p) {
    return dominos::get<dominos::pair_element<I, T1, T2>::type>(p)
}


}

#endif //PAIR_H
