#ifndef GUARD_4a_h
#define GUARD_4a_h

namespace ch8 {
	template<class T>
	void swap(T& v1, T& v2) {
		T t = v1;
		v1 = v2;
		v2 = t;
	}

	template <class fw>
	void reverse(fw begin, fw end) {
		while(begin != end) {
			--end;
			if(begin != end)
				// here we can't swap begin and end values
				// directly, because we don't know type of 
				// container elements, but swap function 
				// takes it as a parameter and deduce it at
				// compile time from function arguments
				swap(*begin++, *end);
		}
	}
}

#endif
