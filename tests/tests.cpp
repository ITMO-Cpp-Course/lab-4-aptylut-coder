#include <FileHandle.hpp>
#include <ResourceError.hpp>
#include <ResourceManager.hpp>
#include <catch2/catch_all.hpp>
#include <memory>

using namespace lab4::resource;

TEST_CASE("Тестирование управления ресурсами FileHandle")
{

    SECTION("Захват и автоматическое освобождение ресурса")
    {
        std::string test_name = "test_raii.txt";

        {
            FileHandle handle(test_name);
            REQUIRE(handle.isOpen() == true);
        }
    }

    SECTION("Передача владения ресурсом (Move)")
    {
        FileHandle handle1("move_test.txt");
        REQUIRE(handle1.isOpen() == true);

        FileHandle handle2 = std::move(handle1);

        REQUIRE_FALSE(handle1.isOpen());
        REQUIRE(handle2.isOpen());
    }

    SECTION("Обработка ошибок при открытии")
    {
        REQUIRE_THROWS_AS(FileHandle(""), ResourceError);
    }
}

TEST_CASE("Тестирование менеджера ресурсов ResourceManager")
{
    ResourceManager manager;
    std::string filename = "shared_resource.txt";

    SECTION("Кеширование: повторный запрос возвращает тот же объект")
    {
        std::shared_ptr<FileHandle> ptr1 = manager.getFile(filename);
        std::shared_ptr<FileHandle> ptr2 = manager.getFile(filename);

        REQUIRE(ptr1 == ptr2);
        REQUIRE(ptr1.use_count() == 2);
    }

    SECTION("Очистка кеша: объект пересоздается, если старый был удален")
    {
        void* original_address = nullptr;

        {
            std::shared_ptr<FileHandle> ptr1 = manager.getFile(filename);
            original_address = ptr1.get();
        }

        std::shared_ptr<FileHandle> ptr2 = manager.getFile(filename);

        REQUIRE(ptr2.get() != original_address);
        REQUIRE(ptr2.use_count() == 1);
    }

    SECTION("Разные файлы создают разные объекты")
    {
        auto fileA = manager.getFile("fileA.txt");
        auto fileB = manager.getFile("fileB.txt");

        REQUIRE(fileA != fileB);
    }
}