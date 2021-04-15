#include "dot_product.h"


int main()
{
	std::cout << "generating random vectors..." << std::endl;
	std::vector<int> vt1 = random_generator(10'000'000, 0, 10);
	std::vector<int> vt2 = random_generator(10'000'000, 0, 10);
	std::cout << "generated!" << std::endl;
	using_std_inner_product(vt1, vt2);
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency());
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency() / 2);
	using_thread_lockguard(vt1, vt2, std::thread::hardware_concurrency() / 4);
	using_thread_divide_conquer(vt1, vt2, std::thread::hardware_concurrency());
	using_thread_divide_conquer(vt1, vt2, std::thread::hardware_concurrency() / 2);
	using_thread_divide_conquer(vt1, vt2, std::thread::hardware_concurrency() / 4);
	using_future_async(vt1, vt2, std::thread::hardware_concurrency());
	using_future_async(vt1, vt2, std::thread::hardware_concurrency() / 2);
	using_future_async(vt1, vt2, std::thread::hardware_concurrency() / 4);
}