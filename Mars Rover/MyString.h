// TODO: Implement this header file
#ifndef MYSTRING_H
#define MYSTRING_H

using std::cin, std::cout, std::endl, std::ifstream, std::istream;

class MyString {
	public:
		// constructors
		MyString();
		MyString (const MyString& str);
		MyString (const char* s);
		~MyString(); //destructor
		void resize (size_t n); //resize
		size_t capacity() const noexcept; //capacity
		size_t size() const noexcept; //size
		size_t length() const noexcept; //length
		const char* data() const noexcept; //data
		bool empty() const noexcept; //empty
		const char& front() const; //front
		const char& at (size_t pos) const; //at 
		void clear() noexcept; //clear
		MyString& operator= (const MyString& str); //operator=
		MyString& operator+= (const MyString& str); //operator+=
		size_t find (const MyString& str, size_t pos = 0) const ; //find operator 
		//operator == 
	private:
		unsigned int m_size;
		unsigned int m_capacity;
		char* woo;
};

std::ostream& operator<<(std::ostream& os, const MyString& str);

#endif