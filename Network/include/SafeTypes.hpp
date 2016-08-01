#ifndef NETWORK_SAFETYPES_H
#define NETWORK_SAFETYPES_H

// определяем безопасные типы
// их можно безопасно передавать по сети
// битовая последовательность их хранения а также размер
// одинаковые во всех распростаненных OC
namespace wv
{
    typedef signed   char int8;
    typedef unsigned char intU8;

    typedef signed   short int16;
    typedef unsigned short intU16;

    typedef signed   int int32;
    typedef unsigned int intU32;
} // namespace wv

#endif
