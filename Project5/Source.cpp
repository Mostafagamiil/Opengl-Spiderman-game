#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sstream>


float mposx_speed = 10;
float mposx = 200;
float mposy = 70;
float mposy_speed = 10;

float webposx = 700;
float webposy = 0;
bool webShoot = false;
float webSpeed = 0.8;

float web2posx = 700;
float web2posy = 0;
bool web2Shoot = false;
float web2Speed = 0.8;
char Mostafa;
double enemyX = 0, enemyY = 380, enemyHealth = 100, enemyWIDTH = 35, enemyHEIGHT = 20;
double enemyRotation = -15;
double enemyShotX = 100, enemyShotY = -100;
void idleCallback(void);

bool hit = false;
bool hit2 = false;
double bg1Y = 0;
double bg2Y = 0;
double bg1Points[30][2];
double bg2Points[30][2];
int gameScore = 0;
bool gameOver = false;
int newgamescore;
int p0[2] = { 30, 380 };
int p1[2];
int p2[2];
int p3[2] = { 550, 380 };
float t = 0;
#define ROUNDF(f, c) (((float)((int)((f) * (c))) / (c)))

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int* res = (int*)(malloc(sizeof(int) * 2));
	res[0] = pow((1 - t), 3) * p0[0] + 3 * t * pow((1 - t), 2) * p1[0] + 3 * pow(t, 2) * (1 - t) * p2[0] + pow(t, 3) * p3[0];
	res[1] = pow((1 - t), 3) * p0[1] + 3 * t * pow((1 - t), 2) * p1[1] + 3 * pow(t, 2) * (1 - t) * p2[1] + pow(t, 3) * p3[1];
	return res;
}
void resetGame()
{
	gameOver = false;
	gameScore = 0;
	bg1Y = 0;
	bg2Y = 0;
	hit = false;
	hit2 = false;
}

void writeToScreen(std::string text, float x, float y, float r, float g, float b)
{
	glColor3f(r, g, b);
	glRasterPos3f(x, y, 0);
	for (int i = 0; i < text.length(); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}
void VenomRedShoe(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1765, 30);
	glVertex2i(1690, 30);
	glVertex2i(1690, 60);
	glVertex2i(1700, 60);
	glVertex2i(1700, 70);
	glVertex2i(1765, 70);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1800, 30);
	glVertex2i(1875, 30);
	glVertex2i(1875, 60);
	glVertex2i(1865, 60);
	glVertex2i(1865, 70);
	glVertex2i(1800, 70);
	glEnd();
}
void VenomRightleg(void)
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1700, 170);
	glVertex2i(1700, 70);
	glVertex2i(1765, 70);
	glVertex2i(1765, 135);
	glVertex2i(1800, 135);
	glVertex2i(1800, 170);
	glEnd();
}
void VenomLeftleg(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1800, 70);
	glVertex2i(1800, 170);
	glVertex2i(1865, 170);
	glVertex2i(1865, 70);
	glEnd();
}
void VenomLeftHand(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1700, 168);
	glVertex2i(1650, 168);
	glVertex2i(1650, 210);
	glVertex2i(1700, 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1650, 210);
	glVertex2i(1700, 210);
	glVertex2i(1700, 285);
	glVertex2i(1650, 270);
	glEnd();
}
void VenomRightHand(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1865, 165);
	glVertex2i(1910, 165);
	glVertex2i(1910, 210);
	glVertex2i(1865, 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1910, 210);
	glVertex2i(1865, 210);
	glVertex2i(1865, 285);
	glVertex2i(1910, 270);
	glEnd();
}
void VenomBody(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1740, 300);
	glVertex2i(1830, 300);
	glVertex2i(1865, 285);
	glVertex2i(1865, 170);
	glVertex2i(1700, 170);
	glVertex2i(1700, 285);
	glEnd();


}
void VenomLeftEye(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1720, 330);
	glVertex2i(1720, 380);
	glVertex2i(1765, 345);
	glVertex2i(1765, 330);
	glVertex2i(1720, 330);
	glEnd();
}
void VenomRightEye(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(1805, 330);
	glVertex2i(1850, 330);
	glVertex2i(1850, 380);
	glVertex2i(1805, 345);
	glVertex2i(1805, 330);
	glEnd();
}
void VenomHead(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i(1740, 300);
	glVertex2i(1830, 300);
	glVertex2i(1875, 330);
	glVertex2i(1875, 390);
	glVertex2i(1835, 410);
	glVertex2i(1745, 410);
	glVertex2i(1695, 390);
	glVertex2i(1695, 330);
	glVertex2i(1740, 300);
	glEnd();
}
void Venom()
{

	glPushMatrix();
	glTranslatef(-0.9f, -0.7f, 0.0f);
	glScalef(0.25f, 0.25f, 1.0f);
	VenomBody();
	VenomHead();
	VenomRedShoe();
	VenomLeftHand();
	VenomRightHand();
	VenomRightEye();
	VenomLeftEye();
	VenomRightleg();
	VenomLeftleg();
	glPopMatrix();

}
void dropTheBall() 
{
	enemyShotX = enemyX;
	enemyShotY = enemyY;
}





