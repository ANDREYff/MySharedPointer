#ifndef MYSHARED_PTR_H
#define MYSHARED_PTR_H

template<typename T/*, typename Deleter*/>
struct myShared_ptr {
	
	myShared_ptr(T* ptr = nullptr) : m_ptr(ptr), m_counter(new size_t(1)) {}
	myShared_ptr(const myShared_ptr& that) noexcept : m_ptr(that.m_ptr), m_counter(that.counter) {
		++(*m_counter);
	}
	myShared_ptr& operator=(const myShared_ptr& that) noexcept {
		if(that == *this) {
			return *this;
		}
		
		//clearing existing data
		if(m_counter > 1) {
			
			--(*m_counter);
		
			m_ptr = that.m_ptr;
			m_counter = that.m_counter;
			++(*m_counter);
			
			return *this;
		}
		
		//if it was the last ptr to data - free memory
		delete m_ptr;
		delete m_counter;
		
		m_ptr = that.m_ptr;
		m_counter = that.m_counter;
		++(m_counter);
		
		return *this;
	}
	myShared_ptr(myShared_ptr&& that) noexcept : m_ptr(that.m_ptr), m_counter(that.m_counter) {
		that.m_ptr = nullptr;
		that.m_counter = nullptr;
		
	}
	myShared_ptr& operator=(myShared_ptr&& that) noexcept {
		if(that == *this) {
			return *this;
		}
		m_ptr = that.m_ptr;
		m_counter = that.m_counter;
		
		that.m_ptr = nullptr;
		that.m_counter = nullptr;
	}
	~myShared_ptr() {
		if (!m_counter) {return;}
		
		--(*m_counter);
		
		if(*m_counter == 0) {
			delete m_ptr;
			delete m_counter;
		}
	}
	size_t getCount() {
		return *m_counter;
	}
	T* get() {
		return m_ptr;
	}
	T& operator*() {
		return *m_ptr;
	}
	T* operator->() {
		return m_ptr;
	}
	
private:
	T* m_ptr;
	size_t* m_counter;
};

#endif