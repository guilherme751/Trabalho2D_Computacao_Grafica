#include "arena.h"
#include <stdio.h>

/**
 * Desenha um retângulo. 
 * A origem está no vértice inferior direito.
*/
void Arena::DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);
   
    glBegin(GL_QUADS);
        glVertex2f(0, height);
        glVertex2f(0, 0);
        glVertex2f(width, 0);
        glVertex2f(width, height);
    glEnd();  
}
/**
 * Desenha a arena. Chama as funções de desenho de todos os elementos e por fim desenha a arena
*/
void Arena::DesenhaArena(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();        
        glRotatef(180, 1, 0, 0);
        glPushMatrix();
            glTranslatef(x, y, 0);
            DesenhaRect(height, width, R, G, B);
        glPopMatrix();
        for (Obstaculo* obstaculo : this->obstaculos) {
                obstaculo->Desenha();
        }
        for (Jogador* oponente : this->oponentes) {
            if (!oponente->morreu)
                oponente->Desenha(OPONENTE);
        }
        if (!this->jogador->morreu) {
            this->jogador->Desenha(JOGADOR);
        }
        

    glPopMatrix();
}

void Arena::printArena() {
    printf("Altura %f\nLargura: %f\n", this->height, this->width);
}

/**
 * Atualiza coordenadas. Função chamada no início para atualizar as posições X e Y dos elementos
 * com base nas posições X e Y da arena. 
 * X do elemento -= X da arena
 * Y do elemento -= Y da arena
 * X da arena, Y da arena = 0 
 * Falicita o entendimento das coordenadas. Poderia usar translações também.
*/
void Arena::AtualizaCoordenadas() {
    for (Obstaculo* obstaculo : obstaculos) {
        obstaculo->updateX(this->x);
        obstaculo->updateY(this->y);
    }

    for (Jogador* oponente : oponentes) {
        oponente->updateX(this->x);
        oponente->updateY(this->y);
    }

    this->jogador->updateX(this->x);
    this->jogador->updateY(this->y);

    this->x = 0;
    this->y = 0;

    

}