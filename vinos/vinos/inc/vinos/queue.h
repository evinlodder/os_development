#ifndef QUEUE_H
#define QUEUE_H
//this is a work-in progress, bare-bones implementation, also not standard

namespace vinos {

template <typename T>
class queue {
public:
    T const& front() const noexcept {
        return begin->value;
    }

    T const& back() const noexcept {
        return end->value;
    }

    inline bool empty() const noexcept {
        return begin->next == nullptr;
    }

    unsigned int size() const noexcept {
        node* current = begin;
        unsigned count{};
        while(current->next != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void push(T const& value) noexcept {
        node n{value};
        end->next = n;
        end = end->next;
    }

    void pop() noexcept {
        node* temp = begin->next;
        delete begin;
        begin = temp;
    }

    queue() : begin(nullptr), end(nullptr) {}
    ~queue() = default;
private:
    //yes i know linked list isn't probably the best idea, but it's what i can currently implement since i dont have memory management yet
    struct node {
        T value;
        node* next;
        node(T const& val, node* nex = nullptr) : value(val), next(nex) {};
    };
    node* begin;
    node* end;
};

}
#endif //QUEUE_H
