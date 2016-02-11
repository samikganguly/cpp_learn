// implementation of read_words
// *ANS = in C++ wc_map would overload the == operator for custom equality
// checking function, in this case check only the word of wc_map to declare
// them equal, then use normal find() instead of find_if and pass the value
#include <algorithm>
#include "5.h"

using std::istream;
using std::vector;
using std::string;
using std::find_if;

string match;// why do we need to declare match as global? *ANS
bool find_condition(const wc_map& w) {// it should be a parameter of condition 
	return w.word == match;// we would check the equality here
}
istream& read_words(istream& is, vector<wc_map>& w_counts) {
	if(is) {
		w_counts.clear();
		while(is >> match) {
			vector<wc_map>::const_iterator it
			   = find_if(w_counts.begin(), w_counts.end(),
			             find_condition);
			if(it == w_counts.end()) {// new word
				wc_map wmap = { match, 1};
				w_counts.push_back(wmap);
			} else {// word is already input
				vector<wc_map>::size_type i
					= it - w_counts.begin();
				w_counts[i].count++;
			}
		}
		is.clear();
	}
	return is;
}
