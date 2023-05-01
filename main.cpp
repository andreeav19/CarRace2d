#include <iostream>
#include <windows.h>
#include <math.h>
#include <GL/freeglut.h>

using namespace std;

GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;

double gameRunning = 1;
double j = 0.0;
double i = 0.0;

double firstIntermittentLineXTranslation = 0.0;
double secondIntermittentLineXTranslation = 0.0;
double thirdIntermittentLineXTranslation = 0.0;

double car_x_pos = 0.0;
double contor = 0;

int vector[3] = { 0, 160, 320 };
double car_obstacle_x = 800;
double car_obstacle_y = vector[rand() % 3];
double coin_x = 800;
double coin_y = ((int)car_obstacle_y + 160) % 320;
int coin_exists = rand() % 2;
double flowers_x = 0;
double flowers_y = 0;

float fuel_x = 1150;
float fuel_y = ((int)car_obstacle_y) % 320;
int fuel_exists = rand() % 5;

int score = 0;
double speed = 0.25;
int points = 1000;
double rbl, rbr, rtl, rtr = 0;

float fuel = 100;

const float PI = 3.14;
const int sides = 50;

void init(void)
{
	glClearColor(0.56, 0.58, 0.58, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}

void resetGame() {
	gameRunning = 1;
	j = 0.0;
	i = 0.0;
	flowers_x = 0;
	flowers_y = 0;
	firstIntermittentLineXTranslation = 0.0;
	secondIntermittentLineXTranslation = 0.0;
	thirdIntermittentLineXTranslation = 0.0;
	car_x_pos = 0.0;
	contor = 0;
	car_obstacle_x = 800;
	car_obstacle_y = vector[rand() % 3];
	score = 0;
	speed = 0.15;
	points = 1000;
	rbl, rbr, rtl, rtr = 0;
	fuel = 100;
	fuel_x = 1150;
	fuel_y = ((int)car_obstacle_y) % 320;
	fuel_exists = rand() % 5;
	coin_x = 800;
	coin_y = ((int)car_obstacle_y + 160) % 320;
	coin_exists = rand() % 2;
}


void startgame(void) {
	if (((car_obstacle_y != j) || abs(car_obstacle_x - car_x_pos) >= 90) && fuel > 0)
	{
		fuel -= 0.01;
		if (flowers_x < -800) {
			flowers_x = 0;
		}
		if (firstIntermittentLineXTranslation < -1275) {
			firstIntermittentLineXTranslation = 0;
		}
		if (secondIntermittentLineXTranslation < -1700) {
			secondIntermittentLineXTranslation = -425;
		}
		if (thirdIntermittentLineXTranslation < -2125) {
			thirdIntermittentLineXTranslation = -850;
		}

		flowers_x -= 2 * speed;

		firstIntermittentLineXTranslation -= 2 * speed;
		secondIntermittentLineXTranslation -= 2 * speed;
		thirdIntermittentLineXTranslation -= 2 * speed;

		car_obstacle_x -= speed;
		coin_x -= speed;
		fuel_x -= speed / 1.1;

		int random_i_o = rand() % 3; // random index for obstacle
		int random_i_c = rand() % 3; // random index for coin
		int random_i_f = rand() % 3;

		// ensure that obstacles and coins are not on the same line
		random_i_c = (random_i_c != random_i_o) ? random_i_c : (random_i_c + 1) % 3;

		if (coin_exists && abs(car_x_pos - coin_x) <= 50 && abs(j - coin_y) <= 25) {
			score += 50;
			cout << "Score:  " << score << endl;
			coin_x = -200;
			coin_exists = 0;
		}

		if (abs(car_x_pos - fuel_x) <= 40 && abs(j - fuel_y) <= 35) {
			fuel = 100;
			fuel_x = -200;
			fuel_exists = 0;
		}

		if (car_obstacle_x < -150)
		{
			score += 100;
			car_obstacle_y = vector[random_i_o];
			cout << "Score:  " << score << endl;
			car_obstacle_x = 800;

			coin_exists = rand() % 2;
			fuel_exists = rand() % 5;
		}

		if (coin_exists && coin_x < -150)
		{
			coin_y = vector[random_i_c];
			coin_x = 800;
		}

		if (fuel_exists == 2 && fuel_x < -150)
		{
			fuel_y = vector[random_i_f];
			fuel_x = 1150;
		}

		if (score >= points && points <= 15000)
		{
			speed += 0.1;
			points += 1000;
		}

		glutPostRedisplay();
	}
	else {
		gameRunning = 0;
	}
}

void drawMeter(GLfloat value) {

	// Draw the meter background
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-90.0, -120.0);
	glVertex2f(-90.0, -110.0);
	glVertex2f(110.0, -110.0);
	glVertex2f(110.0, -120.0);
	glEnd();

	// Draw the meter fill
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-90.0, -120.0);
	glVertex2f(-90.0, -110.0);
	glVertex2f(-90.0 + value * 2.0, -110.0);
	glVertex2f(-90.0 + value * 2.0, -120.0);
	glEnd();

	glPopMatrix();
}

