#pragma once

template<typename N, typename I, typename K>
class Heap {
public:
    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual std::pair <I, K> top() const = 0;

    virtual void push(I id, K key) = 0;

    virtual void pop() = 0;

    virtual void increase_priority(I id, K key) = 0;

    virtual void erase(I id) = 0;
};