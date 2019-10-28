#include <GLUT/GLUT.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
struct Point
{
    float x, y,z;
};


bool perspectiveProjection = false;
bool orthoProjection = true;
uint connectionMode = GL_LINE_LOOP;
void (*currentDisplayFunc)();

const int width = 800;
const int height = 600;
float z_near = 10.0;
float angle = 60.0;


int red = rand()%255 + 1;
int green = rand()%255 + 1;
int blue = rand()%255 + 1;

struct Sight {
    float x_eye, y_eye, z_eye, x_centre, y_centre, z_centre, up_x, up_y, up_z;
};

struct Perspective {
    float angle, aspect, z_near, z_far;
};

struct Ortho {
    float left, right, bottom, top, near, far;
};

Ortho ortho = {
        -100, 100, -100, 100,-100,100
};

Perspective perspective = {
        65, 2, 10, 2*width
};

Sight sight = {
        0,0,200,0,0,15,0,1,0
};


vector<Point> v;
vector<vector<int>> faces;
int point_count, face_count;

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

void changeEye(Sight sight);

void changeEye(Sight sight) {
    gluLookAt(sight.x_eye,sight.y_eye,sight.z_eye,sight.x_centre,sight.y_centre,
              sight.z_centre,sight.up_x,sight.up_y,sight.up_z);
}

void changePerspective(Perspective perspective){
    gluPerspective(perspective.angle,perspective.aspect,perspective.z_near,perspective.z_far);
}

void changeProjection(Ortho projection){
    glOrtho(projection.left,projection.right,projection.bottom,projection.top,projection.near, projection.far);
}

void readFromFile()
{
    float x, y,z;
    Point p;
    ifstream f("object_data", ios::in);
    f >> point_count >> face_count;
    for (int i = 0; i < point_count; i++)
    {
        f >> p.x >> p.y >> p.z;
        v.push_back(p);
    }
    faces.resize(face_count);
    for (int i = 0; i < face_count; i++)
    {
        int n;
        f >> n;
        for (int j = 0; j < n; j++)
        {
            int p;
            f >> p;
            faces[i].push_back(p);
        }
    }
    f.close();
}

