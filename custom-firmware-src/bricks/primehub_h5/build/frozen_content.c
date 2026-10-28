//
// Content for MICROPY_MODULE_FROZEN_STR
//
#include <stdint.h>
#define MP_FROZEN_STR_NAMES \

const uint32_t mp_frozen_str_sizes[] = { 0 };
const char mp_frozen_str_content[] = {
"\0"
};

//
// Content for MICROPY_MODULE_FROZEN_MPY
//
#include "py/mpconfig.h"
#include "py/objint.h"
#include "py/objstr.h"
#include "py/emitglue.h"
#include "py/nativeglue.h"

#if MICROPY_LONGINT_IMPL != 0
#error "incompatible MICROPY_LONGINT_IMPL"
#endif

#if MICROPY_PY_BUILTINS_FLOAT
typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;
#endif

#if MICROPY_PY_BUILTINS_COMPLEX
typedef struct _mp_obj_complex_t {
    mp_obj_base_t base;
    mp_float_t real;
    mp_float_t imag;
} mp_obj_complex_t;
#endif

enum {
    MP_QSTR_Calibrating_dot__dot__dot_ = MP_QSTRnumber_of,
    MP_QSTR_Lifted_space_it_bang_,
    MP_QSTR_Moved_space_it_bang_,
    MP_QSTR_Not_space_90_space_deg_bang_,
    MP_QSTR_Port_space_View_space_Placeholder,
    MP_QSTR_REPEAT,
    MP_QSTR_Result_colon__space_,
    MP_QSTR_SIDE_COUNT,
    MP_QSTR_STATIONARY_COUNT,
    MP_QSTR__builtin_port_view_dot_py,
    MP_QSTR__imu_calibrate_dot_py,
    MP_QSTR_bias,
    MP_QSTR_calibrate_x,
    MP_QSTR_calibrate_y,
    MP_QSTR_calibrate_z,
    MP_QSTR_freq,
    MP_QSTR_gravity,
    MP_QSTR_message,
    MP_QSTR_new_side,
    MP_QSTR_roll_hub,
    MP_QSTR_roll_over_axis,
    MP_QSTR_rotation_x,
    MP_QSTR_rotation_y,
    MP_QSTR_rotation_z,
    MP_QSTR_side,
    MP_QSTR_sides,
    MP_QSTR_start_side,
    MP_QSTR_up_sides,
    MP_QSTR_wait_for_stationary,
};

const qstr_hash_t mp_qstr_frozen_const_hashes[] = {
    54313,
    24079,
    25900,
    25918,
    26418,
    35762,
    42134,
    23074,
    1577,
    33192,
    53172,
    26300,
    453,
    452,
    455,
    15077,
    41155,
    48238,
    893,
    33336,
    28213,
    63606,
    63607,
    63604,
    43134,
    47181,
    5377,
    59959,
    56709,
};

const qstr_len_t mp_qstr_frozen_const_lengths[] = {
    14,
    10,
    9,
    11,
    21,
    6,
    8,
    10,
    16,
    21,
    17,
    4,
    11,
    11,
    11,
    4,
    7,
    7,
    8,
    8,
    14,
    10,
    10,
    10,
    4,
    5,
    10,
    8,
    19,
};

extern const qstr_pool_t mp_qstr_const_pool;
const qstr_pool_t mp_qstr_frozen_const_pool = {
    &mp_qstr_const_pool, // previous pool
    MP_QSTRnumber_of, // previous pool size
    true, // is_sorted
    10, // allocated entries
    29, // used entries
    (qstr_hash_t *)mp_qstr_frozen_const_hashes,
    (qstr_len_t *)mp_qstr_frozen_const_lengths,
    {
        "Calibrating...",
        "Lifted it!",
        "Moved it!",
        "Not 90 deg!",
        "Port View Placeholder",
        "REPEAT",
        "Result: ",
        "SIDE_COUNT",
        "STATIONARY_COUNT",
        "_builtin_port_view.py",
        "_imu_calibrate.py",
        "bias",
        "calibrate_x",
        "calibrate_y",
        "calibrate_z",
        "freq",
        "gravity",
        "message",
        "new_side",
        "roll_hub",
        "roll_over_axis",
        "rotation_x",
        "rotation_y",
        "rotation_z",
        "side",
        "sides",
        "start_side",
        "up_sides",
        "wait_for_stationary",
    },
};

////////////////////////////////////////////////////////////////////////////////
// frozen module _builtin_port_view
// - original source file: build/frozen_mpy/_builtin_port_view.mpy
// - frozen file name: _builtin_port_view.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file _builtin_port_view.py, scope _builtin_port_view__lt_module_gt_
static const byte fun_data__builtin_port_view__lt_module_gt_[13] = {
    0x08,0x04, // prelude
    0x01, // names: <module>
    0x20, // code info
    0x11,0x02, // LOAD_NAME 'print'
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__builtin_port_view__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__builtin_port_view__lt_module_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 13,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 2,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data__builtin_port_view__lt_module_gt_ + 3,
        .line_info_top = fun_data__builtin_port_view__lt_module_gt_ + 4,
        .opcodes = fun_data__builtin_port_view__lt_module_gt_ + 4,
    },
    #endif
    #endif
};
#else
#define proto_fun__builtin_port_view__lt_module_gt_ fun_data__builtin_port_view__lt_module_gt_[0]
#endif

static const qstr_short_t const_qstr_table_data__builtin_port_view[3] = {
    MP_QSTR__builtin_port_view_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_print,
};

// constants

