#pragma once
#include <random>
#include <vector>
#include <mutex>
#include <iostream>
#include <thread>
#include <future>

std::mutex mtx;

std::vector<int> random_generator(const int& num, const int& min, const int& max)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> distrib(min, max);

	std::vector<int> vt;
	vt.reserve(num);
	for (int i = 0; i < num; i += 1)
	{
		vt.push_back(distrib(mt));
	}

	return vt;
}

void local_sum_lockguard(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& start_num, const int& end_num, unsigned long long &result)
{
	for (int i = start_num; i < end_num; i += 1)
	{
		std::lock_guard lock(mtx);
		result += vt1[i] * vt2[i];
	}
}

void local_sum(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& start_num, const int& end_num, unsigned long long& result)
{
	for (int i = start_num; i < end_num; i += 1)
	{
		result += vt1[i] * vt2[i];
	}
}

unsigned long long local_sum_future_async(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& start_num, const int& end_num)
{
	unsigned long long result = 0;
	for (int i = start_num; i < end_num; i += 1)
	{
		result += vt1[i] * vt2[i];
	}
	return result;
}

unsigned long long local_sum_thread_future_async(const std::vector<int>& vt1, const std::vector<int>& vt2, const int& start_num, const int& end_num)
{
	unsigned long long result = 0;
	for (int i = start_num; i < end_num; i += 1)
	{
		result += vt1[i] * vt2[i];
	}
	return result;
}