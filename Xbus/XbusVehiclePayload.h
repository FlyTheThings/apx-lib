#pragma once
#include "XbusStreamReader.h"
#include "XbusStreamWriter.h"

#include <array>

#define VEHICLE_CLASS_LIST \
    UAV,GCU,UGV,USV,SAT,RELAY

class XbusVehiclePayload
{
public:

    // Vehicle IDENT
    typedef std::array<char,16>     callsign_t;
    typedef std::array<uint8_t,12>  vuid_t; //global unique vehicle id
    typedef uint8_t                 vclass_t;


    typedef enum {
        VEHICLE_CLASS_LIST
    } vehicle_class_t;

    struct Ident {
        callsign_t  callsign;
        vuid_t      vuid;
        vclass_t    vclass;

        static inline uint16_t psize()
        {
            return std::tuple_size<callsign_t>()
                    + std::tuple_size<vuid_t>()
                    + sizeof(vclass_t);
        }
        void read(const uint8_t *p)
        {
            XbusStreamReader s(p);
            s >> callsign;
            s >> vuid;
            s >> vclass;
        }
        void write(uint8_t *p) const
        {
            XbusStreamWriter s(p);
            s << callsign;
            s << vuid;
            s << vclass;
        }
    };


    // Vehicle transponder data
    typedef float       lat_t;
    typedef float       lon_t;
    typedef int16_t     alt_t;
    typedef uint16_t    speed_t;
    typedef int16_t     course_t;
    typedef uint8_t     mode_t;

    struct Xpdr {
        lat_t       lat;
        lon_t       lon;
        float       alt;
        float       speed;
        float       course;
        mode_t      mode;

        static inline uint16_t psize()
        {
            return sizeof(lat_t)
                    + sizeof(lon_t)
                    + sizeof(alt_t)
                    + sizeof(speed_t)
                    + sizeof(course_t)
                    + sizeof(mode_t);

        }

        void read(const uint8_t *p)
        {
            XbusStreamReader s(p);
            s >> lat;
            s >> lon;
            alt=s.read<alt_t,float>();
            speed=s.read<speed_t,float>()/100.0f;
            course=s.read<course_t,float>()/(32768.0f/180.0f);
            s >> mode;
        }
        void write(uint8_t *p) const
        {
            XbusStreamWriter s(p);
            s << lat;
            s << lon;
            s.write<alt_t, float>(alt);
            s.write<speed_t, float>(speed*100.0f);
            s.write<course_t, float>(course*(32768.0f/180.0f));
            s << mode;
        }
    };

};
