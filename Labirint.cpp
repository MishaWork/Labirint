#include "TXlib.h"

void labirint ();
void Turtle (int Length, int Wight, HDC Lab);
int Distance (int X1, int Y1, int X2, int Y2);
void Movments ();
int DistanceEnemie (int TurtleX, int TurtleY, int EnemieX, int EnemieY);
void LifeCounting (int *Life, COLORREF Pixel, int *TurtleX, int *TurtleY, int StartTurtleX, int StartTurtleY, int MaxLife, HDC Message, int *Show);
void Levels (int *Level, HDC Lab, HDC Labirint, int Distance1, int *TurtleX, int *TurtleY, int Length, int Wight, int StartTurtleX, int StartTurtleY);
void Controlling (int *TurtleX, int *TurtleY, int TurtleSpeed, int TurtleCentX, int *xSource);


int main ()
    {
    //_txWindowStyle &= ~WS_CAPTION; // FullScreen: окно без заголовка, размером с экран
    txCreateWindow (GetSystemMetrics (SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN));

    txUpdateWindow (false);

    labirint ();


    }

void labirint ()
    {


    HDC Lab = txLoadImage ("laberint.bmp");
    if (Lab == NULL) { txMessageBox ("laberint.bmp isn't found"); return; }

    int Length = GetSystemMetrics (SM_CXSCREEN);

    int Wight = txGetExtentX (Lab);

    Turtle (Length, Wight, Lab);

    txDeleteDC (Lab);

    }

void Turtle (int Length, int Wight, HDC Lab)
    {

    HDC Turtle = txLoadImage ("turtle.bmp");
    if (Turtle == NULL) { txMessageBox ("turtle.bmp isn't found"); return; }

    HDC Labirint = txLoadImage ("labirint2.bmp");
    if (Labirint == NULL) { txMessageBox ("labirint2.bmp isn't found"); return; }

    HDC Coin = txLoadImage ("coin.bmp");
    if (Coin == NULL) { txMessageBox ("coin.bmp isn't found"); return; }

    HDC CoinB = txLoadImage ("coinBad.bmp");
    if (CoinB == NULL) { txMessageBox ("coinBad.bmp isn't found"); return; }

    HDC Message = txLoadImage ("message box.bmp");
    if (Message == NULL) { txMessageBox ("message box.bmp isn't found"); return; }

    HDC Chest = txLoadImage ("chest.bmp");
    if (Chest == NULL) { txMessageBox ("chest.bmp isn't found"); return; }

    HDC Spikes = txLoadImage ("spikes.bmp");
    if (Spikes == NULL) { txMessageBox ("spikes.bmp isn't found"); return; }

    const int StartTurtleX = 150;
    const int StartTurtleY = 460;
    const int TurtleSpeed = 5;
    const int TurtleCentX = txGetExtentX (Turtle)/4/2;
    const int TurtleCentY = txGetExtentY (Turtle)/2;
    int TurtleX = StartTurtleX;
    int TurtleY = StartTurtleY;

    int ChestX = 1250;
    int ChestY = 50;

    int SpikeX = 670;
    int SpikeY = 420;

    int CoinX = 580;
    int CoinY = 500;

    int CoinXb = 1640;
    int CoinYb = 240;

    int SpikesOpened = 0;


    const int MaxLife = 9;

    int CoinA = txGetExtentX (Coin);

    int CoinAb = txGetExtentX (CoinB);

    int GameTime = GetTickCount ();

    int Level = 1;

    int Life = MaxLife;

    int xSource = 0;

    while (!GetAsyncKeyState ('P'))
        {

        double Time = (GetTickCount () - GameTime)/1000.0;

        int Distance1 = Distance (TurtleX, TurtleY, 1750, 405);

        int Distance2 = Distance (TurtleX, TurtleY, 200, 460);

        int DistanceCoin = Distance (TurtleX, TurtleY, CoinX, CoinY);

        int DistanceCoinBad = Distance (TurtleX, TurtleY, CoinXb, CoinYb);

        int DistanceSpikes = Distance (TurtleX, TurtleY, SpikeX, SpikeY);

        int DistanceChest = Distance (TurtleX, TurtleY, ChestX, ChestY);

        int Show = 0;


        Levels (&Level, Lab, Labirint, Distance1, &TurtleX, &TurtleY, Length, Wight, StartTurtleX, StartTurtleY);

        //printf ("Distance1 %d\n", Distance1);

        //printf ("Distance2 %d\n", Distance2);

        //printf ("TurtleX %d\n", TurtleX);
        //printf ("TurtleY %d\n", TurtleY);

        //printf ("Pixel %d\n", Pixel);

        //if (Pixel == TX_BLACK) {TurtleX = 150, TurtleY = 460;}

        printf (" потерял жизнь%d\n", Life);

        COLORREF Pixel = txGetPixel (TurtleX+TurtleCentX, TurtleY+TurtleCentY);

        //printf ("Pixel %d\n", Pixel);

        txAlphaBlend (txDC (), CoinX, CoinY, CoinA, 0, Coin);

        txAlphaBlend (txDC (), CoinXb, CoinYb, CoinAb, 0, CoinB);

        txAlphaBlend (txDC (), TurtleX, TurtleY, TurtleCentX*2, 0, Turtle, xSource);
        txSetFillColor (TX_PINK);
        txCircle (TurtleX+TurtleCentX, TurtleY+TurtleCentY, 2);

        txSetFillColor (TX_BLACK);

        txSetColor (TX_RED);

        txRectangle (1800, 0, 1920, 80);

        txAlphaBlend (txDC (), ChestX, ChestY, 0, 0, Chest);

        txAlphaBlend (txDC (), SpikeX, SpikeY, 0, 0, Spikes);

        char Str [30] = "";

        sprintf (Str, "%.1lf", Time);

        txSelectFont ("Bad Mofo", 100, 33, 100);

        txTextOut (1795, -15, Str);

        LifeCounting (&Life, Pixel, &TurtleX, &TurtleY, StartTurtleX, StartTurtleY, MaxLife, Message, &Show);

        Controlling (&TurtleX, &TurtleY, TurtleSpeed, TurtleCentX, &xSource);

        txSetColor (TX_PINK);




        if (Distance2 < 10)
            {
            Movments ();
            }

        if (DistanceCoin < 30)
            {
            TurtleX = 1560;
            TurtleY = 400;
            }

        if (DistanceCoinBad < 30)
            {
            TurtleX = 200;
            TurtleY = 90;
            }

        if (DistanceSpikes < 30 && SpikesOpened == 0)
            {
            Life = 0;
            }

        if (DistanceChest < 30)
            {
            SpikesOpened = 1;
            }

        if (Pixel == RGB (255, 0, 0)) Life = MaxLife;

        txSleep (100);
        }

    txDeleteDC (Turtle);
    txDeleteDC (Labirint);

    }

