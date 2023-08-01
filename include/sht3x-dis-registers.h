#ifndef SHT3X_DIS_REGISTERS_H
#define SHT3X_DIS_REGISTERS_H
#include <stdint.h>

/*Device addresses - these are 7 bit addresses*/
#define DEVICE_ADDRESS_A                0x44  // default address
#define DEVICE_ADDRESS_B                0x45


/*repeatability measurements with clock stretching enabled and disabled*/
/**
 * @brief Table for single shot measurement modes
 *        Refer to datasheet table 8 page 10
 *        Mode column here is added for ease of reference
 * +---------------+------------------+-------+-----+------+
 * |            Condition             | Hex code    | Mode |
 * +---------------+------------------+-------+-----+------+
 * | Repeatability | Clock Stretching | MSB   | LSB |      |
 * +---------------+------------------+-------+-----+------+
 * | High          |                  |       | 06  |  1   |
 * +---------------+                  +-------+-----+------+
 * | Medium        | enabled          | 0x2C  | 0D  |  2   |
 * +---------------+                  +-------+-----+------+
 * | Low           |                  |       | 10  |  3   |
 * +---------------+------------------+-------+-----+------+
 * | High          |                  |       | 00  |  4   |
 * +---------------+                  +-------+-----+------+
 * | Medium        | disabled         | 0x24  | 0B  |  5   |
 * +---------------+                  +-------+-----+------+
 * | Low           |                  |       | 16  |  6   |
 * +---------------+------------------+-------+-----+------+
 */

#define CLK_STRECH_EN_MSB               0x2C
#define CLK_STRECH_DIS_MSB              0x24

#define CLK_STRECH_EN_HIGH_REPEAT_LSB   0x06
#define CLK_STRECH_EN_MID_REPEAT_LSB    0x0D
#define CLK_STRECH_EN_LOW_REPEAT_LSB    0x10

#define CLK_STRECH_DIS_HIGH_REPEAT_LSB  0x00
#define CLK_STRECH_DIS_MID_REPEAT_LSB   0x0B
#define CLK_STRECH_DIS_LOW_REPEAT_LSB   0x16


struct MeasurementModesSingleShot {
    uint8_t MODE1[2] = {CLK_STRECH_EN_MSB,CLK_STRECH_EN_HIGH_REPEAT_LSB};
    uint8_t MODE2[2] = {CLK_STRECH_EN_MSB,CLK_STRECH_EN_MID_REPEAT_LSB};
    uint8_t MODE3[2] = {CLK_STRECH_EN_MSB,CLK_STRECH_EN_LOW_REPEAT_LSB};
    uint8_t MODE4[2] = {CLK_STRECH_DIS_MSB,CLK_STRECH_DIS_HIGH_REPEAT_LSB};
    uint8_t MODE5[2] = {CLK_STRECH_DIS_MSB,CLK_STRECH_DIS_MID_REPEAT_LSB};
    uint8_t MODE6[2] = {CLK_STRECH_DIS_MSB,CLK_STRECH_DIS_LOW_REPEAT_LSB};
};


/* Measurement commands for peridoic data acquisition*/
/**
 * @brief Table for periodic data acquisition mode
 *        Refer to datasheet table 9 page 11
 *        Mode column is added here for ease of reference
 * +---------------+-----+----------+-----+------+
 * |       Condition     | Hex code |     | Mode |
 * +---------------+-----+----------+-----+       +
 * | Repeatability | mps | MSB      | LSB |      |
 * +---------------+-----+----------+-----+------+
 * |    High       |     |          | 32  | 1    |
 * +---------------+     +          +-----+------+
 * |    Medium     | 0.5 | 0x20     | 24  | 2    |
 * +---------------+     +          +-----+------+
 * |    Low        |     |          | 2F  | 3    |
 * +---------------+-----+----------+-----+------+
 * |    High       |     |          | 30  | 4    |
 * +---------------+     +          +-----+------+
 * |    Medium     | 1   | 0x21     | 26  | 5    |
 * +---------------+     +          +-----+------+
 * |    Low        |     |          | 2D  | 6    |
 * +---------------+-----+----------+-----+------+
 * |    High       |     |          | 36  | 7    |
 * +---------------+     +          +-----+------+
 * |    Medium     | 2   | 0x22     | 20  | 8    |
 * +---------------+     +          +-----+------+
 * |    Low        |     |          | 2B  | 9    |
 * +---------------+-----+----------+-----+------+
 * |    High       |     |          | 34  | 10   |
 * +---------------+     +          +-----+------+
 * |    Medium     | 4   | 0x23     | 22  | 11   |
 * +---------------+     +          +-----+------+
 * |    Low        |     |          | 29  | 12   |
 * +---------------+-----+----------+-----+------+
 * |    High       |     |          | 37  | 13   |
 * +---------------+     +          +-----+------+
 * |    Medium     | 10  | 0x27     | 21  | 14   |
 * +---------------+     +          +-----+------+
 * |    Low        |     |          | 2a  | 15   |
 * +---------------+-----+----------+-----+------+
 */

