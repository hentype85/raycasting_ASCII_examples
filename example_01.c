#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT 10
#define FOV (M_PI/3)            // 60 grados
#define NUM_RAYS (WIDTH * 2)    // cantidad de rayos

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
float pangle = 0.0; // angulo inicial
float ray_step = 0.1; // paso de cada rayo

int main() {
    while(1) {
        printf("\033[H\033[J"); // limpiar pantalla

        // crear mapa temporal para FOV
        char screen[HEIGHT][WIDTH];
        for(int i= 0; i < HEIGHT; i++)
            for(int j= 0; j < WIDTH; j++)
                screen[i][j] = (map[i][j]==1) ? '#' : ' ';

        // proyectar FOV
        for(int r= 0; r < NUM_RAYS; r++) {
            float ray_angle = pangle - FOV/2 + FOV * r / (NUM_RAYS-1);
            float rx = px, ry = py;

            while(1) {
                rx += cos(ray_angle) * ray_step;
                ry += sin(ray_angle) * ray_step;

                int mx = (int)rx;
                int my = (int)ry;

                if(mx<0 || mx>=WIDTH || my<0 || my>=HEIGHT)
                    break;

                if(map[my][mx]==1)
                    break;

                screen[my][mx] = '*'; // marcar el rayo
            }
        }

        // poner jugador
        screen[(int)py][(int)px] = 'P';

        // imprimir mapa
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