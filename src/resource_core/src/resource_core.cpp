#include "resource_core.hpp"

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

std::shared_ptr<FileHandle> ResourceManager::getFile(const std::string& filename)
{
    auto it = cache_.find(filename);

    if (it != cache_.end())
    {
        if (std::shared_ptr<FileHandle> sharedHandle = it->second.lock())
        {
            return sharedHandle;
        }
    }

    std::shared_ptr<FileHandle> newHandle = std::make_shared<FileHandle>(filename);

    cache_[filename] = newHandle;

    return newHandle;
}

} // namespace lab4::resource
