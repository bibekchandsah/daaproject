#include <iostream>
#include <vector>
#include <iomanip> // For formatting output

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

double alphaApproximation(int n) {
    // Approximate values for α(n) based on input size
    if (n <= 10) return 4.0;
    else if (n <= 100) return 4.3;
    else if (n <= 1000) return 4.6;
    else if (n <= 10000) return 5.0;
    else if (n <= 100000) return 5.5;
    else return 6.0;
}

void analyzeDisjointSet(int n) {
    DisjointSet ds(n);
    ds.resetStepCount();

    // Perform union operations on all consecutive pairs
    for (int i = 0; i < n - 1; ++i) {
        ds.unionSets(i, i + 1);
    }

    // Perform find operations on all elements
    for (int i = 0; i < n; ++i) {
        ds.find(i);
    }

    int observedSteps = ds.getStepCount();
    double alpha_n = alphaApproximation(n);
    double expectedSteps = n * alpha_n;
    double asymptoticConstant = observedSteps / expectedSteps;

    std::cout << std::setw(10) << n 
              << std::setw(25) << observedSteps 
              << std::setw(30) << expectedSteps 
              << std::setw(35) << asymptoticConstant 
              << std::endl;
}

int main() {
    std::cout << "Disjoint Set Complexity Analysis\n";
    std::cout << "--------------------------------\n";

    int n;
    char choice;

    do {
        std::cout << "Enter the size of input (n): ";
        std::cin >> n;

std::cout << std::setw(10) << "Input Size (n)" 
              << std::setw(25) << "Observed Steps (C1)" 
              << std::setw(30) << "Expected Steps (C2)" 
              << std::setw(35) << "Asymptotic Constant (C1/C2)" 
              << std::endl;

    std::cout << "------------------------------------------------------------------------------------------------------------\n";
        analyzeDisjointSet(n);

        std::cout << "\nDo you want to enter another input size? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}