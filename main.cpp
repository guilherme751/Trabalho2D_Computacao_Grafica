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

bool checkCollision(Jogador* jogador, float incX, float incY) {
    std::vector<Obstaculo*> obstaculos = jogo.getArena()->getObstaculos();
    GLfloat dimCirculo = jogo.getArena()->getJogador()->getWidth()/0.3;

    GLfloat jogadorAltura = jogador->getSize();
    GLfloat jogadorLargura = jogador->getWidth();
    GLfloat jogadorX = jogador->getX() - dimCirculo*0.15 + incX;
    GLfloat jogadorY = jogador->getY() + dimCirculo/2 - jogadorAltura + incY;
    for (Obstaculo* obstaculo : obstaculos) {
        GLfloat obstaculoX = obstaculo->x;
        GLfloat obstaculoY = obstaculo->y;
        GLfloat obstaculoLargura = obstaculo->getWidth();
        GLfloat obstaculoAltura = obstaculo->getHeight();

        if (jogadorX < obstaculoX + obstaculoLargura && // lado direito do jogador não ultrapassa o lado esquerdo do obstáculo
            jogadorX + jogadorLargura > obstaculoX &&  // lado esquerdo do jogador não ultrapassa o lado direito do obstáculo
            jogadorY < obstaculoY + obstaculoAltura && // lado superior do jogador não ultrapassa o lado inferior do obstáculo
            jogadorY + jogadorAltura > obstaculoY) {  // lado inferior do jogador não ultrapassa o lado superior do obstáculo
            return false; // Colisão detectada
        }
    }
    // printf("%f, %f, %f, %f\n", jogadorX ,jogadorY, jogadorAltura,jogo.getArena()->getHeight() );
    if (jogadorY + jogadorAltura -INC_KEYIDLE> jogo.getArena()->getHeight() || jogadorY < 0) {
        return false;
    }

    return true; 
}
bool wayup, falling = false;
float inc = INC_KEYIDLE;

void mouseCallback(int button, int state, int x, int y) {
    
        if (button == GLUT_RIGHT_BUTTON) {
            if (!isJumping && !falling) {
                if (state == GLUT_DOWN) {
                    positionBeforeJump = jogo.getArena()->getJogador()->getY();
                    
                    wayup = true;
                    isJumping = true;
                    
                    
                } 
            } else if (state == GLUT_UP) {
                wayup = false;
                inc = INC_KEYIDLE;
            }
        }
    
}
void updatePlayer() {
    if (isJumping) {
        if (wayup) {
            if (positionBeforeJump - jogo.getArena()->getJogador()->getY() < 3*jogo.getArena()->getJogador()->getSize()) {
                if (checkCollision(jogo.getArena()->getJogador(), 0, -inc)) {
                    jogo.getArena()->getJogador()->MoveEmY(-inc);
                    // inc = inc - 0.003;
                } 
                else {
                    wayup = false;
                    inc = INC_KEYIDLE;
                }
            } 
            else {
                wayup = false;
                inc = INC_KEYIDLE;
            }
        } 
        else {
            if (checkCollision(jogo.getArena()->getJogador(), 0, INC_KEYIDLE)) {
                jogo.getArena()->getJogador()->MoveEmY(INC_KEYIDLE);
            }
            else {
                isJumping = false;
            }
        }      
    } else {
        if (checkCollision(jogo.getArena()->getJogador(), 0, INC_KEYIDLE)) {
            falling = true;
            jogo.getArena()->getJogador()->MoveEmY(INC_KEYIDLE);
        } else {
            falling = false;
        }
    }
    
}

void updateOpponents() {
    std::vector<Jogador*> oponentes = jogo.getArena()->getOpponents();
    for (Jogador* opponent : oponentes) {        

        if (!checkCollision(opponent, opponent->dir*INC_KEYIDLE, 0)){
            opponent->dir *= -1;
        }

        if (checkCollision(opponent, 0, 2*INC_KEYIDLE)) {
            opponent->dir *= -1;
        }
        opponent->MoveEmX(opponent->dir * INC_KEYIDLE);

        
    }
    // static int dir = 1;
    // Jogador* op1 = oponentes[1];
    // if (!checkCollision(op1, dir*INC_KEYIDLE, 0)) {
    //     dir *= -1;
    // }
    // op1->MoveEmX(dir * INC_KEYIDLE);
}


void timer(int value) {
    updatePlayer();     
    // updateOpponents();
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
    glOrtho(jogadorX-visDim/2,  // X coordinate of left edge
            jogadorX+visDim/2,   // X coordinate of right edge
            -visDim, // Y coordinate of bottom edge
            0,  // Y coordinate of top edge
            -100,                 // Z coordinate of the “near” plane
            100);                 // Z coordinate of the “far” plane
            
    // glOrtho(-500, 500, -500, 500, -100, 100);
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}


void idle(void)
{
    double inc = INC_KEYIDLE; 
    GLfloat size = jogo.getArena()->getJogador()->getWidth();
    if (keyStatus[(int)('a')])
    {
        if (jogadorX -size*0.15 > inc && checkCollision(jogo.getArena()->getJogador(), -inc, 0)) {
            
            jogadorX = jogo.getArena()->getJogador()->MoveEmX(-inc);
        }
    }
    if (keyStatus[(int)('d')])
    {
        if (jogadorX - size*0.15 > jogo.getArena()->getWidth()) {
            
            printf("GANHOU!!\n");
        }
        if (checkCollision(jogo.getArena()->getJogador(), inc, 0)) {
            jogadorX = jogo.getArena()->getJogador()->MoveEmX(inc);
        }
    }
    updatePlayer();
    updateOpponents();     

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
    jogadorX = jogo.getArena()->getJogador()->getX();
    
    // Registra funções do GLUT
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup); 
    glutMouseFunc(mouseCallback);  
    // glutMotionFunc(motionCallback); 
    // glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}