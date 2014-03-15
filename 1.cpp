#include <iostream>
#include<fstream>
#include <cmath>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

using namespace std;

struct Spider
{
    float x,y;
    float vel_y;
    float r,g,b;
    int scoreflag;
} Spider;

struct goli
{
    int theta;
    float x,y;
    float vel_y;
    float vel_x;
    float r,g,b;
} goli;

float max1=-44;
float min1=100;
float max2=-44;
float min2=100;
float max3=-44;
float min3=100;


float togcan,toggreen,togred,rotcan;
float mousex,mousey,mouseposx,mouseposy;     
void drawScene();
void update(int value);
void drawSpider(float Spider_len);
void drawBox(float len,float width);
void initrendering();
void handleResize(int w, int h);
void handlekeypress1(unsigned char a,int w,int h);
void handlekeypress2(int key2, int w, int h);
float myrand(float min,float max);
void drawBasket(float Basket_len,float rad);
void drawBasketOutline(float Basket_len,float rad);
void drawCannon(float Cannon_len);
void drawline();
void drawCannonOutline(float Cannon_len);
void drawGameOver();
void handleMouseclick(int button, int state, int x, int y);
float drag(float position);//,float lefy,float rify);
void dragwithmouse(int x,int y);
void GetOGLPos(int x, int y);


struct goli d[100];
struct Spider a[100];
//float box_len;
//float box_width;
float box_len = 6.0f;
float box_width = 4.0f;
float Spider_len = 0.4f;
float RedBasket_x = -box_len/3;
float GreenBasket_x = box_len/3;
float Cannon_x = 0.0f;
int i;
float Basket_len = 0.6f;
float Cannon_len = 0.3f;
int flag=0;
int j=0;
int k=0;
int Basketflag=0;
int qwe=0;
int goliflag=0;
int Score=0;
//int theta;
float rad = 0.3f;
float angle=0.0f;
int GameOver=0;
int FinalScore;
int pauseflag=0;
int pausectr=0;
int CannonChala=0;
int difficulty=1;
int mouse=0;
float Cannon_y =-box_width/2+0.2f;

