#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <GL/gl.h>
#include <GL/glu.h>


class Obstaculo {
    GLfloat height;
    GLfloat width;

    private:
        void DesenhaRectHorizontal(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaRectVertical(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);

    public:
        GLfloat x;  
        GLfloat y; 
        Obstaculo(GLfloat height, GLfixed width, GLfloat x, GLfloat y) {
            this->height = height;
            this->width = width;
            this->x = x;
            this->y = y;
        }

        void Desenha() {
            DesenhaObstaculo(this->x, this->y, this->height, this->width, 255, 255, 255);
        }

        void updateX(GLfloat x_arena) {
            this->x = this->x - x_arena;
        }
        void updateY(GLfloat y_arena) {
            this->y = this->y - y_arena;
        }
};






#endif
