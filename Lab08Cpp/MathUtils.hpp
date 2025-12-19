#pragma once
#include <vector>
#include <type_traits>
#include <stdexcept>

/// \brief Шаблонная функция для вычисления среднего значения.
///
/// Используется в ЛР-8. Работает только с числовыми типами (int, float, double и т.п.),
/// что контролируется static_assert-ом на этапе компиляции.
template <typename T>
T ComputeAverage(const std::vector<T>& values)
{
    static_assert(std::is_arithmetic<T>::value,
                  "ComputeAverage can be used only with arithmetic (numeric) types");

    if (values.empty())
    {
        throw std::invalid_argument("values must not be empty");
    }

    T sum{};
    for (const auto& v : values)
    {
        sum += v;
    }

    return sum / static_cast<T>(values.size());
}
