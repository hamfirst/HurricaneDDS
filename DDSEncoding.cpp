
#include "DDSEncoding.h"

#include <cassert>

char b64chr(uint8_t v)
{
  if(v < 26)
  {
    return 'A' + v;
  }
  else if(v < 52)
  {
    return 'a' + v - 26;
  }
  else if(v < 62)
  {
    return '0' + v - 52;
  }
  else if(v == 62)
  {
    return '+';
  }
  else if(v == 63)
  {
    return '/';
  }
  else
  {
    return 0;
  }
}

char urlb64chr(uint8_t v)
{
  if(v < 26)
  {
    return 'A' + v;
  }
  else if(v < 52)
  {
    return 'a' + v - 26;
  }
  else if(v < 62)
  {
    return '0' + v - 52;
  }
  else if(v == 62)
  {
    return '-';
  }
  else if(v == 63)
  {
    return '_';
  }
  else
  {
    return 0;
  }
}

uint8_t b64dechr(char c)
{
  if(c >= 'A' && c <= 'Z')
  {
    return (uint8_t)(c - 'A');
  }
  else if(c >= 'a' && c <= 'z')
  {
    return (uint8_t)(c - 'a' + 26);
  }
  else if(c >= '0' && c <= '9')
  {
    return (uint8_t)(c - '0' + 52);
  }
  else if(c == '+' || c == '-')
  {
    return 62;
  }
  else if(c == '/' || c == '_')
  {
    return 63;
  }
  else
  {
    return 0;
  }
}

std::string Base64Encode(const void * data, std::size_t length)
{
  std::string out;
  uint8_t prev_bits = 0;
  uint8_t num_bits = 0;

  uint8_t * ptr = (uint8_t *)data;
  uint8_t * end = ptr + length;

  while(ptr != end)
  {
    if(num_bits >= 6)
    {
      out += b64chr(prev_bits);

      prev_bits = 0;
      num_bits = 0;
    }
    else
    {
      int consumed_bits = 6 - num_bits;
      int extra_bits = 8 - consumed_bits;

      auto val = *ptr;
      val >>= (8 - consumed_bits);
      val |= prev_bits;

      out += b64chr(val);

      prev_bits = (*ptr << (6 - extra_bits)) & 0x3f;
      num_bits = (uint8_t)extra_bits;

      ptr++;
    }
  }

  if(num_bits > 0)
  {
    out += b64chr(prev_bits & 0x3f);
  }

  if (num_bits == 2)
  {
    out += "==";
  }

  if (num_bits == 4)
  {
    out += "=";
  }

  return out;
}

std::string Base64Encode(const std::string_view & str)
{
  return Base64Encode(str.data(), str.length());
}

std::string UrlSafeBase64Encode(const void * data, std::size_t length)
{
  std::string out;
  uint8_t prev_bits = 0;
  uint8_t num_bits = 0;

  uint8_t * ptr = (uint8_t *)data;
  uint8_t * end = ptr + length;

  while(ptr != end)
  {
    if(num_bits >= 6)
    {
      out += urlb64chr(prev_bits);

      prev_bits = 0;
      num_bits = 0;
    }
    else
    {
      int consumed_bits = 6 - num_bits;
      int extra_bits = 8 - consumed_bits;

      auto val = *ptr;
      val >>= (8 - consumed_bits);
      val |= prev_bits;

      out += urlb64chr(val);

      prev_bits = (*ptr << (6 - extra_bits)) & 0x3f;
      num_bits = (uint8_t)extra_bits;

      ptr++;
    }
  }

  if(num_bits > 0)
  {
    out += urlb64chr(prev_bits & 0x3f);
  }

  return out;
}

std::string UrlSafeBase64Encode(const std::string_view & str)
{
  return UrlSafeBase64Encode(str.data(), str.length());
}

std::vector<uint8_t> Base64Decode(const std::string_view & data)
{
  std::vector<uint8_t> buffer;

  uint8_t pushed_bits = 0;
  uint8_t num_bits = 0;

  for(auto & c : data)
  {
    if(c == '=')
    {
      num_bits -= 2;
      continue;
    }

    uint8_t val = b64dechr(c);
    uint8_t available_bits = 8 - num_bits;

    if(available_bits == 8)
    {
      pushed_bits |= (val << 2);
      num_bits = 6;
    }
    else if(available_bits == 6)
    {
      pushed_bits |= (val);
      buffer.emplace_back(pushed_bits);

      num_bits = 0;
      pushed_bits = 0;
    }
    else if(available_bits == 4)
    {
      pushed_bits |= (val >> 2);
      buffer.emplace_back(pushed_bits);

      num_bits = 2;
      pushed_bits = (val << 6);
    }
    else if(available_bits == 2)
    {
      pushed_bits |= (val >> 4);
      buffer.emplace_back(pushed_bits);

      num_bits = 4;
      pushed_bits = (val << 4);
    }
  }

  return buffer;
}


bool IsValidUrlChar(char c)
{
  if(c >= 'A' && c <= 'Z')
  {
    return true;
  }

  if(c >= 'a' && c <= 'z')
  {
    return true;
  }

  if(c >= '0' && c <= '9')
  {
    return true;
  }

  switch(c)
  {
  case '-':
  case '_':
  case '.':
  case '~':
    return true;
  default:
    return false;
  }
}

std::string UrlEncode(const void * data, std::size_t length)
{
  std::string out;
  for(auto c = (const char *)data; length > 0; --length)
  {
    if(IsValidUrlChar(*c))
    {
      out += *c;
    }
    else
    {
      out += '%';

      auto hb = (*c & 0xf0) >> 4;
      auto lb = *c & 0x0f;

      if(hb >= 10)
      {
        out += ('A' + hb - 10);
      }
      else
      {
        out += ('0' + hb);
      }

      if(lb >= 10)
      {
        out += ('A' + lb - 10);
      }
      else
      {
        out += ('0' + lb);
      }
    }

    ++c;
  }

  return out;
}

std::string UrlEncode(const std::string_view & data)
{
  return UrlEncode(data.data(), data.size());
}

std::string UrlDecodeAsString(const std::string_view & data)
{
  std::string out;

  auto len = data.size();
  auto ptr = data.data();
  while(len > 0)
  {
    if(*ptr == '%')
    {
      --len;
      ++ptr;
      if(len == 0)
      {
        return out;
      }

      auto hb = *ptr;

      --len;
      ++ptr;
      if(len == 0)
      {
        return out;
      }

      auto lb = *ptr;

      char val = 0;
      if(hb >= '0' && hb <= '9')
      {
        val |= (hb - '0') << 4;
      }
      else if(hb >= 'a' && hb <= 'f')
      {
        val |= (hb - 'a' + 10) << 4;
      }
      else if(hb >= 'A' && hb <= 'F')
      {
        val |= (hb - 'A' + 10) << 4;
      }

      if(lb >= '0' && lb <= '9')
      {
        val |= (lb - '0');
      }
      else if(lb >= 'a' && lb <= 'f')
      {
        val |= (lb - 'a' + 10);
      }
      else if(lb >= 'A' && lb <= 'F')
      {
        val |= (lb - 'A' + 10);
      }

      out += val;

      --len;
      ++ptr;
    }
    else
    {
      ++ptr;
      --len;
    }
  }

  return out;
}


