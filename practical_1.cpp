#include <iostream>
#include <unordered_set>

int main() {
    // Define sets for students who like Math, Science, and both Math and Science
    std::unordered_set<int> mathStudents = {1, 2, 3, 4, 5};      // You can modify these sets as per your data
    std::unordered_set<int> scienceStudents = {3, 4, 5, 6, 7};   // You can modify these sets as per your data
    std::unordered_set<int> mathAndScienceStudents = {3, 4, 5}; // You can modify these sets as per your data

    // Students who like Math only (M - MnS)
    std::unordered_set<int> mathOnlyStudents;
    for (int student : mathStudents) {
        if (mathAndScienceStudents.find(student) == mathAndScienceStudents.end()) {
            mathOnlyStudents.insert(student);
        }
    }

    // Students who like Science only (S - MnS)
    std::unordered_set<int> scienceOnlyStudents;
    for (int student : scienceStudents) {
        if (mathAndScienceStudents.find(student) == mathAndScienceStudents.end()) {
            scienceOnlyStudents.insert(student);
        }
    }

    // Students who like Either Math or Science (MuS)
    std::unordered_set<int> eitherMathOrScienceStudents;
    for (int student : mathStudents) {
        eitherMathOrScienceStudents.insert(student);
    }
    for (int student : scienceStudents) {
        eitherMathOrScienceStudents.insert(student);
    }

    // Print the results
    std::cout << "Students who like Math only (M - MnS): ";
    for (int student : mathOnlyStudents) {
        std::cout << student << " ";
    }
    std::cout << std::endl;

    std::cout << "Students who like Science only (S - MnS): ";
    for (int student : scienceOnlyStudents) {
        std::cout << student << " ";
    }
    std::cout << std::endl;

    std::cout << "Students who like Either Math or Science (MuS): ";
    for (int student : eitherMathOrScienceStudents) {
        std::cout << student << " ";
    }
    std::cout << std::endl;

    return 0;
}
