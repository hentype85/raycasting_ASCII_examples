#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIDTH  10               // ancho del mapa
#define HEIGHT 10               // alto del mapa
#define FOV (M_PI/ 3)           // campo de vision (60 grados)
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


float px = WIDTH/2.0, py = HEIGHT/2.0; // posicion del jugador
float ray_x = 0, ray_y = 0; // posicion del rayo
float p_angle = 0.0, ray_angle = 0.0 ; // angulo del jugador y del rayo
int cellx = 0, celly = 0; // celda actual del rayo
char screen[HEIGHT][WIDTH]; // pantalla (viewport) del tamano del mapa

int main() {
    while(1) {
        printf("\033[H\033[J"); // limpiar pantalla

        // dibujar mapa base
        for(int i= 0; i < HEIGHT; i++) 
            for(int j= 0; j < WIDTH; j++)
                screen[i][j] = (map[i][j]==1) ? '#' : ' ';

        // lanzar varios rayos para FOV
        for(int r= 0; r < NUM_RAYS; r++) {

            ray_angle = p_angle - FOV/2 + FOV * r / (NUM_RAYS-1); // calcular angulo del rayo

            ray_x = px, ray_y = py; // iniciar el rayo en la posicion del jugador

            while(1) {
                ray_x += cos(ray_angle); // mover el rayo en eje x
                ray_y += sin(ray_angle); // mover el rayo en eje y

                cellx = (int)ray_x; // convertir a coordenadas de celda
                celly = (int)ray_y; // convertir a coordenadas de celda

                if(cellx<0 || cellx>=WIDTH || celly<0 || celly>=HEIGHT)
                    break; // fuera de los limites del mapa

                if(map[celly][cellx]==1)
                    break; // colision con pared

                screen[celly][cellx] = '*'; // dibujar el rayo
            }
        }

        // dibujar jugador
        screen[(int)py][(int)px] = 'P';

        // dibujar mapa
        for(int i=0;i<HEIGHT;i++) {
            for(int j=0;j<WIDTH;j++)
                printf("%c", screen[i][j]);
            printf("\n");
        }

        // girar jugador
        p_angle += 0.1;
        if(p_angle>2*M_PI){
            p_angle -= 2*M_PI;
        }

        usleep(200000); // pausa del bucle
    }
    return 0;
}
