#pragma once
 
// https://probablydance.com/2013/10/05/type-safe-pimpl-implementation-without-overhead/

#include <utility>
#include <stddef.h>
 
namespace detail
{
template<size_t ExpectedSize, size_t ActualSize, size_t ExpectedAlignment, size_t ActualAlignment>
inline void compare_size()
{
    static_assert(ExpectedSize >= ActualSize, 
		"The size for the ForwardDeclaredStrage is wrong");
    static_assert(ExpectedAlignment >= ActualAlignment, 
		"The alignment for the ForwardDeclaredStrage is wrong");
}
template<size_t ExpectedSize, size_t ActualSize, size_t ExpectedAlignment, size_t ActualAlignment>
struct size_comparer
{
    inline size_comparer()
    {
        // going through one additional layer to get good error messages
        // if I put the assert down one more template layer, gcc will show the
        // sizes in the error message
        compare_size<ExpectedSize, ActualSize, ExpectedAlignment, ActualAlignment>();
    }
};
}
 
struct forwarding_constructor {};
 
template<typename T, size_t Size, size_t Alignment = 16>
struct ForwardDeclaredStorage
{
    ForwardDeclaredStorage()
    {
        new (&Get()) T();
    }
    template<typename... Args>
    ForwardDeclaredStorage(forwarding_constructor, Args &&... args)
    {
        new (&Get()) T(std::forward<Args>(args)...);
    }
    ForwardDeclaredStorage(const ForwardDeclaredStorage & other)
    {
        new (&Get()) T(other.Get());
    }
    ForwardDeclaredStorage(const T & other)
    {
        new (&Get()) T(other);
    }
    ForwardDeclaredStorage(ForwardDeclaredStorage && other)
    {
        new (&Get()) T(std::move(other.Get()));
    }
    ForwardDeclaredStorage(T && other)
    {
        new (&Get()) T(std::move(other));
    }
    ForwardDeclaredStorage & operator=(const ForwardDeclaredStorage & other)
    {
        Get() = other.Get();
        return *this;
    }
    ForwardDeclaredStorage & operator=(const T & other)
    {
        Get() = other;
        return *this;
    }
    ForwardDeclaredStorage & operator=(ForwardDeclaredStorage && other)
    {
        Get() = std::move(other.Get());
        return *this;
    }
    ForwardDeclaredStorage & operator=(T && other)
    {
        Get() = std::move(other);
        return *this;
    }
    ~ForwardDeclaredStorage()
    {
        detail::size_comparer<Size, sizeof(T), Alignment, alignof(T)> compare_size{};
        Get().~T();
    }
    T & Get()
    {
        return reinterpret_cast<T &>(*this);
    }
    const T & Get() const
    {
        return reinterpret_cast<const T &>(*this);
    }

	T* operator->() noexcept {
		return reinterpret_cast<T*>(storage);
	}
 
private:
    alignas(Alignment) unsigned char storage[Size];
};