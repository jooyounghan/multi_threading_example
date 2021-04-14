#pragma once
#include <iostream>
#include <chrono>

class timer
{
private : 
	std::chrono::steady_clock::time_point start_time;
	std::chrono::steady_clock::time_point end_time;
public : 
	void start() { start_time = std::chrono::steady_clock::now(); }
	void end() { end_time = std::chrono::steady_clock::now(); }
	void print_time() { std::cout << std::chrono::duration<double>{end_time - start_time}.count() << std::endl; }
	double get_time() { return std::chrono::duration<double>{end_time - start_time}.count(); }
};