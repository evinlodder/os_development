#ifndef IN_LIST_H
#define IN_LIST_H


namespace std {

template <class T>
class initializer_list {
public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;

    using iterator = const T*;
    using const_iterator = const T*;

private:
    iterator _M_array;
    size_type _M_len;

public:
    // The compiler can fix this constructor???
    constexpr initializer_list(const_iterator __a, size_type __l)
    : _M_array(__a), _M_len(__l) { }

    constexpr initializer_list() : _M_array(0), _M_len(0) { }

    // Number of elements.
    constexpr size_type
    size() { return _M_len; }

    // First element.
    constexpr const_iterator
    begin() { return _M_array; }

    // One past the last element.
    constexpr const_iterator
    end() { return begin() + size(); }
};

template<class _Tp>
constexpr const _Tp*
begin(initializer_list<_Tp> __ils)
     { return __ils.begin(); }

template<class _Tp>
     constexpr const _Tp*
     end(initializer_list<_Tp> __ils)
     { return __ils.end(); }

}

namespace dominos {

template <class T>
using initializer_list = std::initializer_list<T>;

template<class _Tp>
constexpr const _Tp*
begin(initializer_list<_Tp> __ils)
     { return __ils.begin(); }

template<class _Tp>
     constexpr const _Tp*
     end(initializer_list<_Tp> __ils)
     { return __ils.end(); }

}

#endif
