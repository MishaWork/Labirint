#include "TXlib.h"

struct Object
    {
    int X;
    int Y;
    HDC Image;
    };

struct MainObject
    {
    int X;
    int Y;
    HDC Image;
    int StartX;
    int StartY;
    int CentX;
    int CentY;
    int Speed;
    };

void labirint ();
void Turtle (int Length, int Wight, HDC Lab);
int Distance (int X1, int Y1, int X2, int Y2);
void Movments ();
int DistanceEnemie (int TurtleX, int TurtleY, int EnemieX, int EnemieY);
void LifeCounting (int *Life, COLORREF Pixel, MainObject *Turtle, int MaxLife, HDC Message);
void Levels (MainObject *Turtle, int *Level, HDC Lab, HDC Labirint, int Distance1, int Length, int Wight);
void Controlling (MainObject *Turtle, int *xSource);


int main ()
    {
    //_txWindowStyle &= ~WS_CAPTION; // FullScreen: ���� ��� ���������, �������� � �����
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

    HDC Labirint = txLoadImage ("labirint2.bmp");
    if (Labirint == NULL) { txMessageBox ("labirint2.bmp isn't found"); return; }

    HDC Message = txLoadImage ("message box.bmp");
    if (Message == NULL) { txMessageBox ("message box.bmp isn't found"); return; }

    Object Coin = {580, 500, txLoadImage ("coin.bmp")};
    if (Coin.Image == NULL) { txMessageBox ("coin.bmp isn't found"); return; }

    Object CoinBad = {1640, 240, txLoadImage ("coinBad.bmp")};
    if (CoinBad.Image == NULL) { txMessageBox ("coinBad.bmp isn't found"); return; }

    MainObject Turtle = {150, 460, txLoadImage ("turtle.bmp"), 150, 460, txGetExtentX (Turtle.Image)/4/2, txGetExtentY (Turtle.Image)/2, 5};
    if (Turtle.Image == NULL) { txMessageBox ("turtle.bmp isn't found"); return; }

    const int MaxLife = 9;

    int CoinA = txGetExtentX (Coin.Image);

    int CoinAb = txGetExtentX (CoinBad.Image);

    int GameTime = GetTickCount ();

    int Level = 1;

    int Life = MaxLife;

    int xSource = 0;

    while (!GetAsyncKeyState ('P'))
        {

        double Time = (GetTickCount () - GameTime)/1000.0;

        int Distance1 = Distance (Turtle.X, Turtle.Y, 1750, 405);

        int Distance2 = Distance (Turtle.X, Turtle.Y, 200, 460);
        printf ("������ ����� %d\n", Distance2);

        int DistanceCoin = Distance (Turtle.X, Turtle.Y, Coin.X, Coin.Y);

        int DistanceCoinB = Distance (Turtle.X, Turtle.Y, CoinBad.X, CoinBad.Y);


        Levels (&Turtle, &Level, Lab, Labirint, Distance1, Length, Wight);

        //printf ("Distance1 %d\n", Distance1);

        //printf ("Distance2 %d\n", Distance2);

        //printf ("TurtleX %d\n", TurtleX);
        //printf ("TurtleY %d\n", TurtleY);

        //printf ("Pixel %d\n", Pixel);

        //if (Pixel == TX_BLACK) {TurtleX = 150, TurtleY = 460;}

        printf (" ������� �����%d\n", Life);

        COLORREF Pixel = txGetPixel (Turtle.X+Turtle.CentX, Turtle.Y+Turtle.CentY);

        //printf ("Pixel %d\n", Pixel);

        txAlphaBlend (txDC (), Coin.X, Coin.Y, CoinA, 0, Coin.Image);

        txAlphaBlend (txDC (), CoinBad.X, CoinBad.Y, CoinAb, 0, CoinBad.Image);

        txAlphaBlend (txDC (), Turtle.X, Turtle.Y, Turtle.CentX*2, 0, Turtle.Image, xSource);
        txSetFillColor (TX_PINK);
        txCircle (Turtle.X+Turtle.CentX, Turtle.Y+Turtle.CentY, 2);

        txSetFillColor (TX_BLACK);

        txSetColor (TX_RED);

        txRectangle (1800, 0, 1920, 80);

        char Str [30] = "";

        sprintf (Str, "%.1lf", Time);

        txSelectFont ("Bad Mofo", 100, 33, 100);

        txTextOut (1795, -15, Str);

        LifeCounting (&Life, Pixel, &Turtle, MaxLife, Message);
        //LifeCounting (int *Life, COLORREF Pixel, MainObject Turtle, int MaxLife, HDC Message);
        void LifeCounting (int *Life, COLORREF Pixel, MainObject *Turtle, int MaxLife, HDC Message);


        Controlling (&Turtle, &xSource);

        txSetColor (TX_PINK);




        if (Distance2 < 10)
            {
            Movments ();
            }

        if (DistanceCoin < 30)
            {
            Turtle.X = 1560;
            Turtle.Y = 400;
            }

        if (DistanceCoinB < 30)
            {
            Turtle.X = 200;
            Turtle.Y = 90;
            }

        if (Pixel == RGB (255, 0, 0))
            {
            Life = MaxLife;
            }

        txSleep (100);
        }

        txDeleteDC (Turtle.Image);
        txDeleteDC (Labirint);

    }

