cmake_minimum_required(VERSION 3.10)
project(KeyboardTrainer C)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(keyboard_trainer 
    main.c 
    keyboard_trainer.c 
    keyboard_trainer.h)

target_link_libraries(keyboard_trainer PRIVATE Threads::Threads)

enable_testing()
add_executable(test_trainer test_keyboard_trainer.c keyboard_trainer.c)
target_link_libraries(test_trainer PRIVATE Threads::Threads)
add_test(NAME keyboard_trainer_test COMMAND test_trainer)