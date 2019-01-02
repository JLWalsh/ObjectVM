#ifndef OVMOPS_H
#define OVMOPS_H

enum OVMOP
{
    OP_HALT,
    OP_NEW,
    OP_INVOKE,
    OP_INVOKE_SUPER,
    OP_RETURN,
    OP_I_PUSH,
    OP_I_PRINT,
    OP_LOCAL_I_LOAD,
    OP_GLOBAL_I_STORE,
    OP_GLOBAL_I_LOAD,
    NUM_OF_OPS
};

#endif /* OVMOPS_H */
