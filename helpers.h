#include <string_view>

namespace help {
	void removePrefix(std::string_view& view, uint32_t n);
	void removeSpaces(std::string_view& view);
}
