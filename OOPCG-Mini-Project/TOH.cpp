#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include<string>

using namespace std;

int m;
int chance = 0;
int col[10] = {BLUE, LIGHTBLUE, YELLOW, LIGHTGREEN, MAGENTA, LIGHTRED, GREEN, RED, LIGHTGRAY, CYAN};

struct peg 
{
    int a[10];
    int n;

    peg() 
    {
        n = 0;
    }
};

void draw() 
{
    char a[5];
    itoa(chance, a, 10);
    setcolor(BLACK);
    settextstyle(GOTHIC_FONT, 0, 3);
    
    std::string movesText = "MOVES";
    outtextxy(260, 20, (char *)movesText.c_str());
    
    outtextxy(360, 20, a);
    rectangle(3, 3, 613, 363);
    rectangle(5, 5, 611, 361);
    line(102, 50, 102, 350);
    line(112, 50, 112, 350);
    line(302, 50, 302, 350);
    line(312, 50, 312, 350);
    line(502, 50, 502, 350);
    line(512, 50, 512, 350);
    line(5, 350, 610, 350);
    line(5, 360, 610, 360);
    line(5, 350, 5, 360);
    line(610, 350, 610, 360);
    
    setfillstyle(1, BLACK);
    bar(102, 50, 112, 350);
    bar(302, 50, 312, 350);
    bar(502, 50, 512, 350);
    
    setcolor(BLACK);
    settextstyle(GOTHIC_FONT, 0, 3);
    
    std::string towerText = "TOWER OF HANOI";
    outtextxy(60, 370, (char *)towerText.c_str());
    
    settextstyle(GOTHIC_FONT, 0, 3);
    std::string syCompText = "SY-COMP (A)";
    outtextxy(170, 430, (char *)syCompText.c_str());
    
    settextstyle(DEFAULT_FONT, 0, 1);
}


void drawdisc(int a[10], int p, int n) 
{
    if (p == 1) p = 107;
    if (p == 2) p = 307;
    if (p == 3) p = 507;

    for (int i = 0; i < n; i++) 
    {
        line(p - (10 * a[i]), 350 - (i + 1) * 10, p + (10 * a[i]), 350 - (i + 1) * 10);
        line(p - (10 * a[i]), 350 - (i + 1) * 10, p - (10 * a[i]), 350 - i * 10);
        line(p + (10 * a[i]), 350 - (i + 1) * 10, p + (10 * a[i]), 350 - i * 10);
        setfillstyle(1, col[a[i] - 1]);
        bar(p - (10 * a[i]), 350 - (i + 1) * 10, p + (10 * a[i]), 350 - i * 10);
    }
}

peg p1, p2, p3;

void initialize(peg &k, peg &m, int n) 
{
    m.a[m.n] = n;
    m.n++;
    k.n--;
}

void change(int n, int a, int c) 
{
    cleardevice();
    if (a == 1 && c == 2) initialize(p1, p2, n);
    if (a == 1 && c == 3) initialize(p1, p3, n);
    if (a == 2 && c == 3) initialize(p2, p3, n);
    if (a == 2 && c == 1) initialize(p2, p1, n);
    if (a == 3 && c == 1) initialize(p3, p1, n);
    if (a == 3 && c == 2) initialize(p3, p2, n);
    chance++;
    draw();
    drawdisc(p1.a, 1, p1.n);
    drawdisc(p2.a, 2, p2.n);
    drawdisc(p3.a, 3, p3.n);
    delay(1100 - 100 * m);
}

void hanoi(int n, int a, int b, int c) 
{
    if (n == 0) return;
    hanoi(n - 1, a, c, b);
    change(n, a, c);
    hanoi(n - 1, b, a, c);
}

int main() 
{

    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, NULL);
    setbkcolor(LIGHTCYAN);

    cout << "HELLO!";
    cout << "\nTHIS IS A SHORT GAME NAMED 'THE TOWER OF HANOI'";
    cout << "\n\nABOUT THE GAME:";
    cout << "\nMOVE ALL THE DISKS FROM THE LEFTMOST ROD TO THE RIGHTMOST ROD.";
    cout << "\nONLY ONE DISK MAY BE MOVED AT A TIME AND";
    cout << "\nIT IS NOT POSSIBLE TO PLACE A BIGGER DISK ON TOP OF A ";
    cout << "\nSMALLER DISK.";
    cout << "\n\nTHE ORIGINAL LA TOUR D'HANOI PUZZLE WAS INVENTED BY ";
    cout << "\nFRANCOIS EDOUARD ANATOLE LUCAS IN 1883.";

    while (true) 
    {
        cout << "ENTER THE NUMBER OF DISCS YOU WANT TO SEE THE SOLUTION (1-10):" << endl;
        cin >> m;
        if (m < 1 || m > 10) 
        {
            cout << "FOR CONVENIENCE, ENTER A NUMBER BETWEEN 1 AND 10." << endl;
            continue;
        }

        cleardevice();
        p1.n = m;
        for (int i = m; i > 0; i--) 
        {
            p1.a[m - i] = i;
        }
        draw();
        drawdisc(p1.a, 1, p1.n);
        hanoi(m, 1, 2, 3);
        getch();
        break;
    }

    closegraph();
    return 0;
}