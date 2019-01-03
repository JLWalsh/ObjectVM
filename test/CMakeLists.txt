enable_testing()

macro(ovm_add_test name strict)
    add_executable(${name} ${name}.c ${ARGN})
    add_test(${name} ${name})
    
    IF(${strict})
        message(STATUS "Creating test target ${name} in strict mode.")
        target_compile_definitions(${name} PRIVATE -DVM_STRICT_MODE)
        target_link_libraries(${name} ovm-lib-strict unity)
    ELSE()
        target_link_libraries(${name} ovm-lib unity)
    ENDIF()
endmacro()

ovm_add_test(test_ovmobject true)
ovm_add_test(test_ovmbytecode false)