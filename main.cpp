#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <stack>
#include <queue>

GLint screen1=0,screen2=0,screen3=0;

#include<string.h>

void *currentfont;

#define size 5
#define MAX 10

int enter;
static int itemno=0;
class button
{
    int x1,y1,x2,y2;
    int state;
    char str[10];

public:
    button(){}
    button(int x11,int y11,int x22,int y22,char *str1)
    {
        x1=x11;
        y1=y11;
        x2=x22;
        y2=y22;
        state=1;
        strcpy(str,str1);
    }
    void draw();
    void togglestate();
    int insidebutton(int x,int y);
};
class stack
{
button s[size];
int top;

public:
stack()
{
    top=-1;
}
int stfull();
button pop();
void push(int item);
int stempty();
void displaystack();
};
stack st;
class queue
{
button que[MAX];
int front,rear;
public:
queue()
{
    front=-1;
    rear=-1;
}
void displayqueue();
void insert_element();
void delete_element();
};
queue q;




void myinit(void)
{
  
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,0,600);
    glMatrixMode(GL_MODELVIEW);
  
}


void setFont(void *font)
{
    currentfont=font;
}
void drawstring(float x,float y,char *string)
{
        char *c;
    glRasterPos2f(x,y);

    for(c=string;*c!='\0';c++)
    {    glColor3f(0.0,0.0,0.0);
        glutBitmapCharacter(currentfont,*c);
    }
}
void button::draw()
{
    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
        drawstring(x1+10,y1+10,str);
    glColor3f(0.2,0.2,0.8);
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
    if(state==0)
    {
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glEnd();
    }
    else if(state==1)
    {
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x1,y2);
        glVertex2f(x1,y2);
        glVertex2f(x2,y2);
        glEnd();
    }
}
void button::togglestate(void)
{
    /*if(state==1)
        state=0;
    else if(state==0)
        state=1;*/
    state=(state==1)?0:1;
}
int button::insidebutton(int x,int y)
{
    if(x>x1&&x<x2&&y>y1&&y<y2)
        return 1;
    else return 0;
}
button btn1(100,100,175,150,"Push");
button btn2(200,100,275,150,"Pop");
button btn3(300,100,375,150,"Insert");
button btn4(400,100,475,150,"Delete");

//
// Stack functions start
//
int stack::stfull() {
if (st.top >= size-1)
    return 1;
else
    return 0;
}

void stack::push(int item) {
    char str[10];
    snprintf(str, sizeof(str), "%d", item);
button btn(100,250+st.top*50,150,300+st.top*50,str);
    st.top++;

st.s[st.top] = btn;

}

int stack::stempty() {
if (st.top == -1)
    return 1;
else
    return 0;
}

button stack::pop() {
button item;
item = st.s[st.top];
st.top--;

return (item);
}

void stack::displaystack() {
int i;
if (st.stempty())
    drawstring(10,10,"Stack Is Empty!");
else {
    for (i = st.top; i >= 0; i--)
        st.s[i].draw();
}
}


void queue::insert_element()
{
static int num=0;
char str[10];
    snprintf(str, sizeof(str), "%d", num++);
    button btn(300,250+rear*50,350,300+rear*50,str);
if(front==0 && rear==MAX-1)
    drawstring(10,10," Queue OverFlow Occured");
else if(front==-1&&rear==-1)
{
    front=rear=0;
    que[rear]=btn;

}
else if(rear==MAX-1 && front!=0)
{
    rear=0;
    que[rear]=btn;
}
else
{
    rear++;
    que[rear]=btn;
}
}
void queue::delete_element()
{
button element;
if(front==-1)
{
    drawstring(300,10," Underflow                 ");
}
element=que[front];
if(front==rear)
    front=rear=-1;
else
{
    if(front==MAX-1)
    front=0;
    else
    front++;
}

}

void queue::displayqueue()
{
    int i;
    if(front==-1)
    drawstring(300,10," No elements to display in queue");
    else
    {
    for(i=front;i<=rear;i++)
    {
        que[i].draw();
    }
    }
}


