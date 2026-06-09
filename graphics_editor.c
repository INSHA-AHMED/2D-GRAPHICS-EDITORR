#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 50
#define HEIGHT 20

char canvas[HEIGHT][WIDTH];

void clearCanvas()
{
    int i, j;
    for(i = 0; i < HEIGHT; i++)
        for(j = 0; j < WIDTH; j++)
            canvas[i][j] = '-';
}

void displayPicture()
{
    int i, j;
    printf("\n");
    for(i = 0; i < HEIGHT; i++)
    {
        for(j = 0; j < WIDTH; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

void plot(int x, int y)
{
    if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        canvas[y][x] = '*';
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        plot(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    drawLine(x, y, x + width, y);
    drawLine(x, y, x, y + height);
    drawLine(x + width, y, x + width, y + height);
    drawLine(x, y + height, x + width, y + height);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while(y >= x)
    {
        plot(xc + x, yc + y);
        plot(xc - x, yc + y);
        plot(xc + x, yc - y);
        plot(xc - x, yc - y);

        plot(xc + y, yc + x);
        plot(xc - y, yc + x);
        plot(xc + y, yc - x);
        plot(xc - y, yc - x);

        x++;

        if(d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
    }
}

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Triangle\n");
        printf("4. Draw Circle\n");
        printf("5. Clear Picture\n");
        printf("6. Display Picture\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            int x1, y1, x2, y2;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            drawLine(x1, y1, x2, y2);
        }
        else if(choice == 2)
        {
            int x, y, w, h;
            printf("Enter x y width height: ");
            scanf("%d%d%d%d", &x, &y, &w, &h);
            drawRectangle(x, y, w, h);
        }
        else if(choice == 3)
        {
            int x1, y1, x2, y2, x3, y3;
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &x1, &y1,
                  &x2, &y2,
                  &x3, &y3);

            drawTriangle(x1, y1, x2, y2, x3, y3);
        }
        else if(choice == 4)
        {
            int xc, yc, r;
            printf("Enter center x y and radius: ");
            scanf("%d%d%d", &xc, &yc, &r);
            drawCircle(xc, yc, r);
        }
        else if(choice == 5)
        {
            clearCanvas();
            printf("Picture Cleared.\n");
        }
        else if(choice == 6)
        {
            displayPicture();
        }
        else if(choice == 7)
        {
            printf("Exiting...\n");
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}