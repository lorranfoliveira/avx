// avx.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <immintrin.h>
#include <array>
#include <chrono>

void sum(const double* a, const double* b, double* c, const size_t n) {
	auto start = std::chrono::steady_clock::now();

	for (size_t i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i];
	}

	auto end = std::chrono::steady_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	std::cout << "--------- NORMAL ---------\n";
	std::cout << "Elapsed time: " << elapsed << "\nResult: " << c[n - 1] << std::endl;
}

void sum_avx(const double* a, const double* b, double* c, const size_t n) {
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < n; i += 4)
	{
		_mm256_store_pd(c + i, _mm256_add_pd(_mm256_load_pd(a + i), _mm256_load_pd(b + i)));
	}

	auto end = std::chrono::steady_clock::now();

	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	std::cout << "\n--------- AVX ---------\n";
	std::cout << "Elapsed time: " << elapsed << "\nResult: " << c[n - 1] << std::endl;
}

int main()
{
	const int n = 10000;

	double* a = new double[n];
	double* b = new double[n];
	double* c = new double[n];

	for (int i = 0; i < n; i++)
	{
		a[i] = (double)0.9 * i;
		b[i] = (double)1.1 * i;
	}

	sum(a, b, c, n);
	sum_avx(a, b, c, n);

	delete[]a;
	delete[]b;
	delete[]c;
}
