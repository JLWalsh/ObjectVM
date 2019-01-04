#ifndef OFLAG_H
#define OFLAG_H

#define OFLAG_READ(value, flag) value &flag
#define OFLAG_ENABLE(value, flags) value |= flags
#define OFLAG_DISABLE(value, flags) value &= ~flags

#endif /* OFLAG_H */
