#pragma once
#include "FileHandle.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace lab4 ::resource
{
class ResourceManager
{
  private:
    std::unordered_map<std::string, std::weak_ptr<FileHandle>> cache_;

  public:
    std::shared_ptr<FileHandle> getFile(const std::string& filename);
};
} // namespace lab4::resource