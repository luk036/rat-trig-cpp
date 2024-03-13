#pragma once

#include <string>

namespace rattrig {

  /**  Language codes to be used with the RatTrig class */
  enum class LanguageCode { EN, DE, ES, FR };

  /**
   * @brief A class for saying hello in multiple languages
   */
  class RatTrig {
    std::string name;

  public:
    /**
     * @brief Creates a new rattrig
     * @param name the name to greet
     */
    RatTrig(std::string name);

    /**
     * @brief Creates a localized string containing the greeting
     * @param lang the language to greet in
     * @return a string containing the greeting
     */
    std::string greet(LanguageCode lang = LanguageCode::EN) const;
  };

}  // namespace rattrig
