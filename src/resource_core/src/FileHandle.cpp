#include "FileHandle.hpp"
#include "ResourceError.hpp"
#include <cstdio>

namespace lab4::resource
{

ResourceError::ResourceError(const std::string& message) : std::runtime_error(message) {}

FileHandle::FileHandle(const std::string& filename)
{
    file_ = std::fopen(filename.c_str(), "a+");
    if (!file_)
    {
        throw ResourceError("Failed to open file: " + filename);
    }
}

FileHandle::~FileHandle()
{
    if (file_)
    {
        std::fclose(file_);
    }
}

FileHandle::FileHandle(FileHandle&& other) noexcept : file_(other.file_)
{
    other.file_ = nullptr;
}

FileHandle& FileHandle::operator=(FileHandle&& other) noexcept
{
    if (this != &other)
    {
        if (file_)
        {
            std::fclose(file_);
        }
        file_ = other.file_;
        other.file_ = nullptr;
    }
    return *this;
}

bool FileHandle::isOpen() const
{
    return file_ != nullptr;
}

} // namespace lab4::resource
