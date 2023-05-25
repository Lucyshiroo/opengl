#include <GL/glut.h>
#include <stdio.h>

// Global variables for camera and scene
float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 0.0f;
float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraSpeed = 0.1f;
bool isPerspective = true;

// Function declarations
void keyboard(unsigned char key, int x, int y);
void mouse(int x, int y);
void mouseScroll(int button, int dir, int x, int y);
void renderScene();
void init();
void drawPlane();
void switchProjection();

// Main function
int main(int argc, char** argv) {
    // Initialization and window creation
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Scene");

    // Initialization of OpenGL settings
    init();

    // Start the main rendering loop
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
    glutPostRedisplay(); // Notify GLUT to redraw the scene
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

    // Set camera position and orientation
    glTranslatef(-cameraX, -cameraY, -cameraZ);
    glRotatef(cameraAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cameraAngleY, 0.0f, 1.0f, 0.0f);

    // Draw the 3D scene objects
    drawPlane();

    glutSwapBuffers();
}

// Function to initialize OpenGL settings and create the window
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing for proper object rendering
    glEnable(GL_DEPTH_TEST);

    // Set up perspective or orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switchProjection();

    // Register callback functions for input handling
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutMouseWheelFunc(mouseScroll);
    glutDisplayFunc(renderScene);
}

// Function to draw a 3D plane
void drawPlane() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f); // Set color to gray

    // Define the vertices of the plane
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);

    glEnd();
}

// Function to switch between perspective and orthographic projection
void switchProjection() {
    if (isPerspective) {
        // Set up perspective projection
        gluPerspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        isPerspective = false;
    } else {
        // Set up orthographic projection
        glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -10.0f, 10.0f);
        isPerspective = true;
    }
}