int main(int argc, char * argv[])
{
    srand(time(NULL));
    readFromFile();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL lesson 7");

    glutReshapeFunc(reshape);

    currentDisplayFunc = display;

    glutDisplayFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    glViewport(0, 0, 2*w, 2*h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(orthoProjection){
        changeProjection(ortho);
    }
    if(perspectiveProjection){
        changePerspective(perspective);
        changeEye(sight);
    }

    //glOrtho(-100, 100, -100, 100,-100,100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(orthoProjection){
        changeProjection(ortho);
    }
    if(perspectiveProjection){
        changePerspective(perspective);
        changeEye(sight);
    }

    for (int i = 0; i < face_count; i++)
    {

        int red = rand()%255 + 1;
        int green = rand()%255 + 1;
        int blue = rand()%255 + 1;
        glColor3f(red/255.0, green/255.0, blue/255.0);
        glBegin(connectionMode);
        for (int j = 0; j < faces[i].size(); j++)
        {
            glVertex3f(v[faces[i][j]].x, v[faces[i][j]].y, v[faces[i][j]].z);
        }


        glEnd();
    }
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    //printf("Key %d\n", key);
    switch (key) {
        case 27:
            exit(0);
        case 61:
            //perspective.z_near += 5;
            //perspective.z_far -= 5;
            printf("z-near: %f, z-far: %f \n", perspective.z_near, perspective.z_far);
            glMatrixMode(GL_MODELVIEW);
            glScaled(1.1,1.1,1.1);
            glutPostRedisplay();
            break;
        case 45:
            //perspective.z_near -= 5;
            //perspective.z_far += 5;
            printf("z-near: %f, z-far: %f \n", perspective.z_near, perspective.z_far);
            glMatrixMode(GL_MODELVIEW);
            glScaled(0.9,0.9,0.9);
            glutPostRedisplay();
            break;
        case 120:
            glMatrixMode(GL_MODELVIEW);
            glRotatef(6,1,0,0);
            glutPostRedisplay();
            break;
        case 121:
            glMatrixMode(GL_MODELVIEW);
            glRotatef(6,0,1,0);
            glutPostRedisplay();
            break;
        case 122:
            glMatrixMode(GL_MODELVIEW);
            glRotatef(6,0,0,1);
            glutPostRedisplay();
            break;
        case 119: // w
            sight.y_eye += 2;
            glutPostRedisplay();
            break;
        case 97: // a
            sight.x_eye -= 2;
            glutPostRedisplay();
            break;
        case 115: // s
            sight.y_eye -= 2;
            glutPostRedisplay();
            break;
        case 100: // d
            sight.x_eye += 2;
            glutPostRedisplay();
            break;
        case 87: // W
            sight.y_centre += 2;
            glutPostRedisplay();
            break;
        case 65: // A
            sight.x_centre -= 2;
            glutPostRedisplay();
            break;
        case 83: // S
            sight.y_centre -= 2;
            glutPostRedisplay();
            break;
        case 68: // D
            sight.x_centre += 2;
            glutPostRedisplay();
            break;
        case 23: // Ctrl - W
            sight.up_y += 2;
            glutPostRedisplay();
            break;
        case 1: // Ctrl - A
            sight.up_x -= 2;
            glutPostRedisplay();
            break;
        case 19: // Ctrl - S
            sight.up_y -= 2;
            glutPostRedisplay();
            break;
        case 4: // Ctrl - D
            sight.up_x += 2;
            glutPostRedisplay();
            break;
        case 113: // q
            sight.z_eye += 2;
            printf("z_eye: %f\n", sight.z_eye);
            glutPostRedisplay();
            break;
        case 101: // e
            sight.z_eye -= 2;
            printf("z_eye: %f\nq", sight.z_eye);
            glutPostRedisplay();
            break;
        case 81: // Q
            sight.z_centre += 2;
            glutPostRedisplay();
            break;
        case 69: // E
            sight.z_centre -= 2;
            glutPostRedisplay();
            break;
        case 17: // Ctrl - Q
            sight.up_z += 2;
            glutPostRedisplay();
            break;
        case 5: // Ctrl - E
            sight.up_z -= 2;
            glutPostRedisplay();
            break;

        case 114: // r
            perspective = {
                    65, 2, 10, 2*width
            };

            sight = {
                    0,0,200,0,0,15,0,1,0
            };
            ortho = {
                    -100, 100, -100, 100,-100,100
            };
            red = rand()%255 + 1;
            green = rand()%255 + 1;
            blue = rand()%255 + 1;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glutPostRedisplay();
            break;
        case 44: // <
            perspective.angle -= 2;
            glutPostRedisplay();
            break;
        case 46: // >
            perspective.angle += 2;
            glutPostRedisplay();
            break;
        case 111: // o
            orthoProjection = true;
            perspectiveProjection = false;
            glutPostRedisplay();
            break;
        case 112: // p
            orthoProjection = false;
            perspectiveProjection = true;
            glutPostRedisplay();
            break;
        case 49: //1
            connectionMode = GL_LINE_LOOP;
            glutPostRedisplay();
            break;
        case 50: //2
            connectionMode = GL_POLYGON;;
            glutPostRedisplay();
            break;
        case 88: // X
            glMatrixMode(GL_MODELVIEW);
            glRotatef(-6,1,0,0);
            glutPostRedisplay();
            break;
        case 89: // Y
            glMatrixMode(GL_MODELVIEW);
            glRotatef(-6,0,1,0);
            glutPostRedisplay();
            break;
        case 90: // Z
            glMatrixMode(GL_MODELVIEW);
            glRotatef(-6,0,0,1);
            glutPostRedisplay();
            break;
        case 107: // k
            glMatrixMode(GL_MODELVIEW);
            glRotatef(6,1,1,1);
            glutPostRedisplay();
            break;
        case 106: // j
            glMatrixMode(GL_MODELVIEW);
            glRotatef(-6,1,1,1);
            glutPostRedisplay();
            break;
    }


}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            glMatrixMode(GL_MODELVIEW);
            glTranslated(0, 1, 0);
            display();
            break;
        case GLUT_KEY_DOWN:
            glMatrixMode(GL_MODELVIEW);
            glTranslated(0, -1, 0);
            display();
            break;
        case GLUT_KEY_LEFT:
            glMatrixMode(GL_MODELVIEW);
            glTranslated(-1, 0, 0);
            display();
            break;
        case GLUT_KEY_RIGHT:
            glMatrixMode(GL_MODELVIEW);
            glTranslated(1, 0, 0);
            display();
            break;
    }
}