#define MPS_0_5_MSB                     0x20
#define MPS_1_MSB                       0x21
#define MPS_2_MSB                       0x22
#define MPS_4_MSB                       0x23
#define MPS_10_MSB                      0x27

#define MPS_0_5_LOW_LSB                 0x32
#define MPS_0_5_MID_LSB                 0x24
#define MPS_0_5_HIGH_LSB                0x2F

#define MPS_1_LOW_LSB                   0x30
#define MPS_1_MID_LSB                   0x26
#define MPS_1_HIGH_LSB                  0x2D

#define MPS_2_LOW_LSB                   0x36
#define MPS_2_MID_LSB                   0x20
#define MPS_2_HIGH_LSB                  0x2B

#define MPS_4_LOW_LSB                   0x34
#define MPS_4_MID_LSB                   0x22
#define MPS_4_HIGH_LSB                  0x29

#define MPS_10_LOW_LSB                  0x37
#define MPS_10_MID_LSB                  0x21
#define MPS_10_HIGH_LSB                 0x2A


struct MeasurementsPerSecondModes {
    uint8_t MODE1[2]  = {MPS_0_5_MSB,MPS_0_5_LOW_LSB};
    uint8_t MODE2[2]  = {MPS_0_5_MSB,MPS_0_5_MID_LSB};
    uint8_t MODE3[2]  = {MPS_0_5_MSB,MPS_0_5_HIGH_LSB};
    uint8_t MODE4[2]  = {MPS_1_MSB,MPS_1_LOW_LSB};
    uint8_t MODE5[2]  = {MPS_1_MSB,MPS_1_MID_LSB};
    uint8_t MODE6[2]  = {MPS_1_MSB,MPS_1_HIGH_LSB};
    uint8_t MODE7[2]  = {MPS_2_MSB,MPS_2_LOW_LSB};
    uint8_t MODE8[2]  = {MPS_2_MSB,MPS_2_MID_LSB};
    uint8_t MODE9[2]  = {MPS_2_MSB,MPS_2_HIGH_LSB};
    uint8_t MODE10[2] = {MPS_4_MSB,MPS_4_LOW_LSB};
    uint8_t MODE11[2] = {MPS_4_MSB,MPS_4_MID_LSB};
    uint8_t MODE12[2] = {MPS_4_MSB,MPS_4_HIGH_LSB};
    uint8_t MODE13[2] = {MPS_4_MSB,MPS_10_LOW_LSB};
    uint8_t MODE14[2] = {MPS_4_MSB,MPS_10_MID_LSB};
    uint8_t MODE15[2] = {MPS_4_MSB,MPS_10_HIGH_LSB};
};

/*readout of measurement results*/
#define FETCH_DATA_LSB                  0x00
#define FETCH_DATA_MSB                  0xE0


/*ART - Accelerated Response Time command*/
#define ART_4HZ_MSB                     0x2B
#define ART_4HZ_LSB                     0x32


/*Break command*/
#define BREAK_CMD_MSB                   0x30
#define BREAK_CMD_LSB                   0x93


/*Soft reset command*/
#define SOFT_RESET_MSB                  0x30
#define SOFT_RESET_LSB                  0xA2

/*General Call reset*/
#define GENERAL_CALL_RESET_MSB          0x00
#define GENERAL_CALL_RESET_LSB          0x06


/*Heater control commands*/
#define HEATER_EN_MSB                   0x30
#define HEATER_EN_LSB                   0x6D
#define HEATER_DIS_MSB                  0x30
#define HEATER_DIS_LSB                  0x66


/*Status register*/
#define READ_STATUS_REGISTER_MSB        0xF3
#define READ_STATUS_REGISTER_LSB        0x2D


/*Clear status register*/
#define CLEAR_STATUS_REGISTER_MSB       0x30
#define CLEAR_STATUS_REGISTER_LSB       0x41

#endif
