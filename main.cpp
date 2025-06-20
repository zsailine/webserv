#include <iostream>
#include <string>
#include <algorithm>
#include <cctype> // Pour std::isspace

std::string supprimerEspaces(const std::string& str) {
    std::string result = str;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}
