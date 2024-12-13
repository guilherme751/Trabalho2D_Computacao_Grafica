#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <GL/gl.h>
#include <GL/glu.h>


class Obstaculo {
    GLfloat height;
    GLfloat width;
    GLfloat x;  
    GLfloat y; 

    private:
        void DesenhaRectHorizontal(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaObstaculo(GLfloat x, GLfloat y, GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);
        void DesenhaRectVertical(GLfloat height, GLfloat width,
                        GLfloat R, GLfloat G, GLfloat B);

    public:
        Obstaculo(GLfloat height, GLfixed width, GLfloat x, GLfloat y) {
            this->height = height;
            this->width = width;
            this->x = x;
            this->y = y;
        }

        void Desenha() {
            DesenhaObstaculo(this->x, this->y, this->height, this->width, 0, 0, 0);
        }
};






#endif
