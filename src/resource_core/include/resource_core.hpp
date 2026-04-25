#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace lab4::resource
{

class ResourceError : public std::runtime_error
{
  public:
    explicit ResourceError(const std::string& message);
};

class FileHandle
{
  private:
    std::FILE* file_;

  public:
    explicit FileHandle(const std::string& filename);

    ~FileHandle();

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& other) noexcept;
    FileHandle& operator=(FileHandle&& other) noexcept;

    bool isOpen() const;
};

class ResourceManager
{
  private:
    std::unordered_map<std::string, std::weak_ptr<FileHandle>> cache_;

  public:
    std::shared_ptr<FileHandle> getFile(const std::string& filename);
};

} // namespace lab4::resource