void drawRedShoe(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(245, 30);
	glVertex2i(170, 30);
	glVertex2i(170, 60);
	glVertex2i(180, 60);
	glVertex2i(180, 70);
	glVertex2i(245, 70);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(280, 30);
	glVertex2i(355, 30);
	glVertex2i(355, 60);
	glVertex2i(345, 60);
	glVertex2i(345, 70);
	glVertex2i(280, 70);
	glEnd();
}
void drawRightleg(void)
{

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(180, 170);
	glVertex2i(180, 70);
	glVertex2i(245, 70);
	glVertex2i(245, 135);
	glVertex2i(280, 135);
	glVertex2i(280, 170);
	glEnd();
}
void drawLeftleg(void)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(280, 70);
	glVertex2i(280, 170);
	glVertex2i(345, 170);
	glVertex2i(345, 70);
	glEnd();
}
void drawLeftHand(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(180, 168);
	glVertex2i(130, 168);
	glVertex2i(130, 210);
	glVertex2i(180, 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(130, 210);
	glVertex2i(180, 210);
	glVertex2i(180, 285);
	glVertex2i(130, 270);
	glEnd();
}
void drawRightHand(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(345, 165);
	glVertex2i(390, 165);
	glVertex2i(390, 210);
	glVertex2i(345, 210);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(390, 210);
	glVertex2i(345, 210);
	glVertex2i(345, 285);
	glVertex2i(395, 270);
	glEnd();
}
void drawBody(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(220, 300);
	glVertex2i(310, 300);
	glVertex2i(345, 285);
	glVertex2i(345, 170);
	glVertex2i(180, 170);
	glVertex2i(180, 285);
	glEnd();


}
void drawLeftEye(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(200, 330);
	glVertex2i(200, 380);
	glVertex2i(245, 345);
	glVertex2i(245, 330);
	glVertex2i(200, 330);
	glEnd();
}
void drawRightEye(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(285, 330);
	glVertex2i(330, 330);
	glVertex2i(330, 380);
	glVertex2i(285, 345);
	glVertex2i(285, 330);
	glEnd();
}
void drawHead(void)
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(220, 300);
	glVertex2i(310, 300);
	glVertex2i(355, 330);
	glVertex2i(355, 390);
	glVertex2i(315, 410);
	glVertex2i(225, 410);
	glVertex2i(175, 390);
	glVertex2i(175, 330);
	glVertex2i(220, 300);
	glEnd();
}
void man()
{
	glPushMatrix();
	glTranslatef(-0.9f, -0.7f, 0.0f);
	glScalef(0.25f, 0.25f, 1.0f);
	drawBody();
	drawHead();
	drawRedShoe();
	drawLeftHand();
	drawRightHand();
	drawRightEye();
	drawLeftEye();
	drawRightleg();
	drawLeftleg();
	glPopMatrix();

}