int Distance (int X1, int Y1, int X2, int Y2)
    {
    return sqrt ((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));

    }

void LifeCounting (int *Life, COLORREF Pixel, int *TurtleX, int *TurtleY, int StartTurtleX, int StartTurtleY, int MaxLife, HDC Message, int *Show)
    {
    if (Pixel == TX_BLACK)
        {
        *Life = 0;
        }

    if (*Life == 0)
        {
        *TurtleX = StartTurtleX;
        *TurtleY = StartTurtleY;
        }

    if (*TurtleX == StartTurtleX && *TurtleY == StartTurtleY)
        {
        *Life = MaxLife;
        }

    if (*Life == 1)
        {
        *Show = 1;
        }

    if (*Show == 1)
        {
        txAlphaBlend (txDC (), *TurtleX + 10, *TurtleY - 40, 0, 0, Message);
        txSetColor (TX_YELLOW);
        txSelectFont ("Comic Sans MS", 13);
        txTextOut (*TurtleX + 13, *TurtleY - 32, "ты скоро сдохнешь тупое ты создание ");
        }

    if (*Life == 9)
        {
        *Show = 0;
        }


    }

void Levels (int *Level, HDC Lab, HDC Labirint, int Distance1, int *TurtleX, int *TurtleY, int Length, int Wight, int StartTurtleX, int StartTurtleY)
    {
    if (*Level == 1)
        {
        txBitBlt (txDC (), (Length-Wight)/2, 0, 0, 0, Lab);
        }

    if (*Level == 2)
        {
        txBitBlt (txDC (), (Length-Wight)/2, 0, 0, 0, Labirint);
        }

    if (Distance1 < 10)
        {
        *Level = 2;
        *TurtleX = StartTurtleX;
        *TurtleY = StartTurtleY+150;
        }
    }

