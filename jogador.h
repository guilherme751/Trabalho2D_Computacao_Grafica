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
        void DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
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
        void MoveEmX(GLfloat dx);
        void MoveEmY(GLfloat dy);

        GLfloat getX() {
            return this->x;
        }
        GLfloat getY() {
            return this->y;
        }
        void setY(GLfloat y) {
            this->y = y;
        }
        void setX(GLfloat x) {
            this->x = x;
        }
        



};





#endif