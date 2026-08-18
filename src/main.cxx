#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Helpers.h"

constexpr size_t MAX_INPUT_FOR_FACTORIAL = 20;
class FactorialOverflowException : public std::out_of_range
{
  private:
    size_t m_inputValue;
    size_t m_maxSupportedValue;

  public:
    FactorialOverflowException(size_t value, size_t maxVal = MAX_INPUT_FOR_FACTORIAL)
        : std::out_of_range("Factorial argument " + std::to_string(value) +
                            " is not supported. Maximum allowed value is " + std::to_string(maxVal) + "."),
          m_inputValue(value), m_maxSupportedValue(maxVal)
    {
    }

    [[nodiscard]] auto getInputValue() const noexcept -> size_t
    {
        return m_inputValue;
    }
    [[nodiscard]] auto getMaxSupportedValue() const noexcept -> size_t
    {
        return m_maxSupportedValue;
    }
};

auto getFactorial(size_t num) -> size_t;

/// @brief Main logic of the program.
/// @return EXIT_SUCCESS on a successful run, otherwise EXIT_FAILURE.
auto main() -> int
{
    size_t num{0};
    std::string raw_input;
    while (true)
    {
        std::cout << "Enter a number: ";

        if (!(std::cin >> raw_input))
        {
            if (std::cin.eof())
            {
                std::cout << "\nTerminating immediately. [This happens if EOF is reached or if "
                             "CTRL+C was pressed.]\n";
                // terminating via EOF and CTRL+C is the standard way for this program.
                // to print this message for CTRL+C too alongwith EOF is intentional.
                break; // while
            }
        }
        try
        {
            if (isInteger(raw_input) && (raw_input.find('-') != std::string::npos))
            {
                std::cout << "\nNegative numbers not allowed.\n";
                continue;
            }

            if (auto result = safeStringToSizeT(raw_input); result.has_value())
            {
                auto num = *result;

                size_t factorial = getFactorial(num);
                std::cout << "Factorial of " << num << " is " << factorial << "\n";
            }
            else
            {
                std::cout << "\nOnly enter a positive number or zero.\n";
                continue;
            }
        }
        catch (FactorialOverflowException)
        {
            std::cout << "\nOnly factorials between 0 to " << MAX_INPUT_FOR_FACTORIAL << " supported.\n";
            continue;
        }
    }

    return EXIT_SUCCESS;
}

auto getFactorial(size_t num) -> size_t
{
    if (num > MAX_INPUT_FOR_FACTORIAL)
    {
        throw FactorialOverflowException(num);
    }
    size_t result = 1;
    while (num > 0)
    {
        result *= num;
        num -= 1;
    }
    return result;
}