int Distance (int X1, int Y1, int X2, int Y2)
    {
    return sqrt ((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));

    }

void LifeCounting (int *Life, COLORREF Pixel, MainObject *Turtle, int MaxLife, HDC Message)
//LifeCounting (int *Life, COLORREF Pixel, MainObject *Turtle, int MaxLife, HDC Message);
    {
    if (Pixel == TX_BLACK)
        {
        *Life = *Life - 1;
        }

    if (*Life == 0)
        {
        Turtle->X = Turtle->StartX;
        Turtle->Y = Turtle->StartY;
        }

    if (Turtle->X == Turtle->StartX && Turtle->Y == Turtle->StartY)
        {
        *Life = MaxLife;
        }

    if (*Life == 1)
        {
        txAlphaBlend (txDC (), Turtle->X + 10, Turtle->Y - 40, 0, 0, Message);
        txSetColor (TX_YELLOW);
        txSelectFont ("Comic Sans MS", 13);
        txTextOut (Turtle->X + 13, Turtle->Y - 32, "�������� ���� �����");
        }

    }

void Levels (MainObject *Turtle, int *Level, HDC Lab, HDC Labirint, int Distance1, int Length, int Wight)
//void Levels (MainObject *Turtle, int *Level, HDC Lab, HDC Labirint, int Distance1, int Length, int Wight);

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
        Turtle->X = Turtle->StartX;
        Turtle->Y = Turtle->StartY+150;
        }
    }

void Controlling (MainObject *Turtle, int *xSource)
    {
    if (GetAsyncKeyState (VK_RIGHT)) {(*Turtle).X = (*Turtle).X + Turtle->Speed*2,   *xSource = 0;}
    if (GetAsyncKeyState (VK_LEFT))  {(*Turtle).X = (*Turtle).X - Turtle->Speed*2,   *xSource = Turtle->CentX*4;}
    if (GetAsyncKeyState (VK_UP))    {(*Turtle).Y = (*Turtle).Y - Turtle->Speed*2,   *xSource = Turtle->CentX*2;}
    if (GetAsyncKeyState (VK_DOWN))  {(*Turtle).Y = (*Turtle).Y + Turtle->Speed*2,   *xSource = Turtle->CentX*6;}
    }








