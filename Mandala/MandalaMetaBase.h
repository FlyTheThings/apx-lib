#pragma once

#include <cinttypes>
#include <sys/types.h>

#include <Xbus/XbusPacket.h>

namespace mandala {

typedef uint16_t uid_t;

typedef float real_t;
typedef uint32_t dword_t;
typedef uint16_t word_t;
typedef uint8_t byte_t;
typedef uint8_t option_t;

typedef uint32_t raw_t;

enum type_id_e {
    // integral formats [max 7]
    type_void,
    type_real,
    type_dword,
    type_word,
    type_byte,
    type_option,

    // bundle formats
    type_bundle = 10,
    type_vec2 = type_bundle,
    type_vec3,
};

static constexpr size_t type_size(type_id_e type)
{
    switch (type) {
    default:
        return 0;
    case type_real:
        return sizeof(real_t);
    case type_dword:
        return sizeof(dword_t);
    case type_word:
        return sizeof(word_t);
    case type_byte:
        return sizeof(byte_t);
    case type_option:
        return sizeof(option_t);
    }
}

// Data Specifier [1 byte] - first byte after pid for mandala data transfers

#pragma pack(1)
union spec_s {
    uint8_t _raw;

    struct
    {
        type_id_e type : 4; // data format
        uint8_t _rsv : 4;   //
    };

    explicit spec_s()
        : _raw(0)
    {}

    static constexpr inline uint16_t psize()
    {
        return sizeof(uint8_t);
    }
    inline void read(XbusStreamReader *s)
    {
        *s >> _raw;
    }
    inline void write(XbusStreamWriter *s) const
    {
        *s << _raw;
    }
};
static_assert(sizeof(spec_s) == spec_s::psize() && sizeof(spec_s) == sizeof(spec_s::_raw), "spec_s size error");
#pragma pack()

enum sfmt_id_e {
    sfmt_void,

    sfmt_bit,

    sfmt_u4, //(uint32)uint
    sfmt_u2, //(uint16)uint
    sfmt_u1, //(uint8)uint

    sfmt_f4,      //float32
    sfmt_f2,      //float16
    sfmt_f1,      //(uint8)float
    sfmt_f1_10,   //(uint8)float/10
    sfmt_f1_01,   //(uint8)float*10
    sfmt_f1_001,  //(uint8)float*100
    sfmt_f1_s,    //(int8)float
    sfmt_f1_s10,  //(int8)float/10
    sfmt_f1_s01,  //(int8)float*10
    sfmt_f1_s001, //(int8)float*100

};

struct meta_s
{
    const char *name;
    const char *title;
    const char *descr;
    const char *units;
    const char *path;

    const uid_t uid : sizeof(uid_t) * 8;
    const uid_t mask : sizeof(uid_t) * 8;
    const uint8_t level : 3;
    const bool group : 1;
    const type_id_e type_id : 4;
};

struct stream_item_s
{
    const uid_t uid : sizeof(uid_t) * 8;
    const sfmt_id_e sfmt : 4;
};

struct stream_id_s
{
    const char *name;
    const char *title;
    const stream_item_s *content;
};

}; // namespace mandala
