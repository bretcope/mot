#include <cassert>
#include <cstring>
#include "FileSpan.h"

FileSpan::FileSpan(const FileContent* content, uint32_t start, uint32_t end):
        _content(content),
        _start(start),
        _end(end)
{
    assert(content != nullptr);
    assert(end <= content->Size());
    assert(end >= start);
}

FileSpan::~FileSpan() = default;

const FileContent* FileSpan::Content() const
{
    return _content;
}

uint32_t FileSpan::Start() const
{
    return _start;
}

uint32_t FileSpan::End() const
{
    return _end;
}

uint32_t FileSpan::Length() const
{
    return _end - _start;
}

uint32_t FileSpan::CopyTo(char* dest) const
{
    auto length = Length();

    if (length == 0)
        return 0;

    memcpy(dest, &_content->Data()[_start], Length());
    return length;
}

size_t FileSpan::Print(FILE* stream) const
{
    auto length = Length();

    if (length == 0)
        return 0;

    return fwrite(&_content->Data()[_start], 1, length, stream);
}

char* FileSpan::NewString() const
{
    auto length = Length();
    auto str = new char[length + 1];

    if (length > 0)
        memcpy(str, &_content->Data()[_start], length);

    str[length] = '\0';
    return str;
}