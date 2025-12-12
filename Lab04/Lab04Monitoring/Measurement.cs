// Класс Measurement хранит одно измерение датчика.
using System.Globalization;


namespace Lab04Monitoring
{
    public class Measurement
    {
        // Идентификатор датчика, с которого получено измерение.
        public string SensorId { get; }

        // Числовое значение измерения.
        public float Value { get; }

        // Момент времени в текстовом виде (ISO-формат).
        public string Timestamp { get; }

        public Measurement(string sensorId, float value, string timestamp)
        {
            SensorId = sensorId;
            Value = value;
            Timestamp = timestamp;
        }

        // Проверяем, что измерение не выходит за указанный диапазон.
        public bool IsAnomalous(float min, float max)
        {
            return Value < min || Value > max;
        }

        public override string ToString()
        {
            // Используем CultureInfo.InvariantCulture, чтобы всегда была точка как разделитель
            // и одинаковый формат независимо от русской/английской локали.
            return $"{Timestamp}: sensor={SensorId}, value={Value.ToString("F2", CultureInfo.InvariantCulture)}";
        }
    }
}