// constant table
static const mp_rom_obj_t const_obj_table_data__builtin_port_view[1] = {
    MP_ROM_QSTR(MP_QSTR_Port_space_View_space_Placeholder),
};

static const mp_frozen_module_t frozen_module__builtin_port_view = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data__builtin_port_view,
        .obj_table = (mp_obj_t *)&const_obj_table_data__builtin_port_view,
    },
    .proto_fun = &proto_fun__builtin_port_view__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// frozen module _imu_calibrate
// - original source file: build/frozen_mpy/_imu_calibrate.mpy
// - frozen file name: _imu_calibrate.py
// - .mpy header: 4d:06:00:1f

// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate__lt_module_gt_
static const byte fun_data__imu_calibrate__lt_module_gt_[367] = {
    0x40,0x58, // prelude
    0x01, // names: <module>
    0x2c,0x32,0x72,0x66,0x84,0x09,0x64,0x40,0x22,0x27,0x27,0x27,0x27,0x27,0x69,0x27,0x49,0x65,0x84,0x39,0x84,0x07,0x84,0x07,0x84,0x07,0x63,0x66,0x84,0x0b,0x22,0x1f,0x41,0x22,0x1f,0x41,0x22,0x1f,0x61,0x28,0x30,0x2a,0x6a, // code info
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x02, // LOAD_CONST_STRING 'ThisHub'
    0x2a,0x01, // BUILD_TUPLE 1
    0x1b,0x03, // IMPORT_NAME 'pybricks.hubs'
    0x1c,0x02, // IMPORT_FROM 'ThisHub'
    0x16,0x02, // STORE_NAME 'ThisHub'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x04, // LOAD_CONST_STRING 'Side'
    0x10,0x05, // LOAD_CONST_STRING 'Axis'
    0x2a,0x02, // BUILD_TUPLE 2
    0x1b,0x06, // IMPORT_NAME 'pybricks.parameters'
    0x1c,0x04, // IMPORT_FROM 'Side'
    0x16,0x04, // STORE_NAME 'Side'
    0x1c,0x05, // IMPORT_FROM 'Axis'
    0x16,0x05, // STORE_NAME 'Axis'
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0x10,0x07, // LOAD_CONST_STRING 'wait'
    0x10,0x08, // LOAD_CONST_STRING 'vector'
    0x2a,0x02, // BUILD_TUPLE 2
    0x1b,0x09, // IMPORT_NAME 'pybricks.tools'
    0x1c,0x07, // IMPORT_FROM 'wait'
    0x16,0x07, // STORE_NAME 'wait'
    0x1c,0x08, // IMPORT_FROM 'vector'
    0x16,0x08, // STORE_NAME 'vector'
    0x59, // POP_TOP
    0x11,0x02, // LOAD_NAME 'ThisHub'
    0x34,0x00, // CALL_FUNCTION 0
    0x16,0x28, // STORE_NAME 'hub'
    0x32,0x00, // MAKE_FUNCTION 0
    0x16,0x19, // STORE_NAME 'beep'
    0x32,0x01, // MAKE_FUNCTION 1
    0x16,0x1b, // STORE_NAME 'wait_for_stationary'
    0x2c,0x06, // BUILD_MAP 6
    0x23,0x00, // LOAD_CONST_OBJ 0
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0a, // LOAD_ATTR 'FRONT'
    0x62, // STORE_MAP
    0x23,0x01, // LOAD_CONST_OBJ 1
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0b, // LOAD_ATTR 'BACK'
    0x62, // STORE_MAP
    0x23,0x02, // LOAD_CONST_OBJ 2
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0c, // LOAD_ATTR 'LEFT'
    0x62, // STORE_MAP
    0x23,0x03, // LOAD_CONST_OBJ 3
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0d, // LOAD_ATTR 'RIGHT'
    0x62, // STORE_MAP
    0x23,0x04, // LOAD_CONST_OBJ 4
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0e, // LOAD_ATTR 'TOP'
    0x62, // STORE_MAP
    0x23,0x05, // LOAD_CONST_OBJ 5
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0f, // LOAD_ATTR 'BOTTOM'
    0x62, // STORE_MAP
    0x16,0x29, // STORE_NAME 'up_sides'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x2b,0x01, // BUILD_LIST 1
    0x86, // LOAD_CONST_SMALL_INT 6
    0xf4, // BINARY_OP 29 __mul__
    0x16,0x2a, // STORE_NAME 'gravity'
    0x11,0x08, // LOAD_NAME 'vector'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x34,0x03, // CALL_FUNCTION 3
    0x17,0x2b, // STORE_GLOBAL 'bias'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x16,0x2c, // STORE_NAME 'STATIONARY_COUNT'
    0x32,0x02, // MAKE_FUNCTION 2
    0x16,0x1f, // STORE_NAME 'roll_over_axis'
    0x23,0x06, // LOAD_CONST_OBJ 6
    0x16,0x2d, // STORE_NAME 'calibrate_x'
    0x23,0x07, // LOAD_CONST_OBJ 7
    0x16,0x2e, // STORE_NAME 'calibrate_y'
    0x23,0x08, // LOAD_CONST_OBJ 8
    0x16,0x2f, // STORE_NAME 'calibrate_z'
    0x82, // LOAD_CONST_SMALL_INT 2
    0x16,0x30, // STORE_NAME 'REPEAT'
    0x11,0x30, // LOAD_NAME 'REPEAT'
    0x82, // LOAD_CONST_SMALL_INT 2
    0xf4, // BINARY_OP 29 __mul__
    0x16,0x31, // STORE_NAME 'SIDE_COUNT'
    0x32,0x03, // MAKE_FUNCTION 3
    0x16,0x26, // STORE_NAME 'roll_hub'
    0x11,0x26, // LOAD_NAME 'roll_hub'
    0x11,0x05, // LOAD_NAME 'Axis'
    0x13,0x10, // LOAD_ATTR 'X'
    0x11,0x2d, // LOAD_NAME 'calibrate_x'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0e, // LOAD_ATTR 'TOP'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0c, // LOAD_ATTR 'LEFT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0f, // LOAD_ATTR 'BOTTOM'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0d, // LOAD_ATTR 'RIGHT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0e, // LOAD_ATTR 'TOP'
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x04, // CALL_FUNCTION 4
    0x16,0x32, // STORE_NAME 'rotation_x'
    0x11,0x26, // LOAD_NAME 'roll_hub'
    0x11,0x05, // LOAD_NAME 'Axis'
    0x13,0x11, // LOAD_ATTR 'Y'
    0x11,0x2e, // LOAD_NAME 'calibrate_y'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0e, // LOAD_ATTR 'TOP'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0a, // LOAD_ATTR 'FRONT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0f, // LOAD_ATTR 'BOTTOM'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0b, // LOAD_ATTR 'BACK'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0e, // LOAD_ATTR 'TOP'
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x04, // CALL_FUNCTION 4
    0x16,0x33, // STORE_NAME 'rotation_y'
    0x11,0x26, // LOAD_NAME 'roll_hub'
    0x11,0x05, // LOAD_NAME 'Axis'
    0x13,0x12, // LOAD_ATTR 'Z'
    0x11,0x2f, // LOAD_NAME 'calibrate_z'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0a, // LOAD_ATTR 'FRONT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0d, // LOAD_ATTR 'RIGHT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0b, // LOAD_ATTR 'BACK'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0c, // LOAD_ATTR 'LEFT'
    0x11,0x04, // LOAD_NAME 'Side'
    0x13,0x0a, // LOAD_ATTR 'FRONT'
    0x2b,0x04, // BUILD_LIST 4
    0x34,0x04, // CALL_FUNCTION 4
    0x16,0x34, // STORE_NAME 'rotation_z'
    0x11,0x28, // LOAD_NAME 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x14, // LOAD_METHOD 'settings'
    0x10,0x15, // LOAD_CONST_STRING 'angular_velocity_bias'
    0x11,0x35, // LOAD_NAME 'tuple'
    0x12,0x2b, // LOAD_GLOBAL 'bias'
    0x11,0x31, // LOAD_NAME 'SIDE_COUNT'
    0xf7, // BINARY_OP 32 __truediv__
    0x11,0x2c, // LOAD_NAME 'STATIONARY_COUNT'
    0xf7, // BINARY_OP 32 __truediv__
    0x86, // LOAD_CONST_SMALL_INT 6
    0xf7, // BINARY_OP 32 __truediv__
    0x34,0x01, // CALL_FUNCTION 1
    0x10,0x16, // LOAD_CONST_STRING 'angular_velocity_scale'
    0x11,0x32, // LOAD_NAME 'rotation_x'
    0x11,0x33, // LOAD_NAME 'rotation_y'
    0x11,0x34, // LOAD_NAME 'rotation_z'
    0x2a,0x03, // BUILD_TUPLE 3
    0x10,0x17, // LOAD_CONST_STRING 'acceleration_correction'
    0x32,0x04, // MAKE_FUNCTION 4
    0x11,0x2a, // LOAD_NAME 'gravity'
    0x34,0x01, // CALL_FUNCTION 1
    0x36,0x86,0x00, // CALL_METHOD 768
    0x59, // POP_TOP
    0x11,0x36, // LOAD_NAME 'print'
    0x10,0x18, // LOAD_CONST_STRING 'Result: '
    0x11,0x28, // LOAD_NAME 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x14, // LOAD_METHOD 'settings'
    0x36,0x00, // CALL_METHOD 0
    0x34,0x02, // CALL_FUNCTION 2
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
// child of _imu_calibrate__lt_module_gt_
// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate_beep
static const byte fun_data__imu_calibrate_beep[44] = {
    0x35,0x0e, // prelude
    0x19,0x37, // names: beep, freq
    0x80,0x09,0x22,0x76,0x23, // code info
    0x48,0x0f, // SETUP_EXCEPT 15
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x1a, // LOAD_ATTR 'speaker'
    0x14,0x19, // LOAD_METHOD 'beep'
    0xb0, // LOAD_FAST 0
    0x22,0x80,0x64, // LOAD_CONST_SMALL_INT 100
    0x36,0x02, // CALL_METHOD 2
    0x59, // POP_TOP
    0x4a,0x0a, // POP_EXCEPT_JUMP 10
    0x57, // DUP_TOP
    0x12,0x38, // LOAD_GLOBAL 'AttributeError'
    0xdf, // BINARY_OP 8 <exception match>
    0x44,0x43, // POP_JUMP_IF_FALSE 3
    0x59, // POP_TOP
    0x4a,0x01, // POP_EXCEPT_JUMP 1
    0x5d, // END_FINALLY
    0x12,0x07, // LOAD_GLOBAL 'wait'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__imu_calibrate_beep = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate_beep,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 44,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 7,
        .n_exc_stack = 1,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 25,
        .line_info = fun_data__imu_calibrate_beep + 4,
        .line_info_top = fun_data__imu_calibrate_beep + 9,
        .opcodes = fun_data__imu_calibrate_beep + 9,
    },
    #endif
    #endif
};
#else
#define proto_fun__imu_calibrate_beep fun_data__imu_calibrate_beep[0]
#endif

