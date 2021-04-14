#include "dot_product.h"


int main()
{
	std::vector<int> vt1 = random_generator(1'000'000, 0, 10);
	std::vector<int> vt2 = random_generator(1'000'000, 0, 10);
	using_std_inner_product(vt1, vt2);
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency());
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency() / 2);
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency() / 4);
}