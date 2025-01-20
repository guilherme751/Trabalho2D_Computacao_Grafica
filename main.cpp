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
#include <random>


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
        case 'r':
        case 'R':
            keyStatus[(int)('r')] = 1; 
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

bool checkCollisionObstaculoTiro(Tiro* tiro, Obstaculo* obstaculo) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = obstaculo->x, ry = obstaculo->y, radius = tiro->radius;

    if (cx + radius > rx && cx - radius < rx + obstaculo->getWidth() &&
        cy + radius > ry && cy - radius < ry + obstaculo->getHeight()) {
            return true;
        }
    
    return false;
}
bool checkCollisionJogadorTiro(Tiro* tiro) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = jogador_principal->getX(), ry = jogador_principal->getY(), radius = tiro->radius;

    if (cx + radius > rx && cx - radius < rx + jogador_principal->getWidth() &&
        cy + radius > ry && cy - radius < ry + jogador_principal->getSize()) {
            return true;
        }
    
    return false;
}
bool checkCollisionOponenteTiro(Tiro* tiro, Jogador* oponente) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = oponente->getX(), ry = oponente->getY(), radius = tiro->radius;
    if (oponente->morreu)   return false;
    if (cx + radius > rx && cx - radius < rx + oponente->getWidth() &&
        cy + radius > ry && cy - radius < ry + oponente->getSize()) {
            return true;
    }
    
    return false;
}
bool tiroValido(Tiro* tiro, Jogador* j)
{
    if (!tiro)  return false;
    if (tiro->getY() > jogo.getArenaHeight() || tiro->getY() < 0 || 
        tiro->getX() > jogo.getArenaWidth() || tiro->getX() < 0) {
        return false;
    }

    for (Obstaculo* obstaculo : jogo.getArena()->getObstaculos()) {
        if (checkCollisionObstaculoTiro(tiro, obstaculo)) {
            return false;
        }
    }

    if (j == jogador_principal) {
        for (Jogador* oponente : jogo.getArena()->getOpponents()) {
            if (checkCollisionOponenteTiro(tiro, oponente)) {
                oponente->morreu = true;
                return false;
            }
        }
    } else {
        if (checkCollisionJogadorTiro(tiro)) {
            jogador_principal->morreu = true;
            return false;
        }
    }
    

    return true;
}

