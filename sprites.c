enum spriteIndex {
    _ball,
    _paddleATop,
    _paddleAMiddle,
    _paddleABottom,
    _paddleBTop,
    _paddleBMiddle,
    _paddleBBottom
};

const _ballTileCount = 1;
const _ballTileIndex = 0;
unsigned char Ball[] =
{
  0x7E,0x7E,0xC3,0xFF,0x99,0xE7,0xBD,0xC3,
  0xBD,0xC3,0x99,0xE7,0xC3,0xFF,0x7E,0x7E
};

const _paddleTileCount = 1;
const _paddleTileIndex = 1;
unsigned char Paddle[] =
{
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18
};