void displaystacknqueue()
{
    st.displaystack();
    q.displayqueue();
}

void display()
{
    
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    btn1.draw();
    btn2.draw();
    btn3.draw();
    btn4.draw();
    displaystacknqueue();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,600,0,600);
    glMatrixMode(GL_MODELVIEW);

}
void idle()
{
    glutPostRedisplay();
}


void Mainoptions(int id)
{

    switch(id){
                case 1:glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                //wait(200);
                break;
            case 2: glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;

            case 3:exit(0);

    }
}
void stackoption(int id)
{
    switch(id){
        case 1: if(!st.stfull())
            st.push(itemno++);
                break;
        case 2: st.pop();
                break;
            }
}
void queueoptions(int id)
{
    switch(id)
    {
    case 1: q.insert_element();
            break;
    case 2: q.delete_element();
            break;
    }
}



void create_menu(void)
{
    int sub1, sub2;
    glutCreateMenu(Mainoptions);
    sub1 = glutCreateMenu(stackoption);

        glutAddMenuEntry("PUSH",1);
        glutAddMenuEntry("POP",2);

    sub2 = glutCreateMenu(queueoptions);

        glutAddMenuEntry("Insert",1);
        glutAddMenuEntry("Delete",2);

    glutAddSubMenu("Stack",sub1);
    glutAddSubMenu("Queue",sub2);
    glutAddMenuEntry("Exit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void display_main(){
    screen1=1;
    glClearColor(0.121093,0.121093,0.140625,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1,1,1);
    setFont(GLUT_BITMAP_HELVETICA_12);
    drawstring(260, 500, "CGV Mini Project");
    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(0, 0.9960,0.9375);
    drawstring(230, 460, "Stack and Queue Operations");
    glColor3f(0.99609, 0.98046, 0);
    drawstring(260, 420, "Submitted by:");
    glColor3f(0, 1, 0.803);
drawstring(100, 380, "NISHANTH Y (1BY20CS126)    NITHIN R SWAMY (1BY20CS129)   PRAJWAL N (1BY20CS135)");
    glColor3f(0, 1, 0);
drawstring(260, 340, "Project Guides: ");
    glColor3f(0, 1, 0);
    drawstring(220, 300, "Dr. Sunanda Dixit, Prof. Shankar R");
    glColor3f(0,0.46875,0.99609);
    drawstring(260, 260, "BMSIT&M");
    glColor3f(0,1,0);
drawstring(220, 220, "Press Enter to Continue");
    glColor3f(1,0,0);
drawstring(220, 190, "Press ESC to Quit");
    
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
      case 'P':
      case 'p':
          if(!st.stfull())
              st.push(itemno++);break;
      case 'o':
      case 'O':
          st.pop();break;
      case 'i':
      case 'I':
          q.insert_element();break;
      case 'd':
      case 'D':
          q.delete_element();break;
      case 13:
          if((screen1==1)){
                glutDisplayFunc(display);
                glutPostRedisplay();
          }
          break;

      case 27:
            exit(1);break;

      case 8:
        if(screen2==1){
            glutDisplayFunc(display_main);
            glutPostRedisplay();
        }
        
      default:
        return;
  }
  glutPostRedisplay();
}



int main(int argc, char **argv)
{
int sub1,sub2;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(1080, 600);
glutCreateWindow("STACK AND QUEUE");
glutDisplayFunc(display_main);
glutKeyboardFunc(keyboard);

sub1 = glutCreateMenu(stackoption);

    glutAddMenuEntry("PUSH",1);
    glutAddMenuEntry("POP",2);

sub2 = glutCreateMenu(queueoptions);

    glutAddMenuEntry("Insert",1);
    glutAddMenuEntry("Delete",2);

glutCreateMenu(Mainoptions);
glutAddSubMenu("Stack",sub1);
glutAddSubMenu("Queue",sub2);
glutAddMenuEntry("Exit",3);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutIdleFunc(idle);
glEnable(GL_DEPTH_TEST);
init();
glutMainLoop();
return 0;
}


