#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT 10


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
float dir_x = 0, dir_y = 0, dir_spd = 0.006; // direccion del rayo y velocidad

int main() {
    while (1) {
        printf("\033[H\033[J"); // limpiar pantalla

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if ((int)px == i && (int)py == j) {

                    dir_x = cos(pangle) * dir_spd;
                    dir_y = sin(pangle) * dir_spd;

                    if (fabs(dir_x) > fabs(dir_y)) {
                        if (dir_x > 0)
                            printf(">");
                        else
                            printf("<");
                    } else {
                        if (dir_y > 0)
                            printf("v");
                        else
                            printf("^");
                    }

                } else if (map[j][i] == 1) {
                    printf("#");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // girar jugador
        pangle += 0.3;
        if (pangle > 2*M_PI) pangle -= 2*M_PI;

        usleep(200000); // pausa del bucle
    }
    return 0;
}