void drawPlayerCar() {

	// draw windows

	glColor3f(0.88, 0.24, 0.22);

	float radius = 25;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * PI / sides;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();


	glColor3f(0.6, 0.92, 0.94);

	radius = 20;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * PI / sides;
		float x = radius * cos(angle);
		float y = radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.88, 0.24, 0.22);

	glRecti(-3, 0, 0, 24); // separate windows
	glRecti(-45, -10, 45, 10);	// car body

	// draw wheels

	glColor3f(0.22, 0.23, 0.23);

	radius = 8;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.35, 0.35, 0.35);

	radius = 5;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.22, 0.23, 0.23);

	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(17.0f, -5.0f);
	glVertex2f(24.0f, -15.0f);

	glVertex2f(24.0f, -5.0f);
	glVertex2f(17.0f, -15.0f);

	glVertex2f(25.5f, -10.0f);
	glVertex2f(15.5f, -10.0f);

	glVertex2f(-17.0f, -5.0f);
	glVertex2f(-24.0f, -15.0f);

	glVertex2f(-24.0f, -5.0f);
	glVertex2f(-17.0f, -15.0f);

	glVertex2f(-25.5f, -10.0f);
	glVertex2f(-15.5f, -10.0f);

	glEnd();

	// draw doors

	glColor3f(0.63, 0.24, 0.2);

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-15.0f, 5.0f);
	glVertex2f(-8.0f, 5.0f);

	glVertex2f(8.0f, 5.0f);
	glVertex2f(1.0f, 5.0f);
	glEnd();

	// draw headlights
	glColor3f(0.78, 0.74, 0.55);
	glRecti(35, 5, 45, 10);

	glColor3f(0.7, 0.34, 0.31);
	glRecti(-45, 5, -40, 10);

}

void drawObstacleCar() {

	// draw windows
	glColor3f(0.2, 0.43, 0.91);

	glBegin(GL_POLYGON);
	glVertex2f(-15.0f, 25.0f);
	glVertex2f(15.0f, 25.0f);
	glVertex2f(25.0f, 10.0f);
	glVertex2f(-25.0f, 10.0f);
	glEnd();

	glColor3f(0.6, 0.92, 0.94);

	glBegin(GL_POLYGON);
	glVertex2f(-13.0f, 21.0f);
	glVertex2f(13.0f, 21.0f);
	glVertex2f(18.0f, 12.0f);
	glVertex2f(-18.0f, 12.0f);
	glEnd();

	glColor3f(0.2, 0.43, 0.91);

	glRecti(3, 0, 0, 24); // separate windows
	glRecti(-45, -10, 45, 10);	// car body

	// draw wheels

	glColor3f(0.22, 0.23, 0.23);

	float radius = 8;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.35, 0.35, 0.35);

	radius = 5;

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = 20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = 2 * index * PI / sides;
		float x = -20.5 + radius * cos(angle);
		float y = -10 + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.22, 0.23, 0.23);

	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(17.0f, -5.0f);
	glVertex2f(24.0f, -15.0f);

	glVertex2f(24.0f, -5.0f);
	glVertex2f(17.0f, -15.0f);

	glVertex2f(25.5f, -10.0f);
	glVertex2f(15.5f, -10.0f);

	glVertex2f(-17.0f, -5.0f);
	glVertex2f(-24.0f, -15.0f);

	glVertex2f(-24.0f, -5.0f);
	glVertex2f(-17.0f, -15.0f);

	glVertex2f(-25.5f, -10.0f);
	glVertex2f(-15.5f, -10.0f);

	glEnd();

	// draw doors

	glColor3f(0.15, 0.32, 0.68);

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2f(-8.0f, 5.0f);
	glVertex2f(-1.0f, 5.0f);

	glVertex2f(15.0f, 5.0f);
	glVertex2f(8.0f, 5.0f);
	glEnd();

	// draw headlights
	glColor3f(0.78, 0.74, 0.55);
	glRecti(-35, 5, -45, 10);

	glColor3f(0.7, 0.34, 0.31);
	glRecti(45, 5, 40, 10);

}

