#include <rattrig/trigonom.hpp>
#include <rattrig/version.h>

#include <cassert>
#include <vector>

auto main() -> int {
    assert(RATTRIG_VERSION_MAJOR == 1);

    const std::vector<int> v{3, 4};
    rattrig::validate_non_negative(v[0], "x");
    const auto q = rattrig::spread(v, v);
    assert(q == 0);

    return 0;
}
