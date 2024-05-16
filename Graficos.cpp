#include <GL/glut.h>
#include <math.h>
#include <cstdlib> 

// Função para desenhar a Astróide
void Astroide() {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 2 * M_PI; t += 0.01) {
        float x = pow(cos(t), 3);
        float y = pow(sin(t), 3);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Cardióide
void Cardioide() {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 2 * M_PI; t += 0.01) {
        float x = 2 * cos(t) * (1 - cos(t));
        float y = 2 * sin(t) * (1 - cos(t));
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Ciclóide
void Cicloide() {
    glBegin(GL_LINE_STRIP);
    for (float t = -10; t <= 10; t += 0.01) {
        float x = t - sin(t);
        float y = 1 - cos(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Circunferência
void Circunferencia() {
    glBegin(GL_LINE_LOOP);
    for (float t = 0; t <= 2 * M_PI; t += 0.01) {
        float x = cos(t);
        float y = sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar o Cosseno
void Cosseno() {
    glBegin(GL_LINE_STRIP);
    for (float x = -10; x <= 10; x += 0.1) {
        float y = cos(x);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Elipse
void Elipse() {
    glBegin(GL_LINE_LOOP);
    float a = 5.0, b = 3.0;
    for (float t = 0; t <= 2 * M_PI; t += 0.01) {
        float x = a * cos(t);
        float y = b * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Espiral
void Espiral() {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 6 * M_PI; t += 0.01) {
        float x = t * cos(t);
        float y = t * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Hipérbole
void Hiperbole() {
    glBegin(GL_LINE_STRIP);
    for (float x = -10; x <= 10; x += 0.1) {
        float y = 1 / x;
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Parábola
void Parabola() {
    glBegin(GL_LINE_STRIP);
    for (float x = -10; x <= 10; x += 0.1) {
        float y = x * x;
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Rosácea
void Rosacea() {
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t <= 2 * M_PI; t += 0.01) {
        float k = 5;
        float x = cos(k * t) * cos(t);
        float y = cos(k * t) * sin(t);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar o Seno
void Seno() {
    glBegin(GL_LINE_STRIP);
    for (float x = -10; x <= 10; x += 0.1) {
        float y = sin(x);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para desenhar a Tangente
void Tangente() {
    glBegin(GL_LINE_STRIP);
    for (float x = -M_PI / 2 + 0.01; x < M_PI / 2 - 0.01; x += 0.01) {
        float y = tan(x);
        glVertex2f(x, y);
    }
    glEnd();
}
enum FunctionType {
    ASTROIDE,
    CARDIOIDE,
    CICLOIDE,
    CIRCUNFERENCIA,
    COSENO,
    ELIPSE,
    ESPIRAL,
    HIPERBOLE,
    PARABOLA,
    ROSACEA,
    SENO,
    TANGENTE
};
// Variável global para armazenar a função selecionada pelo usuário
FunctionType selectedFunction = ASTROIDE;
// Função para desenhar a função selecionada
void drawSelectedFunction() {
    switch (selectedFunction) {
        case ASTROIDE:
            Astroide();
            break;
        case CARDIOIDE:
            Cardioide();
            break;
        case CICLOIDE:
            Cicloide();
            break;
        case CIRCUNFERENCIA:
            Circunferencia();
            break;
        case COSENO:
            Cosseno();
            break;
        case ELIPSE:
            Elipse();
            break;
        case ESPIRAL:
            Espiral();
            break;
        case HIPERBOLE:
            Hiperbole();
            break;
        case PARABOLA:
            Parabola();
            break;
        case ROSACEA:
            Rosacea();
            break;
        case SENO:
            Seno();
            break;
        case TANGENTE:
            Tangente();
            break;
        default:
            break;
    }
}
// Função de renderização
// Função de desenho
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Cor branca

    drawSelectedFunction();

    glFlush();
}
// Função de menu para tratar a seleção do usuário
void menu(int value) {
    switch (value) {
        case ASTROIDE:
        case CARDIOIDE:
        case CICLOIDE:
        case CIRCUNFERENCIA:
        case COSENO:
        case ELIPSE:
        case ESPIRAL:
        case HIPERBOLE:
        case PARABOLA:
        case ROSACEA:
        case SENO:
        case TANGENTE:
            selectedFunction = static_cast<FunctionType>(value);
            glutPostRedisplay();
            break;
        case 99: // Código para sair do programa quando a opção "Exit" for selecionada
            exit(0);
            break;
        default:
            break;
    }
}
// Função para lidar com eventos de teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Tecla ESC para sair do programa
            exit(0);
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Funções Paramétricas");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    // Criando um menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Astroide", ASTROIDE);
    glutAddMenuEntry("Cardioide", CARDIOIDE);
    glutAddMenuEntry("Cicloide", CICLOIDE);
    glutAddMenuEntry("Circunferencia", CIRCUNFERENCIA);
    glutAddMenuEntry("Cosseno", COSENO);
    glutAddMenuEntry("Elipse", ELIPSE);
    glutAddMenuEntry("Espiral", ESPIRAL);
    glutAddMenuEntry("Hiperbole", HIPERBOLE);
    glutAddMenuEntry("Parabola", PARABOLA);
    glutAddMenuEntry("Rosacea", ROSACEA);
    glutAddMenuEntry("Seno", SENO);
    glutAddMenuEntry("Tangente", TANGENTE);
    glutAddMenuEntry("Exit", 99);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}
