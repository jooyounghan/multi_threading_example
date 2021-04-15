#pragma once

#include "random_generator.h"
#include "timer.h"
#include <numeric>
#include <thread>

void using_std_inner_product(const std::vector<int> &vt1, const std::vector<int>& vt2)
{
	std::cout << "with using std::inner_product" << std::endl;
	timer tm;
	tm.start();
	unsigned long long result = std::inner_product(vt1.begin(), vt1.end(), vt2.begin(), 0ull);
	tm.end();
	std::cout << "result : " << result << std::endl;
	std::cout << "time : " << tm.get_time() << std::endl;
}

void using_thread_lockguard(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& thread_num = std::thread::hardware_concurrency()/2)
{
	std::cout << "with using and " << thread_num << " " << "thread lockguard" << std::endl;
	unsigned long long result = 0;
	std::vector<std::thread> threads;
	threads.resize(thread_num);
	int num_data = vt1.size() / thread_num;
	timer tm;
	tm.start();
	for (int i = 0; i < thread_num; i += 1)
	{
		threads[i] = std::thread(local_sum_lockguard, std::ref(vt1), std::ref(vt2), (i * (num_data)), ((i + 1) * (num_data)), std::ref(result));
	}

	for (int i = 0; i < thread_num; i += 1)
	{
		threads[i].join();
	}

	tm.end();

	std::cout << "result : " << result << std::endl;
	std::cout << "time : " << tm.get_time() << std::endl;
}

void using_thread_divide_conquer(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& thread_num = std::thread::hardware_concurrency() / 2)
{
	std::cout << "with using and " << thread_num << " " << "thread divide conquer" << std::endl;
	std::vector<unsigned long long> result_vector;
	std::vector<std::thread> threads;
	result_vector.resize(thread_num);
	threads.resize(thread_num);
	int num_data = vt1.size() / thread_num;
	timer tm;
	tm.start();
	for (int i = 0; i < thread_num; i += 1)
	{
		threads[i] = std::thread(local_sum, std::ref(vt1), std::ref(vt2), (i * (num_data)), ((i + 1) * (num_data)), std::ref(result_vector[i]));
	}

	for (int i = 0; i < thread_num; i += 1)
	{
		threads[i].join();
	}
	unsigned long long result = 0;
	for (int i = 0; i < thread_num; i += 1)
	{
		result += result_vector[i];
	}
	tm.end();

	std::cout << "result : " << result << std::endl;
	std::cout << "time : " << tm.get_time() << std::endl;
}

void using_future_async(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& thread_num = std::thread::hardware_concurrency() / 2)
{
	std::cout << "with using and " << thread_num << " " << "async and future" << std::endl;
	std::vector<std::future<unsigned long long>> result_vector;
	result_vector.resize(thread_num);
	int num_data = vt1.size() / thread_num;
	timer tm;
	tm.start();
	for (int i = 0; i < thread_num; i += 1)
	{
		result_vector[i] = std::async(local_sum_future_async, std::ref(vt1), std::ref(vt2), (i * (num_data)), ((i + 1) * (num_data)));
	}

	unsigned long long result = 0;
	for (int i = 0; i < thread_num; i += 1)
	{
		result += result_vector[i].get();
	}
	tm.end();

	std::cout << "result : " << result << std::endl;
	std::cout << "time : " << tm.get_time() << std::endl;
}

void using_thead_future_async(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& thread_num = std::thread::hardware_concurrency() / 2)
{
	std::cout << "with using and " << thread_num << " " << "thread, async and future" << std::endl;
	std::vector<std::promise<unsigned long long>> promise_vector;
	std::vector<std::future<unsigned long long>> future_vector;
	std::vector<std::thread> thread_vector;
	promise_vector.resize(thread_num);
	future_vector.resize(thread_num);
	thread_vector.resize(thread_num);
	for (int i = 0; i < thread_num; i += 1)
	{
		future_vector[i] = promise_vector[i].get_future();
	}

	int num_data = vt1.size() / thread_num;
	timer tm;
	tm.start();

	for (int i = 0; i < thread_num; i += 1)
	{
		thread_vector[i] = std::thread([](std::promise<unsigned long long>&& prom) {prom.set_value(local_sum_thread_future_async(vt1, vt2, (i * (num_data)), ((i + 1) * (num_data)))); }, std::move(promise_vector[i]));
	}

	for (int i = 0; i < thread_num; i += 1)
	{
		thread_vector[i].join();
	}
	unsigned long long result = 0;
	for (int i = 0; i < thread_num; i += 1)
	{
		result += future_vector[i].get();
	}
	tm.end();

	tm.end();

	std::cout << "result : " << result << std::endl;
	std::cout << "time : " << tm.get_time() << std::endl;
}