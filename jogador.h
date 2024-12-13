#ifndef JOGADOR_H
#define JOGADOR_h
#include <GL/gl.h>
#include <GL/glu.h>
#define JOGADOR 1
#define OPONENTE 2
class Jogador {
    GLfloat x;
    GLfloat y;
    GLfloat size; //diametro do circulo

    private:
        void DesenhaCirc(GLfloat size, 
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaJogador(GLfloat x, GLfloat y, GLfloat size);
        void DesenhaOponente(GLfloat x, GLfloat y, GLfloat size);

    public:
        Jogador(GLfloat x, GLfloat y, GLfloat size) {
            this->x = x;
            this->y = y;
            this->size = size;
        }
        void Desenha(int tipo) {
            if (tipo == JOGADOR)
                DesenhaJogador(this->x, this->y, this->size);
            else if (tipo == OPONENTE) {
                DesenhaOponente(this->x, this->y, this->size);
            }
        }

};





#endif