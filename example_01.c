#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT 10
#define FOV (M_PI/3)    // 60 grados

int map[HEIGHT][WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

float px = WIDTH/2, py = HEIGHT/2; // posicion del jugador
float ray_x = 0, ray_y = 0; // posicion del rayo
float pangle = 0.0, ray_angle = 0.0 ; // angulo del jugador y del rayo
int cellx = 0, celly = 0; // celda actual del rayo

int main() {
    while(1) {
        printf("\033[H\033[J"); // limpiar pantalla

        // crear mapa temporal
        char screen[HEIGHT][WIDTH];
        for(int i= 0; i < HEIGHT; i++)
            for(int j= 0; j < WIDTH; j++)
                screen[i][j] = (map[i][j]==1) ? '#' : ' ';

        // lanzar rayo
        ray_x = px;
        ray_y = py;
        ray_angle = pangle;

        while(1) {
            ray_x += cos(ray_angle);
            ray_y += sin(ray_angle);

            cellx = (int)ray_x;
            celly = (int)ray_y;
            
            if(cellx<0 || cellx>=WIDTH || celly<0 || celly>=HEIGHT)
                break;
            if(map[celly][cellx]==1)
                break;
            
            screen[celly][cellx] = '*'; // dibujar rayo
        }

        // colocar jugador
        screen[(int)py][(int)px] = 'P';

        // dibujar mapa
        for(int i=0;i<HEIGHT;i++) {
            for(int j=0;j<WIDTH;j++)
                printf("%c", screen[i][j]);
            printf("\n");
        }

        // girar jugador
        pangle += 0.1;
        if(pangle>2*M_PI) pangle -= 2*M_PI;

        usleep(200000); // pausa del bucle
    }
    return 0;
}