void web()
{
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(45, 60);
	glVertex2i(45, 90);
	glEnd();
}
void web2()
{
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(60, 45);
	glVertex2i(90, 45);
	glEnd();
}
void Spiderkey(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W') {
		mposy += mposy_speed;
	}
	if (key == 's' || key == 'S') {
		mposy -= mposy_speed;
	}
	if (key == 'a' || key == 'A') {
		mposx -= mposx_speed;
	}
	if (key == 'd' || key == 'D') {
		mposx += mposx_speed;
	}
	if (key == 32) {
		webShoot = true;
		webposx = mposx;
		webposy = mposy;
	}
	if (key == 81) {
		web2Shoot = true;
		web2posx = mposx;
		web2posy = mposy;
	}
	glutPostRedisplay();
}
void Spiderspecial(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) {
		mposy += mposy_speed;
	}
	if (key == GLUT_KEY_DOWN) {
		mposy -= mposy_speed;
	}
	if (key == GLUT_KEY_RIGHT) {
		mposx += mposx_speed;
	}
	if (key == GLUT_KEY_LEFT) {
		mposx -= mposx_speed;
	}
	glutPostRedisplay();

}
void generateBG1Points()
{
	for (int i = 0; i < 30; i++)
	{
		bg1Points[i][0] = rand() % 1000;
		bg1Points[i][1] = rand() % 1000;
	}
}
void generateBG2Points()
{
	for (int i = 0; i < 30; i++)
	{
		bg2Points[i][0] = rand() % 1000;
		bg2Points[i][1] = rand() % 1000;
	}
}
void drawBackground()
{
	glPushMatrix();

	glPushMatrix();
	glTranslated(0, bg1Y, 0);
	glColor3f(0.16, 0.11, 0.24);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(800, 0);
	glVertex2f(800, 501);
	glVertex2f(0, 501);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, bg2Y, 0);
	glColor3f(0.16, 0.11, 0.24);
	glBegin(GL_QUADS);
	glVertex2f(0, -500);
	glVertex2f(800, -500);
	glVertex2f(800, 0);
	glVertex2f(0, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glPointSize(3);
	glTranslated(0, bg1Y, 0);
	glBegin(GL_POINTS);
	glColor3f(0.65, 0.65, 0.65);
	for (int i = 0; i < 30; i++)
	{
		glVertex2f(bg1Points[i][0], bg1Points[i][1]);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, bg2Y, 0);
	glBegin(GL_POINTS);
	glColor3f(0.65, 0.65, 0.65);
	for (int i = 0; i < 30; i++)
	{
		glVertex2f(bg2Points[i][0], bg2Points[i][1]);
	}
	glEnd();
	glPopMatrix();
	glPushMatrix();

	if (bg1Y >= 500)
	{
		bg1Y = -500;
		generateBG1Points();
	}
	else
		bg1Y += 0.1;

	if (bg2Y >= 1000)
	{
		bg2Y = 0;
		generateBG2Points();
	}
	else
		bg2Y += 0.1;
	glPopMatrix();

	glPopMatrix();
}
void drawScore()
{
	glPushMatrix();
	std::ostringstream tmp;
	tmp << gameScore;
	writeToScreen("Current score: " + tmp.str(), 10, 430, 1, 1, 1);
	glPopMatrix();
}
void drawEnemy()
{
	if (enemyY < -50) 
		writeToScreen("Nice job, wait for it ...", 170, 250, 1, 1, 1);
	glPushMatrix();

	glTranslatef(enemyX, enemyY, 0);
	glRotatef(enemyRotation, 0, 0, 1);
	glTranslatef(-enemyX, -enemyY, 0);
	glColor3f(1, 0, 0);


	glPushMatrix();
	glTranslated(enemyX, enemyY, 0);
	glPushMatrix();
	glScalef(35, 10, 1);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();


	glPushMatrix();
	glScalef(3, 3, 1);
	glTranslated(-20, 0, 0);
	glColor3f(1, 1, 0);
	glTranslated(5, 0, 0);
	glColor3f(1, 1, 0);
	glTranslated(5, 0, 0);
	glColor3f(1, 0, 1);
	glutSolidSphere(1, 10, 10);
	glTranslated(5, 0, 0);
	glColor3f(0, 1, 1);
	glutSolidSphere(1, 10, 10);
	glTranslated(5, 0, 0);
	glColor3f(1, 1, 0);
	glutSolidSphere(1, 10, 10);
	glTranslated(5, 0, 0);
	glColor3f(0, 1, 0);
	glutSolidSphere(1, 10, 10);
	glTranslated(5, 0, 0);
	glColor3f(0, 1, 1);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glLineWidth(3.0);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(enemyX - 2, enemyY + 8);
	glVertex2f(enemyX + 2, enemyY + 8);
	glVertex2f(enemyX + 2, enemyY + 12);
	glVertex2f(enemyX - 2, enemyY + 12);
	glEnd();

	glColor3f(0.5, 0.5, 1);
	glBegin(GL_LINES);
	glVertex2f(enemyX, enemyY + 10);
	glVertex2f(enemyX - 25, enemyY + 25);

	glVertex2f(enemyX, enemyY + 10);
	glVertex2f(enemyX + 25, enemyY + 25);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}
