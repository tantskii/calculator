#include "helpers.h"

void help::removeSpaces(std::string_view& view) {
	size_t pos = view.find_first_not_of(' ');
	help::removePrefix(view, pos);
}

void help::removePrefix(std::string_view& view, uint32_t n) {
	view.remove_prefix(n > view.size() ? view.size() : n);
}
