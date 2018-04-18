#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
//#include <unistd.h>

struct Number {
	int number_;
	bool prime_;
};

void* PrimeThread(void* _prime);

class PrimeDevice {
private:
	std::vector<int> prime_numbers_;
	const size_t max_size_;
	HANDLE thread_;
	DWORD thread_id_;
	HANDLE mut_;
	bool end_;
private:
	void Create() {
		mut_ = CreateMutex(nullptr,true,nullptr);
		thread_=CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)&PrimeThread, this,0,&thread_id_);
	}
	void Join() {
		WaitForSingleObject(thread_, INFINITE);
		CloseHandle(thread_);
		CloseHandle(mut_);
	}
	bool isPrime(int num) {
		for (size_t i = 0; i<prime_numbers_.size(); i++) {
			if (num%prime_numbers_[i] == 0 && num != prime_numbers_[i]) {
				return false;
			}
		}
		return true;
	}
	bool isPrime(int num, int index) {
		if (num>prime_numbers_[index]) {
			for (; num >= prime_numbers_[index]; index++) {
				if (num == prime_numbers_[index]) {
					return true;
				}
			}
		}
		else if (num<prime_numbers_[index]) {
			for (; num <= prime_numbers_[index]; index--) {
				if (num == prime_numbers_[index]) {
					return true;
				}
			}
		}
		return false;
	}
	void FindPrime() {
		prime_numbers_.push_back(2);
		for (int num = 3; prime_numbers_.size()<max_size_; num += 2) {
			if (isPrime(num)) {
				WaitForSingleObject(mut_,0);
				if (end_) {
					return;
				}
				prime_numbers_.push_back(num);
				ReleaseMutex(mut_);
			}
		}
	}
public:
	PrimeDevice(size_t _max_size)
		:max_size_(_max_size),end_(false) {
		Create();
	}
	~PrimeDevice() {
		WaitForSingleObject(mut_, 0);
		end_ = true;
		ReleaseMutex(mut_);
		Join();
	}
	void GetPrimes(Number* array, int N) {
		WaitForSingleObject(mut_, 0);
		static size_t index = 5;
		if (index + N >= prime_numbers_.size()) {
			ReleaseMutex(mut_);
			//sleep(1);
			GetPrimes(array, N);
			return;
		}
		srand(time(NULL));
		int n_prime = 1;
		int n_not_prime = N - n_prime;
		int pre_number = rand() % n_not_prime + rand() % 2;

		for (int i = 0; i<N; i++) {
			if (pre_number>0) {
				array[i].number_ = prime_numbers_[index] - 2 * pre_number;
				array[i].prime_ = isPrime(array[i].number_, index);
				pre_number--;
			}
			else if (pre_number == 0) {
				array[i].number_ = prime_numbers_[index];
				array[i].prime_ = true;
				index++;
				pre_number--;
			}
			else {
				array[i].number_ = prime_numbers_[index] - 2 * pre_number;
				array[i].prime_ = isPrime(array[i].number_, index);
				pre_number--;
			}
		}
		ReleaseMutex(mut_);
	}
	template<int N>
	void GetPrimes(Number(&array)[N]) {
		GetPrimes(array, N);
	}
	friend void* PrimeThread(void* _prime);
}prime_device(10000);

void* PrimeThread(void* _prime) {
	PrimeDevice& prime = *static_cast<PrimeDevice*>(_prime);
	prime.FindPrime();
	return nullptr;
}