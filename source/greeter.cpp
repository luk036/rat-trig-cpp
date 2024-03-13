#include <fmt/format.h>
#include <rattrig/greeter.h>

using namespace rattrig;

RatTrig::RatTrig(std::string _name) : name(std::move(_name)) {}

std::string RatTrig::greet(LanguageCode lang) const {
  switch (lang) {
    default:
    case LanguageCode::EN:
      return fmt::format("Hello, {}!", name);
    case LanguageCode::DE:
      return fmt::format("Hallo {}!", name);
    case LanguageCode::ES:
      return fmt::format("¡Hola {}!", name);
    case LanguageCode::FR:
      return fmt::format("Bonjour {}!", name);
  }
}
