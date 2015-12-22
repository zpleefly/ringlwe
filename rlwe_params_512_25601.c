/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * See LICENSE for complete information.
 */
	
#include <inttypes.h>
#include "rlwe_params_512_25601.h"

const RINGELT m = 512, muwords = 8; /* key (mu) is m bits */

const RINGELT q = 25601, qmod4 = 1;

const RINGELT B = 5, BB = 11, LOG2B = 4, BMASK = 0xf;

const RINGELT small_coeff_table[11] = {25596, 25597, 25598, 25599, 25600, 0, 1, 2, 3, 4, 5};

const RINGELT q_1_4 = 6400, q_2_4 = 12800, q_3_4 = 19201;
const RINGELT r0_l = 9600, r0_u = 22401, r1_l = 3199, r1_u = 16001;	


/* Public Parameter a. Each a parameter rejection sampled from non-overlapping
 * segments of the digits of e.
 * Note that this is held in the FFT / CRT basis.*/
const RINGELT a[512] = {
        0x3A5B, 0x163F, 0x0989, 0x155A, 0x2E98, 0x5946, 0x371B, 0x22DE, 
        0x344E, 0x0B8B, 0x1FEF, 0x5C6D, 0x45BE, 0x5930, 0x59E3, 0x3977, 
        0x2F78, 0x3B06, 0x2E09, 0x5C31, 0x5A1D, 0x4092, 0x45A7, 0x4D30, 
        0x2EE7, 0x443C, 0x00D1, 0x296C, 0x3B88, 0x4E51, 0x3863, 0x2967, 
        0x5E9C, 0x11FC, 0x22D5, 0x2ABB, 0x2D33, 0x2523, 0x4F69, 0x3CAA, 
        0x4424, 0x56BC, 0x55E8, 0x0192, 0x532F, 0x005E, 0x0457, 0x256E, 
        0x30D7, 0x1D4F, 0x50CA, 0x1619, 0x5C16, 0x2D9F, 0x5466, 0x35C3, 
        0x4364, 0x33BE, 0x508C, 0x58E1, 0x2D45, 0x3D94, 0x2F83, 0x2C97, 
        0x3BDE, 0x511C, 0x4B08, 0x52E9, 0x5C1D, 0x60B4, 0x47E8, 0x4B12, 
        0x04BA, 0x340F, 0x46F3, 0x4581, 0x52A5, 0x3ED0, 0x130E, 0x6012, 
        0x3964, 0x186F, 0x2622, 0x36E0, 0x4BF8, 0x4EE1, 0x5204, 0x37E7, 
        0x22AF, 0x08B7, 0x05AA, 0x12DA, 0x2EE1, 0x4D00, 0x0BA8, 0x22FC, 
        0x54C8, 0x49A8, 0x2154, 0x2933, 0x3A48, 0x6191, 0x06DC, 0x5007, 
        0x3916, 0x0B43, 0x3BB6, 0x23C4, 0x5ED6, 0x498A, 0x4B70, 0x5C88, 
        0x601B, 0x5DC4, 0x0F92, 0x1964, 0x1959, 0x4795, 0x54B5, 0x5F57, 
        0x5B43, 0x5C5B, 0x6066, 0x1E99, 0x6128, 0x2C19, 0x110E, 0x2CEB, 
        0x3F42, 0x1BB3, 0x536F, 0x19A5, 0x1B34, 0x4629, 0x4993, 0x5EB9, 
        0x114E, 0x4782, 0x5D17, 0x56AC, 0x3392, 0x1AE0, 0x38B5, 0x1FF2, 
        0x4DD6, 0x636E, 0x1A78, 0x15C0, 0x1D91, 0x31C0, 0x3658, 0x404F, 
        0x536A, 0x5120, 0x0428, 0x2A24, 0x03CE, 0x4EB8, 0x0395, 0x0B70, 
        0x2C0E, 0x35E6, 0x4542, 0x3766, 0x1D78, 0x1AFA, 0x1A42, 0x30AC, 
        0x0CA4, 0x298B, 0x1109, 0x0F3D, 0x55AC, 0x5314, 0x2F0A, 0x5B1B, 
        0x2D98, 0x0B7E, 0x21E3, 0x59D9, 0x5FF9, 0x0815, 0x4239, 0x3F48, 
        0x1F14, 0x4267, 0x1F3F, 0x1A8C, 0x0F13, 0x4F3B, 0x01A0, 0x0C03, 
        0x0F43, 0x534F, 0x2FE0, 0x06F6, 0x3270, 0x3207, 0x2137, 0x2AE4, 
        0x025A, 0x600D, 0x008D, 0x31F8, 0x449A, 0x5381, 0x07BB, 0x23DC, 
        0x349A, 0x1884, 0x6312, 0x37E9, 0x3A1F, 0x00A2, 0x5179, 0x1DB6, 
        0x1F53, 0x3220, 0x40FA, 0x15CF, 0x57CD, 0x3EC4, 0x248A, 0x018B, 
        0x5AA2, 0x423A, 0x0F3F, 0x0956, 0x2452, 0x4BA7, 0x0DEC, 0x4D7D, 
        0x4967, 0x2FA5, 0x4BF6, 0x3746, 0x4811, 0x16E9, 0x42C8, 0x2347, 
        0x1875, 0x3CCD, 0x1E50, 0x0D5F, 0x0427, 0x613E, 0x4C1C, 0x1517, 
        0x5241, 0x3612, 0x1F40, 0x0043, 0x31BF, 0x2E95, 0x5050, 0x410C, 
        0x21C0, 0x4462, 0x2B4D, 0x1982, 0x4300, 0x59EC, 0x590A, 0x1697, 
        0x4D25, 0x18BE, 0x000E, 0x3B02, 0x5A52, 0x5F55, 0x0336, 0x2900, 
        0x21FE, 0x3CE6, 0x2FF1, 0x343E, 0x4F90, 0x34D1, 0x48C2, 0x0BF8, 
        0x1AE5, 0x1C33, 0x061A, 0x454B, 0x33EC, 0x1BA2, 0x3340, 0x4DA4, 
        0x3393, 0x5E32, 0x498A, 0x1273, 0x500F, 0x2B16, 0x0811, 0x3F7C, 
        0x2854, 0x2812, 0x4E04, 0x00BE, 0x11B5, 0x0466, 0x140B, 0x2900, 
        0x31D4, 0x20EE, 0x2379, 0x14DF, 0x4642, 0x6194, 0x551B, 0x5571, 
        0x5A28, 0x1D71, 0x05D4, 0x4A67, 0x1BA5, 0x5EE3, 0x62CF, 0x2742, 
        0x53DB, 0x083C, 0x5C1E, 0x0717, 0x1319, 0x37A9, 0x3E20, 0x2867, 
        0x0F3D, 0x6296, 0x5B76, 0x5A4C, 0x2CFF, 0x2B92, 0x5440, 0x2A73, 
        0x5C53, 0x5E4D, 0x5292, 0x480C, 0x2341, 0x3DD5, 0x363E, 0x6270, 
        0x21BF, 0x3FA0, 0x6285, 0x191C, 0x267D, 0x37E2, 0x1B15, 0x63D3, 
        0x13E8, 0x4DA3, 0x6051, 0x217F, 0x53F1, 0x63CC, 0x2CB9, 0x6153, 
        0x3BEB, 0x01CE, 0x62B4, 0x13D4, 0x5CB9, 0x37AE, 0x0743, 0x5257, 
        0x1D81, 0x4BC9, 0x52E2, 0x013E, 0x166F, 0x5B44, 0x4B45, 0x4A26, 
        0x6207, 0x21E6, 0x3C77, 0x03DB, 0x4EC6, 0x49D2, 0x1C92, 0x0DDD, 
        0x380F, 0x634D, 0x3C1F, 0x5D73, 0x51DD, 0x2C68, 0x5E8D, 0x32D3, 
        0x309A, 0x54F7, 0x4332, 0x056D, 0x59DF, 0x4469, 0x411C, 0x0D98, 
        0x471C, 0x1B6A, 0x1541, 0x303A, 0x1F21, 0x0B6C, 0x2338, 0x2EFC, 
        0x3554, 0x614F, 0x0F13, 0x2B48, 0x5108, 0x0344, 0x1E65, 0x2050, 
        0x194F, 0x2690, 0x59A8, 0x5D6E, 0x2A9A, 0x0DA9, 0x09C5, 0x505E, 
        0x096F, 0x3573, 0x3F7E, 0x4BD1, 0x4C07, 0x5E51, 0x4534, 0x53AC, 
        0x4137, 0x3B7B, 0x54CF, 0x010A, 0x187B, 0x3BE9, 0x30F0, 0x53AB, 
        0x2431, 0x3FA4, 0x3EAB, 0x04E4, 0x0478, 0x14CC, 0x2F1A, 0x36CA, 
        0x591F, 0x0FEA, 0x3800, 0x4C58, 0x27AE, 0x6081, 0x0CE9, 0x324B, 
        0x5DCA, 0x2358, 0x5EDC, 0x20AD, 0x34F8, 0x5ADD, 0x21CF, 0x2C70, 
        0x1483, 0x0972, 0x155C, 0x11E9, 0x5591, 0x5C85, 0x43C9, 0x08AC, 
        0x3886, 0x4331, 0x564E, 0x0AB7, 0x40DF, 0x3006, 0x0549, 0x618E, 
        0x473E, 0x05F4, 0x13BB, 0x2FFD, 0x61AF, 0x1C76, 0x369C, 0x2002, 
        0x3C7F, 0x55E2, 0x10B2, 0x03EC, 0x0273, 0x60D5, 0x0DF7, 0x1285, 
        0x4F29, 0x14DE, 0x61DD, 0x5435, 0x110F, 0x60D4, 0x0D75, 0x27C3, 
        0x3F5B, 0x0CFA, 0x0A5B, 0x2FF6, 0x0CAC, 0x4EC5, 0x1BF9, 0x24B5
        };


