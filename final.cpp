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
        std::cout << "Enter the size of input (n) for complexity analysis or -1 for menu options: ";
        std::cin >> n;

        if (n == -1) {
            std::cout << "Enter the number of elements for interactive operations: ";
            std::cin >> n;
            DisjointSet ds(n);

            int menuChoice;
            while (true) {
                std::cout << "\nMenu:\n";
                std::cout << "1. Union\n";
                std::cout << "2. Find\n";
                std::cout << "3. Check if two elements are connected\n";
                std::cout << "4. Show step count for operations\n";
                std::cout << "5. Reset step count\n";
                std::cout << "0. Exit menu\n";
                std::cout << "Enter your choice: ";
                std::cin >> menuChoice;

                if (menuChoice == 0) {
                    break;
                }

                int u, v;
                switch (menuChoice) {
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
        } else {
            std::cout << std::setw(10) << "Input Size (n)" 
                      << std::setw(25) << "Observed Steps (C1)" 
                      << std::setw(30) << "Expected Steps (C2)" 
                      << std::setw(35) << "Asymptotic Constant (C1/C2)" 
                      << std::endl;
            std::cout << "------------------------------------------------------------------------------------------------------------\n";
            analyzeDisjointSet(n);
        }

        std::cout << "\nDo you want to enter another input size or return to the main menu? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
