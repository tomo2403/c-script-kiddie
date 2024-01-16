#ifndef COMMANDLIST_H
#define COMMANDLIST_H

/// @brief Liste aller zu sendenden Befehle
DmxCommand dmxCommandList[74] = {
        {1, 0,     MiniMovingHead14Ch::RGB,          51400},
        {1, 0,     MiniMovingHead14Ch::Pan,          128},
        {1, 0,     MiniMovingHead14Ch::Tilt,         128},

        {0, 0,     RgbwSpotlight8Ch::RGB,            255},
        {0, 0,     RgbwSpotlight8Ch::TotalDimming,   255},
        {0, 400,   RgbwSpotlight8Ch::Blink,          255},
        {0, 800,   RgbwSpotlight8Ch::Blink,          255},
        {0, 1100,  RgbwSpotlight8Ch::Blink,          255},
        {0, 1580,  RgbwSpotlight8Ch::Blink,          255},
        {0, 1950,  RgbwSpotlight8Ch::Blink,          255},
        {0, 2350,  RgbwSpotlight8Ch::Blink,          255},
        {0, 2700,  RgbwSpotlight8Ch::Blink,          255},
        {0, 2990,  RgbwSpotlight8Ch::BlinkTimeout,   255},
        {0, 3000,  RgbwSpotlight8Ch::Blink,          255},
        {0, 3400,  RgbwSpotlight8Ch::BlinkTimeout,   100},
        {0, 3550,  RgbwSpotlight8Ch::Blink,          255},
        {0, 3900,  RgbwSpotlight8Ch::Blink,          255},
        {0, 4200,  RgbwSpotlight8Ch::Blink,          255},
        {0, 4700,  RgbwSpotlight8Ch::TotalDimming,   0}, //???????
        {0, 4700,  RgbwSpotlight8Ch::RGB,            65280},

        {1, 4700,  MiniMovingHead14Ch::Speed,        251},
        {1, 4700,  MiniMovingHead14Ch::Effect,       255},
        {1, 4700,  MiniMovingHead14Ch::Tilt,         255},
        {1, 4700,  MiniMovingHead14Ch::Effect,       190},
        {1, 16000, MiniMovingHead14Ch::Speed,        0},
        {1, 16000, MiniMovingHead14Ch::Effect,       0},
        {1, 16000, MiniMovingHead14Ch::Effect,       255},
        {1, 16000, MiniMovingHead14Ch::Pan,          255},
        {1, 16000, MiniMovingHead14Ch::Tilt,         255},
        {1, 16000, MiniMovingHead14Ch::RGB,          16711680},

        {0, 16000, RgbwSpotlight8Ch::RedDimming,     255},
        {0, 16000, RgbwSpotlight8Ch::BlueDimming,    0},

        {1, 18000, MiniMovingHead14Ch::Speed,        100},
        {1, 18000, MiniMovingHead14Ch::Pan,          0},
        {1, 18000, MiniMovingHead14Ch::Tilt,         0},
        {1, 18000, MiniMovingHead14Ch::GreenDimming, 100},

        {1, 21000, MiniMovingHead14Ch::Pan,          200},
        {1, 21000, MiniMovingHead14Ch::Tilt,         180},
        {1, 21000, MiniMovingHead14Ch::RedDimming,   0},
        {1, 21000, MiniMovingHead14Ch::WhiteDimming, 100},

        {0, 22000, RgbwSpotlight8Ch::GreenDimming,   255},
        {0, 22001, RgbwSpotlight8Ch::RedDimming,     0},

        {1, 24000, MiniMovingHead14Ch::Pan,          0},
        {1, 24000, MiniMovingHead14Ch::Tilt,         0},
        {1, 24000, MiniMovingHead14Ch::BlueDimming,  100},

        {1, 26000, MiniMovingHead14Ch::Pan,          80},
        {1, 26000, MiniMovingHead14Ch::Tilt,         190},
        {1, 26000, MiniMovingHead14Ch::BlueDimming,  0},
        {1, 26000, MiniMovingHead14Ch::GreenDimming, 0},
        {1, 26000, MiniMovingHead14Ch::RGB,          0},
        {1, 26000, MiniMovingHead14Ch::WhiteDimming, 255},

        {0, 26000, RgbwSpotlight8Ch::WhiteDimming,   200},

        {1, 27000, MiniMovingHead14Ch::Pan,          40},
        {1, 27000, MiniMovingHead14Ch::Tilt,         150},
        {1, 27000, MiniMovingHead14Ch::WhiteDimming, 0},
        {1, 27000, MiniMovingHead14Ch::RGB,          255},

        {1, 28000, MiniMovingHead14Ch::Pan,          80},
        {1, 28000, MiniMovingHead14Ch::Tilt,         190},
        {1, 28000, MiniMovingHead14Ch::RGB,          16711680},

        {1, 29000, MiniMovingHead14Ch::Pan,          255},
        {1, 29000, MiniMovingHead14Ch::Tilt,         0},
        {1, 29000, MiniMovingHead14Ch::RGB,          65280},

        {0, 30000, RgbwSpotlight8Ch::TotalDimming,   255},

        {1, 30500, MiniMovingHead14Ch::Speed,        190},
        {1, 30501, MiniMovingHead14Ch::Pan,          128},
        {1, 30501, MiniMovingHead14Ch::Tilt,         128},

        {0, 31000, RgbwSpotlight8Ch::Fade,           30},
        {1, 31000, MiniMovingHead14Ch::Fade,         30},
        {0, 32800, RgbwSpotlight8Ch::Stop,           0},
        {1, 32800, MiniMovingHead14Ch::Stop,         0}
};

#endif
