#include <GL/glut.h>
#include <stdio.h>
#include "lodepng.h"

// Global variables for camera and scene
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraSpeed = 0.1f;
bool isPerspective = true;

// Texture IDs for storing the loaded textures
GLuint textureIDs[4];

// Function declarations
void keyboard(unsigned char key, int x, int y);
void mouse(int x, int y);
void mouseScroll(int button, int dir, int x, int y);
void renderScene();
void init();
void loadTextures();
void drawPlane();

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Scene");

    init();
    loadTextures();

    glutMainLoop();

    return 0;
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            cameraZ -= cameraSpeed;
            break;
        case 's':
            cameraZ += cameraSpeed;
            break;
        case 'a':
            cameraX -= cameraSpeed;
            break;
        case 'd':
            cameraX += cameraSpeed;
            break;
        case 'q':
            cameraY -= cameraSpeed;
            break;
        case 'e':
            cameraY += cameraSpeed;
            break;
        case 'p':
            switchProjection();
            break;
    }
    glutPostRedisplay();
}

// Function to handle mouse input
void mouse(int x, int y) {
    // Change camera orientation based on mouse movement
    // ...
}

// Function to handle mouse scroll input
void mouseScroll(int button, int dir, int x, int y) {
    // Adjust camera movement speed based on mouse scroll
    // ...
}

// Function to render the scene
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    drawPlane();

    glutSwapBuffers();
}

// Function to initialize OpenGL settings and create the window
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switchProjection();

    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutMouseWheelFunc(mouseScroll);
    glutDisplayFunc(renderScene);
}

// Function to load textures using lodepng library
void loadTextures() {
    std::string textureFiles[4] = {
        "resources\textures\20230515_204415.jpg",
        "resources\textures\20230515_204419.jpg",
        "resources\textures\20230515_204428.jpg",
        "resources\textures\20230515_204439.jpg"
    };

    glGenTextures(4, textureIDs);

    for (int i = 0; i < 4; i++) {
        std::vector<unsigned char> image;
        unsigned width, height;

        unsigned error = lodepng::decode(image, width, height, textureFiles[i]);

        if (error != 0) {
            printf("Error loading texture: %s\n", textureFiles[i].c_str());
            continue;
        }

        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

// Function to draw a textured plane
void drawPlane() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureIDs[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[1]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[2]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, textureIDs[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Function to switch between perspective and orthographic projection
void switchProjection() {
    if (isPerspective) {
        gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        isPerspective = false;
    } else {
        glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -10.0f, 10.0f);
        isPerspective = true;
    }
}
