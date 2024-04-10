#include <iostream>
#include <list>

//Problem 1
std::list<int> intersection(const std::list<int>& l1, const std::list<int>& l2) {
    std::list<int> ans;
    auto it1 = l1.begin();
    auto it2 = l2.begin();

    while (it1 != l1.end() && it2 != l2.end()) {
        if (*it1 < *it2) {
            ++it1;
        }
        else if (*it1 > *it2) {
            ++it2;
        }
        else {
            ans.push_back(*it1);
            ++it1;
            ++it2;
        }
    }
    return ans;
}

//Problem 2
template<typename T>
struct Node {
    Node* next;
    T obj;
    Node(T obj, Node* next = nullptr)   
    : obj(obj), next(next)
    { }
};

template<typename T>
int count_nodes(Node<T>* node) {
    // Insert code
    if (node == nullptr) {
        return 0;
    }
    return 1 + count_nodes(node->next);
}

//Problem 3
#include <vector>

int find_max_value(std::vector<int> vec, int start, int end) {
	// Insert code
    if (start == end) {
        return vec[start];
    }
    else {
        int mid = (start + end) / 2;
        int max_left = find_max_value(vec, start, mid);
        int max_right = find_max_value(vec, mid + 1, end);
        return (max_left > max_right) ? max_left : max_right;
    }
}

//Problem 5
template<typename T>
int count_filled_nodes(const Node<T>* node) {
    if (node == nullptr) {
        return 0; // Base case: empty tree or leaf node
    }

    // Check if the current node has both left and right children
    int count = 0;
    if (node->left != nullptr && node->right != nullptr) {
        count = 1;
    }

    // Recursively count filled nodes in the left and right subtrees
    count += count_filled_nodes(node->left);
    count += count_filled_nodes(node->right);

    return count;
}


int main() {
    // std::list<int> l1 = {2, 4, 6, 8, 10};
    // std::list<int> l2 = {2, 6, 10};

    // std::list<int> result = intersection(l1, l2);

    // std::cout << "Intersection of l1 and l2: ";
    // for (const int& num : result) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    // // Test case 1: Count nodes in a non-empty list
    // Node<int> *list1 = new Node<int>(2, new Node<int>(4, new Node<int>(3, nullptr)));
    // int count1 = count_nodes(list1);
    // std::cout << "Number of nodes in list1: " << count1 << std::endl;

    // // Test case 2: Count nodes in an empty list
    // Node<int> *list2 = nullptr;
    // int count2 = count_nodes(list2);
    // std::cout << "Number of nodes in list2: " << count2 << std::endl;

    // // Clean up memory (optional)
    // while (list1 != nullptr) {
    //     Node<int> *temp = list1;
    //     list1 = list1->next;
    //     delete temp;
    // }

    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::cout << find_max_value(v1) << std::endl;

    std::vector<int> v2;
    std::cout << find_max_value(v2) << std::endl;

    return 0;
}