void Controlling (int *TurtleX, int *TurtleY, int TurtleSpeed, int TurtleCentX, int *xSource)
    {
    if (GetAsyncKeyState (VK_RIGHT)) {*TurtleX = *TurtleX + TurtleSpeed*2,   *xSource = 0;}
    if (GetAsyncKeyState (VK_LEFT))  {*TurtleX = *TurtleX - TurtleSpeed*2,   *xSource = TurtleCentX*4;}
    if (GetAsyncKeyState (VK_UP))    {*TurtleY = *TurtleY - TurtleSpeed*2,   *xSource = TurtleCentX*2;}
    if (GetAsyncKeyState (VK_DOWN))  {*TurtleY = *TurtleY + TurtleSpeed*2,   *xSource = TurtleCentX*6;}
    }








void Movments ()
    {
    HDC Turtle = txLoadImage ("1.bmp");
    if (Turtle == NULL) { txMessageBox ("1.bmp isn't found"); return; }

    HDC Wall = txLoadImage ("wall.bmp");
    if (Wall == NULL) { txMessageBox ("wall.bmp ins't found"); return; }

    HDC Enemie = txLoadImage ("Enemie.bmp");
    if (Enemie == NULL) { txMessageBox ("Enemie.bmp isn't found"); return; }

    int Frames = 5;

    int TurtleX = 170;
    int TurtleY = 1000;

    int EnemieX = 1100;
    int EnemieY = 1000;

    int TurtleM = txGetExtentX (Turtle) / Frames;
    int TurtleMY = txGetExtentY (Turtle);
    int EnemieMX = txGetExtentX (Enemie) / 7;
    int EnemieMY = txGetExtentY (Enemie) / 2;



    //int EnemieWight = txGEtExtentX (Enemie) / 2;

    int xSource = 0;

    int t = 0;

    int Life = 9;

    while (!GetAsyncKeyState ('C'))
        {
        txClear ();

        txSetFillColor (TX_BLACK);

        //txAlphaBlend (txDC (), 0, 0, SkateParkX, 0, SkatePark, t % Frames * SkateParkX);

        txBitBlt (txDC (), 0, 0, 0, 0, Wall, 0);

        txAlphaBlend (txDC (), TurtleX-TurtleM/2, TurtleY-TurtleMY/2, TurtleM, 0, Turtle, xSource);

        txAlphaBlend (txDC (), EnemieX-EnemieMX/2, EnemieY-EnemieMY, EnemieMX, 0, Enemie, 0);

       //txSetFillColor (TX_LIGHTRED);

        txCircle (TurtleX, TurtleY, 12);
        txCircle (EnemieX, EnemieY, 12);

        if (GetAsyncKeyState (VK_RIGHT))  TurtleX = TurtleX + 18, xSource = 0;
        if (GetAsyncKeyState (VK_LEFT))   TurtleX = TurtleX - 18, xSource = 1328;
        if (GetAsyncKeyState (VK_SPACE))  TurtleY = TurtleY - 68;
        if (GetAsyncKeyState ('1'))       xSource = 996;
        if (GetAsyncKeyState ('2'))       xSource = 0;

        if (GetAsyncKeyState ('W')) EnemieY = EnemieY - 68;
        if (GetAsyncKeyState ('D')) EnemieX = EnemieX + 18;
        if (GetAsyncKeyState ('A')) EnemieX = EnemieX - 18;

        TurtleY = TurtleY + 8;
        if (TurtleY >= 800) TurtleY = 800;
        if (TurtleY <= 10)  TurtleY = 800;

        int distance = DistanceEnemie (TurtleX, TurtleY, EnemieX, EnemieY);

        //printf ("я медведь %d\n", distance);
        printf ("я медведь %d\n", TurtleY);

        txSetColor (TX_ORANGE);

        txRectangle (1500, 0, 1680, 100);

        char Str [30] = "";

        txSelectFont ("Bad Mofo", 100, 50, 200);

        itoa (Life, Str, 10);

        txTextOut (1580, 0, Str);

        EnemieY = EnemieY + 8;
        if (EnemieY >= 800) EnemieY = 800;
        if (EnemieY <= 10) EnemieY = 800;

        if (distance < 20)
            {
            Life = Life - 1;
            TurtleX = 170;
            TurtleY = 700;
            EnemieX = 1100;
            EnemieY = 600;
            }

        if (Life == 0)
            {

            break;
            }

        t++;

        txSleep (20);

        }

    txDeleteDC (Turtle);
    txDeleteDC (Wall);
    txDeleteDC (Enemie);
    }

int DistanceEnemie (int TurtleX, int TurtleY, int EnemieX, int EnemieY)
    {
    return sqrt ((TurtleX - EnemieX) * (TurtleX - EnemieX) + (TurtleY - EnemieY) * (TurtleY - EnemieY));
    }



