#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include <GL/gl.h>
#include <GL/glu.h>

class Personagem {  
    GLfloat x;
    GLfloat y;
    GLfloat size;


    public:
        void DesenhaCirculo();
        void DesenhaRect();
        void DesenhaPersonagem();
};






#endif
