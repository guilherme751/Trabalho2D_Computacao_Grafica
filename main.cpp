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

// Window dimensions
const GLint Width = 500;
const GLint Height = 500;
GLfloat visDim;
GLfloat jogadorX;
Jogo jogo;
Jogador* jogador_principal;
bool isJumping;
GLfloat positionBeforeJump;
Tiro* tiro = NULL;
int keyStatus[256];

// configurações para apresentação
GLfloat prob_tiro = 0.04;
bool mov_oponente = true;

/**
 * Identifica quando uma tecla é pressionada
*/
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
/**
 * Identifica quando uma tecla é solta 
*/
void keyup(unsigned char key, int x, int y) {
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}
/**
 * Reinicia o status das teclas
*/
void ResetKeyStatus() {
    int i;
    // Initialize keyStatus
    for (i = 0; i < 256; i++)
        keyStatus[i] = 0;
}
/**
 * Checa Colisão do tiro com os obstáculos do mapa.
 * Retorna true se encontrar colisão
*/
bool checkCollisionObstaculoTiro(Tiro* tiro, Obstaculo* obstaculo) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = obstaculo->x, ry = obstaculo->y, radius = tiro->radius;

    if (cx + radius > rx && cx - radius < rx + obstaculo->getWidth() &&
        cy + radius > ry && cy - radius < ry + obstaculo->getHeight()) {
            return true;
        }
    
    return false;
}

/**
 * Checa Colisão do tiro com o jogador do mapa.
 * Retorna true se encontrar colisão
*/

bool checkCollisionJogadorTiro(Tiro* tiro) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = jogador_principal->getX(), ry = jogador_principal->getY(), radius = tiro->radius;

    if (cx + radius > rx && cx - radius < rx + jogador_principal->getWidth() &&
        cy + radius > ry && cy - radius < ry + jogador_principal->getSize()) {
            return true;
        }
    
    return false;
}

/**
 * Checa Colisão do tiro com os oponentes do mapa.
 * Retorna true se encontrar colisão
*/
bool checkCollisionOponenteTiro(Tiro* tiro, Jogador* oponente) {
    GLfloat cx = tiro->getX(), cy = tiro->getY(), rx = oponente->getX(), ry = oponente->getY(), radius = tiro->radius;
    if (oponente->morreu)   return false;
    if (cx + radius > rx && cx - radius < rx + oponente->getWidth() &&
        cy + radius > ry && cy - radius < ry + oponente->getSize()) {
            return true;
    }
    
    return false;
}
/**
 * Verifica se é um tiro válido. 
 * Para ser válido, o tiro deve: 
 * 1) Estar dentro das dimensões da arena
 * 2) Não ter colisão com um obstáculo
 * 3) Não ter clisão com o jogador ou um oponente
 * Se o tiro for inválido, retorna false
*/
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
/**
 * Passa pela lista de tiros do jogador ou oponente e vê se todos são válidos. 
 * Se encontrar um tiro inválido, esse será excluído
*/
void verificaTirosValidos(Jogador* j) {
    std::list<Tiro*>& tiros = j->getTiros();
    for (auto it = tiros.begin(); it != tiros.end(); ) {
        if (!tiroValido(*it, j)) { 
            delete *it;         
            it = tiros.erase(it); 
        } else {
            ++it; 
        }
    }
}

/**
 * Checa colisão entre o jogador e os obstáculos, os oponentes e as dimensões do mapa.
 * Faz o mesmo para os oponentes.
*/
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
    if (Y + altura - 0.5> jogo.getArena()->getHeight() || Y < 0) {
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
        for (Jogador* oponente : jogo.getArena()->getOpponents()) {
            if (!oponente->morreu && oponente != jogador) {
                if (X < oponente->getX() + largura && 
                    X + largura > oponente->getX() && 
                    Y < oponente->getY() + altura && 
                    Y + altura > oponente->getY()) {  
                
                    return false; // Colisão detectada
                }
            }
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
// flags para ajudar no pulo
bool wayup, falling = false;

/**
 * Função de callback do click do mouse para identificar que deve ser feito uma ação de pulo
 * O pulo corresponde a subida e a descida. As variáveis isJumping e wayup controlam isso. 
 * O pulo ocorre até o usuário soltar o botão direito do mouse ou atingir a altura de 3 vezes o tamanho do jogador.
*/
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
            }
        } else if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN)
                jogador_principal->addTiro(jogador_principal->Atira(JOGADOR, prob_tiro));
        }

        glutPostRedisplay();
    
}
/**
 * Atualiza a posição do jogador em Y quando há um pulo. 
 * Verifica se há uma colisão com os pés do jogador, caso não haja, significa que o jogador está no ar e portanto deve iniciar
 * um movimento de queda. (Ao cair de obstáculos por exemplo). A variável falling controla isso.
*/
void updatePlayer(GLdouble timeDiference, GLfloat dy) {
    if (isJumping) {
        if (wayup) {
            if (positionBeforeJump - jogador_principal->getY() < 3*jogador_principal->getSize()) {
                if (checkCollision(jogador_principal, 0, -dy)) {
            
                    jogador_principal->MoveEmY(-1, timeDiference);
                    
                } 
                else {
                    wayup = false;                    
                }
            } 
            else {
                wayup = false;                
            }
        } 
        else {
            if (checkCollision(jogador_principal, 0, dy)) {
                jogador_principal->MoveEmY(1, timeDiference);
            }
            else {
                isJumping = false;
            }
        }      
    } else {
        if (checkCollision(jogador_principal, 0, dy)) {
            falling = true;
            jogador_principal->MoveEmY(1, timeDiference);
        } else {
            falling = false;
        }
    }
    
}

