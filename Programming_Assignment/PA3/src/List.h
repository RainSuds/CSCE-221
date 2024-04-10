#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() : node(nullptr) { /* TODO */ };
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            // TODO
            return node->data;
        }
        pointer operator->() const {
            // TODO
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            // TODO
            if (node) {
                node = node->next;
            }
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            // TODO
            basic_iterator temp = *this;
            ++(*this);
            return temp;
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            // TODO
            if (node) {
                node = node->prev;
            }
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            // TODO
            basic_iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const basic_iterator& other) const noexcept {
            // TODO
            return node == other.node;
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            // TODO
            return !(node == other.node);
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head(), tail(), _size(0) {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
    }
    List( size_type count, const T& value ) : head(), tail(), _size(0) {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        for (unsigned int i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    explicit List( size_type count ) : head(), tail(), _size(0) {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        for (unsigned int i = 0; i < count; ++i) {
            T defaultValue = T{};
            push_back(std::move(defaultValue));
        }
    }
    List( const List& other ) : head(), tail(), _size(0) {
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        for (const_iterator it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }
    List(List&& other) noexcept : head(), tail(), _size(other._size) {
        if (!other.empty()) {
            head.next = other.head.next;
            tail.prev = other.tail.prev;
            head.next->prev = &head;
            tail.prev->next = &tail;
            other.head.next = &other.tail;
            other.tail.prev = &other.head;
            other._size = 0;
        }
        else {
            head.next = &tail;
            tail.prev = &head;
        }        
    }
    ~List() {
        // TODO
        clear();
    }
    List& operator=( const List& other ) {
        // TODO
        if (this != &other) {
            clear();
            for (const_iterator it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }
        return *this;
    }
    List& operator=( List&& other ) noexcept {
        // TODO /* Move operator*/
        if (this != &other) {
            clear();
            if (!other.empty()) {
                head.next = other.head.next;
                tail.prev = other.tail.prev;
                head.next->prev = &head;
                tail.prev->next = &tail;
                _size = other._size;

                other.head.next = &other.tail;
                other.tail.prev = &other.head;
                other._size = 0;
            }
            else {
                head.next = &tail;
                tail.prev = &head;
                _size = 0;
            }
            
        }
        return *this;
    }

    reference front() {
        // TODO
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head.next->data;
    }
    const_reference front() const {
        // TODO
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return head.next->data;
    }
	
    reference back() {
        // TODO
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail.prev->data;
    }
    const_reference back() const {
        // TODO
        if (empty()) {
            throw std::out_of_range("List is empty");
        }
        return tail.prev->data;
    }
	
    iterator begin() noexcept {
        // TODO
        if (empty()) {
            return end();
        }
        return iterator(head.next);
    }
    const_iterator begin() const noexcept {
        // TODO
        if (empty()) {
            return end();
        }
        return const_iterator(head.next);
    }
    const_iterator cbegin() const noexcept {
        // TODO
        if (empty()) {
            return cend();
        }
        return begin();
    }

    iterator end() noexcept {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept {
        // TODO
        return const_iterator(&tail);
    }
    const_iterator cend() const noexcept {
        // TODO
        return const_iterator(&tail);
    }

    bool empty() const noexcept {
        // TODO
        return head.next == &tail;
    }

    size_type size() const noexcept {
        // TODO
        return _size;
    }

    void clear() noexcept {
        // TODO
        while (!empty()) {
            deleteNode(head.next);
        }
    }

    void deleteNode(Node* node) noexcept {
        if (node) {
            if (node->next) {
                node->next->prev = node->prev;
            }
            if (node->prev) {
                node->prev->next = node->next;
            }
            delete node;
            --_size;
        }
    }

    iterator insert( const_iterator pos, const T& value ) {
        // TODO
        Node* newNode = new Node(value);
        Node* curr = pos.node;

        if (pos == begin()) {
            newNode->next = head.next;
            newNode->prev = &head;
            head.next->prev = newNode;
            head.next = newNode;
        }
        else if (pos == end()) {
            newNode->next = &tail;
            newNode->prev = tail.prev;
            tail.prev->next = newNode;
            tail.prev = newNode;
        }
        else {
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
        }        
        ++_size;
        return iterator(newNode);
    }
    iterator insert( const_iterator pos, T&& value ) {
        // TODO
        Node* newNode = new Node(std::move(value));
        Node* curr = pos.node;

        if (pos == begin()) {
            newNode->next = head.next;
            newNode->prev = &head;
            head.next->prev = newNode;
            head.next = newNode;
            ++_size;
        }
        else if (pos == end()) {
            push_back(value);
        }
        else {
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
            ++_size;
        }        
        
        return iterator(newNode);
    }

    iterator erase( const_iterator pos ) {
        // TODO
        if (pos == end()) {
            return end();
        }
        Node* nodeToDelete = pos.node;
        Node* prev = nodeToDelete->prev;
        
        if (pos == begin()) {
            head.next = head.next->next;
            head.next->prev = &head;
        }
        else {
            prev->next = nodeToDelete->next;
            nodeToDelete->next->prev = prev;
        }
        delete nodeToDelete;
        --_size;

        return iterator(prev->next);
    }

    void push_back( const T& value ) {
        // TODO
        Node* newNode = new Node(value, tail.prev);
        tail.prev->next = newNode;
        tail.prev = newNode;
        newNode->next = &tail;
        ++_size;
    }
    void push_back( T&& value ) {
        // TODO
        Node* newNode = new Node(std::move(value), tail.prev);
        tail.prev->next = newNode;
        tail.prev = newNode;
        newNode->next = &tail;
        ++_size;
    }

    void pop_back() {
        // TODO
        Node* nodeToDelete = tail.prev;
        nodeToDelete->prev->next = &tail;
        tail.prev = nodeToDelete->prev;
        delete nodeToDelete;
        --_size;
    }
	
    void push_front( const T& value ) {
        // TODO
        insert(begin(), value);
    }
	void push_front( T&& value ) {
        // TODO
        insert(begin(), std::move(value));
    }

    void pop_front() {
        // TODO
        erase(begin());
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}