// child of _imu_calibrate__lt_module_gt_
// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate_wait_for_stationary
static const byte fun_data__imu_calibrate_wait_for_stationary[43] = {
    0x21,0x0a, // prelude
    0x1b,0x39, // names: wait_for_stationary, side
    0x80,0x12,0x22, // code info
    0x42,0x46, // JUMP 6
    0x12,0x07, // LOAD_GLOBAL 'wait'
    0x8a, // LOAD_CONST_SMALL_INT 10
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x1c, // LOAD_METHOD 'stationary'
    0x36,0x00, // CALL_METHOD 0
    0x44,0x30, // POP_JUMP_IF_FALSE -16
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x1d, // LOAD_METHOD 'up'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x00, // CALL_METHOD 256
    0xb0, // LOAD_FAST 0
    0xdc, // BINARY_OP 5 __ne__
    0x43,0x20, // POP_JUMP_IF_TRUE -32
    0x51, // LOAD_CONST_NONE
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__imu_calibrate_wait_for_stationary = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate_wait_for_stationary,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 43,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 5,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 27,
        .line_info = fun_data__imu_calibrate_wait_for_stationary + 4,
        .line_info_top = fun_data__imu_calibrate_wait_for_stationary + 7,
        .opcodes = fun_data__imu_calibrate_wait_for_stationary + 7,
    },
    #endif
    #endif
};
#else
#define proto_fun__imu_calibrate_wait_for_stationary fun_data__imu_calibrate_wait_for_stationary[0]
#endif

