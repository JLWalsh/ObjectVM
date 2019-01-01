enable_testing()

macro(ovm_add_test name)
    add_executable(${name} ${name}.c ${ARGN})
    target_link_libraries(${name} ovm-lib unity)
    add_test(${name} ${name})
endmacro()