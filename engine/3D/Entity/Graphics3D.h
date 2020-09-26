//
// Created by Lado on 16/7/20.
//

#ifndef LOTOS_GRAPHICS3D_H
#define LOTOS_GRAPHICS3D_H

#include <iostream>
#include "SDL2/SDL.h"
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"

class Graphics3D {
private:
    const int width = 640;
    const int height = 320;
    SDL_Window *window;
public:
    void init() {
        // Инициализация SDL

        if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
            std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        // Включаем двойной буфер, настраиваем цвета

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

        // Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

        window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

        if(window == NULL){	// если не получилось создать окно, то выходим
            exit(1);
        }

        // Инициализация OpenGL

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
        glClearDepth(1.0);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST); // включаем тест глубины
        glShadeModel(GL_SMOOTH);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
        glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
    }
    void drawCube(float x, float y, float z) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

        glRotatef(x, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
        glRotatef(y, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
        glRotatef(z, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

        glBegin(GL_QUADS);		// Рисуем куб

        glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
        glVertex3f( 1.0f, 1.0f, -1.0f);		// Верхний правый угол квадрата
        glVertex3f(-1.0f, 1.0f, -1.0f);		// Верхний левый
        glVertex3f(-1.0f, 1.0f,  1.0f);		// Нижний левый
        glVertex3f( 1.0f, 1.0f,  1.0f);		// Нижний правый

        glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Верхний правый угол квадрата
        glVertex3f(-1.0f, -1.0f,  1.0f);	// Верхний левый
        glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
        glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

        glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
        glVertex3f( 1.0f,  1.0f, 1.0f);		// Верхний правый угол квадрата
        glVertex3f(-1.0f,  1.0f, 1.0f);		// Верхний левый
        glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
        glVertex3f( 1.0f, -1.0f, 1.0f);		// Нижний правый

        glColor3f(1.0f,1.0f,0.0f);			// Желтая сторона (Задняя)
        glVertex3f( 1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
        glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
        glVertex3f(-1.0f,  1.0f, -1.0f);	// Нижний левый
        glVertex3f( 1.0f,  1.0f, -1.0f);	// Нижний правый

        glColor3f(0.0f,0.0f,1.0f);			// Синяя сторона (Левая)
        glVertex3f(-1.0f,  1.0f,  1.0f);	// Верхний правый угол квадрата
        glVertex3f(-1.0f,  1.0f, -1.0f);	// Верхний левый
        glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
        glVertex3f(-1.0f, -1.0f,  1.0f);	// Нижний правый

        glColor3f(1.0f,0.0f,1.0f);			// Фиолетовая сторона (Правая)
        glVertex3f( 1.0f,  1.0f, -1.0f);	// Верхний правый угол квадрата
        glVertex3f( 1.0f,  1.0f,  1.0f);	// Верхний левый
        glVertex3f( 1.0f, -1.0f,  1.0f);	// Нижний левый
        glVertex3f( 1.0f, -1.0f, -1.0f);	// Нижний правый

        glEnd();	// Закончили квадраты
    }

};

#endif //LOTOS_GRAPHICS3D_H
