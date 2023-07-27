#include <kernel/paging.h>

struct page_table {
        using flags = kernel::table_flags;
        void set_entry_flags(size_t, std::initializer_list<flags>);
        void clear_entry_flags(size_t, std::initializer_list<flags>);
        void map_addr(size_t, uintptr_t, std::initializer_list<flags>);
        void unmap_idx(size_t);
        uint32_t get_entry(size_t);
        uint32_t m_ptes[kernel::PT_SIZE];
};

struct page_directory {
        using flags = kernel::directory_flags;
        void set_entry_flags(size_t, std::initializer_list<flags>);
        void clear_entry_flags(size_t, std::initializer_list<flags>);
        void map_table(size_t, uint32_t, std::initializer_list<flags>);
        void unmap_idx(size_t);
        bool table_exists(size_t);
        uintptr_t virt_to_phys(uintptr_t);
        uintptr_t m_tables[kernel::PD_SIZE];
};

static page_directory* directory {nullptr};
static page_table* tables[kernel::PD_SIZE] {}; //array of virtual addresses of each table

/// SET SPECIFIED FLAGS FOR PAGE TABLE ENTRY
void page_table::set_entry_flags(size_t idx, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PT_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    for(auto& flag : fgs) {
        m_ptes[idx] |= static_cast<uint8_t>(flag);
    }
}

/// CLEAR SPECIFIED FLAGS FOR PAGE TABLE ENTRY
void page_table::clear_entry_flags(size_t idx, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PT_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    for(auto& flag : fgs) {
        m_ptes[idx] ^= static_cast<uint8_t>(flag);
    }
}

/// MAP ADDRESS TO PAGE TABLE INDEX
/// NOTE: THIS FUNCTION DOES NOT CHECK ALIGNMENT OF PHYSICAL ADDRESS.
/// THE OFFICIAL FUNCTION TO MAP SHOULD CHECK ALIGNMENT
void page_table::map_addr(size_t idx, uintptr_t phys, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PT_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    m_ptes[idx] |= phys;
    for(auto& flag : fgs) {
        m_ptes[idx] |= static_cast<uint8_t>(flag);
    }
}

void page_table::unmap_idx(size_t idx) {
    if(idx >= kernel::PT_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    m_ptes[idx] = 0;
}

uint32_t page_table::get_entry(size_t idx) {
    return m_ptes[idx];
}

///
/// PAGE DIRECTORY FUNCTIONS
///

void page_directory::set_entry_flags(size_t idx, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PD_SIZE) {
        kernel::panic::panic("page directory index greater than page table size", "", true);
    }
    for(auto& flag : fgs) {
        m_tables[idx] |= static_cast<uint16_t>(flag);
    }
}

/// CLEAR SPECIFIED FLAGS FOR PAGE TABLE ENTRY
void page_directory::clear_entry_flags(size_t idx, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PD_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    for(auto& flag : fgs) {
        m_tables[idx] ^= static_cast<uint16_t>(flag);
    }
}

