cmake_minimum_required(VERSION 3.15)
project(Joystick C)

set(CMAKE_C_STANDARD 99)

add_executable(Joystick main/main.c main/main.h dyn/dyn_app_common.c dyn/dyn_app_common.h
 dyn/dyn_app_sensor.c dyn/dyn_app_sensor.h dyn/dyn_frames.c dyn/dyn_frames.h dyn/dyn_instr.c dyn/dyn_instr.h
        dyn_test/b_queue.c dyn_test/b_queue.h dyn_test/dyn_emu.c dyn_test/dyn_emu.h dyn_test/fake_msp.h
        hal_dyn_uart/hal_dyn_uart_emu.c hal_dyn_uart/hal_dyn_uart_emu.h
        joystick_emu/joystick.c joystick_emu/joystick.h
        dyn/dyn_motors.c dyn/dyn_motors.h)

set( CMAKE_C_FLAGS "-pthread")