void drawFuelTank() {
	// red body
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 30.0);
	glVertex2f(30.0, 30.0);
	glVertex2f(30.0, -0.0);
	glEnd();

	// black cap
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(5.0, 30.0);
	glVertex2f(5.0, 35.0);
	glVertex2f(10.0, 35.0);
	glVertex2f(10.0, 30.0);
	glEnd();

	// red handle
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(30.0, 25.0);
	glVertex2f(35.0, 25.0);
	glVertex2f(35.0, 20.0);
	glVertex2f(30.0, 20.0);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(30.0, 5.0);
	glVertex2f(35.0, 5.0);
	glVertex2f(35.0, 10.0);
	glVertex2f(30.0, 10.0);
	glEnd();

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(35.0, 25.0);
	glVertex2f(35.0, 5.0);
	glVertex2f(33.0, 5.0);
	glVertex2f(33.0, 25.0);
	glEnd();

	//F text
	RenderString(13.0f, 11.0f, GLUT_BITMAP_HELVETICA_12, (const unsigned char*)"F");
}

void drawCoin() {
	glColor3f(1, 0.84, 0.33);

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * 2.0f * PI / sides;
		float cx = 15 * cosf(angle);
		float cy = 20 * sinf(angle);
		glVertex2f(cx, cy);
	}
	glEnd();

	glColor3f(0.92, 0.71, 0.17);

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * 2.0f * PI / sides;
		float cx = 13 * cosf(angle);
		float cy = 18 * sinf(angle);
		glVertex2f(cx, cy);
	}
	glEnd();

	glColor3f(1, 0.84, 0.33);

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * 2.0f * PI / sides;
		float cx = 11 * cosf(angle);
		float cy = 16 * sinf(angle);
		glVertex2f(cx, cy);
	}
	glEnd();

	// draw crown
	glColor3f(0.92, 0.71, 0.17);

	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(-8.0, 2.0);
	glVertex2f(-4.0, -2.0);
	glVertex2f(0.0, 6.0);
	glVertex2f(4.0, -2.0);
	glVertex2f(8.0, 2.0);
	glVertex2f(8.0, -6.0);
	glVertex2f(-8.0, -6.0);
	glVertex2f(-8.0, 2.0);

	glEnd();

}