/// MAP ADDRESS TO PAGE DIRECTORY INDEX
/// NOTE: THIS FUNCTION DOES NOT CHECK ALIGNMENT OF PHYSICAL ADDRESS.
/// THE OFFICIAL FUNCTION TO MAP SHOULD CHECK ALIGNMENT
void page_directory::map_table(size_t idx, uintptr_t phys, std::initializer_list<flags> fgs) {
    if(idx >= kernel::PD_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    m_tables[idx] |= phys;
    for(auto& flag : fgs) {
        m_tables[idx] |= static_cast<uint16_t>(flag);
    }
}

void page_directory::unmap_idx(size_t idx) {
    if(idx >= kernel::PD_SIZE) {
        kernel::panic::panic("page table index greater than page table size", "", true);
    }
    m_tables[idx] = 0;
}

bool page_directory::table_exists(size_t idx) {
    return m_tables[idx] != 0; //yes, i know != 0 is redundant but it helps me visualize it better
}

//


static size_t v_to_dir_idx(uintptr_t virt) {
    return virt >> 22;
}

static size_t v_to_tab_idx(uintptr_t virt) {
    return (virt >> 12) & 0b1111111111;
}

static size_t v_to_pag_off(uintptr_t virt) {
    return virt & 0xFFF;
}


uintptr_t page_directory::virt_to_phys(uintptr_t virt) {
    const auto didx = v_to_dir_idx(virt);
    if(!table_exists(didx)) kernel::panic::panic("address hasn't been allocated yet!", "", true);
    const auto table = kernel::get_table_virt(didx);
    const auto tidx = v_to_tab_idx(virt);
    const auto tentry = ((page_table*)table)->get_entry(tidx);
    return (tentry & 0xFFFFF000) + v_to_pag_off(virt);
}

///
/// HELPER FUNCTIONS
///

template<typename T>
static T& min(T& first, T& second) {
    return first < second ? first : second;
}

template<typename T>
static T min(const T& first, const T& second) {
    return first < second ? first : second;
}

static constexpr size_t PAGE_SIZE_4K {0x400000 / 1024};

template<typename T>
static bool is_aligned(const T& num, T align) {
    return !(num % align);
}

static void check_params(uintptr_t ps, uintptr_t pe, uintptr_t vs, uintptr_t ve) {
    using namespace kernel::panic;
    if(!is_aligned(ps, PAGE_SIZE_4K)) panic("phys_start isn't aligned!", "", true);
    if(!is_aligned(pe, PAGE_SIZE_4K)) panic("phys_end isn't aligned!", "", true);
    if(!is_aligned(vs, PAGE_SIZE_4K)) panic("virt_start isn't aligned!", "", true);
    if(!is_aligned(ve, PAGE_SIZE_4K)) panic("virt_end isn't aligned!", "", true);

    if(ps > pe) panic("phys_start > phys_end!", "", true);
    if(vs > ve) panic("virt_start > virt_end!", "", true);

    if((pe - ps) != (ve - vs)) panic("ranges aren't equal!", "", true);
}

#include <stdio.h>

void kernel::map(uintptr_t phys_start, uintptr_t phys_end, uintptr_t virt_start, uintptr_t virt_end, std::initializer_list<kernel::table_flags> tflags, std::initializer_list<kernel::directory_flags> dflags) {

    check_params(phys_start, phys_end, virt_start, virt_end);
    if(!p_detail::initialized) kernel::panic::panic("PAGING NOT INITIALIZED!", "", true);

    uintptr_t virt_addr {virt_start};
    uintptr_t phys_addr {phys_start};
    uintptr_t virt_next {min(virt_end, virt_addr + PAGE_SIZE_4K)};
    uintptr_t phys_next {min(phys_end, phys_addr + PAGE_SIZE_4K)};
    auto d_idx {v_to_dir_idx(virt_addr)};
    while(virt_addr < virt_end && d_idx < kernel::PD_SIZE) {
        if(!directory->table_exists(d_idx)) {
            auto addr = (page_table*) kernel::kmalloc_aligned(sizeof(page_table));
            directory->map_table(d_idx, directory->virt_to_phys((uintptr_t)addr), dflags);
            tables[d_idx] = addr;
        }
        tables[d_idx]->map_addr(v_to_tab_idx(virt_addr), phys_addr, tflags);

        virt_addr = virt_next;
        phys_addr = phys_next;
        virt_next = min(virt_end, virt_addr + PAGE_SIZE_4K);
        phys_next = min(phys_end, phys_addr + PAGE_SIZE_4K);
        d_idx = v_to_dir_idx(virt_addr);
    }
    printf(" last virt addr to be mapped on this call: 0x%x\n", virt_addr);
    printf(" last pd idx to be used on this call: %d\n", v_to_dir_idx(virt_addr));
}

uintptr_t kernel::get_table_virt(size_t idx) {
    return (uintptr_t)tables[idx];
}

void kernel::init_paging(uintptr_t dir, uintptr_t start_table1, uintptr_t start_table2, size_t start_idx) {
    directory = (page_directory*)dir;
    tables[start_idx] = (page_table*)start_table1;
    tables[start_idx + 1] = (page_table*)start_table2;
    directory->map_table(start_idx, directory->virt_to_phys(start_table1), {kernel::directory_flags::present, kernel::directory_flags::writable});
    directory->map_table(start_idx + 1, directory->virt_to_phys(start_table2), {kernel::directory_flags::present, kernel::directory_flags::writable});

    p_detail::initialized = true;
}
