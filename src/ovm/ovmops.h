#ifndef OVMOPS_H
#define OVMOPS_H

enum OVMOP
{
    OP_HALT,
    OP_NEW,
    OP_INVOKE,
    OP_INVOKE_SUPER,
    OP_RETURN,
    OP_UI_PUSH,
    OP_UI_PRINT,
    OP_LOCAL_LOAD,
    OP_GLOBAL_STORE,
    OP_GLOBAL_LOAD,
    NUM_OF_OPS
};

#endif /* OVMOPS_H */
