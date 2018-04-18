#pragma once
#include <cstdio>
#include <iostream>

class String {
private:
	char* str_;
	size_t cap_;
	size_t size_;
public:
	String()
		:cap_(1), size_(1) {
		str_ = new char[cap_];
		str_[0] = '\0';
	}
	String(const char* _str) {
		size_t i = 0;
		for (; _str[i] != '\0'; i++) {
		}
		cap_ = i + 1;
		size_ = i + 1;
		str_ = new char[cap_];
		for (size_t j = 0; j<cap_; j++) {
			str_[j] = _str[j];
		}
	}
	String(const String& _str)
		:cap_(_str.cap_), size_(_str.size_) {
		str_ = new char[cap_];
		for (size_t i = 0; i<size_; i++) {
			str_[i] = _str.str_[i];
		}
	}
	String(int _int):String() {
		*this = _int;
	}
	~String() {
		delete[] str_;
	}
	size_t capacity()const {
		return cap_;
	}
	size_t length()const {
		return size_;
	}
	void Extend(size_t _cap) {
		cap_ = _cap;
		char* tmp = str_;
		str_ = new char[cap_];
		for (size_t i = 0; i<size_; i++) {
			str_[i] = tmp[i];
		}
		delete[] tmp;
	}
	String& operator=(const String& _str) {
		if (str_ != _str.str_) {
			Extend(_str.cap_);
			size_ = _str.size_;
			for (size_t i = 0; i<size_; i++) {
				str_[i] = _str.str_[i];
			}
		}
		return *this;
	}
	String& operator=(const char* _str) {
		size_t i = 0;
		for (; _str[i] != '\0'; i++) {
		}
		if (cap_<i + 1) {
			Extend(i + 1);
			size_ = i + 1;
		}
		for (size_t i = 0; i<size_; i++) {
			str_[i] = _str[i];
		}
		return *this;
	}
	String& operator=(int _int) {
		const size_t USED_CAP = 32;
		if (cap_<USED_CAP) {
			Extend(USED_CAP);
		}
		sprintf_s(str_,USED_CAP, "%d", _int);
		size_t i = 0;
		for (; str_[i] != '\0'; i++) {
		}
		size_ = i + 1;
		return *this;
	}
	String& operator+=(const String& rhs) {
		if (this->cap_ <= rhs.size_ + this->size_) {
			Extend(rhs.size_ + this->size_+1);
		}
		for (int i = 0; i <= rhs.size_; i++) {
			this->str_[this->size_ + i] = rhs.str_[i];
		}
		this->size_ += rhs.size_;
		return *this;
	}
	String& operator+=(const char* rhs) {
		return *this += String(rhs);
	}
	const char* c_str()const {
		return str_;
	}
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};
std::ostream& operator<<(std::ostream& os, const String& str) {
	return os << str.str_;
}