/**
 * Atualiza a posição X dos oponentes. Eles mudam de sentido sempre que encontrarem uma colisão na direita ou esquerda. 
 * Também mudam de sentido se não tiver mais colisão com os pés deles.
*/
void updateOpponents(GLdouble timeDiference) {
    
    std::vector<Jogador*> oponentes = jogo.getArena()->getOpponents();
    for (Jogador* oponente : oponentes) {        
        if (!oponente->morreu) {
            if (!checkCollision(oponente, oponente->dir*timeDiference*oponente->vel, 0)){
                oponente->dir *= -1;
            }

            if (checkCollision(oponente, 0, 1)) {
                oponente->dir *= -1;
            }
            if (mov_oponente)
                oponente->MoveEmX(oponente->dir, timeDiference*0.5, isJumping || falling);
           
        }
        
    }
    
}
int ultimaPosMouseY = 0; 

/**
 * Movimento do braço do jogador com base no movimento do mouse. O ângulo varia entre -40 e -130 graus. 
 * A posição inicial do braço é em 85. Isso permite o jogador mexer o braõ 45 graus para cima ou para baixo.
*/
void movimentarBracoMouse(int x, int y) {

    Jogador* jogador = jogador_principal;
    GLfloat anguloBraco = jogador->getAngle();

    int deltaY = y - ultimaPosMouseY;

    GLfloat anguloIncremento = deltaY * 0.2f; 

    if (anguloIncremento > 0) { 
        if (anguloBraco + anguloIncremento < -40) {          
            anguloBraco = jogador->updateAngle(anguloIncremento);
        }
    } else if (anguloIncremento < 0) { 
        if (anguloBraco + anguloIncremento >= -130) {          
            anguloBraco = jogador->updateAngle(anguloIncremento);
        }
    }

    ultimaPosMouseY = y;

    glutPostRedisplay();
}

/**
 * Renderiza um texto na tela, com uma determinada fonte (vide documentação do OPENGL)
*/
void renderText(float x, float y, const char* text, void* font) {
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(font, text[i]);
    }
}

/**
 * Reinicia o jogo. Volta todos os elementos para suas posições iniciais.
*/
void reiniciarJogo() {
    for (Jogador* oponente : jogo.getArena()->getOpponents()) {
        oponente->reiniciaPosicao();
    }
    jogador_principal->reiniciaPosicao();
    jogadorX = jogador_principal->getX();

}
/**
 * Tela de fim de jogo. Mostra a tela correta, caso seja vitória ou derrota. Chama a função para reiniciar jogo.
*/
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

/**
 * Pontuação do jogo que mantêm a contagem de quantos inimigos estão vivos.
*/
void pontuacao() {
    char buffer[100];
    glColor3f(255, 255, 255);
    sprintf(buffer, "Enemies Alive: %d/%ld", jogo.getArena()->contaOponentesVivos(), 
                                            jogo.getArena()->getOpponents().size());

    renderText(jogador_principal->getX(), -5, buffer, GLUT_BITMAP_9_BY_15); 
}
/**
 * Movimenta a câmera de acordo com a posição X do jogador.
*/
void updateCameraView()
{
    glMatrixMode(GL_MODELVIEW); // Switch to the model-view matrix
    glLoadIdentity();          // Reset the matrix

    glTranslatef(-jogadorX, 0, 0);
}

/**
 * Desenha todos os elementos na tela
*/
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


/**
 * Inicializa funções básicas do OPENGL. 
 * Chama o glOrtho para ajustar a janela de visualização que é do tamanho da altura da arena.
*/
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

/**
 * Função que é chamada a todo momento. Faz diversas verificações e ações.
 * 1) Calcula o tempo entre uma chamada e outra para passar para as funções de movimento para que o jogo não
 * dependa do processador do computador. 
 * 2) Verifica se as teclas 'a', 'd' e 'r' foram pressionadas para movimentar o jogador para esquerda, para direita
 * e reiniciar o jogo (caso o jogo tenha acabado) respectivamente.
 * 3) Atualiza os tiros do jogador
 * 4) Atualiza os tiros dos oponentes e faz eles atirarem aleatoriamente
 * 5) Chama funções que atualizam as posições dos elementos
 * 6) Verifica se o jogador morreu
*/
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

    for (Jogador* oponente : jogo.getArena()->getOpponents()) {
        Tiro* tiro = oponente->Atira(OPONENTE, prob_tiro);
        
        if (tiro) {
            oponente->addTiro(tiro);
        }
        oponente->updateAngleOponente(jogador_principal, jogo.getArenaHeight());
        oponente->UpdateTiros(timeDiference);
        verificaTirosValidos(oponente);
    }

    updatePlayer(timeDiference, inc);
    updateOpponents(timeDiference); 

    if (jogador_principal->morreu) {
        jogo.gameOver = true;
        jogo.vitoria = false;
    }
    
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // inicialização padrão do openGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("Trabalho 2D");

    // Inicializa o jogo  

    jogo.CarregarArquivoSVG(argv[1]);
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
    init();
    glutMainLoop();
    return 0;
}