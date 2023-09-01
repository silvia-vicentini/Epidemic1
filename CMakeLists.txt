cmake_minimum_required(VERSION 3.16)
project(epidemic VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# richiedi SFML
# le dipendenze vengono identificate automaticamente
#find_package(SFML 2.6 COMPONENTS graphics REQUIRED)
#/usr/local/Cellar/sfml/2.6.0

add_executable(epidemic main.cpp result/result.cpp epidemic/epidemic.cpp)
#target_link_libraries(epidemic PRIVATE sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile epidemic.t
  add_executable(epidemic.t epidemic/epidemic.test.cpp epidemic/epidemic.cpp)
  #target_link_libraries(epidemic.t PRIVATE sfml-graphics)
   add_test(NAME epidemic.t COMMAND epidemic.t)

endif()
