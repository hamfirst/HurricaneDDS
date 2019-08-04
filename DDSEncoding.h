#pragma once

#include <cstdint>

#include <vector>
#include <string>
#include <string_view>

std::string Base64Encode(const void * data, std::size_t length);
std::string Base64Encode(const std::string_view & str);

std::string UrlSafeBase64Encode(const void * data, std::size_t length);
std::string UrlSafeBase64Encode(const std::string_view & str);

std::vector<uint8_t> Base64Decode(const std::string_view & data);

std::string UrlEncode(const void * data, std::size_t length);
std::string UrlEncode(const std::string_view & data);
std::string UrlDecodeAsString(const std::string_view & data);
