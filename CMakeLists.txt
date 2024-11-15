cmake_minimum_required(VERSION 3.10.0)
project(LinkedList)
enable_language(C ASM_NASM)

set(DEFAULT_OUT_OF_SOURCE_FOLDER "build")

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(WARNING "In-source builds not allowed. CMake will now be run with arguments:
cmake -H. -B${DEFAULT_OUT_OF_SOURCE_FOLDER}
")

    # Run CMake with out of source flag
    execute_process(
        COMMAND ${CMAKE_COMMAND} -H. -B${DEFAULT_OUT_OF_SOURCE_FOLDER}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

    # Cause fatal error to stop the script from further execution
    message(FATAL_ERROR "CMake has been ran to create an out of source build.
This error prevents CMake from running an in-source build.")
endif()

if(NOT DEFINED CMAKE_ASM_NASM_OBJECT_FORMAT)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)
endif()

if(CMAKE_ASM_NASM_OBJECT_FORMAT MATCHES "elf64")
    set(extra_flags "-m elf_x86_64")
elseif(CMAKE_ASM_NASM_OBJECT_FORMAT MATCHES "elfx32")
    set(extra_flags "-m elf32_x86_64")
elseif(CMAKE_ASM_NASM_OBJECT_FORMAT MATCHES "elf(32)?")
    set(extra_flags "-m elf_i386")
else()
    set(extra_flags "")
endif()

set(CMAKE_ASM_NASM_FLAGS_DEBUG "-g")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)
set(SRC ${CMAKE_SOURCE_DIR}/src)

add_executable(asmhello ${SRC}/LinkedList.asm ${SRC}/main.c)
add_executable(chello ${SRC}/LinkedList.c ${SRC}/main.c)

enable_testing()

add_test(NAME asm COMMAND $<TARGET_FILE:asmhello>)
add_test(NAME c COMMAND $<TARGET_FILE:chello>)
