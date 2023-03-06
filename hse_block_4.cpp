#include <memory>
#include <type_traits>
#include <iostream>

template <typename vt> class smart_ptr
{
public:
    smart_ptr() noexcept(std::is_nothrow_default_constructible_v<vt>) {_ptr = new (std::nothrow) vt;}
    smart_ptr operator=(const smart_ptr<vt>& other) = delete;
    smart_ptr(const smart_ptr<vt>& other) = delete;
    smart_ptr(const smart_ptr<vt>&& other) noexcept {_ptr = other._ptr;}
    smart_ptr& operator=(const smart_ptr<vt>&& other) noexcept(std::is_nothrow_destructible_v<vt>)
    {
        delete _ptr;
        _ptr = std::move(other._ptr);
        return *this;
    }
    vt* get() const noexcept {return _ptr;}
    vt* operator->() const noexcept {return _ptr;}
    vt& operator*() const noexcept {return *_ptr;}
    ~smart_ptr() noexcept(std::is_nothrow_destructible_v<vt>)
    {
        operator delete(_ptr, std::nothrow);
        
    }
private:
    vt *_ptr;
};

//int main()
//{
//    smart_ptr<char> list = new char ('a');
//    char a = *list;
//    std::cout << a;
//    list.~smart_ptr();
//    std::cout << a;
//    return 0;
//}