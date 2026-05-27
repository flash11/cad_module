## newton toolkit

Реализация численных методов и геометрических алгоритмов.  
Используется метод Ньютона и модульная структура с unit-тестами.

---

## Установка зависимостей (vcpkg)

### 1. Установить vcpkg

Рекомендуемая папка: C:\vcpkg
```
git clone https://github.com/microsoft/vcpkg C:\vcpkg

```
### 2. Собрать vcpkg
```
cd C:\vcpkg
bootstrap-vcpkg.bat

```
### 3. (Рекомендуется) интеграция с системой
```
vcpkg integrate install

```
### 4. Установить GoogleTest
```
vcpkg install gtest:x64-windows

```
## Сборка

```

cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build

```

---

## Тестирование

Используется GoogleTest:

```
ctest --test-dir build

```

---

## Стек

* C++17
* CMake
* GoogleTest
* MSVC / Visual Studio

---

## Архитектура

* `src/` — реализация алгоритмов
* `include/` — заголовочные файлы
* `tests/` — модульные тесты
* `CMakeLists.txt` — система сборки