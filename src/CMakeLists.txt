SET(OVM_LIB_SOURCES
    ovm/oobject.h
    ovm/oobject.c
    ovm/otypes.h
    ovm/ostate.h
    ovm/ovm.h
    ovm/ovm.c
    ovm/ostack.h
    ovm/ostack.c
    ovm/obytecode.h
    ovm/obytecode.c
    ovm/oexecutor.h
    ovm/oexecutor.c
    ovm/oexecutor_int.h
    ovm/oexecutor_int.c
    ovm/omemory.h
    ovm/omemory.c
    ovm/omath.h
    ovm/omath.c
)

add_library(ovm-lib STATIC ${OVM_LIB_SOURCES})
add_library(ovm-lib-strict STATIC ${OVM_LIB_SOURCES})

target_compile_definitions(ovm-lib-strict PRIVATE -DVM_STRICT_MODE)

target_include_directories(ovm-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(ovm-lib-strict PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ovm main.c)
target_link_libraries(ovm ovm-lib)

TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

IF(NOT ${IS_BIG_ENDIAN})
    add_definitions( -DVM_IS_LITTLE_ENDIAN )
ENDIF()