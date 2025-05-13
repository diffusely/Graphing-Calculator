#pragma once
#include <glad/glad.h>

class Triangle
{
public:
    Triangle();
    void draw() const;

private:
    unsigned int VAO, VBO;
};
