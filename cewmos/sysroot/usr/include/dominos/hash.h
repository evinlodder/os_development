#ifndef HASH_H
#define HASH_H



namespace dominos {

template <typename T>
struct hash {
    size_t operator()(const T&) const;
};

}
#endif //HASH_H
