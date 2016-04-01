#ifndef LUHN_H
#define LUHN_H

#include <string>

using namespace std;

namespace luhn
{
  class luhn
  {
    public:
     enum class digits_state {invalid, valid};

      luhn() = default;
      luhn(const std::string& _digits) : m_digits(_digits) {  }

      int calculate() { return calculate(m_digits); }
      int calculate(const string&);

      int checksum() { return m_sum % 10; }
      int checksum(const string & _digits) { return calculate(_digits) % 10; }

      int calc_check_digit() { return calc_check_digit(m_digits); }

      int calc_check_digit(const string & _partial_digits)
      {
        if (is_valid(_partial_digits))
          return -1;
        int _check_digit = checksum(_partial_digits);
        return ((_check_digit == 0) ? _check_digit : 10 - _check_digit);
      }

      string complete();
      string complete(string & );

      string& digits() { return m_digits; }

      bool is_valid()                                { return checksum() == 0; }
      bool is_valid(const string & _complete_digits) { return checksum(_complete_digits) == 0; }

      string prev_luhn();
      string next_luhn();

      void set_digits(string && _digits)      { m_digits = std::move(_digits); }
      void set_digits(const string & _digits) { m_digits = _digits; }

      digits_state state();
      int  sum() { return m_sum; }

    private:
      string m_digits = "";
      int    m_sum = 0;
  };

  int luhn::calculate(const string& _digits)
  {
    const int m[10]  = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9}; // mapping for rule 3
    bool is_odd_dgt = false;
    auto lambda = [&](int a, char c)
    {
      a += ((is_odd_dgt = !is_odd_dgt) ? c - '0' : m[c - '0']);
      return a;
    };

    m_sum = std::accumulate(_digits.rbegin(), _digits.rend(), 0, lambda);
    return m_sum;
  }

  string luhn::complete()
  {
    if (!is_valid())
    {
      string new_digits = m_digits;
      for (uint i = 0; i < 10; ++i)
      {
        new_digits.erase(new_digits.size() - 1);
        new_digits.append(std::to_string(i));
        if (is_valid(new_digits))
          return new_digits;
      }
    }
    return m_digits;
  }

  string luhn::complete(string & _partial_digits)
  {
    if (!is_valid(_partial_digits))
    {
      string new_digits = _partial_digits;
      for (uint i = 0; i <= 10; ++i)
      {
        new_digits.erase(new_digits.size() - 1);
        new_digits.append(to_string(i));
        if (is_valid(new_digits))
          return new_digits;
      }
    }
    return _partial_digits;
  }

  string luhn::luhn::prev_luhn()
  {
    string str = to_string(stoull(m_digits) - 10);
    return complete(str);
  }

  string luhn::luhn::next_luhn() //Checking using +1, hence not needing complete() -- Suggestion
  {
    string str = to_string(stoull(m_digits));
    return complete(str);
    //string str = to_string(stoull(m_digits) + 1);
    //return (is_valid(str) ? str : m_digits);
  }

  luhn::digits_state luhn::state()
  {
    if (m_digits.size() == 0)
      return digits_state::invalid;

    for (auto && c : m_digits)
      if (!isdigit(c) || isblank(c))
        return digits_state::invalid;

    return digits_state::valid;
  }
}

#endif//LUHN_H
