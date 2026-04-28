#include "ResourceManager.hpp"

namespace lab4::resource
{

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
