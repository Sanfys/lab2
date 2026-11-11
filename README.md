# Лабораторна робота №2

**Синхронізація паралельних операцій за допомогою механізму подій та механізму майбутніх результатів**

Курс: Паралельні та розподілені обчислення. Студент: Яремко О.Р., група КН-42.

## Збірка

```bash
make          # збирає всі програми в build/
make clean
```

Потрібен компілятор з підтримкою C++17 та pthread (g++ / clang++).

## Програми

| Пункт | Файл | Опис |
|-------|------|------|
| 1.2.1 | `src/task1_flag.cpp` | Синхронізація прапорцем + `sleep_for(100 мс)` |
| 1.2.2 | `src/task2_notify_all.cpp` | Три потоки `Waits` та потік `Awake` (`notify_all`) |
| 1.2.3 | `src/task3_notify_one.cpp` | Три потоки та потік `Notify` (`notify_one`) |
| 1.2.4 | `src/task4_condition_variable.cpp` | Умовна змінна замість прапорця |
| 1.2.5 | `src/task5_async.cpp` | `std::async`: `launch::deferred` vs `launch::async` |
| 1.2.6 | `src/task6_packaged_task.cpp` | Деки з `std::packaged_task` + потік-виконавець |
| 1.2.7 | `src/task7_promise_future.cpp` | `std::promise` / `std::future` |

Допоміжні функції `NthPrime`, `IsPrime` – у `src/common.h`.

## Запуск

```bash
./build/task1_flag            # вводьте числа, завершіть нечисловим символом (q) або Ctrl+D
./build/task2_notify_all
./build/task3_notify_one
./build/task4_condition_variable
./build/task5_async           # n, потім номер функції (1 - sqrt, 2 - sin, 3 - ln) двічі
./build/task6_packaged_task   # n, n, ... ; стоп - q
./build/task7_promise_future
```
