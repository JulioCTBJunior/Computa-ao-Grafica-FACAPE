#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Dimensões da janela
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Tamanho do labirinto
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

// Estruturas dos labirintos (1 = parede, 0 = caminho, 2 = estrela)
int maze1[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 2, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

int maze2[MAZE_HEIGHT][MAZE_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 2, 1},
    {1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

int* currentMaze = (int*)maze1;
int currentPhase = 1;

// Posição inicial e objetivo
int playerX = 1, playerY = 1;
int goalX = 8, goalY = 9;
int score = 0;
bool starsCollected[2][MAZE_HEIGHT * MAZE_WIDTH] = {0};

// Funções do OpenGL
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void init();
void drawMaze();
void drawPlayer();
void drawGoal();
void drawStars();
void checkGoal();
void checkStar();
void switchPhase();

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Labirinto com OpenGL");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MAZE_WIDTH, 0, MAZE_HEIGHT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMaze();
    drawPlayer();
    drawGoal();
    drawStars();
    checkGoal();
    checkStar();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, MAZE_WIDTH, 0, MAZE_HEIGHT);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
        case ' ': // Muda de fase
            switchPhase();
            break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (((int(*)[MAZE_WIDTH])currentMaze)[playerY][playerX - 1] != 1) playerX--;
            break;
        case GLUT_KEY_RIGHT:
            if (((int(*)[MAZE_WIDTH])currentMaze)[playerY][playerX + 1] != 1) playerX++;
            break;
        case GLUT_KEY_UP:
            if (((int(*)[MAZE_WIDTH])currentMaze)[playerY + 1][playerX] != 1) playerY++;
            break;
        case GLUT_KEY_DOWN:
            if (((int(*)[MAZE_WIDTH])currentMaze)[playerY - 1][playerX] != 1) playerY--;
            break;
    }
    glutPostRedisplay();
}

void drawMaze() {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (((int(*)[MAZE_WIDTH])currentMaze)[y][x] == 1) {
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + 1, y);
                glVertex2f(x + 1, y + 1);
                glVertex2f(x, y + 1);
                glEnd();
            }
        }
    }
}

void drawPlayer() {
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(playerX, playerY);
    glVertex2f(playerX + 1, playerY);
    glVertex2f(playerX + 1, playerY + 1);
    glVertex2f(playerX, playerY + 1);
    glEnd();
}

void drawGoal() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(goalX, goalY);
    glVertex2f(goalX + 1, goalY);
    glVertex2f(goalX + 1, goalY + 1);
    glVertex2f(goalX, goalY + 1);
    glEnd();
}

void drawStars() {
    glColor3f(1.0, 1.0, 0.0);
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            int index = y * MAZE_WIDTH + x;
            if (((int(*)[MAZE_WIDTH])currentMaze)[y][x] == 2 && !starsCollected[currentPhase - 1][index]) {
                glBegin(GL_TRIANGLES);
                glVertex2f(x + 0.5, y + 0.8);
                glVertex2f(x + 0.2, y + 0.2);
                glVertex2f(x + 0.8, y + 0.2);
                glEnd();
            }
        }
    }
}

void checkGoal() {
    if (playerX == goalX && playerY == goalY) {
        printf("Voce venceu a fase %d! Pontuacao: %d\n", currentPhase, score);
        switchPhase();
    }
}

void checkStar() {
    int index = playerY * MAZE_WIDTH + playerX;
    if (((int(*)[MAZE_WIDTH])currentMaze)[playerY][playerX] == 2 && !starsCollected[currentPhase - 1][index]) {
        starsCollected[currentPhase - 1][index] = true;
        score += 10;
        printf("Estrela coletada! Pontuacao: %d\n", score);
    }
}

void switchPhase() {
    if (currentPhase == 1) {
        currentMaze = (int*)maze2;
        playerX = 1;
        playerY = 1;
        goalX = 8;
        goalY = 9;
        currentPhase = 2;
    } else {
        printf("Voce completou o jogo! Pontuacao final: %d\n", score);
        exit(0);
    }
    glutPostRedisplay();
}

