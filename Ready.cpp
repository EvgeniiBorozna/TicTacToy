/* Moving: w, a, s, d
   spacebar: your step
   q - exit game anytime */

#include <iostream>
#include <windows.h>

uint8_t keypress = 255;
uint8_t X = 1, Y = 1;
const uint8_t WinCases = 8, fieldSize = 3;

void GameInit();
void plateDraw(uint8_t* pfield);
void GetKeyPress();
void gotoxy(uint8_t x, uint8_t y);

int main()
{
    bool Shape;
    uint16_t gameX = 0, gameO = 0;
    const uint16_t winnings[WinCases] = { 7, 56, 448, 73, 146, 292, 84, 273 }; // bit-mask for win cases 
    uint8_t steps = 0, field[91] = {
        201, 205, 205, 205, 209, 205, 205, 205, 209, 205, 205, 205, 187,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186 ,
        199, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 182,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186 ,
        199, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 182,
        186, 32, 32, 32, 179, 32, 32, 32, 179, 32, 32, 32, 186,
        200, 205, 205, 205, 207, 205, 205, 205, 207, 205, 205, 205, 188 };
    srand(time(0));
    Shape = rand() % 2;
    GameInit();
    gotoxy(0, 0);
    plateDraw(field);
    gotoxy(6, 3);
m0: keypress = 255;
    if (Shape) {
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
                if (field[4 * fieldSize + 3 + Y * 26 + 4 * X] == 32) {
                    field[4 * fieldSize + 3 + Y * 26 + 4 * X] = 'X';
                    uint8_t step = Y * 3 + X;
                    gameX |= (1 << step);
                    Shape = !Shape;
                    steps++;
                }
                break;
            }
        }
        else return (0);
    }
    else {
        for (size_t Ys = 0; Ys < fieldSize; Ys++) {
            for (size_t Xs = 0; Xs < fieldSize; Xs++) {
                if (field[4 * fieldSize + 3 + Ys * 26 + 4 * Xs] == 32) {
                    uint8_t Xc = 0, Yc = 0;// AI
                    for (size_t i = 0; i < fieldSize; i++)
                    {
                        if (field[4 * fieldSize + 3 + Ys * 26 + 4 * i] == 'X') Xc++;
                    }
                    for (size_t i = 0; i < fieldSize; i++)
                    {
                        if (field[4 * fieldSize + 3 + i * 26 + 4 * Xs] == 'X') Yc++;
                    }
                    if (Xc == fieldSize - 1 || Yc == fieldSize - 1) {
                        field[4 * fieldSize + 3 + Ys * 26 + 4 * Xs] = 'O';
                        uint8_t step = Ys * 3 + Xs;
                        gameO |= (1 << step);
                        Shape = !Shape;
                        steps++;
                        goto m2;
                    }
                }
            }
            }
    m1: X = rand() % 3; // random step
        Y = rand() % 3;
        if (field[4 * fieldSize + 3 + Y * 26 + 4 * X] == 32) {
            field[4 * fieldSize + 3 + Y * 26 + 4 * X] = 'O';
            uint8_t step = Y * 3 + X;
            gameO |= (1 << step);
            Shape = !Shape; 
            steps++;
        }

        m2:;
    }
    gotoxy(0, 0);
    plateDraw(field);
    for (uint8_t i = 0; i < WinCases; i++) {
        if (!(gameX & winnings[i] ^ winnings[i])) {
            std::cout << "!!! Human win !!!\n";
            return 0;
        }
        if (!(gameO & winnings[i] ^ winnings[i])) {
            std::cout << "!!! Computer win !!!\n";
            return 0;
        }
    }
    if (steps == 9) {
        std::cout << "!!! DRAW !!!";
        return 0;
    }
    gotoxy(X * 4 + 2, Y * 2 + 1);
    goto m0;
}

void plateDraw(uint8_t* pfield) {
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

void GameInit() {
    float B = 493.88, D = 587.32, A = 440.00, G = 392.00;
    std::cout << "\nHello, human!";
    Beep(B, 300);
    Beep(D, 300);
    Beep(B, 300);
    Beep(D, 600);
    Beep(B, 300);
    Beep(A, 300);
    Beep(B, 600);
    Beep(A, 300);
    Beep(G, 300);
    Beep(A, 600);
    Beep(G, 600);
}
