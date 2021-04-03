#pragma once
#include <string>;

template<class Array, class Search, class Compare >
Array* BSearch(Array arr[], int size, Search search, Compare cmpFunc){
	int l, r, m;
	l = 0;
	r = size - 1;
	while (l <= r) {
		m = (l + r) / 2;
		if (cmpFunc(arr[m], search) == 0) {
			return &arr[m];
		}
		else if (cmpFunc(arr[m], search) > 0) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	throw "not found";
};
