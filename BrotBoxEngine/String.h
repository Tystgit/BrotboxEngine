#pragma once

#include <string>
#include "DynamicArray.h"

namespace bbe {
	class String {
		//TODO use allocators
	private:
		wchar_t *m_data = nullptr;
		size_t m_length = 0;

		void initializeFromWCharArr(const wchar_t *data) {
			if (m_length == 0) {
				m_length = wcslen(data);
			}
			m_data = new wchar_t[m_length + 1];
			memcpy(m_data, data, (m_length + 1) * sizeof(wchar_t));
		}

		void initializeFromCharArr(const char *data) {
			if (m_length == 0) {
				m_length = strlen(data);
			}
			m_data = new wchar_t[m_length + 1];
			mbstowcs_s(0, m_data, m_length + 1, data, m_length);
		}

	public:
		String()
		{
			initializeFromWCharArr(L"");
		}

		String(const wchar_t *data) {
			initializeFromWCharArr(data);
		}

		String(const char* data) {
			initializeFromCharArr(data);
		}

		String(const std::string &data) {
			m_length = data.length();
			initializeFromCharArr(data.c_str());
		}

		String(const std::wstring &data) {
			m_length = data.length();
			initializeFromWCharArr(data.c_str());
		}

		String(double value) {
			initializeFromCharArr(std::to_string(value).c_str());
		}

		String(const String&  other) { //Copy Constructor
			m_length = other.getLength();
			initializeFromWCharArr(other.m_data);
		}

		String(String&& other) { //Move Constructor
			m_length = other.m_length;
			m_data = other.m_data;
			other.m_data = nullptr;
		}

		String& operator=(const String&  other) { //Copy Assignment
			m_length = other.getLength();
			initializeFromWCharArr(other.m_data);
			return *this;
		}

		String& operator=(String&& other) { //Move Assignment
			m_length = other.m_length;
			m_data = other.m_data;
			other.m_data = nullptr;
			return *this;
		}

		~String() {
			if (m_data != nullptr) {
				delete[] m_data;
			}
		}

		bool operator==(const String& other) const {
			return wcscmp(m_data, other.m_data) == 0;
		}

		bool operator==(const wchar_t* arr) const {
			return wcscmp(m_data, arr) == 0;
		}

		bool operator==(const char* arr) const {
			String localString(arr);
			return operator==(localString);
		}

		friend bool operator==(const wchar_t* arr, const String& a) {
			return a.operator==(arr);
		}

		friend bool operator==(const char* arr, const String& a) {
			return a.operator==(arr);
		}

		bool operator!=(const String& other) const {
			return !operator==(other);
		}

		bool operator!=(const wchar_t* arr) const {
			return !operator==(arr);
		}

		bool operator!=(const char* arr) const {
			return !operator==(arr);
		}

		friend bool operator!=(const wchar_t* arr, const String& string) {
			return string.operator!=(arr);
		}

		friend bool operator!=(const char* arr, const String& string) {
			return string.operator!=(arr);
		}

		String operator+(const String& other) const {
			size_t totalLength = m_length + other.m_length;
			wchar_t *newData = new wchar_t[totalLength + 1];
			memcpy(newData, m_data, sizeof(wchar_t) * m_length);
			memcpy(newData + m_length, other.m_data, sizeof(wchar_t) * other.m_length);
			newData[totalLength] = 0;
			String retVal;
			delete[] retVal.m_data;
			retVal.m_data = newData;
			retVal.m_length = totalLength;
			return retVal;
		}

		String operator+(const std::string& other) const {
			return operator+(String(other));
		}

		String operator+(const wchar_t* other) const {
			return operator+(String(other));
		}

		String operator+(const char* other) const {
			return operator+(String(other));
		}

		String operator+(double number) const {
			return operator+(String(number));
		}

		friend String operator+(const std::string& other, const String& string) {
			return string + other;
		}

		friend String operator+(const wchar_t* other, const String& string) {
			return string + other;
		}

		friend String operator+(const char* other, const String& string) {
			return string + other;
		}

		friend String operator+(double number, const String& string) {
			return string + number;
		}

