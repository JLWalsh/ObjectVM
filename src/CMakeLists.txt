add_library(ovm-lib STATIC
    ovm/ovmobject.h
    ovm/ovmobject.c
    ovm/ovmtypes.h
    ovm/ovmstate.h
    ovm/ovm.h
    ovm/ovm.c
    ovm/ovmstack.h
    ovm/ovmstack.c
    ovm/ovmbytecode.h
    ovm/ovmbytecode.c
    ovm/ovmexecutor.h
    ovm/ovmexecutor.c
    ovm/ovmexecutor_int.h
    ovm/ovmexecutor_int.c
    ovm/ovmmemory.h
    ovm/ovmmemory.c
)

target_include_directories(ovm-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(ovm main.c)
target_link_libraries(ovm ovm-lib)

TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

IF(NOT ${IS_BIG_ENDIAN})
    add_definitions( -DVM_IS_LITTLE_ENDIAN )
ENDIF()