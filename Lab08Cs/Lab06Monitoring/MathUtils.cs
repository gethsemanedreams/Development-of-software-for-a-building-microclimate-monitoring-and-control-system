using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab06Monitoring
{
    /// <summary>
    /// Вспомогательный класс с обобщёнными вычислительными методами (ЛР‑8).
    /// </summary>
    public static class MathUtils
    {
        /// <summary>
        /// Обобщённая функция вычисления среднего значения.
        /// Разрешены только значимые типы, реализующие IConvertible (обычно числовые).
        /// Это даёт ограничение типов на этапе компиляции: ссылочные типы использовать нельзя.
        /// </summary>
        public static double Average<T>(IEnumerable<T> values) where T : struct, IConvertible
        {
            if (values == null) throw new ArgumentNullException(nameof(values));

            var list = values.ToList();
            if (list.Count == 0)
            {
                throw new ArgumentException("Collection must not be empty.", nameof(values));
            }

            decimal sum = 0;
            foreach (var v in list)
            {
                sum += Convert.ToDecimal(v);
            }

            decimal result = sum / list.Count;
            return (double)result;
        }
    }
}