		String& operator+=(const String& other) {
			*this = *this + other;
		}

		String& operator+=(const std::string& other) {
			*this = *this + other;
		}

		String& operator+=(const wchar_t* other) {
			*this = *this + other;
		}

		String& operator+=(const char* other) {
			*this = *this + other;
		}

		String& operator+=(double number) {
			*this = *this + number;
		}

		void trim() {
			size_t start = 0;
			size_t end = m_length - 1;
			while (iswspace(m_data[start])) {
				start++;
			}
			while (iswspace(m_data[end]) && end != 0) {
				end--;
			}

			if (start != 0 || end != m_length) {
				if (end == 0) { //Special Case, if the string only contains whitespace
					m_length = 0;
					m_data[m_length] = 0;
				}
				else {
					m_length = end - start + 1;
					memmove(m_data, &m_data[start], sizeof(wchar_t) * m_length);
					m_data[m_length] = 0;
				}
			}
		}

		size_t count(const String& countand) const
		{
			size_t countandLength = countand.getLength();
			if (countandLength == 0) {
				return 0;
			}
			size_t amount = 0;
			wchar_t *readHead = m_data;

			while ((readHead = wcsstr(readHead, countand.m_data)) != nullptr) {
				amount++;
				readHead += countandLength;
			}
			return amount;
		}

		size_t count(const wchar_t* countand) const
		{
			return count(String(countand));
		}

		DynamicArray<String> split(const String& splitAt) const
		{
			size_t counted = count(splitAt);
			if (counted == 0) {
				DynamicArray<String> retVal(1);
				retVal[0] = m_data;
				return retVal;
			}
			DynamicArray<String> retVal(counted + 1);
			wchar_t *previousFinding = m_data;
			for (size_t i = 0; i < retVal.getLength() - 1; i++) {
				wchar_t *currentFinding = wcsstr(previousFinding, splitAt.m_data);
				String currentString;
				delete[] currentString.m_data;
				size_t currentStringLength = currentFinding - previousFinding;
				currentString.m_data = new wchar_t[currentStringLength + 1];
				memcpy(currentString.m_data, previousFinding, currentStringLength * sizeof(wchar_t));
				currentString.m_data[currentStringLength] = 0;
				currentString.m_length = currentStringLength;

				retVal[i] = currentString;

				previousFinding = currentFinding + splitAt.getLength();
			}

			String currentString;
			delete[] currentString.m_data;
			size_t currentStringLength = m_data + m_length - previousFinding;
			currentString.m_data = new wchar_t[currentStringLength + 1];
			memcpy(currentString.m_data, previousFinding, currentStringLength * sizeof(wchar_t));
			currentString.m_data[currentStringLength] = 0;
			currentString.m_length = currentStringLength;
			retVal[retVal.getLength() - 1] = currentString;

			return retVal;
		}

		DynamicArray<String> split(const wchar_t* splitAt) const
		{
			return split(String(splitAt));
		}

		bool contains(const wchar_t* string) const {
			return contains(String(string));
		}

		bool contains(const char* string) const {
			return contains(String(string));
		}

		bool contains(const std::string& string) const {
			return contains(String(string));
		}

		bool contains(const String& string) const {
			return wcsstr(m_data, string.m_data) != nullptr;
		}

		int search(const wchar_t* string) const {
			return search(String(string));
		}

		int search(const char* string) const {
			return search(String(string));
		}

		int search(const std::string& string) const {
			return search(String(string));
		}

		int search(const String& string) const {
			wchar_t *found = wcsstr(m_data, string.m_data);
			if (found == nullptr) {
				return -1;
			}

			return found - m_data;
		}

		long toLong(int base = 10) {
			return wcstol(m_data, nullptr, base);
		}

		double toDouble() {
			return wcstod(m_data, nullptr);
		}

		float toFloat() {
			return wcstof(m_data, nullptr);
		}

		wchar_t& operator[](size_t index) {
			return m_data[index];
		}

		wchar_t* getRaw() {
			return m_data;
		}

		size_t getLength() const{
			return m_length;
		}
	};


}