#ifndef FBA_HPP
#define FBA_HPP
#include <stdint.h>
#include <kernel/panic.h>

namespace helplib {


struct fixed_buffer_allocator {
    //header struct
    struct meta {
        uint32_t size;
        header* last;
        header* next;
    } __attribute__((packed));

    //typedefs
    using header = meta*;
    using size_type = size_t;

    //ctor
    fixed_buffer_allocator(uint8_t* b, size_type l) : buffer(b), len(l), free_list_len(l / 3), free_list(nullptr) {}

    //allocate num items of type T
    template <typename T>
    T* alloc(size_type num);

    //allocate num items of type T aligned at align
    template <typename T>
    T* aligned_alloc(size_type num, size_type align);

    //free memory
    template <typename T>
    void free(T* ptr);
private:
    //physical buffer and len
    uint8_t* buffer;
    size_type len;

    //free list buffer and len
    header* free_list;
    size_type free_list_len;

    //helper functions
    void insert_into_free_list(header hdr) {
        if(!free_list[0]) {
            free_list[0] = hdr;
            return;
        }

        size_t i{};
        for(; reinterpret_cast<uintptr_t>(free_list[i]) < reinterpret_cast<uintptr_t>(hdr) && i < free_list_len && free_list[i]; ++i); //find index to put header in

        if(free_list[i]) {
            for(size_t p{i}; p < free_list_size - 1; ++p) {
                free_list[p + 1] = free_list[p]; //shift the rest of the list over (since it isn't empty (we checked earlier))
            }
        }
        free_list[i] = header; //then place the value in
    }
    void remove_from_free_list(header hdr) {
        for(size_t i{}; i < free_list_len; ++i) { //loop through list to find index of header
            if(free_list[i] == hdr) { //found, now shift the rest of them over
                free_list[free_list_len - 1] = nullptr;
                for(size_t p{free_list_len - 1}; p > i; --p) {
                    free_list[p - 1] = free_list[p];
                }
                return;
            }
        }
    }
    bool free_list_contains(header hdr) {
        for(size_t i{}; i < free_list_len; ++i) {
            if(free_list[i] == nullptr) {
                break;
            }

            if(free_list[i] == hdr) {
                return true;
            }
        }
        return false;
    }
    void compress_memory() {
        
    }

    uintptr_t find_header_alloc_spot(size_type size, bool aligned)

};

}

#endif