void Movments ()
    {
    //HDC Turtle = txLoadImage ("1.bmp");
    //if (Turtle == NULL) { txMessageBox ("1.bmp isn't found"); return; }

    HDC Wall = txLoadImage ("wall.bmp");
    if (Wall == NULL) { txMessageBox ("wall.bmp ins't found"); return; }

    //HDC Enemie = txLoadImage ("Enemie.bmp");
    //if (Enemie == NULL) { txMessageBox ("Enemie.bmp isn't found"); return; }

    int Frames = 5;

    //int TurtleX = 170;
    //int TurtleY = 1000;

    Object Enemie = {1100, 1000, txLoadImage ("Enemie.bmp")};
    if (Enemie.Image == NULL) { txMessageBox ("Enemie.bmp isn't found"); return; }

    Object Turtle {170, 1000, txLoadImage ("1.bmp")};
    if (Turtle.Image == NULL) { txMessageBox ("1.bmp isn't found"); return; }



    //int EnemieX = 1100;
    //int EnemieY = 1000;

    int TurtlM = txGetExtentX (Turtle.Image) / Frames;
    int TurtlMY = txGetExtentY (Turtle.Image);
    int EnemiMX = txGetExtentX (Enemie.Image) / 7;
    int EnemiMY = txGetExtentY (Enemie.Image) / 2;



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

        txAlphaBlend (txDC (), Turtle.X-TurtlM/2, Turtle.Y-TurtlMY/2, TurtlM, 0, Turtle.Image, xSource);

        txAlphaBlend (txDC (), Enemie.X-EnemiMX/2, Enemie.Y-EnemiMY, EnemiMX, 0, Enemie.Image, 0);

       //txSetFillColor (TX_LIGHTRED);

        txCircle (Turtle.X, Turtle.Y, 12);
        txCircle (Enemie.X, Enemie.Y, 12);

        if (GetAsyncKeyState (VK_RIGHT))  Turtle.X = Turtle.X + 18, xSource = 0;
        if (GetAsyncKeyState (VK_LEFT))   Turtle.X = Turtle.X - 18, xSource = 1328;
        if (GetAsyncKeyState (VK_SPACE))  Turtle.Y = Turtle.Y - 68;
        if (GetAsyncKeyState ('1'))       xSource = 996;
        if (GetAsyncKeyState ('2'))       xSource = 0;

        if (GetAsyncKeyState ('W')) Enemie.Y = Enemie.Y - 68;
        if (GetAsyncKeyState ('D')) Enemie.X = Enemie.X + 18;
        if (GetAsyncKeyState ('A')) Enemie.X = Enemie.X - 18;

        Turtle.Y = Turtle.Y + 8;
        if (Turtle.Y >= 800) Turtle.Y = 800;
        if (Turtle.Y <= 10)  Turtle.Y = 800;

        int distance = Distance (Turtle.X, Enemie.X, Turtle.Y, Enemie.Y);

        //printf ("� ������� %d\n", distance);
        printf ("� ������� %d\n", Turtle.Y);

        txSetColor (TX_ORANGE);

        txRectangle (1500, 0, 1680, 100);

        char Str [30] = "";

        txSelectFont ("Bad Mofo", 100, 50, 200);

        itoa (Life, Str, 10);

        txTextOut (1580, 0, Str);

        Enemie.Y = Enemie.Y + 8;
        if (Enemie.Y >= 800) Enemie.Y = 800;
        if (Enemie.Y <= 10) Enemie.Y = 800;

        if (distance < 20)
            {
            Life = Life - 1;
            Turtle.X = 170;
            Turtle.Y = 700;
            Enemie.X = 1100;
            Enemie.Y = 600;
            }

        if (Life == 0)
            {

            break;
            }

        t++;

        txSleep (20);

        }

    txDeleteDC (Turtle.Image);
    txDeleteDC (Wall);
    txDeleteDC (Enemie.Image);
    }

int DistanceEnemie (int TurtleX, int TurtleY, int EnemieX, int EnemieY)
    {
    return sqrt ((TurtleX - EnemieX) * (TurtleX - EnemieX) + (TurtleY - EnemieY) * (TurtleY - EnemieY));
    }



