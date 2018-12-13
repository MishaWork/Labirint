
#include "TXLib.h"

void Rocket ();
int Distance (int RX1, int RY1, int PX1, int PY1);


int main()
    {
    txCreateWindow (1680, 1050);

    Rocket ();

    return 0;
    }

void Rocket ()
    {
    HDC Rocket = txLoadImage ("Rocket.bmp");
    if (Rocket == NULL) txMessageBox ("Rocket.bmp isn't found");

    HDC Space = txLoadImage ("space.bmp");
    if (Space == NULL) txMessageBox ("space.bmp isn't found");

    HDC SpStation = txLoadImage ("spaceStation.bmp");
    if (SpStation == NULL) txMessageBox ("sapceStation.bmp isn't found");

    HDC TrollFace = txLoadImage ("trollface.bmp");
    if (TrollFace == NULL) txMessageBox ("trollface.bmp isn't found");

    HDC Troll = txLoadImage ("troll.bmp");
    if (Troll == NULL) txMessageBox ("troll.bmp isn't found");

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

    //Win32::AlphaBlend (txDC (), 12, 12, 12, 12, Rocket, 0, 0, 450, 450, blend);

    int RocketM = txGetExtentX (Rocket);

    int SpaceX = txGetExtentX (Space);

    int RocketX = 500;
    int RocketY = 500;

    int hDest = 50;
    int wDest = 50;

    int PlanetX = 1191;
    int PlanetY = 338;

    int Sizing = +2;

    int SourceX = 0;
    int SourceY = 0;

    int Level = 1;

    while (! GetAsyncKeyState ('L'))
        {

        int MouseX = txMouseX();
        int MouseY = txMouseY();

        txBitBlt (txDC (), 0, 0, SpaceX, 0, Space, 0, 0);

        //txAlphaBlend (txDC (), RocketX, RocketY, RocketM, 0, Rocket, 0, 0);

        BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

        //printf ("старый идиот %d\n", MouseY - RocketY);

        printf ("Mouse %d%d\n", txMouseX (), txMouseY ());

        if (MouseX - RocketX < 0)
            {
            SourceX = 900;
            }
        else SourceX = 0;

        if (MouseY - RocketY > 0 )
            {
            SourceX = 450;
            }
        else SourceX = 0;


        RocketX = MouseX;

        RocketY = MouseY;

        if (Distance (RocketX, RocketY, PlanetX, PlanetY) < 15)
            {
            Level = 2;
            }

        if (Level == 2)
            {
            txBitBlt (txDC (), 0, 0, 0, 0, SpStation);
            SourceX = 900;
            SourceY = 450;
            hDest = 450;
            wDest = 450;
            }

        Win32::AlphaBlend (txDC (), RocketX, RocketY, hDest, wDest, Rocket, SourceX, SourceY, 450, 450, blend);


        if (GetAsyncKeyState (VK_CONTROL))
            {
            hDest = hDest + Sizing;
            wDest = wDest + Sizing;
            }

        if (GetAsyncKeyState (VK_SHIFT))
            {
            hDest = hDest - Sizing;
            wDest = wDest - Sizing;
            }

        printf ("“упое яблоко %d %d \n", hDest, wDest);

        if (hDest > 200 && wDest > 200)
            {
            txAlphaBlend (txDC (), RocketX, RocketY, 0, 0, TrollFace, 0, 0);
            }


        if (GetAsyncKeyState ('M')) { wDest = 500,  hDest = 500; }

        txSleep (50);
        }
    }

int Distance (int RX1, int RY1, int PX1, int PY1)
    {
    return sqrt ((RX1 - PX1) * (RX1 - PX1) + (RY1 - PY1) * (RY1 - PY1));
    }



