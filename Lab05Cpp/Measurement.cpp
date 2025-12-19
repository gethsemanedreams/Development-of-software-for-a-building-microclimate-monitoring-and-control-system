#include "Measurement.hpp"
#include <iomanip>
#include <ctime>

Measurement::Measurement(const std::string& sensorId,
                         float value,
                         std::chrono::system_clock::time_point timestamp)
    : m_sensorId(sensorId)
    , m_value(value)
    , m_timestamp(timestamp)
{
}

Measurement::Measurement(const Measurement& other)
    : m_sensorId(other.m_sensorId)
    , m_value(other.m_value)
    , m_timestamp(other.m_timestamp)
{
}

std::ostream& operator<<(std::ostream& os, const Measurement& m)
{
    auto t = std::chrono::system_clock::to_time_t(m.m_timestamp);

    std::tm tmBuf{};
    localtime_s(&tmBuf, &t);

    os << "Measurement{sensor=" << m.m_sensorId
        << ", value=" << std::fixed << std::setprecision(2) << m.m_value
        << ", time=" << std::put_time(&tmBuf, "%F %T") << "}";

    return os;
}


bool Measurement::operator<(const Measurement& other) const
{
    return m_value < other.m_value;
}

bool Measurement::operator==(const Measurement& other) const
{
    return m_sensorId == other.m_sensorId &&
           m_value == other.m_value &&
           m_timestamp == other.m_timestamp;
}