// child of _imu_calibrate__lt_module_gt_
// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate_roll_over_axis
static const byte fun_data__imu_calibrate_roll_over_axis[425] = {
    0x9a,0x10,0x52, // prelude
    0x1f,0x3a,0x3b, // names: roll_over_axis, axis, new_side
    0x80,0x26,0x40,0x47,0x2e,0x22,0x2f,0x2a,0x2f,0x27,0x1f,0x45,0x22,0x52,0x2d,0x47,0x27,0x48,0x22,0x30,0x30,0x73,0x48,0x27,0x2f,0x31,0x4f,0x45,0x22,0x30,0x30,0x53,0x2b,0x47,0x68,0x40,0x4b,0x48, // code info
    0x12,0x36, // LOAD_GLOBAL 'print'
    0x23,0x09, // LOAD_CONST_OBJ 9
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0xb0, // LOAD_FAST 0
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0xc2, // STORE_FAST 2
    0x42,0x77, // JUMP 55
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x21, // LOAD_METHOD 'orientation'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0xf4, // BINARY_OP 29 __mul__
    0x30,0x03, // UNPACK_SEQUENCE 3
    0xc3, // STORE_FAST 3
    0xc3, // STORE_FAST 3
    0xc4, // STORE_FAST 4
    0x12,0x3c, // LOAD_GLOBAL 'abs'
    0xb4, // LOAD_FAST 4
    0x34,0x01, // CALL_FUNCTION 1
    0x23,0x0a, // LOAD_CONST_OBJ 10
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x56, // POP_JUMP_IF_FALSE 22
    0x12,0x36, // LOAD_GLOBAL 'print'
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x21, // LOAD_METHOD 'orientation'
    0x36,0x00, // CALL_METHOD 0
    0xb0, // LOAD_FAST 0
    0xf4, // BINARY_OP 29 __mul__
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x3d, // LOAD_GLOBAL 'RuntimeError'
    0x10,0x22, // LOAD_CONST_STRING 'Lifted it!'
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x07, // LOAD_GLOBAL 'wait'
    0x22,0x80,0x64, // LOAD_CONST_SMALL_INT 100
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x1d, // LOAD_METHOD 'up'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x00, // CALL_METHOD 256
    0xb1, // LOAD_FAST 1
    0xdc, // BINARY_OP 5 __ne__
    0x43,0xb8,0x7f, // POP_JUMP_IF_TRUE -72
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x1c, // LOAD_METHOD 'stationary'
    0x36,0x00, // CALL_METHOD 0
    0x44,0xad,0x7f, // POP_JUMP_IF_FALSE -83
    0x12,0x3c, // LOAD_GLOBAL 'abs'
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0xb0, // LOAD_FAST 0
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0xb2, // LOAD_FAST 2
    0xf3, // BINARY_OP 28 __sub__
    0x34,0x01, // CALL_FUNCTION 1
    0xc5, // STORE_FAST 5
    0x12,0x3c, // LOAD_GLOBAL 'abs'
    0xb5, // LOAD_FAST 5
    0x22,0x80,0x5a, // LOAD_CONST_SMALL_INT 90
    0xf3, // BINARY_OP 28 __sub__
    0x34,0x01, // CALL_FUNCTION 1
    0x8a, // LOAD_CONST_SMALL_INT 10
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x3d, // LOAD_GLOBAL 'RuntimeError'
    0x23,0x0b, // LOAD_CONST_OBJ 11
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x36, // LOAD_GLOBAL 'print'
    0x23,0x0c, // LOAD_CONST_OBJ 12
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x19, // LOAD_GLOBAL 'beep'
    0x22,0x87,0x68, // LOAD_CONST_SMALL_INT 1000
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x08, // LOAD_GLOBAL 'vector'
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x10, // LOAD_ATTR 'X'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x11, // LOAD_ATTR 'Y'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x12, // LOAD_ATTR 'Z'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x34,0x03, // CALL_FUNCTION 3
    0xc6, // STORE_FAST 6
    0x12,0x08, // LOAD_GLOBAL 'vector'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x80, // LOAD_CONST_SMALL_INT 0
    0x34,0x03, // CALL_FUNCTION 3
    0xc7, // STORE_FAST 7
    0x12,0x2c, // LOAD_GLOBAL 'STATIONARY_COUNT'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x6a, // JUMP 42
    0x57, // DUP_TOP
    0xc8, // STORE_FAST 8
    0xb7, // LOAD_FAST 7
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x23, // LOAD_METHOD 'acceleration'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x00, // CALL_METHOD 256
    0xe5, // BINARY_OP 14 __iadd__
    0xc7, // STORE_FAST 7
    0x12,0x2b, // LOAD_GLOBAL 'bias'
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x24, // LOAD_METHOD 'angular_velocity'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x00, // CALL_METHOD 256
    0xe5, // BINARY_OP 14 __iadd__
    0x17,0x2b, // STORE_GLOBAL 'bias'
    0x12,0x07, // LOAD_GLOBAL 'wait'
    0x81, // LOAD_CONST_SMALL_INT 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x11, // POP_JUMP_IF_TRUE -47
    0x59, // POP_TOP
    0x59, // POP_TOP
    0xb7, // LOAD_FAST 7
    0x12,0x2c, // LOAD_GLOBAL 'STATIONARY_COUNT'
    0xea, // BINARY_OP 19 __itruediv__
    0xc7, // STORE_FAST 7
    0x12,0x08, // LOAD_GLOBAL 'vector'
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x10, // LOAD_ATTR 'X'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x11, // LOAD_ATTR 'Y'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x12,0x28, // LOAD_GLOBAL 'hub'
    0x13,0x13, // LOAD_ATTR 'imu'
    0x14,0x20, // LOAD_METHOD 'rotation'
    0x12,0x05, // LOAD_GLOBAL 'Axis'
    0x13,0x12, // LOAD_ATTR 'Z'
    0x10,0x1e, // LOAD_CONST_STRING 'calibrated'
    0x50, // LOAD_CONST_FALSE
    0x36,0x82,0x01, // CALL_METHOD 257
    0x34,0x03, // CALL_FUNCTION 3
    0xc9, // STORE_FAST 9
    0x12,0x3c, // LOAD_GLOBAL 'abs'
    0xb9, // LOAD_FAST 9
    0xb6, // LOAD_FAST 6
    0xf3, // BINARY_OP 28 __sub__
    0x34,0x01, // CALL_FUNCTION 1
    0x81, // LOAD_CONST_SMALL_INT 1
    0xd8, // BINARY_OP 1 __gt__
    0x44,0x47, // POP_JUMP_IF_FALSE 7
    0x12,0x3d, // LOAD_GLOBAL 'RuntimeError'
    0x10,0x25, // LOAD_CONST_STRING 'Moved it!'
    0x34,0x01, // CALL_FUNCTION 1
    0x65, // RAISE_OBJ
    0x12,0x29, // LOAD_GLOBAL 'up_sides'
    0xb1, // LOAD_FAST 1
    0x55, // LOAD_SUBSCR
    0x30,0x02, // UNPACK_SEQUENCE 2
    0xca, // STORE_FAST 10
    0xcb, // STORE_FAST 11
    0x12,0x2a, // LOAD_GLOBAL 'gravity'
    0xba, // LOAD_FAST 10
    0x58, // DUP_TOP_TWO
    0x55, // LOAD_SUBSCR
    0xb7, // LOAD_FAST 7
    0xbb, // LOAD_FAST 11
    0x55, // LOAD_SUBSCR
    0xe5, // BINARY_OP 14 __iadd__
    0x5b, // ROT_THREE
    0x56, // STORE_SUBSCR
    0x12,0x19, // LOAD_GLOBAL 'beep'
    0x22,0x83,0x74, // LOAD_CONST_SMALL_INT 500
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0xb5, // LOAD_FAST 5
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__imu_calibrate_roll_over_axis = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate_roll_over_axis,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 425,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 20,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 2,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 31,
        .line_info = fun_data__imu_calibrate_roll_over_axis + 6,
        .line_info_top = fun_data__imu_calibrate_roll_over_axis + 44,
        .opcodes = fun_data__imu_calibrate_roll_over_axis + 44,
    },
    #endif
    #endif
};
#else
#define proto_fun__imu_calibrate_roll_over_axis fun_data__imu_calibrate_roll_over_axis[0]
#endif

