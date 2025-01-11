#ifndef JOGADOR_H
#define JOGADOR_h
#include <GL/gl.h>
#include <GL/glu.h>
#define JOGADOR 1
#define OPONENTE 2
class Jogador {
    GLfloat x;
    GLfloat y;
    GLfloat size; 
    GLfloat total_size;
    bool oponente;
    

    private:
        void DesenhaCirc(GLfloat size, 
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaRect(GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
        void DesenhaJogador(GLfloat x, GLfloat y, GLfloat size);
        void DesenhaOponente(GLfloat x, GLfloat y, GLfloat size);

    public:
        int dir;
        Jogador(GLfloat x, GLfloat y, GLfloat size) {
            this->x = x;
            this->y = y;
            this->size = size;
            this->dir = 1;
        }
        void Desenha(int tipo) {
            if (tipo == JOGADOR)
                DesenhaJogador(this->x, this->y, this->size);
            else if (tipo == OPONENTE) {
                DesenhaOponente(this->x, this->y, this->size);
            }
        }
        GLfloat MoveEmX(GLfloat dx);
        GLfloat MoveEmY(GLfloat dy);

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
        GLfloat getWidth() {
            return this->size*0.3;
        }

        GLfloat getSize() {
            return this->total_size;
        }
        

        void updateX(GLfloat x_arena) {
            this->x = this->x - x_arena;
        }
        void updateY(GLfloat y_arena) {
            this->y = this->y - y_arena;
        }
        



};





#endif