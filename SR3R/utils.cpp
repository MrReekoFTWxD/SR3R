#include "pch.h"
#include "utils.h"


__int64 ResolveImport(LPCWSTR Library)
{
    return (__int64)GetModuleHandle(Library);
}

std::string to_upper(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}