// child of _imu_calibrate__lt_module_gt_
// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate_roll_hub
static const byte fun_data__imu_calibrate_roll_hub[76] = {
    0x80,0x14,0x1c, // prelude
    0x26,0x3a,0x3e,0x3f,0x40, // names: roll_hub, axis, message, start_side, sides
    0x80,0x7a,0x26,0x26,0x28,0x22,0x27,0x25,0x34, // code info
    0x12,0x36, // LOAD_GLOBAL 'print'
    0xb1, // LOAD_FAST 1
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x1b, // LOAD_GLOBAL 'wait_for_stationary'
    0xb2, // LOAD_FAST 2
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x12,0x19, // LOAD_GLOBAL 'beep'
    0x22,0x83,0x74, // LOAD_CONST_SMALL_INT 500
    0x34,0x01, // CALL_FUNCTION 1
    0x59, // POP_TOP
    0x80, // LOAD_CONST_SMALL_INT 0
    0xc4, // STORE_FAST 4
    0x12,0x30, // LOAD_GLOBAL 'REPEAT'
    0x80, // LOAD_CONST_SMALL_INT 0
    0x42,0x54, // JUMP 20
    0x57, // DUP_TOP
    0xc5, // STORE_FAST 5
    0xb3, // LOAD_FAST 3
    0x5f, // GET_ITER_STACK
    0x4b,0x0c, // FOR_ITER 12
    0xc6, // STORE_FAST 6
    0xb4, // LOAD_FAST 4
    0x12,0x1f, // LOAD_GLOBAL 'roll_over_axis'
    0xb0, // LOAD_FAST 0
    0xb6, // LOAD_FAST 6
    0x34,0x02, // CALL_FUNCTION 2
    0xe5, // BINARY_OP 14 __iadd__
    0xc4, // STORE_FAST 4
    0x42,0x32, // JUMP -14
    0x81, // LOAD_CONST_SMALL_INT 1
    0xe5, // BINARY_OP 14 __iadd__
    0x58, // DUP_TOP_TWO
    0x5a, // ROT_TWO
    0xd7, // BINARY_OP 0 __lt__
    0x43,0x27, // POP_JUMP_IF_TRUE -25
    0x59, // POP_TOP
    0x59, // POP_TOP
    0xb4, // LOAD_FAST 4
    0x12,0x30, // LOAD_GLOBAL 'REPEAT'
    0xf7, // BINARY_OP 32 __truediv__
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__imu_calibrate_roll_hub = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate_roll_hub,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 76,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 17,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 4,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 38,
        .line_info = fun_data__imu_calibrate_roll_hub + 8,
        .line_info_top = fun_data__imu_calibrate_roll_hub + 17,
        .opcodes = fun_data__imu_calibrate_roll_hub + 17,
    },
    #endif
    #endif
};
#else
#define proto_fun__imu_calibrate_roll_hub fun_data__imu_calibrate_roll_hub[0]
#endif

