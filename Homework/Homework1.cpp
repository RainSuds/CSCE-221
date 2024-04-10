#include <iostream>
#include <vector>
#include <cmath>

/*
(10 points) Use the STL class \texttt{vector<int>} to write two C++
functions that return true if there exist \textbf{two} elements of
the vector such that their \textbf{product} is divisible by 12, and
return false otherwise. The efficiency of the first function should
be $O(n)$ and the efficiency of second one should be $O(n^{2})$
where $n$ is the size of the vector.
*/

bool productDivisibleBy12_O_N(const std::vector<int>& nums) {
    int countDivBy2 = 0;
    int countDivBy3 = 0;
    int countDivBy4 = 0;
    int countDivBy6 = 0;

    for (int num : nums) {
        if (num % 12 == 0 && nums.size() >= 2)
            return true;
        else if (num % 6 == 0)
            countDivBy6;
        else if (num % 4 == 0)
            countDivBy4++;
        else if (num % 3 == 0)
            countDivBy3++;
        else if (num % 2 == 0)
            countDivBy2++;           
    }
    // 3*4 2*6
    if (countDivBy4 >= 1 && countDivBy3 >= 1)
        return true;
    if (countDivBy2 >= 1 && countDivBy6 >= 1)
        return true;

    return false;
}

bool productDivisibleBy12_O_N2(const std::vector<int>& nums) {
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] * nums[j] % 12 == 0)
                return true;
        }
    }

    return false;
}

/*
Implement a templated C++ function for the binary search
algorithm based on the set of the lecture slides Analysis
of Algorithms.

Be sure that before calling Binary_Search, elements of the
vector v are arranged in ascending order. The function
should also keep track of the number of comparisons used to find the
target x. The (global) variable \texttt{num\_comp} keeps
the number of comparisons and initially should be set to zero.
\item[\textbf{Solution:}]
*/

int Binary_Search(std::vector<int> &v, int x, int &num_comp) {
    int mid, low = 0;
    int high = (int) v.size() - 1;
    while (low < high) {
        mid = (low + high) / 2;

        if (num_comp++, v[mid] < x)
            low = mid+1;
        else
            high = mid;
        }
    if (num_comp++, x == v[low]) return low; //OK: found
    return -1; //not found
}

template <typename Compare>
int Binary_Search_Descending(std::vector<int> &v, int x, int &num_comp, Compare cmp) {
    int mid, low = 0;
    int high = static_cast<int>(v.size()) - 1;
    while (low < high) {
        mid = (low + high) / 2;

        if (++num_comp, cmp(x, v[mid])) // Use the comparison function object
            low = mid + 1;
        else
            high = mid;
    }
    if (num_comp++, x == v[low]) return low; // OK: found
    return -1; // not found
}

int main() {
    // std::vector<int> vec = {1, 2, 3, 5, 7, 9, 11};
    // std::cout << productDivisibleBy12_O_N(vec) << std::endl;
    int k = 3;
    int size = pow(2, k);
    std::vector<int> descending_vector(size);
    for (unsigned int i = 0; i < descending_vector.size(); ++i) {
        descending_vector[i] = descending_vector.size() - i;
    }
    int num_comp = 0; // Initialize the comparison counter
    int target = 1;
    int result = Binary_Search_Descending(descending_vector, target, num_comp, std::greater<int>());
    std::cout << "For vector:" << std::endl <<  "{ " ;
    for (unsigned int i = 0; i < descending_vector.size(); ++i) {
        std::cout << descending_vector[i] << " ";
    }
    std::cout << "}" << std::endl;

    if (result != -1) {
        std::cout << "Element " << target << " found at index " << result << std::endl;
    }
    else {
        std::cout << "Element " << target << " not found." << std::endl;
    }
    std::cout << "Number of comparisons: " << num_comp << std::endl;

    return 0;
}