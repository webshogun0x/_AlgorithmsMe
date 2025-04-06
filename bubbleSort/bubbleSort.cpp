#include <iostream>
#include <vector>

void bubbleSort(std::vector<int>& toys) {
    int size = toys.size();
    bool swapped;
    
    // Loop through all array elements
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < size - i - 1; j++) {
            // If the element on the left is bigger than the element on the right
            if (toys[j] > toys[j + 1]) {
                // Swap them!
                std::swap(toys[j], toys[j + 1]);
                swapped = true;
            }
        }
        // If no swapping occurred in this pass, array is sorted
        if (!swapped) {
            break;
        }
    }
}

void printItems(const std::vector<int>& toys) {
    for (int toy : toys) {
        std::cout << toy << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> BlockSizes = {9, 5, 1, 4, 3};
    std::cout << "Toy blocks before sorting (mixed up): ";
    printItems(BlockSizes);
    bubbleSort(BlockSizes);
    std::cout << "Toy blocks after sorting (smallest to biggest): ";
    printItems(BlockSizes);
    
    return 0;
}