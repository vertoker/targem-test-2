Тестовое задание в Targem Games, попытка №2

Данный `README` на русском, все комментарии в коде - на английском

Со времени [прошлого](https://github.com/vertoker/targem-test) тестового, сделал несколько side-проектов
- [cpp-lua-testcase](https://github.com/vertoker/cpp-lua-testcase) - абстрактный
скриптовый движок, который имплементирует основной функционал работы с `Lua`
- [mystd](https://github.com/vertoker/mystd) - моя реализация `std` типов с особенностями

## Как собрать

Я специально добавил 2 системы сборки: простой `.bat` файл и `cmake` с конфигурациями

`.bat` файл настроен для `g++` и общей конфигурацией `Release`, рассчитан на 
сборку во всех случаях. Чтобы его собрать и запустить, достаточно запустить его из *папки проекта*

`cmake` написан достаточно просто, здесь есть выбор конфигураций между `Debug/Release` и 
обе из них работают через `clang++` и `Ninja`. Чтобы его собрать и запустить, 
нужно из *папки проекта* запустить консоль и прописать эти команды

```bat
cmake . --preset Debug
cd build/Debug
cmake --build .

targemtest2.exe
```

По необходимости заменить `Debug` на `Release` (ну или просто использовать VS Code/Visual Studio)

## Решения разработки

Тут я хочу описать мотивацию своих решений по поводу дизайна самого кода

`String.h`
- Coding style был полностью украден из файлов на вашем сайте. Видно, что файлы были написаны 
более 10 лет назад, но раз другого я не нашёл, то именно в таком стиле и будет весь код
- Я изучил как устроен оригинальный `std::string` и постарался скопировать его поведение полностью
(в меру возможного, без шаблонов, аллокаторов и прочих фишек)
- `size` и `capacity` описывают строку **без** `null-terminated` символа `/0`, такое поведение
есть в `std::string` и всех реализациях, которые я видел
- Управление памятью очевидно самое простое и выглядит не слишком уж производительно
(это особенно заметно на `default ctor`), тут явно не хватает оптимизаций по работе
с динамической памятью по типу `SSO` и аллокаторов (опять же в задании этого не было)
- У меня было желание добавить дополнительные функции по типу `Swap`, `Resize` или
различные операторы, но я решил не перегружать задание

`String.cpp`
- Я использую `initializer list` не всегда, скорее по вкусу. Считаю этот вопрос больше
синтаксическим сахаром и в такие моменты лучше смотреть на результат компилятора
- Использование `memcpy` вместо `strcpy(_s)` является как по мне вкусовщиной. Выбор по факту
стоит между `for` и `while`. Пускай такие вопросы опять же будет решать компилятор
- Реализация `operator==(const String& lhs, const char* rhs)` отличается
от типовой в угоду оптимизации. Лучше использовать цикл с условием, чем 2 цикла (`strlen`)
- Реализация `operator>>(std::istream& is, String& str)` не использует `getline`, чтобы
динамически аллоцировать строку по необходимости
- `GrowthFactor` я поставил `1.5`, потому что изначальный фактор `2` у `std::string`
не является самым оптимальным, а среди разных факторов я выбрал самый распространённый.
[`FBVector`](https://github.com/facebook/folly/blob/main/folly/docs/FBVector.md),
[Scott Meyers](https://groups.google.com/g/comp.lang.c++.moderated/c/asH_VojWKJw/m/4jJHJXPzWJ0J),
[Тесты вариантов](https://ece.uwaterloo.ca/~dwharder/aads/Algorithms/Array_resizing/)

`main.cpp`
- Я использовал `std::sort`, я мог бы написать свою сортировку, но в задании я не увидел
ничего про написание своего алгоритма сортировки
- Я не написал для строки `operator<`, так как этого не было в задании, 
а ещё мне было так проще его отлаживать
- Предикат для сортировки я написал в виде отдельного типа-функции
(правда не шаблонного), который я скопировал с `std::greater`
