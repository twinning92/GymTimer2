// #pragma once
// #include <HardwareSerial.h>
// #include <NMEAGPS.h>
// #include <GPSfix_cfg.h>
// #include <NMEAGPS_cfg.h>
// #include "../Observers/TimeObserver.h"
// #include "../Subjects/TimerSignalEmitter.h"

// #ifdef GPS_FIX_SATELLITES
// #undef GPS_FIX_SATELLITES
// #endif
// #ifdef GPS_FIX_HEADING
// #undef GPS_FIX_HEADING
// #endif
// #ifdef GPS_FIX_SPEED
// #undef GPS_FIX_SPEED
// #endif
// #ifdef GPS_FIX_ALTITUDE
// #undef GPS_FIX_ALTITUDE
// #endif
// #ifdef GPS_FIX_LOCATION
// #undef GPS_FIX_LOCATION
// #endif

// #ifdef NMEAGPS_PARSE_GGA
// #undef NMEAGPS_PARSE_GGA
// #endif

// #ifdef NMEAGPS_PARSE_RMC
// #undef NMEAGPS_PARSE_RMC
// #endif

// #ifndef NMEAGPS_TIMESTAMP_FROM_INTERVAL
// #define NMEAGPS_TIMESTAMP_FROM_INTERVAL
// #endif

// #define DEBUG_PORT gps_serial_port
// class GPS : public TimeObserver
// {
// public:
//     GPS() : gps_serial_port(2)
//     {
//         gps_serial_port.begin(9600, SERIAL_8N1, 6, 7);
//         while (!get_gps_time())
//         {
//             Serial.println("Invalid GPS");
//         }
//     }

//     bool get_gps_time()
//     {
//         if (gps.available(gps_serial_port))
//         {
//             fix = gps.read();
//             if (fix.valid.time)
//             {
//                 this->seconds = fix.dateTime;
//                 this->seconds += this->zone_offset;
//                 return true;
//             }
//         }
//         return false;
//     }

//     void on_notify_second() override
//     {
//         update_gps_seconds++;
//         if (update_gps_seconds >= 60 * 60 * 12) // Update every 12 hours
//         {
//             get_gps_time();
//             update_gps_seconds = 0;
//         }
//     }

//     uint32_t get_seconds() { return this->seconds; }

// private:
//     HardwareSerial gps_serial_port;
//     NMEAGPS gps;
//     gps_fix fix;
//     NeoGPS::time_t seconds;
//     uint16_t update_gps_seconds = 0;
//     static const int32_t zone_hours = 8L; // AWST
//     static const int32_t zone_minutes = 0L;
//     static const NeoGPS::clock_t zone_offset =
//         zone_hours * NeoGPS::SECONDS_PER_HOUR +
//         zone_minutes * NeoGPS::SECONDS_PER_MINUTE;
// };

// extern GPS gps_sensor;