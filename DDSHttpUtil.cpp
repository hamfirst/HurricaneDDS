
#include "DDSHttpUtil.h"

std::string DDSUriEncode(const std::string & str)
{
  std::string result;
  result.reserve(str.length() * 3);

  for (char c : str)
  {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '-') || (c == '_') || (c == '.') || (c == '~'))
    {
      result.push_back(c);
    }
    else
    {
      result.push_back('%');
      char h = (c >> 4) & 0xF;

      if (h <= 9)
      {
        result.push_back('0' + h);
      }
      else
      {
        result.push_back('A' + h - 10);
      }

      h = c & 0xF;

      if (h <= 9)
      {
        result.push_back('0' + h);
      }
      else
      {
        result.push_back('A' + h - 10);
      }
    }
  }

  return result;
}

std::string DDSUriDecode(const std::string & str)
{
  std::string result;
  result.reserve(str.length());

  auto itr = str.begin();
  while (itr != str.end())
  {
    if (*itr == '%')
    {
      char c = 0;

      itr++;
      if (itr == str.end())
      {
        return result;
      }

      char u = *itr;

      itr++;
      if (itr == str.end())
      {
        return result;
      }

      char l = *itr;

      if (u >= '0' && u <= '9')
      {
        c = u - '0';
      }
      else if (u >= 'A' && u <= 'F')
      {
        c = u = 'A' + 10;
      }
      else
      {
        return result;
      }

      c <<= 4;

      if (l >= '0' && l <= '9')
      {
        c += l - '0';
      }
      else if (l >= 'A' && l <= 'F')
      {
        c += l = 'A' + 10;
      }
      else
      {
        return result;
      }

      itr++;

      result.push_back(c);
    }
    else
    {
      result.push_back(*itr);
    }
  }

  return result;
}

