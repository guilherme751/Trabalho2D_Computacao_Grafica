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

#define INC_KEYIDLE 0.5
// Window dimensions
const GLint Width = 800;
const GLint Height = 800;
GLfloat visDim;
GLfloat jogadorX;
Jogo jogo;
bool isJumping;
GLfloat positionBeforeJump;

int keyStatus[256];

void keyPress(unsigned char key, int x, int y) {
    switch (key) { 
        case 'a':
        case 'A':
            keyStatus[(int)('a')] = 1; 
            break;
        case 'd':
        case 'D':
            keyStatus[(int)('d')] = 1; 
            break;
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void ResetKeyStatus() {
    int i;
    // Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            positionBeforeJump = jogo.getArena()->getJogador()->getY();
            isJumping = true;  
              
        } else if (state == GLUT_UP) {
            isJumping = false; // Right button released
        }
    }
}

void updatePlayer() {
    if (isJumping) {
        if (positionBeforeJump - jogo.getArena()->getJogador()->getY() < 3*jogo.getArena()->getJogador()->getSize()) {
            jogo.getArena()->getJogador()->MoveEmY(-INC_KEYIDLE);
        }        
    }
}



void timer(int value) {
    updatePlayer();     
    glutPostRedisplay(); 
    glutTimerFunc(16, timer, 0); 
}

void updateCameraView()
{
    glMatrixMode(GL_MODELVIEW); // Switch to the model-view matrix
    glLoadIdentity();          // Reset the matrix

    // Translate the world so the player is always centered
    glTranslatef(-jogadorX, 0, 0);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa a tela
    updateCameraView();
    // Chama o método para desenhar todos os elementos
    jogo.Desenha();

    glutSwapBuffers(); // Troca os buffers (Double buffering)
}



void init(void)
{
    
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    glClearColor(0.f, 0.f, 0.f, 0.f); // Black, no opacity(alpha).

    glMatrixMode(GL_PROJECTION);  // Select the projection matrix
    // glOrtho(jogadorX-visDim/2,  // X coordinate of left edge
    //         jogadorX+visDim/2,   // X coordinate of right edge
    //         -visDim, // Y coordinate of bottom edge
    //         0,  // Y coordinate of top edge
    //         -100,                 // Z coordinate of the “near” plane
    //         100);                 // Z coordinate of the “far” plane
            
    glOrtho(-500, 500, -500, 500, -100, 100);
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}


void idle(void)
{
    double inc = INC_KEYIDLE; 
    
    if (keyStatus[(int)('a')])
    {
        jogo.getArena()->getJogador()->MoveEmX(-inc);
        jogadorX = jogo.getArena()->getJogador()->getX() - jogo.getArena()->getX();
    }
    if (keyStatus[(int)('d')])
    {
        jogo.getArena()->getJogador()->MoveEmX(inc);
        jogadorX = jogo.getArena()->getJogador()->getX() - jogo.getArena()->getX();
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Trabalho 2D");
    // Inicializa o jogo
    jogo.CarregarArquivoSVG("arena_teste.svg");
    jogo.getArena()->AtualizaCoordenadas();
    visDim = jogo.getArenaHeight();
    jogadorX = jogo.getArena()->getJogador()->getX() - jogo.getArena()->getX();
    
    // Registra funções do GLUT
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup); 
    glutMouseFunc(mouseCallback);  
    // glutMotionFunc(motionCallback); 
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}