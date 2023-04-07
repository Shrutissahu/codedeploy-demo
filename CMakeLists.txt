project(Factorial)

set(SOURCES src/main.cpp src/Factorial.cpp )
set(HEADERS src/Factorial.h)
add_executable(Factorial ${SOURCES} ${HEADERS})
set_property(TARGET Factorial PROPERTY CXX_STANDARD 17)
set_property(TARGET Factorial PROPERTY CXX_STANDARD_REQUIRED ON)