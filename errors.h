#ifndef ERRORS_H
#define ERRORS_H

enum class ERRORS
{
    NO_ERROR = 1,

    OBJ_EMPTY = -1,
    INVALID_ARGUMENT = -2,

    JSON_PART_BROKEN = -10,

    FILE_OPEN_ERROR = -20,
};

#endif // ERRORS_H
