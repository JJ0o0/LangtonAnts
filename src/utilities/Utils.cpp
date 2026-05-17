#include <LangtonAnts/utilities/Utils.hpp>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

namespace JJ0o0::LangtonAnts::Utils {
std::string IntToString(int number) { return std::to_string(number); }
std::string FloatToString(float number, int precision) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(precision) << number;
  return oss.str();
}
} // namespace JJ0o0::LangtonAnts::Utils