void drawFlower(char* color, float rotation) {

	if (strcmp(color, "blue") == 0)
		glColor3f(0.04, 0.54, 0.99);
	else if (strcmp(color, "pink") == 0)
		glColor3f(0.99, 0.58, 0.94);
	else if (strcmp(color, "red") == 0)
		glColor3f(1, 0.11, 0.33);
	else if (strcmp(color, "purple") == 0)
		glColor3f(0.71, 0.18, 0.79);
	else
		glColor3f(1.0, 1.0, 1.0);

	float petalRadius = 3;
	float polenRadius = 2;
	int noPetals = 5;

	glPushMatrix();
	glRotated(rotation, 0.0, 0.0, 1.0);

	for (int i = 0; i <= noPetals; i++) {
		float a1 = i * 2 * PI / noPetals;
		float tx = 5 * cosf(a1);
		float ty = 5 * sinf(a1);

		glPushMatrix();
		glTranslated(tx, ty, 0.0);

		glBegin(GL_POLYGON);
		for (int index = 0; index <= sides; index++) {
			float angle = index * 2.0f * PI / sides;
			float px = petalRadius * cosf(angle);
			float py = petalRadius * sinf(angle);
			glVertex2f(px, py);
		}
		glEnd();

		glPopMatrix();
	}

	glPopMatrix();

	glColor3f(1, 0.83, 0.3);

	glBegin(GL_POLYGON);
	for (int index = 0; index <= sides; index++) {
		float angle = index * 2.0f * PI / sides;
		float px = polenRadius * cosf(angle);
		float py = polenRadius * sinf(angle);
		glVertex2f(px, py);
	}
	glEnd();
}