void drawEnemyShot()
{
	glPushMatrix();
	glLineWidth(7.0);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(enemyShotX, enemyShotY);
	glVertex2f(enemyShotX, enemyShotY - 10);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 1);
	glVertex2f(enemyShotX, enemyShotY);
	glVertex2f(enemyShotX + 5, enemyShotY + 20);
	glVertex2f(enemyShotX - 5, enemyShotY + 20);
	glEnd();
	glPopMatrix();
}
void enemyShotInterval(int val)
{
	if (enemyShotY == -100)
		dropTheBall();
	glutTimerFunc(500, enemyShotInterval, 0);
}
void drawHealthBar()
{
	glPushMatrix();
	std::ostringstream tmp;
	tmp << ROUNDF(enemyHealth, 100);

	writeToScreen("Enemy health: " + tmp.str() + "\%", 10, 450, 1, 1, 1);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(10, 470);
	glVertex2f(10 + 100, 470);
	glVertex2f(10 + 100, 490);
	glVertex2f(10, 490);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex2f(10, 470);
	glVertex2f(10 + enemyHealth, 470);
	glVertex2f(10 + enemyHealth, 490);
	glVertex2f(10, 490);
	glEnd();
	glPopMatrix();
}
void drawHealthBar()
{
	glPushMatrix();
	std::ostringstream tmp;
	tmp << ROUNDF(100, 100);

	writeToScreen("Project By : Mostafa Gamil " + tmp.str() + "\%", 10, 450, 1, 1, 1);

}



void myDisplay(void)
{
	if (!gameOver) {
		glClear(GL_COLOR_BUFFER_BIT);
		glLineWidth(GLfloat(3.0));
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		drawBackground();
		drawEnemy();
		drawHealthBar();
		drawEnemyShot();
		drawScore();
		glPushMatrix();
		glTranslatef(webposx, webposy, 0.0f);
		web();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(web2posx, web2posy, 0.0f);
		web2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(mposx, mposy, 0.0f);
		man();
		glPopMatrix();

		if (webShoot == true)
			webposy += webSpeed;
		if (webposy >= 610)
			webShoot = false;

		if (web2Shoot == true)
			web2posx += web2Speed;
		if (web2posx >= 610)
			web2Shoot = false;

		if (!hit) Venom();
		if (web2posx >= 330 && web2posx <= 440 && web2posy >= 0 && web2posy <= 100) {
			gameScore >= 30;
			gameScore = +10;
			newgamescore = 10;
			hit = true;
		}

		
	}
	else {
		std::ostringstream tmp;
		tmp << gameScore;
		writeToScreen("You lost! :(", 150, 280, 0, 0, 0);
		writeToScreen("Total score: " + tmp.str(), 150, 250, 0, 0, 0);
	}

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}
void myInit(void)
{
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Abo Shabaka");
	glutSpecialFunc(Spiderspecial);
	glutKeyboardFunc(Spiderkey);
	glutIdleFunc(idleCallback);
	glutTimerFunc(1000, enemyShotInterval, 0);
	glutDisplayFunc(myDisplay);
	glutFullScreen();
	myInit();
	glutMainLoop();
}
void handleEnemyMovement()
{

	int* point = bezier(t, p0, p1, p2, p3);
	t += 0.0002;

	if (t >= 1)
	{
		enemyRotation = -enemyRotation;
		t = 0;
		p0[0] = p3[0];
		p0[1] = p3[1];

		p3[0] = rand() % 500;
		p3[1] = rand() % 400;
		p1[0] = rand() % 500;
		p1[1] = rand() % 400;
		p2[0] = rand() % 500;
		p2[1] = rand() % 400;
	}

	if (p3[1] < 250)
	{
		p3[1] += 220;
	}
	if (p1[1] < 250)
	{
		p1[1] += 220;
	}
	if (p2[1] < 250)
	{
		p2[1] += 220;
	}

	enemyX = point[0];
	if (enemyY < -50) // Enemy is currently respawning
	{
		enemyY += 0.01;
	}
	else
		enemyY = point[1];

	// Lock him to the borders.
	if (enemyX > 460)
		enemyX = 460;
	else if (enemyX < 20)
		enemyX = 20;
}


void idleCallback()
{

	if (bg1Y >= 500)
	{
		bg1Y = -500;
		generateBG1Points();
	}
	else
		bg1Y += 0.1;

	if (bg2Y >= 1000)
	{
		bg2Y = 0;
		generateBG2Points();
	}
	else
		bg2Y += 0.1;

	handleEnemyMovement();


	if (webposy > 0)
	{
		if (abs(webposy - enemyY) < enemyHEIGHT && abs(webposx - enemyX) < enemyWIDTH)
		{
			webposy = -100;
			double factorOfSpawns = (gameScore + 100) / 100;
			enemyHealth -= 10 / factorOfSpawns;
			gameScore += 10;
			if (enemyHealth <= 0)
			{

				enemyY = -100;
				enemyHealth = 100;
			}
		}
		webposy += (webSpeed / 10);
	}

	if (enemyShotY > 0)
	{
		enemyShotY -= 0.3;
		if (abs(enemyShotY - mposy ) < 10)
		{
			if (abs(enemyShotX - mposx) < 25)
				gameOver = true;
		}
	}
	else 
		enemyShotY = -100;
	glutPostRedisplay();
}