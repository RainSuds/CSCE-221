#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::out_of_range
#include <type_traits> // std::is_same

template <class T>
class Vector {
public:
    class iterator;
private:
    T* array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow() { /* TODO */ 
        if (_capacity == 0) {
            _capacity++;
        }
        else {
            _capacity *= 2;    
        }
        T* newArray = new T[_capacity];
        for (unsigned int i = 0; i < _size; i++) {
            newArray[i] = std::move(array[i]);
        }
        delete[] array;
        array = newArray;
    }

public:
    Vector() noexcept { /* TODO */ /* Default Constructor */
        array = nullptr;
        _capacity = 0;
        _size = 0;
    }
    Vector(size_t count, const T& value) { /* TODO */ /* Parameterized Constructor */
        _size = count;
        _capacity = _size;
        array = new T[_capacity];

        for (size_t i = 0; i < _size; i++) {
            array[i] = value;
        }
    }
    explicit Vector(size_t count) { /* TODO */ /* Parameterized Constructor */
        _size = count;
        _capacity = _size;
        array = new T[_capacity];

        for (size_t i = 0; i < _size; i++) {
            array[i] = T();
        }
    }
    Vector(const Vector& other) { /* TODO */ /* Copy Constructor */
        array = new T[other._capacity];
        for (unsigned int i = 0; i < other.size(); i++) {
            array[i] = other.array[i];
        } 
        _capacity = other._capacity;
        _size = other._size;
    }
    Vector(Vector&& other) noexcept { /* TODO */ /* Move Constructor */
        array = std::move(other.array);
        _capacity = other._capacity;
        _size = other._size;
        other.array = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    ~Vector() { /* TODO */ /* Destructor */
        delete[] array;
        array = nullptr;
        _capacity = 0;
        _size = 0;
    } 

    Vector& operator=(const Vector& other) { /* TODO */ /* Copy Assignment Operator */
        if (this != &other) {
            delete[] array;
            array = new T[other._capacity];
            for (unsigned int i = 0; i < other.size(); i++) {
                array[i] = other.array[i];
            }
            _capacity = other._capacity;
            _size = other._size;
        }
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept { /* TODO */ /* Move Assignment Operator */
        if (this != &other) {
            delete[] array;
            array = other.array;
            _capacity = other._capacity;
            _size = other._size;
            other.array = nullptr;
            other._capacity = 0;
            other._size = 0;
        }        
        return *this;
    }

    iterator begin() noexcept { /* TODO */ 
        return iterator(array);
    }
    iterator end() noexcept { /* TODO */ 
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept { /* TODO */ 
        return (_size == 0);
    }
    size_t size() const noexcept { /* TODO */ 
        return _size;
    }
    size_t capacity() const noexcept { /* TODO */ 
        return _capacity;
    }

    T& at(size_t pos) { /* TODO */
        if (pos >= _size) {
            throw std::out_of_range("Out of range");
        }
        return array[pos];
    }
    const T& at(size_t pos) const { /* TODO */ 
        if (pos >= _size) {
            throw std::out_of_range("Out of range");
        }
        return array[pos];  
    }
    T& operator[](size_t pos) { /* TODO */ 
        return array[pos];
    }
    const T& operator[](size_t pos) const { /* TODO */ 
        return array[pos];
    }
    T& front() { /* TODO */ 
        return array[0];
    }
    const T& front() const { /* TODO */ 
        return array[0];
    }
    T& back() { /* TODO */ 
        return array[_size - 1];
    }
    const T& back() const { /* TODO */ 
        return array[_size - 1];
    }

    void push_back(const T& value) { /* TODO */ 
        if (_size + 1 > _capacity) {
            grow();
        }
        array[_size] = value;
        _size++;
    }
    void push_back(T&& value) { /* TODO */ 
        if (_size + 1 > _capacity) {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }
    void pop_back() { /* TODO */ 
        if (_size > 0) {
            //delete &array[_size];
            _size--;
        }
    }

    iterator insert(iterator pos, const T& value) { /* TODO */ 
        if (pos >= this->begin() && pos <= this->end() ) {
            unsigned int index = pos - begin();

            if (_size + 1 >= _capacity) {
                grow();
            }
            for (unsigned int i = _size; i > index; i--) {
                array[i] = std::move(array[i - 1]);
            }
            array[index] = value;
            _size++;
            ptrdiff_t difference = index;
            return begin() + difference;  
        }
        else {
            return end();
        }       
    }
    iterator insert(iterator pos, T&& value) { /* TODO */ 
        if (pos >= this->begin() && pos <= this->end() ) {
            unsigned int index = pos - this->begin();

            if (_size + 1 >= _capacity) {
                grow();
            }
            for (unsigned int i = _size; i > index; i--) { // move everything over 1 before pos
                array[i] = std::move(array[i - 1]);
            }
            array[index] = std::move(value); // fill
            _size++;
            ptrdiff_t difference = index;
            return this->begin() + difference;
        }
        else if (pos == this->end() + 1) { // inserting at the end
            unsigned int index = pos - this->begin();
            if (_size + 1 >= _capacity) {
                grow();
            }
            array[index] = value; // fill
            _size++;
            return this->end();
        }
        else {
            return this->end();
        }       
    }
    iterator insert(iterator pos, size_t count, const T& value) { /* TODO */ 
        if (pos >= this->begin() && pos <= this->end() ) {
            unsigned int index = pos - this->begin();

            while ((_size + count) >= _capacity) { // double more times
                grow();
            }
            for (unsigned int i = _size - 1; i >= index; i--) {
                if (i > _capacity) {
                    break;
                }
                array[i + count] = std::move(array[i]);
            }
            for (unsigned int i = 0; i < count; i++) {
                array[index + i] = value;                
            }
            _size += count;
            ptrdiff_t difference = index;
            return this->begin() + difference;
        }
        else {
            return this->end();
        }        
    }
    iterator erase(iterator pos) { /* TODO */ 
        if (pos >= this->begin() && pos < this->end() ) {
            unsigned int index = pos - this->begin();
            for (unsigned int i = index; i < _size - 1; i++) {
                array[i] = std::move(array[i + 1]);
            }
            _size--;
            ptrdiff_t difference = index;
            return this->begin() + difference;
        }
        else if (pos == this->end()) {
            delete[] array;
            _size--;
        }
        return this->end();
    }
    iterator erase(iterator first, iterator last) { /* TODO */ 
        if (first >= this->begin() && last <= this->end() && (first < last)) {
            unsigned int count = last - first;
            unsigned int index = first - this->begin();

            for (unsigned int i = index; i + count < _size; i++) {
                array[i] = std::move(array[i + count]);
            }
            _size -= count;

            return this->begin() + index;
        }
        else if (first == last) {
            return last;
        }
        else {
            return this->end();
        }
    }

    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
        T* ptr;
    public:
        iterator() { /* TODO */ /* Constructor */
            ptr = nullptr;
        }
        // Add any constructors that you may need
        iterator(T* new_ptr) : ptr(new_ptr) {} /* Parameterized Constructor*/

        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept { /* TODO */ 
            return *ptr;
        }
        [[nodiscard]] pointer operator->() const noexcept { /* TODO */ 
            return ptr;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept { /* TODO */ 
            ptr += 1;
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept { /* TODO */ 
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept { /* TODO */
            ptr -= 1; 
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept { /* TODO */ 
            iterator temp = *this;
            --(*this);
            return temp;
        }

        iterator& operator+=(difference_type offset) noexcept { /* TODO */
            ptr = ptr + offset;
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept { /* TODO */ 
            return iterator(ptr + offset);
        }
        
        iterator& operator-=(difference_type offset) noexcept { /* TODO */ \
            ptr = ptr - offset;
            return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept { /* TODO */ 
            return iterator(ptr - offset);
        }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr - rhs.ptr;
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept { /* TODO */ 
            return *(ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr == rhs.ptr;
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept { /* TODO */ 
            return !(*this == rhs);
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr < rhs.ptr;
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr > rhs.ptr;
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr <= rhs.ptr;
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept { /* TODO */ 
            return ptr >= rhs.ptr;
        }
    };


    void clear() noexcept { /* TODO */ 
        delete[] array;
        array = nullptr;
        _size = 0;
    }
};

// This ensures at compile time that the deduced argument _Iterator is a Vector<T>::iterator
// There is no way we know of to back-substitute template <typename T> for external functions
// because it leads to a non-deduced context
namespace {
    template <typename _Iterator>
    using is_vector_iterator = std::is_same<typename Vector<typename _Iterator::value_type>::iterator, _Iterator>;
}

template <typename _Iterator, bool _enable = is_vector_iterator<_Iterator>::value>
[[nodiscard]] _Iterator operator+(typename _Iterator::difference_type offset, _Iterator const& iterator) noexcept { /* TODO */ 
    return iterator + offset;
}

#endif
