#include <stdio.h>
#include <new>
#include <cstddef> // std::max_align_t

class BaseWrapper {
 public:
    virtual ~BaseWrapper() {}
	virtual void execute() = 0;
    virtual void copy_to(void* a_dst) = 0;
};

template<typename F>
class Wrapper final: public BaseWrapper {
 public:
	explicit Wrapper(const F& a_func): m_func(a_func) {
        printf("created function wrapper of size %lu\n", sizeof(*this));
    }
    ~Wrapper() {
        printf("destroyed function wrapper of size %lu\n", sizeof(*this));
    }
	void execute() override {
		m_func();
	}
    void copy_to(void* a_dst) override {
        // placement new
        ::new (a_dst) Wrapper(m_func);
    }
 private:
	F m_func;
};

class NullWrapper final: public BaseWrapper {
	void execute() override {
        // do nothing
	}
    void copy_to(void* a_dst) override {
        // placement new
        ::new (a_dst) NullWrapper();
    }
};

class Command {
 public:
    Command()
        //m_wrapper(nullptr) {}
        //m_wrapper(new (m_storage) Wrapper<decltype(nop)>(nop)) {}
        //m_wrapper(new (m_storage) NullWrapper()) {}
    {
        new (m_memory) NullWrapper();
    }
        
	template<typename F>
	explicit Command(const F& a_func)
        // placement new
		//m_wrapper(new (m_storage) Wrapper<F>(a_func)) {}
    {
        static_assert(sizeof(Wrapper<F>) <= sizeof(m_memory), 
            "function too big to store in command. did you use too many parameters?");
        new (m_memory) Wrapper<F>(a_func);
    }
    // no copy constructor
    Command(const Command& other) = delete;
    // no copy assignment
    Command& operator=(const Command& other) = delete;
    // move assignment
    Command& operator=(Command&& other) noexcept {
        //m_wrapper = other.m_wrapper;
        other.wrapper().copy_to(m_memory);
        //other.m_wrapper = nullptr;
        return *this;
    }
	~Command() {
        // "placement delete"
        //if (m_wrapper) {
		    wrapper().~BaseWrapper();
        //}
	}
	void execute() {
		wrapper().execute();
	}
 private:
    BaseWrapper& wrapper() {
        return reinterpret_cast<BaseWrapper&>(m_memory);
    }
 private:
    alignas(std::max_align_t) unsigned char m_memory [64];
    //BaseWrapper* m_wrapper;
};