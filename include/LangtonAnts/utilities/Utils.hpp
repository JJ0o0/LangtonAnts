#pragma once

#include <string>

namespace JJ0o0::LangtonAnts::Utils {
enum class Direction { North, East, South, West };

std::string IntToString(int number);
std::string FloatToString(float number, int precision);
} // namespace JJ0o0::LangtonAnts::Utils