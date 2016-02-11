#ifndef GUARD_5_h
#define GUARD_5_h

#include <iostream>
#include <vector>

struct wc_map {
	std::string word;
	int count;
};
std::istream& read_words(std::istream& is, 
                         std::vector<wc_map>& w_counts);

#endif
