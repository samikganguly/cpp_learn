#ifndef GUARD_4a_h
#define GUARD_4a_h

namespace ch8 {
	template <class T, template<class> class fw>
	void reverse(fw<T> begin, fw<T> end) {
		while(begin != end) {
			--end;
			if(begin != end) {
				// here we can swap begin and end values
				// directly, because we've parameterized
				// the type of container elements
				T t = *begin;
				*begin++ = *end;
				*end = t;
			}
		}
	}
}

#endif