// child of _imu_calibrate__lt_module_gt_
// frozen bytecode for file _imu_calibrate.py, scope _imu_calibrate__lt_listcomp_gt_
static const byte fun_data__imu_calibrate__lt_listcomp_gt_[22] = {
    0x41,0x08, // prelude
    0x27,0x41, // names: <listcomp>, *
    0x80,0x91, // code info
    0x2b,0x00, // BUILD_LIST 0
    0xb0, // LOAD_FAST 0
    0x5f, // GET_ITER_STACK
    0x4b,0x09, // FOR_ITER 9
    0xc1, // STORE_FAST 1
    0xb1, // LOAD_FAST 1
    0x12,0x31, // LOAD_GLOBAL 'SIDE_COUNT'
    0xf7, // BINARY_OP 32 __truediv__
    0x2f,0x14, // STORE_COMP 20
    0x42,0x35, // JUMP -11
    0x63, // RETURN_VALUE
};
#if MICROPY_PERSISTENT_CODE_SAVE
static const mp_raw_code_truncated_t proto_fun__imu_calibrate__lt_listcomp_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate__lt_listcomp_gt_,
    .children = NULL,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 22,
    .n_children = 0,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 1,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 39,
        .line_info = fun_data__imu_calibrate__lt_listcomp_gt_ + 4,
        .line_info_top = fun_data__imu_calibrate__lt_listcomp_gt_ + 6,
        .opcodes = fun_data__imu_calibrate__lt_listcomp_gt_ + 6,
    },
    #endif
    #endif
};
#else
#define proto_fun__imu_calibrate__lt_listcomp_gt_ fun_data__imu_calibrate__lt_listcomp_gt_[0]
#endif

static const mp_raw_code_t *const children__imu_calibrate__lt_module_gt_[] = {
    (const mp_raw_code_t *)&proto_fun__imu_calibrate_beep,
    (const mp_raw_code_t *)&proto_fun__imu_calibrate_wait_for_stationary,
    (const mp_raw_code_t *)&proto_fun__imu_calibrate_roll_over_axis,
    (const mp_raw_code_t *)&proto_fun__imu_calibrate_roll_hub,
    (const mp_raw_code_t *)&proto_fun__imu_calibrate__lt_listcomp_gt_,
};

static const mp_raw_code_truncated_t proto_fun__imu_calibrate__lt_module_gt_ = {
    .proto_fun_indicator[0] = MP_PROTO_FUN_INDICATOR_RAW_CODE_0,
    .proto_fun_indicator[1] = MP_PROTO_FUN_INDICATOR_RAW_CODE_1,
    .kind = MP_CODE_BYTECODE,
    .is_generator = 0,
    .fun_data = fun_data__imu_calibrate__lt_module_gt_,
    .children = (void *)&children__imu_calibrate__lt_module_gt_,
    #if MICROPY_PERSISTENT_CODE_SAVE
    .fun_data_len = 367,
    .n_children = 5,
    #if MICROPY_EMIT_MACHINE_CODE
    .prelude_offset = 0,
    #endif
    #if MICROPY_PY_SYS_SETTRACE
    .line_of_definition = 0,
    .prelude = {
        .n_state = 9,
        .n_exc_stack = 0,
        .scope_flags = 0,
        .n_pos_args = 0,
        .n_kwonly_args = 0,
        .n_def_pos_args = 0,
        .qstr_block_name_idx = 1,
        .line_info = fun_data__imu_calibrate__lt_module_gt_ + 3,
        .line_info_top = fun_data__imu_calibrate__lt_module_gt_ + 46,
        .opcodes = fun_data__imu_calibrate__lt_module_gt_ + 46,
    },
    #endif
    #endif
};

