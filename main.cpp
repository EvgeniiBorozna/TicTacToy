#include <iostream>
#include <chrono>
#include <windows.h>

uint8_t keypress = 255;
uint8_t X = 1, Y = 1;

void plateDraw (uint8_t* pfield);
void GetKeyPress();
void gotoxy(uint8_t x, uint8_t y);

int main()
{
    const uint32_t winnings[8] = {21, 1344, 86016, 66576, 16644, 4161, 65793, 4368};
    uint8_t field[91] = {201, 205, 205, 205, 209, 205, 205, 205, 209, 205, 205, 205, 187,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186 ,
        199, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 182,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186 ,
        199, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 182,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186,
        200, 205, 205, 205, 207, 205, 205, 205, 207, 205, 205, 205, 188 };
    plateDraw(field);
    gotoxy(6, 3);
m0: keypress = 255;
    GetKeyPress();
    if (keypress != 81) {
        Sleep(100);
        switch (keypress) {
        case 87:
            if (Y > 0) Y--;
            break;
        case 83:
            if (Y < 2) Y++;
            break;
        case 65:
            if (X > 0) X--;
            break;
        case 68:
            if (X < 2) X++;
            break;
        case 32:
            std::cout << 'X';
            field[((Y + 1 ) * 13 ) + (X + 1) * 3 ] = 'X';
            break;
        }
    }
    else goto m1;
    gotoxy(0, 0);
    plateDraw(field);
    gotoxy(X * 4 + 2, Y * 2 + 1 );
    goto m0;
m1: gotoxy(0, 12);
    return (0);
}

void plateDraw (uint8_t* pfield) {
    system("Color 1E");
    for (uint8_t i = 0; i < 7; i++)
    {
        for (uint8_t j = 0; j < 13; j++)
        {
            std::cout << pfield[i * 13 + j];
        }
        std::cout << std::endl;
    }
}

void GetKeyPress() {
    while (1)
    {
        uint8_t i = 32;
    for (i; i <= 122; i++)
    {
        uint8_t k = GetAsyncKeyState(i);
        if (k != 0) {
            keypress = i;
            break;
        }
    }
    if (keypress != 255) break;
    }
}

void gotoxy(uint8_t x, uint8_t y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
