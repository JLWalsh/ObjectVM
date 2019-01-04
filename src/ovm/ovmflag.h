#ifndef OVMFLAG_H
#define OVMFLAG_H

#define OVMFLAG_READ(value, flag) value &flag
#define OVMFLAG_ENABLE(value, flags) value |= flags
#define OVMFLAG_DISABLE(value, flags) value &= ~flags

#endif /* OVMFLAG_H */
