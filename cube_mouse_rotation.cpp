#define GL_SILENCE_DEPRECATION

#include <bits/stdc++.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int mouse_x, mouse_y;
bool RIGHT_BUTTON_DOWN;

double rotate_y = 0; 
double rotate_x = 0;

void init(void) //Initialization
{
  glClearColor(0,0,0,0);
}

float cube_cord[8][3] = {
    {-1.0, -1.0, 1.0},  //a -0
    {-1.0, 1.0, 1.0},   //b -1
    {1.0, 1.0, 1.0},    //c -2 
    {1.0, -1.0, 1.0},   //d -3
    {-1.0, -1.0, -1.0}, //e -4
    {-1.0, 1.0, -1.0},  //f -5
    {1.0, 1.0, -1.0},   //g -6
    {1.0, -1.0, -1.0},  //h -7
};

GLfloat color[6][3] = {
	{0.4, 0.4, 0.4},
	{1.0, 1.0, 1.0},
	{0.7, 0.7, 0.7},
	{0.4, 0.4, 0.4},
    {0.7, 0.7, 0.7},
	{1.0, 1.0, 1.0},
};

void polygon(int a,int b,int c,int d) //Draw the face of Polygon
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(cube_cord[a]);
    glVertex3fv(cube_cord[b]);
    glVertex3fv(cube_cord[c]);
    glVertex3fv(cube_cord[d]);

    glEnd();
}

void colorcube()  //Draw polygon
{
    polygon(0,3,2,1);  //1
	polygon(4,5,6,7);  //2
    polygon(2,3,7,6);  //3
    polygon(0,4,7,3);  //4
	polygon(0,1,5,4);  //5
    polygon(1,2,6,5);  //6
}


void keybourdKeys( int key, int x, int y )  // Up, Down, Right, Left
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    glutPostRedisplay();
}

void mouseCordValue( int button, int state, int x , int y ) //Mouse coordinate value
{
    mouse_x = x;
    mouse_y = y;

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        RIGHT_BUTTON_DOWN = true;
    glutPostRedisplay();
	
}

void motion(int x, int y)  //conver the mouse coordinate value for rotation
{
    if (RIGHT_BUTTON_DOWN) {
        rotate_x += (float)(x - mouse_x) / 4.0; 
        rotate_y += (float)(mouse_y - y) / 4.0;
    }

    mouse_x = x;
    mouse_y = y;
    glutPostRedisplay();
}

void display() //Display the cube
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 60, w / h, 0.1, 10 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 3, 3, 3, 
               0, 0, 0,
               0, 0, 1
              );

    glRotatef( -rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( -rotate_y, 0.0, 1.0, 0.0 );
    colorcube();

    glutSwapBuffers();
}


int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( 640, 480 );
    glutCreateWindow("Render 3D Box");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseCordValue);
    glutMotionFunc(motion);
    glutSpecialFunc(keybourdKeys);
    glEnable( GL_DEPTH_TEST );
    glutMainLoop();
    return 0;
}