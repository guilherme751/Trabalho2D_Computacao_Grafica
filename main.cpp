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
Jogador* jogador_principal;
bool isJumping;
GLfloat positionBeforeJump;
Tiro* tiro = NULL;
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

    GLfloat altura = jogador->getSize();
    GLfloat largura = jogador->getWidth();
    GLfloat X = jogador->getX() + incX;
    GLfloat Y = jogador->getY() + incY;
    for (Obstaculo* obstaculo : obstaculos) {
        GLfloat obstaculoX = obstaculo->x;
        GLfloat obstaculoY = obstaculo->y;
        GLfloat obstaculoLargura = obstaculo->getWidth();
        GLfloat obstaculoAltura = obstaculo->getHeight();

        if (X < obstaculoX + obstaculoLargura && 
            X + largura > obstaculoX &&  
            Y < obstaculoY + obstaculoAltura && 
            Y + altura > obstaculoY) {  
            return false; // Colisão detectada
        }
    }
    if (Y + altura -INC_KEYIDLE> jogo.getArena()->getHeight() || Y < 0) {
        return false;
    }
    if (jogador != jogador_principal) {
        Jogador* jogador_bom = jogador_principal;
        if (X < jogador_bom->getX() + largura && 
            X + largura > jogador_bom->getX() &&  
            Y < jogador_bom->getY() + altura && 
            Y + altura > jogador_bom->getY()) { 
            return false; // Colisão detectada
        }

    } else {
        for (Jogador* oponente : jogo.getArena()->getOpponents()) {
            if (X < oponente->getX() + largura && 
            X + largura > oponente->getX() && 
            Y < oponente->getY() + altura && 
            Y + altura > oponente->getY()) {  
               
            return false; // Colisão detectada
        }
        }
    }

    return true; 
}
bool wayup, falling = false;
float inc = INC_KEYIDLE;


void mouseCallback(int button, int state, int x, int y) {
    
        if (button == GLUT_RIGHT_BUTTON) {
            if (!isJumping && !falling) {
                if (state == GLUT_DOWN) {
                    positionBeforeJump = jogador_principal->getY();
                    
                    wayup = true;
                    isJumping = true;
                    
                    
                } 
            } else if (state == GLUT_UP) {
                wayup = false;
                inc = INC_KEYIDLE;
            }
        } else if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN)
                jogador_principal->addTiro(jogador_principal->Atira());
        }

        glutPostRedisplay();
    
}
void updatePlayer() {
    if (isJumping) {
        if (wayup) {
            if (positionBeforeJump - jogador_principal->getY() < 3*jogador_principal->getSize()) {
                if (checkCollision(jogador_principal, 0, -inc)) {
                    jogador_principal->MoveEmY(-inc);
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
            if (checkCollision(jogador_principal, 0, INC_KEYIDLE)) {
                jogador_principal->MoveEmY(INC_KEYIDLE);
            }
            else {
                isJumping = false;
            }
        }      
    } else {
        if (checkCollision(jogador_principal, 0, INC_KEYIDLE)) {
            falling = true;
            jogador_principal->MoveEmY(INC_KEYIDLE);
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
        opponent->MoveEmX(opponent->dir * INC_KEYIDLE*0.4);

        
    }
    
}
int ultimaPosMouseY = 0; 
void movimentarBracoMouse(int x, int y) {
    y = Height - y; 
    Jogador* jogador = jogador_principal;
    GLfloat anguloBraco = jogador->getAngle();
    if (y < ultimaPosMouseY) {
        if (anguloBraco + 2.0 < -40) {          
            anguloBraco = jogador->updateAngle(0.5);
        }
    } else if (y > ultimaPosMouseY) {

        if (anguloBraco - 2.0 >= -130) {          
            anguloBraco = jogador->updateAngle(-0.5);
        }
    }

    ultimaPosMouseY = y;

    glutPostRedisplay();
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
    if (jogador_principal->temTiro()) {
        
    }
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
    GLfloat size = jogador_principal->getWidth();
    if (keyStatus[(int)('a')])
    {
        if (jogadorX -size*0.15 > inc && checkCollision(jogador_principal, -inc, 0)) {
            
            jogadorX = jogador_principal->MoveEmX(-inc);
        }
    }
    if (keyStatus[(int)('d')])
    {
        if (jogadorX - size*0.15 > jogo.getArena()->getWidth()) {
            
            printf("GANHOU!!\n");
        }
        if (checkCollision(jogador_principal, inc, 0)) {
            jogadorX = jogador_principal->MoveEmX(inc);
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
    jogador_principal = jogo.getArena()->getJogador();
    jogadorX = jogador_principal->getX();
    
    // Registra funções do GLUT
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutKeyboardUpFunc(keyup); 
    glutMouseFunc(mouseCallback);  
    glutPassiveMotionFunc(movimentarBracoMouse);
   
    glutMotionFunc(movimentarBracoMouse); 
    // glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}