#pragma once

#include <vector>

template<typename T>
class Memory {
protected:
    std::vector<T> memory;
public:
    virtual T &operator[](int) = 0;
    virtual std::size_t size() const = 0;
};
