#pragma once
#include <cstddef>
#include <exception>
#include "Monitor.h"

template <typename T>
class Pointer {
    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = ptrdiff_t;

    private:
        T* _ptr;

    public:
        Pointer(): _ptr(nullptr) {}
        Pointer(T* ptr): _ptr(ptr) {}
        Pointer(const Pointer& other): _ptr(other._ptr) {}

        T& operator[](size_t offset) { 
            Monitor::update_brackets();
            return _ptr[offset]; 
        }
        T& operator*() const noexcept { return *_ptr; }
        T* operator->() const noexcept { return _ptr; }

        Pointer& operator++() noexcept {
            Monitor::update_iterate();
            ++_ptr;
            return *this;
        }
        Pointer operator++(int) noexcept {
            Monitor::update_iterate();
            Pointer temp(*this);
            ++(*this);
            return temp;
        }
        Pointer& operator--() noexcept {
            Monitor::update_iterate();
            --_ptr;
            return *this;
        }
        Pointer operator--(int) noexcept {
            Monitor::update_iterate();
            Pointer temp(*this);
            --(*this);
            return temp;
        }
        Pointer& operator+=(difference_type offset) noexcept {
            Monitor::update_iterate();
            _ptr += offset;
            return *this;
        }
        Pointer operator+(difference_type offset) const noexcept {
            Monitor::update_iterate();
            Pointer temp(*this);
            return temp += offset;
        }
        Pointer& operator-=(difference_type offset) noexcept {
            Monitor::update_iterate();
            _ptr -= offset;
            return *this;
        }
        Pointer operator-(difference_type offset) const noexcept {
            Monitor::update_iterate();
            Pointer temp(*this);
            return temp -= offset;
        }
        difference_type operator-(const Pointer& rhs) const noexcept {
            return _ptr - rhs._ptr;
        }

        bool operator!() const { return !_ptr; }

        bool operator==(const Pointer& rhs) const noexcept { return _ptr == rhs._ptr; }
        bool operator!=(const Pointer& rhs) const noexcept { return _ptr != rhs._ptr; }
        bool operator<(const Pointer& rhs) const noexcept { return _ptr < rhs._ptr; }
        bool operator>(const Pointer& rhs) const noexcept { return _ptr > rhs._ptr; }
        bool operator<=(const Pointer& rhs) const noexcept { return _ptr <= rhs._ptr; }
        bool operator>=(const Pointer& rhs) const noexcept { return _ptr >= rhs._ptr; }
};

template <typename _Pointer>
_Pointer operator+(typename _Pointer::difference_type offset, _Pointer const& p) noexcept {
    return p + offset;
}
