#include <iostream>
#include <vector>

// Function to merge two sorted halves
void merge(std::vector<int>& toys, int left, int mid, int right) {
    // Calculate sizes of the two sub-arrays
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    std::vector<int> leftToys(n1);
    std::vector<int> rightToys(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftToys[i] = toys[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightToys[j] = toys[mid + 1 + j];
    }
    
    // Merge the temporary arrays back
    int i = 0;    // Index for left array
    int j = 0;    // Index for right array
    int k = left; // Index for merged array
    
    // Compare and place the smaller toy first
    while (i < n1 && j < n2) {
        if (leftToys[i] <= rightToys[j]) {
            toys[k] = leftToys[i];
            i++;
        } else {
            toys[k] = rightToys[j];
            j++;
        }
        k++;
    }
    
    // Copy any remaining toys from the left array
    while (i < n1) {
        toys[k] = leftToys[i];
        i++;
        k++;
    }
    
    // Copy any remaining toys from the right array
    while (j < n2) {
        toys[k] = rightToys[j];
        j++;
        k++;
    }
}


void mergeSort(std::vector<int>& toys, int left, int right) {
    // Base case: if there's only one toy or none, it's already sorted
    if (left >= right) {
        return;
    }
    
    int mid = left + (right - left) / 2;
    mergeSort(toys, left, mid);
    mergeSort(toys, mid + 1, right);
    merge(toys, left, mid, right);
}

void mergeSort(std::vector<int>& toys) {
    mergeSort(toys, 0, toys.size() - 1);
}

void printToys(const std::vector<int>& toys) {
    for (int toy : toys) {
        std::cout << toy << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Create a collection of toy blocks with different heights
    std::vector<int> toyBlocks = {9, 5, 1, 4, 3, 8, 2, 7, 6};
    
    std::cout << "Toy blocks before sorting (mixed up): ";
    printToys(toyBlocks);
    mergeSort(toyBlocks);
    std::cout << "Toy blocks after sorting (smallest to biggest): ";
    printToys(toyBlocks);
    
    return 0;
}