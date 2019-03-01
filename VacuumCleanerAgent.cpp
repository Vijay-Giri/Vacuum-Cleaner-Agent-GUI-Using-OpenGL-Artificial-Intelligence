#include<bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glut.h>

using namespace std;

vector<int>path;    //This vector stores the path of the vaccuum cleaner
vector<int>rev;
vector<pair<double,double>>dirt_loc[100];    // This vector stores the position of dirt
vector<bool> dirt_clean[100];         //This vector store whether it is clean or not. It stores only true or false
int dirty_pos[100];   //This array stores the dirty positions
double step = 10;     //variable storing no of steps
char str[1000];
double scale = 1.2;

struct point    //This structure stores the x and y coordinates
{
double x;
double y;
};
int i,j;
  
vector<int>order;  //order of movement of cleaner

int n,m;  // n is no of columns and m is no of rows

void drawFilledCircle(GLdouble x, GLdouble y, GLdouble radius);  //this creates small circles which represents dirt
double win_w=600, win_h=600;   //size of display window


double pan_x = 0.0;  
double pan_y = 0.0;
double zoom_k = 200.0;
int h[10000];



double x_c=1;    //initial position of vaccuum cleaner
double y_c=1;


vector<int>Step[100];   //this vector stores the position of cleaner 


void dirt()   //this function is responsible for making dirt wherever mouse is clicked
{


for(int i=0;i<n*n;i++)
for(int j=0;j<dirt_loc[i].size();j++){
int pp1;
glColor3f(1,1,1);

if(dirt_clean[i][j])
drawFilledCircle((dirt_loc[i][j].first)/200.0,dirt_loc[i][j].second/200.0,0.01);


}}

int cnt=0;

int stepp=0;
void nxt(int value){






if(dirt_loc[path[stepp%(path.size())]].size()<=cnt)
	{
		str[path[stepp%(path.size())]]='1';
		x_c=path[stepp%path.size()]/m-0.5+1;
y_c=path[stepp%path.size()]%m -0.5+1;
	if(cnt==0){
//move left or right according to square position
	cout<<" "<<str<<endl;}
	else{
	cout<<str<<endl;}
	stepp=(stepp+1)%path.size();
	cnt=0;
	dirty_pos[path[stepp%path.size()]]=0;
//dirt_loc[path[stepp%path.size()]].clear();	
		
	}
	else if(dirt_clean[path[stepp%path.size()]][cnt]){
//clean dirt
x_c=dirt_loc[path[stepp%path.size()]][cnt].first/200.0;
 y_c=dirt_loc[path[stepp%path.size()]][cnt].second/200.0;
//cout<<dirt_loc[path[stepp%path.size()]][cnt].first/200.0<<" ";
dirt_clean[path[stepp%path.size()]][cnt]=false;
		cnt++;}
else{
//search dirt in current square

x_c=path[stepp%path.size()]/m-0.5+1;
y_c=path[stepp%path.size()]%m -0.5+1;
cnt++;


}
		
		





glutPostRedisplay();
glutTimerFunc(900,nxt,0);






}

//-----------







void init(int n,int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(i&1)
			path.push_back(i*m+m-j-1);
			else
			path.push_back(i*m+j);
			str[m*i+j]='1';
		}
		
	}
	for(int i=n-2;i>=0;i--){
		path.push_back(m*i+m-1);
	}
	for(int j=m-2;j>0;j--)
        path.push_back(j);
}

int idx=0;













void drawFilledCircle(GLdouble x, GLdouble y, GLdouble radius){
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	double PI=3.14;
	//GLdouble radius = 0.8f; //radius
	GLdouble twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}


void draw_S(int i,int j){

if(0)
glColor3f(0,0,0);
else if(i==0&& j==0)
glColor3f(0,1,1);
else{
if(i%2){
if(j%2)
glColor3f(0,1,0);
else
glColor3f(1,0,0);}
else{



if(j%2)
glColor3f(1,0,0);
else
glColor3f(0,1,0);


}

}
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glBegin(GL_POLYGON);
glVertex2i(i,j);

glVertex2i(i,j-1);
glVertex2i(i-1,j-1);
glVertex2i(i-1,j);
glEnd();






}

void draw_object(void)
{

    
for(int i=1;i<=n;i++)
for( int j=1;j<=m;j++){
draw_S(i,j);
}glColor3f(1,1,1);

drawFilledCircle(x_c,y_c,0.1);
glColor3f(0,0,0);
//drawFilledCircle(xx_c,yy_c,0.03);

glColor3f(1,1,0);
dirt();

 






}

void zoom(double factor)
{
    zoom_k *= factor;
}

void pan(double dx, double dy)
{
    pan_x += dx / zoom_k;
    pan_y += dy / zoom_k;
}

void zoom_at(double x, double y, double factor)
{
    pan(-x, -y);
    zoom(factor);
    pan(x, y);
}






void key(unsigned char key, int x, int y)
{
    if (key == 's')
glutTimerFunc(900,nxt,0);
if(key=='s'){

glutPostRedisplay();

}
if(key=='c'){

for(int i=0;i<n*n;i++)
dirt_loc[i].clear();

}
        
}

void special(int k, int x, int y)
{
     if (k == GLUT_KEY_LEFT)
        pan(-step, 0);
    else if (k == GLUT_KEY_RIGHT)
        pan( step, 0);
    else if (k == GLUT_KEY_DOWN)
        pan(0, -step);
    else if (k == GLUT_KEY_UP)
        pan(0, step);

    glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{

    if (s != GLUT_DOWN)
        return;

    y = win_h - 1 - y;

    if (b == GLUT_LEFT_BUTTON)
;
//zoom_at(x, y, scale);
    else if (b == GLUT_RIGHT_BUTTON)



        zoom_at(x, y, 1/scale);
dirt_loc[m*(x/200) + (y/200)].push_back(make_pair(x,y));
int idxx=m*(x/200) + (y/200);
str[idxx]='0';
cout<<str<<endl;
dirt_clean[idxx].push_back(true);
dirty_pos[idxx]++;;
//cout<<m*(x/200) + (y/200)<<endl;

    glutPostRedisplay();
}

void draw(void)
{
    glClearColor(0.5, 0.5, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom_k, zoom_k, 1);
    glTranslatef(pan_x, pan_y, 0);

   draw_object();

    glutSwapBuffers();
}

void resize(int w, int h)
{
    if (h == 0)
        h = 1;

    win_w = w;
    win_h = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.0, 1.0, 1.0);

    draw();
  //  glutSwapBuffers();
}
int main(int argc,char **argv)
{

	
	
	cin>>n>>m;
	init(n,m);


int x_,y_;
x_c=x_-0.5;
y_c=y_-0.5;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600,600);
    glutCreateWindow("Vaccuum Cleaner");

    glutDisplayFunc(display);
    glutIdleFunc(display);

      glutReshapeFunc(resize);
      glutKeyboardFunc(key);
      glutSpecialFunc(special);
      glutMouseFunc(mouse);

  
    glutMainLoop();
   return 0;
}