static const qstr_short_t const_qstr_table_data__imu_calibrate[66] = {
    MP_QSTR__imu_calibrate_dot_py,
    MP_QSTR__lt_module_gt_,
    MP_QSTR_ThisHub,
    MP_QSTR_pybricks_dot_hubs,
    MP_QSTR_Side,
    MP_QSTR_Axis,
    MP_QSTR_pybricks_dot_parameters,
    MP_QSTR_wait,
    MP_QSTR_vector,
    MP_QSTR_pybricks_dot_tools,
    MP_QSTR_FRONT,
    MP_QSTR_BACK,
    MP_QSTR_LEFT,
    MP_QSTR_RIGHT,
    MP_QSTR_TOP,
    MP_QSTR_BOTTOM,
    MP_QSTR_X,
    MP_QSTR_Y,
    MP_QSTR_Z,
    MP_QSTR_imu,
    MP_QSTR_settings,
    MP_QSTR_angular_velocity_bias,
    MP_QSTR_angular_velocity_scale,
    MP_QSTR_acceleration_correction,
    MP_QSTR_Result_colon__space_,
    MP_QSTR_beep,
    MP_QSTR_speaker,
    MP_QSTR_wait_for_stationary,
    MP_QSTR_stationary,
    MP_QSTR_up,
    MP_QSTR_calibrated,
    MP_QSTR_roll_over_axis,
    MP_QSTR_rotation,
    MP_QSTR_orientation,
    MP_QSTR_Lifted_space_it_bang_,
    MP_QSTR_acceleration,
    MP_QSTR_angular_velocity,
    MP_QSTR_Moved_space_it_bang_,
    MP_QSTR_roll_hub,
    MP_QSTR__lt_listcomp_gt_,
    MP_QSTR_hub,
    MP_QSTR_up_sides,
    MP_QSTR_gravity,
    MP_QSTR_bias,
    MP_QSTR_STATIONARY_COUNT,
    MP_QSTR_calibrate_x,
    MP_QSTR_calibrate_y,
    MP_QSTR_calibrate_z,
    MP_QSTR_REPEAT,
    MP_QSTR_SIDE_COUNT,
    MP_QSTR_rotation_x,
    MP_QSTR_rotation_y,
    MP_QSTR_rotation_z,
    MP_QSTR_tuple,
    MP_QSTR_print,
    MP_QSTR_freq,
    MP_QSTR_AttributeError,
    MP_QSTR_side,
    MP_QSTR_axis,
    MP_QSTR_new_side,
    MP_QSTR_abs,
    MP_QSTR_RuntimeError,
    MP_QSTR_message,
    MP_QSTR_start_side,
    MP_QSTR_sides,
    MP_QSTR__star_,
};

