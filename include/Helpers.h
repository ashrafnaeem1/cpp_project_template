#pragma once
#include <optional>
#include <string>
#include <string_view>

auto safeStringToSizeT(const std::string &str) -> std::optional<size_t>;
auto isInteger(std::string_view sv) -> bool;
