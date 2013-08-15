#ifndef _GAMMA_H_
#define _GAMMA_H_

// Gamma correction

static unsigned char Gamma[] = {
  0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
  0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
  0x02,0x02,0x03,0x03,0x03,0x03,0x03,0x03,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
  0x03,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
  0x04,0x04,0x04,0x04,0x04,0x05,0x05,0x05,
  0x05,0x05,0x05,0x05,0x05,0x05,0x06,0x06,
  0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x07,
  0x07,0x07,0x07,0x07,0x07,0x08,0x08,0x08,
  0x08,0x08,0x09,0x09,0x09,0x09,0x09,0x09,
  0x0A,0x0A,0x0A,0x0A,0x0B,0x0B,0x0B,0x0B,
  0x0C,0x0C,0x0C,0x0C,0x0D,0x0D,0x0D,0x0D,
  0x0E,0x0E,0x0E,0x0F,0x0F,0x0F,0x10,0x10,
  0x10,0x11,0x11,0x11,0x12,0x12,0x13,0x13,
  0x13,0x14,0x14,0x15,0x15,0x16,0x16,0x17,
  0x17,0x18,0x18,0x19,0x19,0x1A,0x1A,0x1B,
  0x1B,0x1C,0x1D,0x1D,0x1E,0x1F,0x1F,0x20,
  0x21,0x21,0x22,0x23,0x24,0x24,0x25,0x26,
  0x27,0x28,0x29,0x29,0x2A,0x2B,0x2C,0x2D,
  0x2E,0x2F,0x30,0x31,0x32,0x33,0x35,0x36,
  0x37,0x38,0x39,0x3B,0x3C,0x3D,0x3E,0x40,
  0x41,0x43,0x44,0x46,0x47,0x49,0x4A,0x4C,
  0x4E,0x4F,0x51,0x53,0x55,0x56,0x58,0x5A,
  0x5C,0x5E,0x60,0x62,0x65,0x67,0x69,0x6B,
  0x6E,0x70,0x72,0x75,0x78,0x7A,0x7D,0x80,
  0x82,0x85,0x88,0x8B,0x8E,0x91,0x94,0x98,
  0x9B,0x9E,0xA2,0xA5,0xA9,0xAD,0xB0,0xB4,
  0xB8,0xBC,0xC0,0xC5,0xC9,0xCD,0xD2,0xD6,
  0xDB,0xE0,0xE5,0xEA,0xEF,0xF4,0xFA,0xFF
};

#endif // _GAMMA_H_