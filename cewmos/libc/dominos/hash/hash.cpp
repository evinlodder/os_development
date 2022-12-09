#include <dominos/hash.h>

using namespace dominos;

//works for any integrals
static inline size_t FNV_hash(auto i, auto prime, auto result) {
    //implementation of Fowler-Noll-Vo hash function from cppreference
    for(size_t j{}; j < sizeof(i) / 8; ++j) {
        uint8_t byte = i >> (8 * j);
        result = result ^ byte;
        result = result * prime;
    }
    return result;
}

static inline size_t FNV_hash_32(uint32_t i) {
    return FNV_hash(i, 0x01000193, 0x811c9dc5);
}

static inline size_t FNV_hash_64(uint64_t i) {
    return FNV_hash(i, 0x100000001B3, 0xcbf29ce484222325);
}

template<>
size_t hash<bool>::operator()(const bool& b) const {
    return static_cast<size_t>(b);    
}

template<>
size_t hash<char>::operator()(const char& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

template<>
size_t hash<signed char>::operator()(const signed char& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

template<>
size_t hash<unsigned char>::operator()(const unsigned char& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

#if __cplusplus >= 202002L

template<>
size_t hash<char8_t>::operator()(const char8_t& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

#endif

template<>
size_t hash<char16_t>::operator()(const char16_t& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

template<>
size_t hash<char32_t>::operator()(const char32_t& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

template<>
size_t hash<wchar_t>::operator()(const wchar_t& c) const {
    return FNV_hash_32(static_cast<uint32_t>(c));
}

template<>
size_t hash<short>::operator()(const short& s) const {
    return FNV_hash_32(static_cast<uint32_t>(s));
}

template<>
size_t hash<unsigned short>::operator()(const unsigned short& s) const {
    return FNV_hash_32(static_cast<uint32_t>(s));
}

template<>
size_t hash<int>::operator()(const int& i) const {
    if(sizeof(i) == 4) {
        return FNV_hash_32(i);
    }
    return FNV_hash_32(static_cast<uint32_t>(i));
}

template<>
size_t hash<unsigned int>::operator()(const unsigned int& i) const {
    if(sizeof(i) == 4) {
        return FNV_hash_32(i);
    }
    return FNV_hash_32(static_cast<uint32_t>(i));
}

template<>
size_t hash<long>::operator()(const long& l) const {
    if(sizeof(l) == 4) {
        return FNV_hash_32(l);
    }
    return FNV_hash_64(l);
}

template<>
size_t hash<unsigned long>::operator()(const unsigned long& l) const {
    if(sizeof(l) == 4) {
        return FNV_hash_32(l);
    }
    return FNV_hash_64(l);
}

template<>
size_t hash<long long>::operator()(const long long& l) const {
    return FNV_hash_64(l);
}

template<>
size_t hash<unsigned long long>::operator()(const unsigned long long& l) const {
    return FNV_hash_64(l);
}

template<>
size_t hash<float>::operator()(const float& f) const {
    return FNV_hash_32(f);
}

template<>
size_t hash<double>::operator()(const double& d) const {
    return FNV_hash_64(d);
}

template<>
size_t hash<long double>::operator()(const long double& d) const {
    return FNV_hash_64(static_cast<uint64_t>(d));
}
