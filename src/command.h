#include <cstddef> // std::max_align_t

template<int Size = 64>
class Command final {
 public:
    Command() {
        init();
    }
        
	template<typename F>
	Command(F&& a_func) {
        init(std::forward<F>(a_func));
    }

    // no copy constructor
    Command(const Command& other) = delete;
    // no copy assignment
    Command& operator=(const Command& other) = delete;
    // move assignment
    Command& operator=(Command&& other) noexcept {
        reset();
        other.wrapper().copy_to(m_memory);
        return *this;
    }
    // move assignment from callable
    template<typename F>
	Command& operator=(F&& a_func) {
        reset();
        init(std::forward<F>(a_func));
        return *this;
    }
    // destructor    
	~Command() {
        reset();
	}

	void execute() {
		wrapper().execute();
	}
 private:
    class BaseWrapper;
    BaseWrapper& wrapper() {
        return reinterpret_cast<BaseWrapper&>(m_memory);
    }
    template<typename F>
    void init(F&& a_func) {
        static_assert(sizeof(Wrapper<F>) <= sizeof(m_memory), 
            "function too big to store in command. did you use too many parameters?");
        // placement new
        new (m_memory) Wrapper<F>(std::forward<F>(a_func));
    }
    void init(std::nullptr_t = nullptr) {
        // placement
        new (m_memory) NullWrapper();
    }
    void reset() {
        // "placement delete"
	    wrapper().~BaseWrapper();
    }
 // private helper classes
 private: 

    class BaseWrapper {
    public:
        virtual ~BaseWrapper() {}
        virtual void execute() = 0;
        virtual void move_to(void* a_dst) = 0;
    };

    template<typename F>
    class Wrapper final: public BaseWrapper {
    public:
        explicit Wrapper(F&& a_func): m_func(std::forward<F>(a_func)) {
            printf("created function wrapper of size %lu\n", sizeof(*this));
        }
        ~Wrapper() {
            printf("destroyed function wrapper of size %lu\n", sizeof(*this));
        }
        void execute() override {
            m_func();
        }
        void move_to(void* a_dst) override {
            // placement new
            ::new (a_dst) Wrapper(std::forward<F>(m_func));
        }
    private:
        F m_func;
    };

    class NullWrapper final: public BaseWrapper {
        void execute() override {
            // do nothing
        }
        void move_to(void* a_dst) override {
            // placement new
            ::new (a_dst) NullWrapper();
        }
    };

 // private members   
 private:
    alignas(std::max_align_t) unsigned char m_memory [Size];
};