#pragma once
#include <string>

namespace lab4 ::resource
{
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
} // namespace lab4::resource