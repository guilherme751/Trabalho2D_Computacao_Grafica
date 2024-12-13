#include <stdio.h>
#include <math.h>
#include "tinyxml2.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include "jogo.h"
#include "arena.h"

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;
GLfloat visDim;
Jogo jogo;

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Limpa a tela

    // Chama o método para desenhar todos os elementos
    jogo.Desenha();

    glutSwapBuffers(); // Troca os buffers (Double buffering)
}


void init(void)
{
    // ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    glOrtho(-(visDim / 2),  // X coordinate of left edge
            (visDim / 2),   // X coordinate of right edge
            -(visDim / 2), // Y coordinate of bottom edge
            (visDim / 2),  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Trabalho 2D");
    // Inicializa o jogo
    jogo.CarregarArquivoSVG("arena_teste.svg");
    visDim = jogo.getArenaHeight();
    visDim = 600.0;
    // Registra funções do GLUT
    glutDisplayFunc(display); // Função de renderização
    // glutKeyboardFunc(teclado); // Entrada do teclado
    init();
    glutMainLoop();
    return 0;
}