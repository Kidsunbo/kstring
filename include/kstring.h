#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <cmath>

#if __cplusplus > 202002L
// For C++23, std::unique_ptr is constexpr which can be used to make string constexpr
#define CONSTEXPR constexpr
#else
// For pre-version of C++23, std::unique_ptr is not constexpr, so all the class using it should not be constexpr
#define CONSTEXPR
#endif

namespace kie
{


  /**
   * @brief This is the main class of this library, naming `string`, which own the life of underline data.
   * 
   * This class is marked as final, which means you should not inherit it. If more functionality is needed, consider write a free function rather than inheriting.
   */
  class string final
  {
    /**
     * @brief This is the pointer which holds the data of the string.
     * 
     * This memory is managed by a `std::unique_ptr`. So the whole class is non-copyable.
     */
    std::unique_ptr<char[]> _data = nullptr;

    /**
     * @brief This is the length of the string.
     * 
     * It's the total length of the string which must be less or equal to @ref{_capacity}.
     * 
     * @see _capacity
     */
    std::size_t _length = 0;

    /**
     * @brief This is the capacity of the string.
     * 
     * It's the total capacity of the string which must be equal or greater than @ref{_length}
     * 
     * @see _length
     */
    std::size_t _capacity = 0;

  private:
    constexpr std::size_t calculate_capacity(std::size_t length)
    {
      if (length < 1024)
      {
        return length * 2;
      }
      return std::floor(length * 1.25);
    }

  public:
    CONSTEXPR string() noexcept = default;

    CONSTEXPR string(const char *s)
    {
      while (s[_length] != '\0')
      {
        _length++;
      }
      _capacity = _length;
      _data = std::make_unique<char[]>(_capacity);
      std::copy(s, s + _length, _data.get());
    }

    CONSTEXPR string(const char *s, std::size_t length) : _length(length), _capacity(length)
    {
      _data = std::make_unique<char[]>(_capacity);
      std::copy(s, s + length, _data.get());
    }

    CONSTEXPR string(const string &other) : _length(other._length), _capacity(other._length)
    {
      _data = std::make_unique<char[]>(_capacity);
      std::copy(other._data.get(), other._data.get() + _length, _data.get());
    }

    CONSTEXPR string(string &&other) noexcept : _length(std::exchange(other._length, 0)), _data(std::exchange(other._data, nullptr)), _capacity(std::exchange(other._capacity, 0))
    {
    }

    CONSTEXPR string(const std::string &other)
    {
      _length = other.length();
      _capacity = other.capacity();
      _data = std::make_unique<char[]>(_capacity);
      std::copy(other.begin(), other.end(), _data.get());
    }

    CONSTEXPR string &operator=(const string &other)
    {
      if (&other == this)
      {
        return *this;
      }
      if (other._length > _capacity)
      {
        _length = other._length;
        _capacity = other._capacity;
        _data = std::make_unique<char[]>(_capacity);
      }
      else
      {
        _length = other._length;
      }
      std::copy(other._data.get(), other._data.get() + _length, _data.get());
    }

    CONSTEXPR string &operator=(string &&other) noexcept
    {
      _length = std::exchange(other._length, 0);
      _capacity = std::exchange(other._capacity, 0);
      _data = std::exchange(other._data, nullptr);
    }

    CONSTEXPR string &operator=(const std::string &s)
    {
      _length = s.length();
      _capacity = s.capacity();
      _data = std::make_unique<char[]>(_capacity);
      std::copy(s.begin(), s.end(), _data.get());
      return *this;
    }

    ~string() noexcept {}

    std::string to_std_string() const{
      return std::string{_data.get(), _length};
    }

    std::string_view to_std_string_view() const{
      return std::string_view{_data.get(), _length};
    }

    constexpr const char* to_c_str()const{
      return _data.get();
    }

    constexpr std::size_t length()const{
      return _length;
    }

    constexpr std::size_t capacity() const{
      return _capacity;
    }

    constexpr bool is_full() const{
      return _length == _capacity;
    }



  };

  class string_view
  {
    const char *_data = nullptr;
    std::size_t _length = 0;
  };
} // namespace kie