void drawTopandBotFlowers() {
	const char* flowerColors[] = {
		// bottom
		"purple",
		"pink",
		"blue",
		"red",
		"blue",
		"pink",
		"purple",
		"pink",
		"blue",
		"red",
		"blue",
		"pink",

		// top
		"red",
		"pink",
		"blue",
		"purple",
		"red",
		"red",
		"pink",
		"red",
		"pink",
		"blue",
		"purple",
		"red",
		"red",
		"pink"
	};

	float flowerTranslate[26][3] = {
		// bottom
		{-50, -100, 0},
		{67, -113, 0},
		{248, -130, 0},
		{415, -100, 0},
		{551, -130, 0},
		{639, -98, 0},
		{750, -100, 0},
		{867, -113, 0},
		{1048, -130, 0},
		{1215, -100, 0},
		{1351, -130, 0},
		{1439, -98, 0},

		// top
		{-5, 411, 0},
		{134, 426, 0},
		{267, 423, 0},
		{419, 418, 0},
		{448, 432, 0},
		{651, 441, 0},
		{722, 428, 0},

		{795, 411, 0},
		{934, 426, 0},
		{1067, 423, 0},
		{1219, 418, 0},
		{1248, 432, 0},
		{1451, 441, 0},
		{1522, 428, 0}
	};

	float flowerRotate[26] = {
		// bottom
		0.0,
		45.0,
		78.0,
		125.0,
		270.0,
		150.0,
		0.0,
		45.0,
		78.0,
		125.0,
		270.0,
		150.0,

		// top
		34,
		87,
		264,
		54,
		90,
		32.1,
		172.5,
		34,
		87,
		264,
		54,
		90,
		32.1,
		172.5
	};

	for (int i = 0; i < 26; i++) {
		glPushMatrix();
		glTranslated(flowerTranslate[i][0], flowerTranslate[i][1], flowerTranslate[i][2]);
		drawFlower((char*)flowerColors[i], flowerRotate[i]);
		glPopMatrix();
	}
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.55, 0.788, 0.451);

	// Bottom grass
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// bottom left
	glVertex2i(700, -140); // bottom right
	glVertex2i(700, -80);  // top right
	glVertex2i(-100, -80); // top left
	glEnd();

	// Top grass
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// bottom left
	glVertex2i(700, 400); // bottom right
	glVertex2i(700, 460); // top right
	glVertex2i(-100, 460);// top left
	glEnd();

	// Flowers
	glPushMatrix();
	glTranslated(flowers_x, 0.0, 0.0);

	drawTopandBotFlowers();

	glPopMatrix();

	// Display text
	RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Outrun the cars!");

	// Road boundary
	glLineWidth(3);
	glColor3f(1, 1, 1);

	// Boundary between road and bottom grass
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Boundary between road and top grass
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Intermittent Lines
	glPushMatrix();
	glTranslated(firstIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(700, 80);
	glVertex2i(1075, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(700, 240);
	glVertex2i(1075, 240);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslated(secondIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(1125, 80);
	glVertex2i(1500, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(1125, 240);
	glVertex2i(1500, 240);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslated(thirdIntermittentLineXTranslation, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(1550, 80);
	glVertex2i(1925, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(1550, 240);
	glVertex2i(1925, 240);
	glEnd();

	glPopMatrix();


	// Draw player car
	glPushMatrix();
	glTranslated(car_x_pos, j, 0.0);

	drawPlayerCar();

	if (!gameRunning)
	{
		rbl = 8;
		rtl = -8;
		rbr = -8;
		rtr = 8;
	}

	glPopMatrix();
	glPopMatrix();

	if (contor == 1 && (j != 160 && j != 320))
		j = j + 1;
	else if (contor == -1 && (j != 160 && j != 0))
		j = j - 1;
	else {
		contor = 0;
	}

	// Draw obstacle car
	glPushMatrix();
	glTranslated(car_obstacle_x, car_obstacle_y, 0.0);

	drawObstacleCar();

	glPopMatrix();

	// Draw coin
	if (coin_exists) {

		glPushMatrix();
		glTranslated(coin_x, coin_y, 0.0);

		drawCoin();

		glPopMatrix();
	}

	// Draw fuel tank
	glPushMatrix();
	glTranslated(fuel_x, fuel_y, 0.0);

	drawFuelTank();

	glPopMatrix();

	// Fuel gauge
	drawMeter(fuel);

	if (!gameRunning) {
		RenderString(250.0f, 200.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"GAME OVER!");
		if (fuel <= 0) {
			RenderString(205.0f, 100.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"YOU RAN OUT OF FUEL!");
		}
		glColor3f(1, 0.4, 0.3);
		glBegin(GL_QUAD_STRIP);
		glVertex2f(260.0, 180.0);
		glVertex2f(260.0, 130.0);
		glVertex2f(350.0, 180.0);
		glVertex2f(350.0, 130.0);
		glEnd();
		RenderString(275.0f, 150.0f, GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Restart");
	}

	startgame();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void moveCarUp(void)
{
	if (gameRunning)
	{
		if (j < 320)
		{
			contor = 1;
			j += 1;
		}
		glutPostRedisplay();
	}
}

void moveCarDown(void)
{
	if (gameRunning)
	{
		if (j > 0)
		{
			contor = -1;
			j -= 1;
		}
		glutPostRedisplay();
	}
}

void moveCarForwards(void) {
	if (gameRunning) {
		if (car_x_pos < 650) {
			car_x_pos += 0.5;
			speed += 0.002;
			fuel -= 0.02;
		}
		glutPostRedisplay();
	}
}

void moveCarBackwards(void) {
	if (gameRunning) {
		if (car_x_pos > 0) {
			car_x_pos -= 0.5;
			speed -= 0.002;
		}
		glutPostRedisplay();
	}
}

void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		double wx = (double)mx / glutGet(GLUT_WINDOW_WIDTH) * (right_m - left_m) + left_m;
		double wy = (1.0 - (double)my / glutGet(GLUT_WINDOW_HEIGHT)) * (top_m - bottom_m) + bottom_m;

		if (wx >= 260.0 && wx <= 350.0 && wy >= 130.0 && wy <= 180.0) {
			if (!gameRunning)
				resetGame();
		}
	}
}

bool keys[256]; // array to store the state of each key

void keyboard(int key, int x, int y)
{
	keys[key] = true; // set the corresponding element to true when a key is pressed

	// handling these two cases here because handling in handleKeys() makes the car move up two lanes with a slight keypress making precise movements hard to achieve
	if (key == GLUT_KEY_UP) {
		moveCarUp();
	}
	if (key == GLUT_KEY_DOWN) {
		moveCarDown();
	}
}

void keyboardUp(int key, int x, int y)
{
	keys[key] = false; // set the corresponding element to false when a key is released
}

void handleKeys()
{
	if (keys[GLUT_KEY_RIGHT]) {
		moveCarForwards();
	}
	if (keys[GLUT_KEY_LEFT]) {
		moveCarBackwards();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Outrun the cars! - mini game");
	init();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUp);

	glutIdleFunc(handleKeys);

	glutMainLoop();
}