void verificaTirosValidos(Jogador* j) {
    std::list<Tiro*>& tiros = j->getTiros();
    // printf("%ld\n", tiros.size()); 
    for (auto it = tiros.begin(); it != tiros.end(); ) {
        if (!tiroValido(*it, j)) { 
            delete *it;         
            it = tiros.erase(it); 
        } else {
            ++it; 
        }
    }
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
        if (X > jogo.getArenaWidth() || X < 0) {
            return false;
        }

    } else {
        for (Jogador* oponente : jogo.getArena()->getOpponents()) {
            if (!oponente->morreu) {
                if (X < oponente->getX() + largura && 
                    X + largura > oponente->getX() && 
                    Y < oponente->getY() + altura && 
                    Y + altura > oponente->getY()) {  
                
                    return false; // Colisão detectada
                }
            }
        }
        if (X + jogador_principal->getWidth() > jogo.getArenaWidth() || X < 0) {
            return false;
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
                jogador_principal->addTiro(jogador_principal->Atira(JOGADOR));
        }

        glutPostRedisplay();
    
}
void updatePlayer(GLdouble timeDiference) {
    if (isJumping) {
        if (wayup) {
            if (positionBeforeJump - jogador_principal->getY() < 3*jogador_principal->getSize()) {
                if (checkCollision(jogador_principal, 0, -inc)) {
            
                    jogador_principal->MoveEmY(-inc, timeDiference);
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
                jogador_principal->MoveEmY(INC_KEYIDLE, timeDiference);
            }
            else {
                isJumping = false;
            }
        }      
    } else {
        if (checkCollision(jogador_principal, 0, INC_KEYIDLE)) {
            falling = true;
            jogador_principal->MoveEmY(INC_KEYIDLE, timeDiference);
        } else {
            falling = false;
        }
    }
    
}

void updateOpponents(GLdouble timeDiference) {
    
    std::vector<Jogador*> oponentes = jogo.getArena()->getOpponents();
    for (Jogador* opponent : oponentes) {        
        if (!opponent->morreu) {
            if (!checkCollision(opponent, opponent->dir*timeDiference*opponent->vel, 0)){
                opponent->dir *= -1;
            }

            if (checkCollision(opponent, 0, 2*INC_KEYIDLE)) {
                opponent->dir *= -1;
            }
            
            opponent->MoveEmX(opponent->dir, timeDiference*0.3, isJumping || falling);
           
        }
        
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

void renderText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(font, text[i]);
    }
}
void reiniciarJogo() {
    for (Jogador* oponente : jogo.getArena()->getOpponents()) {
        oponente->reiniciaPosicao();
    }
    jogador_principal->reiniciaPosicao();
    jogadorX = jogador_principal->getX();

}
void gameOver(bool vitoria) {
    if (vitoria) {
        glColor3f(0.0f, 1.0f, 0.0f); 
        renderText(jogador_principal->getX(), - jogo.getArenaHeight()/2, "VICTORY!", GLUT_BITMAP_HELVETICA_18);
        renderText(jogador_principal->getX(), - jogo.getArenaHeight()/2 - 2.5, "Press R to Restart", GLUT_BITMAP_HELVETICA_18);
    } else {
        glColor3f(1.0f, 0.0f, 0.0f); 
        renderText(jogador_principal->getX(), - jogo.getArenaHeight()/2, "GAME OVER!", GLUT_BITMAP_HELVETICA_18);
        renderText(jogador_principal->getX(), - jogo.getArenaHeight()/2 - 2.5, "Press R to Try Again", GLUT_BITMAP_HELVETICA_18);

    }

        
    if (jogo.reiniciar) {
        reiniciarJogo();
        jogo.gameOver = false;
        jogo.vitoria = false;
        jogo.reiniciar = false;
        jogo.teste = true;
        glutPostRedisplay();
    }   

}

void pontuacao() {
    char buffer[100];
    glColor3f(255, 255, 255);
    sprintf(buffer, "Enemies Alive: %d/%ld", jogo.getArena()->contaOponentesVivos(), 
                                            jogo.getArena()->getOpponents().size());

    renderText(jogador_principal->getX(), -5, buffer, GLUT_BITMAP_9_BY_15); 
}
void updateCameraView()
{
    glMatrixMode(GL_MODELVIEW); // Switch to the model-view matrix
    glLoadIdentity();          // Reset the matrix

    glTranslatef(-jogadorX, 0, 0);
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa a tela
    updateCameraView();
    // Chama o método para desenhar todos os elementos
    jogo.Desenha();
    jogador_principal->DesenhaTiros();
    for (Jogador* oponente : jogo.getArena()->getOpponents()) {
        oponente->DesenhaTiros();
    }

    if (jogo.gameOver) {
        gameOver(jogo.vitoria);
    }

    pontuacao();
    

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
            
    // glOrtho(-300, 300, -300, 300, -100, 100);
    glMatrixMode(GL_MODELVIEW);   // Select the projection matrix
    glLoadIdentity();
}


void idle(void)
{

    static GLdouble previousTime = 0;
    GLdouble currentTime;
    GLdouble timeDiference;
    
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeDiference = currentTime - previousTime; 
   
    previousTime = currentTime; 
    
    double inc = jogador_principal->vel * timeDiference; 
    GLfloat size = jogador_principal->getWidth();
    if (keyStatus[(int)('a')]) {
        if (checkCollision(jogador_principal, -inc, 0)) {
            jogadorX = jogador_principal->MoveEmX(-1, timeDiference, isJumping || falling);
        }
    }
    if (keyStatus[(int)('d')]) {
        if (jogadorX + jogador_principal->getWidth() > jogo.getArena()->getWidth()) {
            if (jogo.getArena()->contaOponentesVivos() == 0) {
                jogo.gameOver = true;
                jogo.vitoria = true;
            }
        }
        if (checkCollision(jogador_principal, inc, 0)) {
            jogadorX = jogador_principal->MoveEmX(1, timeDiference, isJumping || falling);
        }
    }
    if (keyStatus[(int)('r')]) {
        if (jogo.gameOver)
            jogo.reiniciar = true;
    }

    jogador_principal->UpdateTiros(timeDiference);
    verificaTirosValidos(jogador_principal);

    for (Jogador* jogador : jogo.getArena()->getOpponents()) {
        Tiro* tiro = jogador->Atira(OPONENTE);
        
        if (tiro) {
            jogador->addTiro(tiro);
        }
        jogador->updateAngleOponente(jogador_principal, jogo.getArenaHeight());
        jogador->UpdateTiros(timeDiference);
        verificaTirosValidos(jogador);
    }

    updatePlayer(timeDiference);
    updateOpponents(timeDiference); 

    if (jogador_principal->morreu) {
        jogo.gameOver = true;
        jogo.vitoria = false;
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