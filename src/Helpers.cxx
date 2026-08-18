#include "Helpers.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>

/// @brief Safe std::string to size_t conversion using std::stringstream
/// @param str std::string
/// @return std::optional wrapper of size_t represented by the std::string.
auto safeStringToSizeT(const std::string &str) -> std::optional<size_t>
{
    std::stringstream sstream(str);
    size_t value{};

    // Attempt to extract the integer
    if (!(sstream >> value))
    {
        return std::nullopt; // Extraction failed (e.g., non-numeric input "abc")
    }

    // Check for trailing unparsed characters (e.g., "123abc")
    char remaining{};
    if (sstream >> remaining)
    {
        return std::nullopt; // Extra characters were found after the number
    }

    return value;
}

/// @brief Helper to check for minus sign
/// @param sv takes a string_view or string (converted to string_view)
/// @return true if str represents a valid integer otherwise false.
auto isInteger(std::string_view sv) -> bool
{
    if (sv.empty())
    {
        return false;
    }

    // Remove leading sign if present
    if (sv.front() == '-' || sv.front() == '+')
    {
        sv.remove_prefix(1);
    }

    // Must have at least one digit remaining (prevents "+" or "-")
    if (sv.empty())
    {
        return false;
    }

    // Validate remaining characters
    return std::all_of(sv.begin(), sv.end(), [](unsigned char c) -> bool { return std::isdigit(c); });
}
