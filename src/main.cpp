#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <GL/glut.h>

using namespace std;

// Define the screen size
const int screenWidth = 320;
const int screenHeight = 240;

// Define the model data
vector<float> vertices;
vector<int> indices;

float xAngle = 0.0f;  // X-axis rotation angle
float scale = 1.0f; 
float yAngle = 0.0f;  // Y-axis rotation angle

void idle()
{
    if (yAngle < 0.5){
     // Rotate the pyramid around the y-axis
    yAngle += 0.1f;
    }
    else
    {
       yAngle -= 0.5f; 
    }

    // Redraw the scene
    glutPostRedisplay();
}

// Function to read the OBJ file
void readObjFile(string filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    char line[256];
    while (file.getline(line, 256)) {
        char* token = strtok(line, " ");

        if (token == NULL) continue;

        if (strcmp(token, "v") == 0) {
            float x = stof(strtok(NULL, " "));
            float y = stof(strtok(NULL, " "));
            float z = stof(strtok(NULL, " "));
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        } else if (strcmp(token, "f") == 0) {
            int v1 = stoi(strtok(NULL, " ")) - 1;
            int v2 = stoi(strtok(NULL, " ")) - 1;
            int v3 = stoi(strtok(NULL, " ")) - 1;
            indices.push_back(v1);
            indices.push_back(v2);
            indices.push_back(v3);
        }
    }

    file.close();
}

// Function to display the model
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glScalef(scale,scale,scale);
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

    // Draw the model
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < indices.size(); i++) {
        int index = indices[i] * 3;
        float x = vertices[index];
        float y = vertices[index + 1];
        float z = vertices[index + 2];
        glVertex3f(x, y, z);
    }
    glEnd();

    glutSwapBuffers();
}

// Function to initialize the graphics settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, screenWidth / (float)screenHeight, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void special(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_LEFT:
        yAngle -= 10.0f;
        break;
    case GLUT_KEY_RIGHT:
        yAngle += 10.0f;
        break;
    case GLUT_KEY_UP:
        xAngle -= 10.0f;
        break;
    case GLUT_KEY_DOWN:
        xAngle += 10.0f;
        break;
    }
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 27:  // Escape key
        exit(0);
        break;
    case 0x000D:
        yAngle=0;
        xAngle=0;
        scale=1.0f;
        break;
// No Caps Lock regular keys
    case 0x0075:  // X key // u
        yAngle -= 15.0f;
        break;
    case 0x006B:  // B key // k
        yAngle += 15.0f;
        break;
    case 0x0069:  // Y key // i
        xAngle -= 15.0f;
        break;
    case 0x006A:  // A key // j
        xAngle += 15.0f;
        break;
// // Caps Lock regular keys
//     case 0x0055:  // X key // u
//         yAngle -= 15.0f;
//         break;
//     case 0x004B:  // B key // k
//         yAngle += 15.0f;
//         break;
//     case 0x0049:  // Y key // i
//         xAngle -= 15.0f;
//         break;
//     case 0x004A:  // A key // j
//         xAngle += 15.0f;
//         break;  
// // Caps Lock new keys
//     case 0x0059:  // X key // Y
//         yAngle -= 15.0f;
//         break;
//     case 0x004C:  // B key // L
//         yAngle += 15.0f;
//         break;
//     case 0x004F:  // Y key // O
//         xAngle -= 15.0f;
//         break;
//     case 0x0048:  // A key // H
//         xAngle += 15.0f;
//         break;
// Caps Lock new keys
    case 0x0079:  // X key // y
        scale += 0.01f;
        break;
    case 0x006C:  // B key // l
        scale -= 0.01f;
        break;
    case 0x006F:  // Y key // o
       scale += 0.01f;
        break;
    case 0x0068:  // A key // h
        scale -= 0.01f;
        break;  
    }
    glutPostRedisplay();  // Tell GLUT to redraw the scene
}


// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("OBJ Viewer");

    // Read the OBJ file
    readObjFile("model.obj");

    // Initialize the graphics settings
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    // Set the display function
    glutDisplayFunc(display);

    // Start the main loop
    glutMainLoop();

    return 0;
}
