#include <iostream>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent, rank;
    int stepCount = 0; // Counter for step analysis

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        stepCount++; // Counting step
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            stepCount++; // Counting step
            if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    int getStepCount() const {
        return stepCount;
    }

    void resetStepCount() {
        stepCount = 0;
    }
};

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;
    DisjointSet ds(n);

    int choice;
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Union\n";
        std::cout << "2. Find\n";
        std::cout << "3. Check if two elements are connected\n";
        std::cout << "4. Show step count for operations\n";
        std::cout << "5. Reset step count\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        int u, v;
        switch (choice) {
        case 1:
            std::cout << "Enter two elements to union: ";
            std::cin >> u >> v;
            if (u >= 0 && u < n && v >= 0 && v < n) {
                ds.unionSets(u, v);
                std::cout << "Union performed between " << u << " and " << v << ".\n";
            } else {
                std::cout << "Invalid elements.\n";
            }
            break;

        case 2:
            std::cout << "Enter element to find its set representative: ";
            std::cin >> u;
            if (u >= 0 && u < n) {
                int root = ds.find(u);
                std::cout << "The set representative of " << u << " is " << root << ".\n";
            } else {
                std::cout << "Invalid element.\n";
            }
            break;

        case 3:
            std::cout << "Enter two elements to check connection: ";
            std::cin >> u >> v;
            if (u >= 0 && u < n && v >= 0 && v < n) {
                if (ds.find(u) == ds.find(v)) {
                    std::cout << u << " and " << v << " are connected.\n";
                } else {
                    std::cout << u << " and " << v << " are not connected.\n";
                }
            } else {
                std::cout << "Invalid elements.\n";
            }
            break;

        case 4:
            std::cout << "Total steps taken for operations: " << ds.getStepCount() << "\n";
            break;

        case 5:
            ds.resetStepCount();
            std::cout << "Step count reset.\n";
            break;

        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}