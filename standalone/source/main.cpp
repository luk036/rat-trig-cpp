#include <rattrig/greeter.h>
#include <rattrig/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
    const std::unordered_map<std::string, rattrig::LanguageCode> languages{
        {"en", rattrig::LanguageCode::EN},
        {"de", rattrig::LanguageCode::DE},
        {"es", rattrig::LanguageCode::ES},
        {"fr", rattrig::LanguageCode::FR},
    };

    cxxopts::Options options(*argv, "A program to welcome the world!");

    std::string language;
    std::string name;

    // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result["version"].as<bool>()) {
        std::cout << "RatTrig, version " << RATTRIG_VERSION << std::endl;
        return 0;
    }

    auto lang_iter = languages.find(language);
    if (lang_iter == languages.end()) {
        std::cerr << "unknown language code: " << language << std::endl;
        return 1;
    }

    rattrig::RatTrig rattrig_app(name);
    std::cout << rattrig_app.greet(lang_iter->second) << std::endl;

    return 0;
}