float distance(float x1,float y1,float x2,float y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

float myrand(float min ,float max)
{
    return rand()*(max-min)/RAND_MAX + min;
}

int main(int argc, char **argv)
{

  /*  string line; 
    int fileline=0;
    ifstream myfile ("world.txt"); 
    if (myfile.is_open()) { 
        while ( getline (myfile,line) ) 
        { 
            fileline++;
            if(fileline==2)
                box_len = ::atof(line.c_str());
            if(fileline==4)
                box_width= ::atof(line.c_str());
        } 
        myfile.close(); 
    }

    else cout << "Unable to open file"; 
    printf("%lf\n%lf\n",box_len,box_width);*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);

    int windowWidth = w*2/3;
    int windowHeight = h*2/3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w- windowWidth)/2,(h-windowHeight)/2);

    glutCreateWindow("Assignment1");
    initrendering();
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handlekeypress1);
    if(pauseflag==0)
    {
        glutSpecialFunc(handlekeypress2);
        glutReshapeFunc(handleResize);
        glutMouseFunc(handleMouseclick);
        //glutMouseFunc(handleMouseclick);
        glutMotionFunc(dragwithmouse);
        glutTimerFunc(10,update,0);
    }
    glutMainLoop();
    return 0;
}
char text2[100];

void drawGameOver()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0f,0.0f,-5.0f);
    drawBox(box_len,box_width);
    glColor3f(0.0f,0.0f,1.0f);
    sprintf(text2, "GAME OVER \n");
    glRasterPos3f(-0.5,0,0.0f);
    for(int l=0;text2[l]!='\0';l++)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, text2[l]);
    sprintf(text2,"\nYour Final Score is %d",FinalScore);
    glRasterPos3f(-0.7,-0.2,0.0f);
    for(int l =0;text2[l]!='\0';l++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text2[l]);
    glPopMatrix();
    glutSwapBuffers();
}

void drawScene()
{
    if(GameOver==0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();

        glTranslatef(0.0f, 0.0f, -5.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        drawBox(box_len,box_width);
        sprintf(text2, "Score --> %d", Score);
        glRasterPos3f(2.0,1.7,0.0f);
        for(int l=0;text2[l]!='\0';l++)
            glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, text2[l]);
        char text[20];
        sprintf(text,"Level-->%d",difficulty);
        glRasterPos3f(2.0,1.4,0.0f);
        for(int l=0;text[l]!='\0';l++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[l]);
        // printf("jdskj\n");
        // for(i=k;i<20;i++)
        // {

        // }

        //  i=j; 
        glPushMatrix();
        glBegin(GL_LINES);
        glVertex2f(-box_len/2,-box_width/2+0.6f);
        glVertex2f(box_len/2,-box_width/2+0.6f);
        glColor3f(0.0f,0.0f,1.0f);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(RedBasket_x,-box_width/2+0.4f,0.0f);
        glColor3f(1.0f,0.0f,0.0f);
        drawBasket(Basket_len,rad);
        glPopMatrix();
        if(Basketflag==5)
        {
            glPushMatrix();
            glTranslatef(RedBasket_x,-box_width/2+0.4f,0.0f);
            glColor3f(0.7f,0.2f,0.1f);
            drawBasketOutline(Basket_len,rad);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(GreenBasket_x,-box_width/2+0.4f,0.0f);
        glColor3f(0.0f,1.0f,0.0f);
        drawBasket(Basket_len,rad);
        glPopMatrix();
        if(Basketflag==10)
        {
            glPushMatrix();
            glTranslatef(GreenBasket_x,-box_width/2+0.4f,0.0f);
            glColor3f(0.0f,0.7f,0.3f);
            drawBasketOutline(Basket_len,rad);
            glPopMatrix();
        }

        glPushMatrix();
        glTranslatef(Cannon_x,-box_width/2+0.2f,0.0f);
        glColor3f(0.0f,0.0f,0.0f);
        glRotatef(angle,0.0f,0.0f,1.0f);
        drawCannon(Cannon_len);
        glPopMatrix();
        if(Basketflag==15 || mouse==1)
        {
            glPushMatrix();
            glTranslatef(Cannon_x,-box_width/2+0.2f,0.0f);
            glColor3f(1.0f,1.0f,1.0f);
            glRotatef(angle,0.0f,0.0f,1.0f);
            drawCannonOutline(Cannon_len);
            glPopMatrix();
        }
        if(flag==1)
        {
            for(i=0;i<j;i++)
            {
                glPushMatrix();
                glTranslatef(a[i].x,a[i].y,0.0f);
                glColor3f(a[i].r,a[i].g,a[i].b);
                drawSpider(Spider_len);
                glPopMatrix();

            }
        }
        //       if(goliflag==1)
        //     {
        int variable=0;
        for(variable=0;variable<qwe;variable++)
        {
            glPushMatrix();
            glColor3f(0.0f,0.0f,0.0f);
            glTranslatef(d[variable].x,d[variable].y,0.0f);
            glRotatef(d[variable].theta,0.0f,0.0f,1.0f);
            //    glTranslatef(Cannon_x,0.0f,0.0f);
            //      glRotatef(d[variable].theta,0.0f,0.0f,1.0f);
            //     glVertex2f(d[variable].x,d[variable].y);
            //   glVertex2f((d[variable].x-0.3f*sin(angle)),(d[variable].y+0.3f*cos((angle))));
            //        glVertex2f(((d[variable].x)*sin(DEG2RAD(angle))),((d[variable].y)*(cos(DEG2RAD(angle)))));
            //        glVertex2f(((d[variable].x)*(sin(DEG2RAD(angle)))),(((d[variable].y+0.3f))*(cos(DEG2RAD(angle)))));
            drawline();
            glPopMatrix();
        }
        //   }
        //  glPushMatrix();
        // glTranslatef(0.2f,1.8f,0.0f);
        //   glColor3f(0.2f,0.3f,1.2f);
        //     drawSpider(Spider_len);
        //       glPopMatrix();

        glPopMatrix();
        glutSwapBuffers();
    }
    else
    {
        drawGameOver();
        //sprintf(text2, "GAME OVER %d", Score);
        // glRasterPos3f(-0.5,0,0.0f);
        // for(int l=0;text2[l]!='\0';l++)
        //   glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, text2[l]);
    }
}

int ctr = 0;
int start = 0;
int fg=0;
int asd=0;
int t=0;
int golictr=0;
int golistart=0;

void update(int value)
{
    if(pauseflag==0)
    {
        // printf("rand");
        // a[i].y += a[i].vel_y;
        // printf("%f\n",a[i].y);
        if(ctr == 300 || start == 0)
        {
            i=j;
            a[i].x = myrand(-box_len/2+0.3f,box_len/2-0.3f);

            //printf("%f\n",a[i].x);
            a[i].y = box_width+0.3f;
            if(Score<=5)
            {
                a[i].vel_y = -0.01f;
                difficulty=1;
            }
            if(Score>=5&&Score<=10)
            {
                a[i].vel_y = myrand(-0.02f,-0.01f);
                difficulty=2;
            }
            if(Score>=10&&Score<=20)
            {
                a[i].vel_y = myrand(-0.03f,-0.02f);
                difficulty=3;
            }
            if(Score<=20&&Score>=30)
            {
                a[i].vel_y = myrand(-0.04f,-0.03f);
                difficulty=4;
            }
            if(Score>=30)
            {
                a[i].vel_y = myrand(-0.07f,-0.04f);
                difficulty=5;
            }
            a[i].scoreflag=0;
            float random = myrand(0.0f,6.0f);
            if(random<2.0f && random>=0.0f)
            {
                // printf("wow\n");
                a[i].r = 1.0f;
                a[i].g = 0.0f;

                a[i].b = 0.0f;
            }
            else if(random<4.0f && random>=2.0f)
            {
                a[i].r = 0.0f;
                a[i].g = 1.0f;
                a[i].b = 0.0f;
            }
            else if(random>=4.0f && random<=6.0f)
            {
                a[i].r = 0.0f;
                a[i].g = 0.0f;
                a[i].b = 0.0f;
            }
            if(i>=0)
                flag=1;
            j++;
            ctr = 0;
        }
        start++;
        ctr++;
        for(i=0;i<j;i++)
        {  
            a[i].y += a[i].vel_y;
        }
        for(i=0;i<j;i++)
        {
            if(a[i].y<=-box_width/2+0.2f)
                a[i].vel_y=0;
        }
        //   int f=0;

        if(goliflag==1)
        {
            if(golistart==0 || golictr==0)
            {
                system("aplay laser.wav &");
                asd=qwe;
                d[asd].theta=angle;
                d[asd].x = Cannon_x;
                d[asd].y = -box_width/2+0.3f;
                if(difficulty==1)
                {
                    d[asd].vel_y = 0.03f;
                    d[asd].vel_x =  0.03f;
                }
                if(difficulty==2)
                {
                    d[asd].vel_y=0.05f;
                    d[asd].vel_x=0.05f;
                }
                if(difficulty==3)
                {
                    d[asd].vel_y=0.07f;
                    d[asd].vel_x=0.07f;
                }
                if(difficulty==4)
                {
                    d[asd].vel_y=0.09f;
                    d[asd].vel_x=0.09f;
                }
                if(difficulty==5)
                {  d[asd].vel_y=0.12f;
                    d[asd].vel_x=0.12f;
                }
                qwe++;
            }
            golictr++;
            if(golictr==100)
            {
                golictr=0;
                goliflag=0;
            }
            golistart=1;

        }

        for(fg=0;fg<qwe;fg++)
        {
            d[fg].y +=0.04f*cos(DEG2RAD(d[fg].theta));
            d[fg].x -= 0.04f*sin(DEG2RAD(d[fg].theta));
            for(i=0;i<j;i++)
            {
                //  printf("%lf\n",d[fg].y);
                // printf("%lf\n",d[fg].x);
                if(((d[fg].y+0.15f*cos(DEG2RAD(d[fg].theta)))>=(a[i].y-0.25f)) && ((d[fg].y+0.15f*cos(DEG2RAD(d[fg].theta)))<=(a[i].y+0.2f))&& ((d[fg].x)>=(a[i].x-0.2f)) && ((d[fg].x)<=(a[i].x+0.2f)))
                {
                    if(a[i].vel_y!=0)
                    {
                        if(a[i].r==1.0f)
                        {
                            Score--;
                        }
                        else if(a[i].g==1.0f)
                        {
                            // printf("WHY\n");
                            Score--;
                        }
                        else
                        {
                            // printf("KYUN\n");
                            Score++;
                        }
                        a[i].x = myrand(-box_len/2+0.3f,box_len/2-0.3f);
                        a[i].y=-10.0f;
                        if(difficulty==1)
                            a[i].vel_y = -0.01f;
                        if(difficulty==2)
                            a[i].vel_y = myrand(-0.02f,-0.01f);
                        if(difficulty==3)
                            a[i].vel_y = myrand(-0.03f,-0.02f);
                        if(difficulty==4)
                            a[i].vel_y = myrand(-0.04f,-0.03f);
                        if(difficulty==5)
                            a[i].vel_y = myrand(-0.07f,-0.04f);
                        t=fg+1;
                        while(t<qwe)
                        {
                            d[t-1]=d[t];
                            t++;
                        }
                        qwe--;
                    }
                }
            }
            // printf("%lf\n",d[fg].x);
            if(d[fg].x>=box_len/2 || d[fg].x<=-box_len/2)
            {
                // printf("ladjasj");
                d[fg].theta= -d[fg].theta;
                d[fg].y +=0.04f*cos(DEG2RAD(d[fg].theta));
                d[fg].x -= 0.04f*sin(DEG2RAD(d[fg].theta));
                //   printf("%d\n",d[fg].theta);
            }
        }

        for(i=0;i<j;i++)
        {
            if(a[i].vel_y!=0)
            {
                // printf("Basket-->%lf\n",GreenBasket_x+Basket_len/2);
                //      printf("a[i].x->%lf\n",a[i].x);
                if((GreenBasket_x+Basket_len/2>=a[i].x-0.15f)&&(GreenBasket_x-Basket_len/2<=a[i].x+0.15f)&&(-box_width/2+0.8f>=a[i].y+0.2f)&&(RedBasket_x+Basket_len/2>=a[i].x-0.15f)&&(RedBasket_x-Basket_len/2<=a[i].x+0.15f))
                {
                    if(a[i].r==1.0f)
                        Score++;
                    else if(a[i].g==1.0f)
                        Score++;
                    else
                        Score--;
                    a[i].y=10.0f;
                }
                else if((GreenBasket_x+Basket_len/2>=a[i].x-0.15f)&&(GreenBasket_x-Basket_len/2<=a[i].x+0.15f)&&(-box_width/2+0.8f>=a[i].y+0.2f))
                {
                    //        printf("Gaya\n");
                    if(a[i].g==1.0f)
                        Score++;
                    else
                        Score--;
                    a[i].y=10.0f;
                }
                else if((RedBasket_x+Basket_len/2>=a[i].x-0.15f)&&(RedBasket_x-Basket_len/2<=a[i].x+0.15f)&&(-box_width/2+0.8f>=a[i].y+0.2f))
                {
                    if(a[i].r==1.0f)
                        Score++;
                    else
                        Score--;
                    a[i].y=10.0f;
                }
                // printf("Canno_X-->%lf\n",Cannon_x+Cannon_len/2);
                //  printf("a[%d].x%lf",i,a[i].x);
                //  printf("Cannon_x-->%lf\n",Cannon_x-Cannon_len);
                if((Cannon_x+Cannon_len>=a[i].x)&&(Cannon_x-Cannon_len<=a[i].x)&&(-box_width/2+0.8f>=a[i].y+0.2f))
                {
                    //    printf("aa jaa bhai\n");
                    GameOver=1;
                    FinalScore=Score;
                }
            }

        }
        for(i=0;i<j;i++)
        {   
            if(a[i].vel_y==0)
            {
                if(a[i].scoreflag==0)
                {
                    Score=Score-5;
                    a[i].scoreflag=1;
                }
                if(Cannon_x>a[i].x)
                {
                    if(a[i].x>=max1)
                        max1=a[i].x;
                    if(Cannon_x-Cannon_len/2<=max1+0.15f)
                        Cannon_x += 0.1f;
                }
                if(Cannon_x<a[i].x)
                {
                    if(a[i].x<=min1)
                        min1=a[i].x;
                    if(Cannon_x+Cannon_len/2>=min1-0.15f)
                        Cannon_x -= 0.1f;
                }
                if(RedBasket_x>a[i].x)
                {
                    if(a[i].x>=max2)
                        max2=a[i].x;
                    if(RedBasket_x-Basket_len/2<=max2+0.15f)
                        RedBasket_x += 0.1f;
                }
                if(RedBasket_x<a[i].x)
                {
                    if(a[i].x<=min2)
                        min2=a[i].x;
                    if(RedBasket_x+Basket_len/2>=min2-0.15f)
                        RedBasket_x -= 0.1f;
                }
                if(GreenBasket_x>a[i].x)
                {
                    if(a[i].x>=max3)
                        max3=a[i].x;
                    if(GreenBasket_x-Basket_len/2<=max3+0.15f)
                        GreenBasket_x += 0.1f;
                }
                if(GreenBasket_x<a[i].x)
                {
                    if(a[i].x<=min3)
                        min3=a[i].x;
                    if(GreenBasket_x+Basket_len/2>=min3-0.15f)
                        GreenBasket_x -= 0.1f;
                }
            }}




        t=0;
        while(t<qwe)
        {

            if(d[t].y>=box_width/2+0.3f)
            {

                for(fg=t+1;fg<qwe;fg++)
                    d[fg-1]=d[fg];
                qwe--;

            }
            t++;
        }

    }
    glutTimerFunc(10,update,0);

}

void drawBox(float len,float width)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -width / 2);
    glVertex2f(len / 2, -width / 2);
    glVertex2f(len / 2, width / 2);
    glVertex2f(-len / 2, width / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawSpider(float Spider_len)
{
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(Spider_len *0.2 * cos(DEG2RAD(o)),Spider_len *0.4* sin(DEG2RAD(o)));
    glEnd();
    glPushMatrix();
    glTranslatef(Spider_len*0.2,Spider_len*0.1,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.05f,0.00f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.05f,0.00f);
    glVertex2f(0.07f,0.08f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(Spider_len*0.2,Spider_len*-0.1,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.05f,0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.05f,0.0f);
    glVertex2f(0.07f,-0.08f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-Spider_len*0.2,Spider_len*0.1,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(-0.05f,0.00f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.05f,0.00f);
    glVertex2f(-0.07f,0.08f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-Spider_len*0.2,-Spider_len*0.1,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(-0.05f,0.00f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.05f,0.00f);
    glVertex2f(-0.07f,-0.08f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.03,Spider_len*0.30,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.05f,0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.05f,0.06f);
    glVertex2f(0.053f,0.10f);
    glEnd();
    glTranslatef(-0.07,Spider_len*0.0,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(-0.05f,0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.05f,0.06f);
    glVertex2f(-0.047f,0.10f);
    glEnd();
    glTranslatef(-0.00f,-Spider_len*0.60,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(-0.05f,-0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(-0.05f,-0.06f);
    glVertex2f(-0.053f,-0.10f);
    glEnd();
    glTranslatef(0.07f,-Spider_len*0.0,0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.05f,-0.06f);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.05f,-0.06f);
    glVertex2f(0.053f,-0.10f);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glBegin(GL_QUADS);
    // glVertex2f(-Spider_len/2, -Spider_len/2);
    // glVertex2f(Spider_len/2, -Spider_len/2);
    // glVertex2f(Spider_len/2, Spider_len/2);
    // glVertex2f(-Spider_len/2, Spider_len/2);
    // glEnd();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawline()
{
    glBegin(GL_LINES);
    glVertex2f(0.0f,0.0f);
    glVertex2f(0.0f,0.2f);
    glEnd();
}
void drawBasket(float Basket_len,float rad)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(-Basket_len/2,-Basket_len/2);
    glVertex2f(Basket_len/2,-Basket_len/2);
    glVertex2f(Basket_len/2,Basket_len/2);
    glVertex2f(-Basket_len/2,Basket_len/2);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f,Basket_len/2,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad  * cos(DEG2RAD(o)),rad *0.25* sin(DEG2RAD(o)));
    glEnd();
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad/2 * cos(DEG2RAD(o)), rad/2* 0.25 * sin(DEG2RAD(o)));
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,-Basket_len/2,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad * cos(DEG2RAD(o)),rad * 0.25* sin(DEG2RAD(o)));
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void drawBasketOutline(float Basket_len,float rad)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-Basket_len/2,-Basket_len/2);
    glVertex2f(Basket_len/2,-Basket_len/2);
    glVertex2f(Basket_len/2,Basket_len/2);
    glVertex2f(-Basket_len/2,Basket_len/2);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f,Basket_len/2,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad  * cos(DEG2RAD(o)),rad *0.25* sin(DEG2RAD(o)));
    glEnd();
    glPushMatrix();
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad/2 * cos(DEG2RAD(o)), rad/2* 0.25 * sin(DEG2RAD(o)));
    glEnd();
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f,-Basket_len/2,0.0f);
    glBegin(GL_TRIANGLE_FAN);
    for(int o=0;o<360;o++)
        glVertex2f(rad * cos(DEG2RAD(o)),rad * 0.25* sin(DEG2RAD(o)));
    glEnd();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}






void drawCannon(float Cannon_len)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(-Cannon_len/2,-Cannon_len/2);
    glVertex2f(Cannon_len/2,-Cannon_len/2);
    glVertex2f(Cannon_len/2,Cannon_len/2);
    glVertex2f(-Cannon_len/2,Cannon_len/2);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f,Cannon_len/2,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-Cannon_len/4,-Cannon_len/4);
    glVertex2f(Cannon_len/4,-Cannon_len/4);
    glVertex2f(Cannon_len/4,Cannon_len/4);
    glVertex2f(-Cannon_len/4,Cannon_len/4);
    glEnd();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void drawCannonOutline(float Cannon_len)
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-Cannon_len/2,-Cannon_len/2);
    glVertex2f(Cannon_len/2,-Cannon_len/2);
    glVertex2f(Cannon_len/2,Cannon_len/2);
    glVertex2f(-Cannon_len/2,Cannon_len/2);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0f,Cannon_len/2,0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-Cannon_len/4,-Cannon_len/4);
    glVertex2f(Cannon_len/4,-Cannon_len/4);
    glVertex2f(Cannon_len/4,Cannon_len/4);
    glVertex2f(-Cannon_len/4,Cannon_len/4);
    glEnd();
    glPopMatrix();
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}




void initrendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.4f, 0.6f, 1.0f, 0.5f);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);;
    glLoadIdentity();
    gluPerspective(45.0f, (float)w/(float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handlekeypress1(unsigned char key, int x, int y)
{
    if(pauseflag==0)
    {
        if(key==27)
            exit(0);
        if(key==114 || key==82)
            Basketflag=5;
        if(key==71 || key==103)
            Basketflag=10;
        if(key==66 || key==98)
            Basketflag=15;
        if(key==' ')
        {

            goliflag=1;
        }
    }
    if(key=='p' || key=='P')
    {
        //    printf("gya\n");
        pausectr++;
        if(pausectr%2!=0)
        {
            //          printf("yaar\n");
            pauseflag=1;
        }
        else
            pauseflag=0;
    }
    if(key=='q' || key=='Q')
        exit(0);
}

void handlekeypress2(int key2, int x, int y)
{
    //    float max=-44;
    //  float min=100;
    if(pauseflag==0)
    {
        if(Basketflag==5)
        {

            if(key2==GLUT_KEY_LEFT)
            {
                if(RedBasket_x >=-box_len/2+0.45f)
                {
                    RedBasket_x -= 0.1f;
                }
            }
            if(key2==GLUT_KEY_RIGHT)
            {
                if(RedBasket_x <= box_len/2-0.45f)
                    RedBasket_x += 0.1f;
            }
        }
        if(Basketflag==10)
        {
            if(key2==GLUT_KEY_LEFT)
            {
                if(GreenBasket_x >= -box_len/2+0.45f)
                    GreenBasket_x -= 0.1f;
            }
            if(key2==GLUT_KEY_RIGHT)
            {
                if(GreenBasket_x <= box_len/2-0.45f)
                    GreenBasket_x += 0.1f;
            }
        }
        if(Basketflag==15)
        {
            if(key2==GLUT_KEY_LEFT)
            {
                if(Cannon_x >=-box_len/2+0.3f)
                    Cannon_x -= 0.1f;


            }

            if(key2==GLUT_KEY_RIGHT)
            {
                if(Cannon_x <=box_len/2-0.3f)
                    Cannon_x += 0.1f;

            }
            if(key2==GLUT_KEY_UP)
            {
                if(angle<70)
                    angle += 10;
            }
            if(key2==GLUT_KEY_DOWN)
            {
                if(angle>-70)
                    angle-=10;
            }

        }
    }
}


void GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    mouseposx=posX*100/2;
    mouseposy=(posY*100)/2;
}




void handleMouseclick(int button, int state, int x, int y)  
{

    GetOGLPos(x,y);
    mousex=mouseposx;
    mousey=mouseposy;
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            //cout<<x<<":"<<mousex<<": "<<can_x<<"\n";
            if(distance(mousex,mousey,Cannon_x,Cannon_y)<0.2)
            {
                togcan=1;
                toggreen=0;
                togred=0;
                rotcan=0;

            }
            else if(distance(mousex,mousey,GreenBasket_x,Cannon_len+Cannon_y)<0.2)
            {
                togcan=0;
                toggreen=1;
                togred=0;
                rotcan=0;
            }
            else if(distance(mousex,mousey,RedBasket_x,Cannon_len+Cannon_y)<0.2)
            {
                togcan=0;
                toggreen=0;
                togred=1;
                rotcan=0;
            }
            else
            {
                togcan=0;
                toggreen=0;
                togred=0;
                rotcan=0;
            }

            //  cout<<"hi\n";
        }
        if(button == GLUT_RIGHT_BUTTON)
        {
            togcan=0;
            toggreen=0;
            togred=0;
            if(distance(mousex,mousey,Cannon_x,Cannon_y)<0.5)
            {
                rotcan=1;
            }
            else
                rotcan=0;
        }
        //cout<<"x: "<<mousex<<"can_x: "<<can_x<<"\n";
        //else if (button == GLUT_RIGHT_BUTTON)
        //           cout<<"y: "<<mousey<<"\n";
    }
   // printf("%f %f %f %f %f\n",mousex,mousey,mouseposx,mouseposy,distance(mousex,mousey,Cannon_x,Cannon_y));
    //cout<<togcan<<rotcan<<togred<<toggreen<<"\n";
    glutPostRedisplay();
}

float drag(float position)//,float lefy,float rify)
{
    float  move;
    if(distance(mousex,mousey,position,Cannon_y)<0.7)
    {   
        move=(2*(mousex-position));
        if(move>0)
        {   
                position+=(move*0.3);
        }   
        else if(move<0)
        {   
                position+=(move*0.3);
        }   
    }   
    return position;
}

void dragwithmouse(int x,int y)
{
    GetOGLPos(x,y);
    mousex=mouseposx;
    mousey=mouseposy;
    if(togred==1)
    {
        RedBasket_x=drag(RedBasket_x);//,min2,max2);
    }
    else if(toggreen==1)
    {
        GreenBasket_x=drag(GreenBasket_x);//,min3,max3);
    }
    else if(togcan)
    {
        Cannon_x=drag(Cannon_x);//,min1,max1);

    }
    if(rotcan && distance(mousex,mousey,Cannon_x,Cannon_y)<0.8)
    {
        if (Cannon_x - mousex > 0)
        {
            if (angle <= 70)
                angle += 3;
        }
        else 
        {   
            if (angle >= -70)
                angle -= 3;
        }

        /*
           if(can_x-mousex>0)
           {
           if(angle + DEG2RAD(7)<DEG2RAD(180))
           angle += DEG2RAD(7);
           }
           else
           if(angle - DEG2RAD(7)>DEG2RAD(0))
           angle -= DEG2RAD(7);
           */
    }

}










