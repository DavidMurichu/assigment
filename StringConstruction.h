#ifndef STRINGCONSTRUCTION_H
#define STRINGCONSTRUCTION_H

#include <string>
using std::string;


// TODO: your code goes here:

#include <vector>

// Custom implementation of min function: returns the smaller of two values
template <typename T>
T my_min(const T& a, const T& b) {
  return (a < b) ? a : b;
}

// Custom implementation of max function: returns the larger of two values
template <typename T>
T my_max(const T& a, const T& b) {
  return (a > b) ? a : b;
}

// Custom implementation of string reversal
// Reverses the input string `s` in place
void custom_reverse(std::string& s) {
  std::size_t n = s.length();
  for (std::size_t i = 0; i < n / 2; ++i) {
    std::swap(s[i], s[n - i - 1]); // Swap characters from both ends
  }
}

using Cost = unsigned long long; // Define a type alias for cost

// Computes the Z-function for a string
// Z-function computes the length of the longest substring starting at each
// position `i` that matches the prefix of the string.
std::vector<std::size_t> ZFunction(std::string s) {
  std::size_t n = s.length();
  std::vector<std::size_t> z(n); // Z-array to store the Z-values
  for (std::size_t i = 1, l = 0, r = 0; i < n; i++) {
    // If i is within the current Z-box, calculate the initial Z-value
    if (i <= r) {
      z[i] = my_min(r - i + 1, z[i - l]);
    }
    // Extend the Z-box by comparing characters
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    // Update the boundaries of the Z-box
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

// Finds the length of the longest prefix of the string `s` that can be created
// by cloning a suffix of `s`.
std::size_t BestClone(std::string s) {
  std::string r{s};       // Create a reversed copy of the string
  custom_reverse(r);      // Reverse the string using the custom_reverse function
  auto z = ZFunction(r);  // Compute the Z-function for the reversed string
  std::size_t best = 0;   // Variable to track the best cloneable prefix
  for (std::size_t i = 0; i < z.size(); i++) {
    // Update the best value using the maximum of current best and the minimum
    // of the Z-value or the index `i`
    best = my_max(best, my_min(z[i], i));
  }
  return s.length() - best; // Return the length of the non-cloneable portion
}

// Computes the minimum cost to construct a string `s`
// `clone_cost`: Cost of cloning a substring
// `append_cost`: Cost of appending a single character
Cost stringConstruction(std::string s, Cost clone_cost, Cost append_cost) {
  std::vector<Cost> costs = {0}; // Store cumulative costs for each prefix of `s`
  for (std::size_t j = 0; j < s.length(); j++) {
    // Find the best prefix that can be cloned to construct the current prefix
    std::size_t i = BestClone(s.substr(0, j + 1));
    if (i <= j) {
      // Either append the remaining characters or clone from the best prefix
      costs.push_back(
          my_min(costs.back() + append_cost, costs[i] + clone_cost));
    } else {
      // If no cloning is possible, append the character
      costs.push_back(costs.back() + append_cost);
    }
  }
  return costs.back(); // Return the total cost to construct the string
}

// do not write or edit anything below this line

#endif
