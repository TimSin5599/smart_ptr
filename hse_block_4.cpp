#include <memory>
#include <type_traits>

template <typename vt> class smart_ptr
{
public:
    smart_ptr() noexcept(std::is_nothrow_default_constructible_v<vt>) {_ptr = new (std::nothrow) vt;}
    smart_ptr operator=(const smart_ptr<vt>& other) = delete;
    smart_ptr(const smart_ptr<vt>& other) = delete;
    smart_ptr(smart_ptr<vt>&& other) noexcept {_ptr = other._ptr; other._ptr = nullptr;}
    smart_ptr& operator=(smart_ptr<vt>&& other) noexcept(std::is_nothrow_destructible_v<vt>)
    {
        if (_ptr != other._ptr)
        {
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }
    vt* get() const noexcept {return _ptr;}
    vt* operator->() const noexcept {return _ptr;}
    vt& operator*() const noexcept {return *_ptr;}
    ~smart_ptr() noexcept(std::is_nothrow_destructible_v<vt>) { _ptr->~vt(); operator delete (_ptr, (std::nothrow));}
private:
    vt *_ptr;
};