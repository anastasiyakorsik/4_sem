#include <algorithm>
#include <iostream>
#include <vector>

template <int n>
struct F {
	enum {
		result = n * F<n - 1>::result
	};
};

template <int n, int k>
struct C {
	enum {
		result_C = F<n>::result / F<n - k>::result / F<k>::result
	};
};

template <int n>
struct C<n, 1> {
		static const int result_C = n;
};

template <int n>
struct C<n,0> {
	static const int result_C = 1;
};

template <int n>
struct C<n,n> {
	static const int result_C = 1;
};

template <>
struct F<0>
{
	static const int result = 1;
};

int main() {
	std::cout << C<2,1>::result_C << " " << C<2,0>::result_C;
	return 0;
}