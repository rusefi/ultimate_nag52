#include <stdint.h>
#include <can_common.h>
#include "enums.h"

#define GS_418_ID 0x0418

typedef union {
    uint8_t bytes[8];
    uint64_t raw;
    // Sets speed step
    void set_FSC(FSC value){ raw = (raw & 0x00ffffffffffffff) | (value & 0x8) << 56; }
    // Gets speed step
    FSC get_FSC() { return static_cast<FSC>(raw >> 0 & 0x8); }

    // Sets driving program
    void set_FPC(FPC value){ raw = (raw & 0xff00ffffffffffff) | (value & 0x8) << 48; }
    // Gets driving program
    FPC get_FPC() { return static_cast<FPC>(raw >> 8 & 0x8); }

    // Sets transmission oil temperature
    void set_T_GET(uint8_t value){ raw = (raw & 0xffff00ffffffffff) | (value & 0x8) << 40; }
    // Gets transmission oil temperature
    uint8_t get_T_GET() { return raw >> 16 & 0x8; }

    // Sets Kickdown
    void set_KD(bool value){ raw = (raw & 0xfffffffeffffffff) | (value & 0x1) << 32; }
    // Gets Kickdown
    bool get_KD() { return raw >> 31 & 0x1; }

    // Sets apply brake when switching on
    void set_ESV_BRE(bool value){ raw = (raw & 0xfffffffdffffffff) | (value & 0x1) << 33; }
    // Gets apply brake when switching on
    bool get_ESV_BRE() { return raw >> 30 & 0x1; }

    // Sets gear mechanism variant
    void set_MECH(GearVariant value){ raw = (raw & 0xfffffff3ffffffff) | (value & 0x2) << 34; }
    // Gets gear mechanism variant
    GearVariant get_MECH() { return static_cast<GearVariant>(raw >> 28 & 0x2); }

    // Sets continuously variable transmission [1], multi-step transmission [0]
    void set_CVT(bool value){ raw = (raw & 0xffffffefffffffff) | (value & 0x1) << 36; }
    // Gets continuously variable transmission [1], multi-step transmission [0]
    bool get_CVT() { return raw >> 27 & 0x1; }

    // Sets switching
    void set_SWITCH(bool value){ raw = (raw & 0xffffffdfffffffff) | (value & 0x1) << 37; }
    // Gets switching
    bool get_SWITCH() { return raw >> 26 & 0x1; }

    // Sets front-wheel drive [1], rear-wheel drive [0]
    void set_FRONT(bool value){ raw = (raw & 0xffffffbfffffffff) | (value & 0x1) << 38; }
    // Gets front-wheel drive [1], rear-wheel drive [0]
    bool get_FRONT() { return raw >> 25 & 0x1; }

    // Sets all-wheel drive
    void set_ALL_WHEEL(bool value){ raw = (raw & 0xffffff7fffffffff) | (value & 0x1) << 39; }
    // Gets all-wheel drive
    bool get_ALL_WHEEL() { return raw >> 24 & 0x1; }

    // Sets actual gear
    void set_GIC(GEAR value){ raw = (raw & 0xfffffffff0ffffff) | (value & 0x4) << 24; }
    // Gets actual gear
    GEAR get_GIC() { return static_cast<GEAR>(raw >> 36 & 0x4); }

    // Sets target gear
    void set_GZC(GEAR value){ raw = (raw & 0xffffffff0fffffff) | (value & 0x4) << 28; }
    // Gets target gear
    GEAR get_GZC() { return static_cast<GEAR>(raw >> 32 & 0x4); }

    // Sets torque loss (FFh at KSG)
    void set_M_VERL(uint8_t value){ raw = (raw & 0xffffffffff00ffff) | (value & 0x8) << 16; }
    // Gets torque loss (FFh at KSG)
    uint8_t get_M_VERL() { return raw >> 40 & 0x8; }

    // Sets Gear selector lever position (NAG, KSG, CVT)
    void set_WHST(GearSelectorPos value){ raw = (raw & 0xffffffffffffc7ff) | (value & 0x3) << 11; }
    // Gets Gear selector lever position (NAG, KSG, CVT)
    GearSelectorPos get_WHST() { return static_cast<GearSelectorPos>(raw >> 50 & 0x3); }

    // Sets Factor wheel torque toggle 40ms + -10
    void set_FMRADTGL(bool value){ raw = (raw & 0xffffffffffffbfff) | (value & 0x1) << 14; }
    // Gets Factor wheel torque toggle 40ms + -10
    bool get_FMRADTGL() { return raw >> 49 & 0x1; }

    // Sets Wheel torque parity factor (even parity)
    void set_FMRADPAR(bool value){ raw = (raw & 0xffffffffffff7fff) | (value & 0x1) << 15; }
    // Gets Wheel torque parity factor (even parity)
    bool get_FMRADPAR() { return raw >> 48 & 0x1; }

    // Sets wheel torque factor (7FFh at KSG)
    void set_FMRAD(short value){ raw = (raw & 0xfffffffffffff800) | (value & 0xb) << 0; }
    // Gets wheel torque factor (7FFh at KSG)
    short get_FMRAD() { return raw >> 53 & 0xb; }

    void export_frame(CAN_FRAME &f) {
        f.id = GS_418_ID;
        f.length = 8;
        f.priority = 4;
        f.rtr = false;
        f.extended = false;
        memcpy(&f.data.int64, &raw, 8);
    }
} GS_418;