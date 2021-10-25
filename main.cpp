#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include "cstring"
#include <time.h>


#define mapH 10
#define mapW 10

typedef struct
{
    bool mine;
    bool flag;
    bool open;
    int cntAround;
} Tcell ;

Tcell map[mapW][mapH];

int mines;
int closedCell;


bool IsCellInMap(int x, int y){
    return ( x >= 0) && (y>= 0) && (x < mapW) && (y < mapH);
}

void Game_New (){
    srand(time(NULL));
    memset(map,0, sizeof(map));

    mines = 20;
    closedCell = mapW * mapH;

    for(int i = 0; i<mines ; ++i){
        int x = rand() % mapW;
        int y = rand() % mapH;
        if(map[x][y].mine) i--;
        else{

            map[x][y].mine =true;

            for(int dx = -1; dx < 2; ++dx)
                for(int dy = -1; dy< 2; ++dy)
                    if(IsCellInMap(x+dx,y+dy))
                        map[x+dx][y+dy].cntAround +=1; 
        } 
    }
    
}

    void Line(float x1 ,float y1, float x2 ,float y2){
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    }

void ShowCount(int a){


    glLineWidth(3);
    glColor3f(1,1,0);
    glBegin(GL_LINES);
        if((a!= 1) && (a!=4)) Line(0.3,0.85,0.7,0.85);
        if((a!= 0) &&  (a != 1) && (a!= 7)) Line(0.3,0.5,0.7,0.5);
        if((a!=1) && (a!=4) && (a!=7)) Line(0.3,0.15,0.7,0.15);

        if((a != 5) && (a!=6)) Line(0.7,0.5,0.7,0.85);
        if((a!=2)) Line(0.7,0.5,0.7,0.15);

        if((a!= 1) && (a!= 2) && (a!= 3) && (a!= 7)) Line(0.3,0.5,0.3,0.85);
        if((a== 0) || (a == 2) || (a ==6) || (a==8)) Line(0.3,0.5,0.3,0.15);
    glEnd();

}


void ShowMine(){
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0,0,0);
        glVertex2f(0.3,0.3);
        glVertex2f(0.7,0.3);
        glVertex2f(0.7,0.7);
        glVertex2f(0.3,0.7);
    glEnd();
}

void ShowFieldOpen(){
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.8,0.8,0.8); glVertex2f (0,1);
        glColor3f(0.7,0.7,0.7); glVertex2f (1,1); glVertex2f(0,0);
        glColor3f(0.6,0.6,0.6); glVertex2f(1,0);
    glEnd();
}


void ShowField(){
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.3,0.7,0.3); glVertex2f (0,1);
        glColor3f(0.3,0.6,0.3); glVertex2f (1,1); glVertex2f(0,0);
        glColor3f(0.3,0.5,0.3); glVertex2f(1,0);
    glEnd();
}


void GameShow(){ 
    glLoadIdentity();
    glScalef(2.0/mapW,2.0/mapH,1);
    glTranslatef(-mapW*0.5, -mapH*0.5,0);

    for(int j = 0; j < mapH; j++)
        for(int i = 0 ; i < mapW; i++){

            glPushMatrix();
            glTranslatef(i,j,0);

            if(map[i][j].open){

            ShowFieldOpen();
            if(map[i][j].mine)
                ShowMine();
            else if (map[i][j].cntAround > 0)
                ShowCount(map[i][j].cntAround);

            }else{
                ShowField();
            }
            glPopMatrix();

        }
}

void Render(){

    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GameShow();

    glutSwapBuffers();
	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(900, 900);
	glutCreateWindow("OpenGL Snake");
    Game_New();
    glutDisplayFunc(Render);
    
	glutMainLoop();
	return 0;

}