// constants
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_0 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(0),
    MP_ROM_INT(0),
}};
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_1 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(1),
    MP_ROM_INT(0),
}};
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_2 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(2),
    MP_ROM_INT(1),
}};
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_3 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(3),
    MP_ROM_INT(1),
}};
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_4 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(4),
    MP_ROM_INT(2),
}};
static const mp_rom_obj_tuple_t const_obj__imu_calibrate_5 = {{&mp_type_tuple}, 2, {
    MP_ROM_INT(5),
    MP_ROM_INT(2),
}};
static const mp_obj_str_t const_obj__imu_calibrate_6 = {{&mp_type_str}, 38293, 140, (const byte*)"\x0a\x47\x6f\x69\x6e\x67\x20\x74\x6f\x20\x63\x61\x6c\x69\x62\x72\x61\x74\x65\x20\x58\x20\x6e\x6f\x77\x21\x0a\x2d\x20\x50\x75\x74\x20\x74\x68\x65\x20\x68\x75\x62\x20\x6f\x6e\x20\x74\x68\x65\x20\x74\x61\x62\x6c\x65\x20\x69\x6e\x20\x66\x72\x6f\x6e\x74\x20\x6f\x66\x20\x79\x6f\x75\x2e\x0a\x2d\x20\x74\x6f\x70\x20\x73\x69\x64\x65\x20\x28\x64\x69\x73\x70\x6c\x61\x79\x29\x20\x66\x61\x63\x69\x6e\x67\x20\x75\x70\x0a\x2d\x20\x72\x69\x67\x68\x74\x20\x73\x69\x64\x65\x20\x28\x70\x6f\x72\x74\x73\x20\x42\x44\x46\x29\x20\x74\x6f\x77\x61\x72\x64\x73\x20\x79\x6f\x75\x2e\x0a"};
static const mp_obj_str_t const_obj__imu_calibrate_7 = {{&mp_type_str}, 8943, 136, (const byte*)"\x0a\x47\x6f\x69\x6e\x67\x20\x74\x6f\x20\x63\x61\x6c\x69\x62\x72\x61\x74\x65\x20\x59\x20\x6e\x6f\x77\x0a\x2d\x20\x50\x75\x74\x20\x74\x68\x65\x20\x68\x75\x62\x20\x6f\x6e\x20\x74\x68\x65\x20\x74\x61\x62\x6c\x65\x20\x69\x6e\x20\x66\x72\x6f\x6e\x74\x20\x6f\x66\x20\x79\x6f\x75\x2e\x0a\x2d\x20\x74\x6f\x70\x20\x73\x69\x64\x65\x20\x28\x64\x69\x73\x70\x6c\x61\x79\x29\x20\x66\x61\x63\x69\x6e\x67\x20\x75\x70\x0a\x2d\x20\x62\x61\x63\x6b\x20\x73\x69\x64\x65\x20\x28\x73\x70\x65\x61\x6b\x65\x72\x29\x20\x74\x6f\x77\x61\x72\x64\x73\x20\x79\x6f\x75\x2e\x0a"};
static const mp_obj_str_t const_obj__imu_calibrate_8 = {{&mp_type_str}, 1800, 141, (const byte*)"\x0a\x47\x6f\x69\x6e\x67\x20\x74\x6f\x20\x63\x61\x6c\x69\x62\x72\x61\x74\x65\x20\x5a\x20\x6e\x6f\x77\x21\x0a\x2d\x20\x50\x75\x74\x20\x74\x68\x65\x20\x68\x75\x62\x20\x6f\x6e\x20\x74\x68\x65\x20\x74\x61\x62\x6c\x65\x20\x69\x6e\x20\x66\x72\x6f\x6e\x74\x20\x6f\x66\x20\x79\x6f\x75\x2e\x0a\x2d\x20\x66\x72\x6f\x6e\x74\x20\x73\x69\x64\x65\x20\x28\x55\x53\x42\x20\x70\x6f\x72\x74\x29\x20\x66\x61\x63\x69\x6e\x67\x20\x75\x70\x0a\x2d\x20\x6c\x65\x66\x74\x20\x73\x69\x64\x65\x20\x28\x70\x6f\x72\x74\x73\x20\x41\x43\x45\x29\x20\x74\x6f\x77\x61\x72\x64\x73\x20\x79\x6f\x75\x0a"};
static const mp_obj_str_t const_obj__imu_calibrate_9 = {{&mp_type_str}, 54843, 48, (const byte*)"\x52\x6f\x6c\x6c\x20\x69\x74\x20\x74\x6f\x77\x61\x72\x64\x73\x20\x79\x6f\x75\x2c\x20\x77\x69\x74\x68\x6f\x75\x74\x20\x6c\x69\x66\x74\x69\x6e\x67\x20\x74\x68\x65\x20\x68\x75\x62\x20\x75\x70\x21"};
#if MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_A || MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_B
static const mp_obj_float_t const_obj__imu_calibrate_10 = {{&mp_type_float}, (mp_float_t)0.07000000000000001};
#define const_obj__imu_calibrate_10_macro MP_ROM_PTR(&const_obj__imu_calibrate_10)
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_C
#define const_obj__imu_calibrate_10_macro ((mp_rom_obj_t)(0xbe0f5c2a))
#elif MICROPY_OBJ_REPR == MICROPY_OBJ_REPR_D
#define const_obj__imu_calibrate_10_macro ((mp_rom_obj_t)(0xbfb5eb851eb851ec))
#endif

// constant table
static const mp_rom_obj_t const_obj_table_data__imu_calibrate[13] = {
    MP_ROM_PTR(&const_obj__imu_calibrate_0),
    MP_ROM_PTR(&const_obj__imu_calibrate_1),
    MP_ROM_PTR(&const_obj__imu_calibrate_2),
    MP_ROM_PTR(&const_obj__imu_calibrate_3),
    MP_ROM_PTR(&const_obj__imu_calibrate_4),
    MP_ROM_PTR(&const_obj__imu_calibrate_5),
    MP_ROM_PTR(&const_obj__imu_calibrate_6),
    MP_ROM_PTR(&const_obj__imu_calibrate_7),
    MP_ROM_PTR(&const_obj__imu_calibrate_8),
    MP_ROM_PTR(&const_obj__imu_calibrate_9),
    const_obj__imu_calibrate_10_macro,
    MP_ROM_QSTR(MP_QSTR_Not_space_90_space_deg_bang_),
    MP_ROM_QSTR(MP_QSTR_Calibrating_dot__dot__dot_),
};

static const mp_frozen_module_t frozen_module__imu_calibrate = {
    .constants = {
        .qstr_table = (qstr_short_t *)&const_qstr_table_data__imu_calibrate,
        .obj_table = (mp_obj_t *)&const_obj_table_data__imu_calibrate,
    },
    .proto_fun = &proto_fun__imu_calibrate__lt_module_gt_,
};

////////////////////////////////////////////////////////////////////////////////
// collection of all frozen modules

const char mp_frozen_names[] = {
    #ifdef MP_FROZEN_STR_NAMES
    MP_FROZEN_STR_NAMES
    #endif
    "_builtin_port_view.py\0"
    "_imu_calibrate.py\0"
    "\0"
};

const mp_frozen_module_t *const mp_frozen_mpy_content[] = {
    &frozen_module__builtin_port_view,
    &frozen_module__imu_calibrate,
};

#ifdef MICROPY_FROZEN_LIST_ITEM
MICROPY_FROZEN_LIST_ITEM("_builtin_port_view", "_builtin_port_view.py")
MICROPY_FROZEN_LIST_ITEM("_imu_calibrate", "_imu_calibrate.py")
#endif

/*
byte sizes:
qstr content: 29 unique, 420 bytes
bc content: 990
const str content: 465
const int content: 0
const obj content: 76
const table qstr content: 0 entries, 0 bytes
const table ptr content: 14 entries, 56 bytes
raw code content: 7 * 4 = 112
mp_frozen_mpy_names_content: 41
mp_frozen_mpy_content_size: 8
total: 2168
*/
