#include <algorithm>
#include <map>
#include "Glut.h"
#include "Generator.h"
#include "KeyboardCommands.h"

///@brief
///@param aaa
///@return

using namespace std;

/*=============================================================================
Global variables
=============================================================================*/

/* Neighbours stored here */
list<Cube> myL;
/* Basic array with all objects */
Cube Vertex[15][15][15];

/* Camera Eye */
int eyeX = 30;
int eyeY = 30;
int eyeZ = 30;


/* Current cube positions */
int indexX=0;
int indexY=0;
int indexZ=15;




/* random number from 1 to 3 */
int randNum=1;

/* lighting */
GLfloat lightPos[] = { 16, 16, 16, 1.0f };
GLfloat whiteLight[] = { 0.2f, 0.2f, 0.2f, 0.2f };
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };


int displayCount = 0;

/* pause */

int gg=0;


int flag=0;

int camFlag=0;

/* Overall objects */
int cubeNum=0;






/*=============================================================================
Lunch time!
=============================================================================*/
void eat() {
	int tc;
	if ((indexZ > 0) && (Vertex[indexX][indexY][indexZ - 1].getActive() == 1)) {
		int z = Vertex[indexX][indexY][indexZ].getColour();
		switch (z) {
			case 1:
				if (Vertex[indexX][indexY][indexZ - 1].getColour() == 3) {
					Vertex[indexX][indexY][indexZ].setActive(0);
					Vertex[indexX][indexY][indexZ - 1].setActive(0);
				}
				break;
			case 2:
				tc = Vertex[indexX][indexY][indexZ - 1].getColour();
				if (tc != 2) {
					int i = indexZ - 1;
					Vertex[indexX][indexY][indexZ].setActive(0);
					while ((i >= 0) && Vertex[indexX][indexY][i].getColour() == tc) {
						Vertex[indexX][indexY][i].setActive(0);
						i--;
					}
				}
				break;
			case 3:
				if (Vertex[indexX][indexY][indexZ - 1].getColour() == 1) {
					Vertex[indexX][indexY][indexZ].setActive(0);
					Vertex[indexX][indexY][indexZ - 1].setActive(0);
				}
				break;
			default:
				break;
		}
	}
}

/*==============================================================================
Time to store cube to the global array
==============================================================================*/

//TODO Synarthsh antikeimenoy
void storeCube() {
	Vertex[indexX][indexY][indexZ].setColour(randNum);
	Vertex[indexX][indexY][indexZ].setPos(indexX, indexY,  indexZ);
	Vertex[indexX][indexY][indexZ].setActive(1);
}

/*==============================================================================
Display the yellow selected cube
==============================================================================*/
void displaySelectedCube() {
	int x = selectX;
	int y = selectY;
	int z = selectZ;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	//The bottom face
	glNormal3d(0, 0, -1);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y + 1, z);

	//The back face
	glNormal3d(-1, 0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y + 1, z);
	glVertex3f(x, y + 1, z + 1);
	glVertex3f(x, y, z + 1);

	//The top face
	glNormal3d(0, 0, 1);
	glVertex3f(x, y, z + 1);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);

	//The right face
	glNormal3d(0, 1, 0);
	glVertex3f(x, y + 1, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);


	//The left face
	glNormal3d(0, -1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x, y, z + 1);


	//The front face
	glNormal3d(1, 0, 0);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1, y, z + 1);

	glEnd();
	glFlush();
}

/*==============================================================================
Display the current cube
==============================================================================*/
void displayCube(int x, int y, int z, int c) {
	int edgeFlag = 0;
	switch (c) {
		case 1:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 2:
			glColor3f(0.0, 1.0, 0.0);
			break;
		case 3:
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 4:
			glColor3f(1.0, 1.0, 0.0);
			break;
		default:
			break;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	//The bottom face
	glNormal3d(0, 0, -1);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x, y + 1, z);

	//The left face
	glNormal3d(0, -1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x, y, z + 1);

	//The back face
	glNormal3d(-1, 0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y + 1, z);
	glVertex3f(x, y + 1, z + 1);
	glVertex3f(x, y, z + 1);


	//The right face
	glNormal3d(0, 1, 0);
	glVertex3f(x, y + 1, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);

	//The front face
	glNormal3d(1, 0, 0);
	glVertex3f(x + 1, y, z);
	glVertex3f(x + 1, y + 1, z);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x + 1, y, z + 1);

	//The top face
	glNormal3d(0, 0, 1);
	glVertex3f(x, y, z + 1);
	glVertex3f(x + 1, y, z + 1);
	glVertex3f(x + 1, y + 1, z + 1);
	glVertex3f(x, y + 1, z + 1);
	glEnd();

	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	// ============= 1 ===============
	if ((y > 0) && (Vertex[x][y - 1][z].getActive() == 1) && (Vertex[x][y - 1][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z > 0) && (Vertex[x][y][z - 1].getActive() == 1) && (Vertex[x][y][z - 1].getColour() == c)) {
		edgeFlag = 1;
	}



	if (edgeFlag == 0) {
		glVertex3f(x, y, z);
		glVertex3f(x + 1, y, z);
	} else {
		edgeFlag = 0;
	}


	// ============= 2 ===============
	if ((y < 14) && (Vertex[x][y + 1][z].getActive() == 1) && (Vertex[x][y + 1][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z > 0) && (Vertex[x][y][z - 1].getActive() == 1) && (Vertex[x][y][z - 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y + 1, z);
		glVertex3f(x, y + 1, z);
	} else {
		edgeFlag = 0;
	}

	// ============= 3 ===============
	if ((x > 0) && (Vertex[x - 1][y][z].getActive() == 1) && (Vertex[x - 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z > 0) && (Vertex[x][y][z - 1].getActive() == 1) && (Vertex[x][y][z - 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x, y, z);
		glVertex3f(x, y + 1, z);
	} else {
		edgeFlag = 0;
	}

	// ============= 4 ===============
	if ((x > 0) && (Vertex[x - 1][y][z].getActive() == 1) && (Vertex[x - 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z < 14) && (Vertex[x][y][z + 1].getActive() == 1) && (Vertex[x][y][z + 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x, y + 1, z + 1);
		glVertex3f(x, y, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 5 ===============
	if ((y > 0) && (Vertex[x][y - 1][z].getActive() == 1) && (Vertex[x][y - 1][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z < 14) && (Vertex[x][y][z + 1].getActive() == 1) && (Vertex[x][y][z + 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x, y, z + 1);
		glVertex3f(x + 1, y, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 6 ===============
	if ((y < 14) && (Vertex[x][y + 1][z].getActive() == 1) && (Vertex[x][y + 1][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z < 14) && (Vertex[x][y][z + 1].getActive() == 1) && (Vertex[x][y][z + 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y + 1, z + 1);
		glVertex3f(x, y + 1, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 7 ===============
	if ((x < 14) && (Vertex[x + 1][y][z].getActive() == 1) && (Vertex[x + 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z > 0) && (Vertex[x][y][z - 1].getActive() == 1) && (Vertex[x][y][z - 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y, z);
		glVertex3f(x + 1, y + 1, z);
	} else {
		edgeFlag = 0;
	}

	// ============= 8 ===============
	if ((x < 14) && (Vertex[x + 1][y][z].getActive() == 1) && (Vertex[x + 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((z < 14) && (Vertex[x][y][z + 1].getActive() == 1) && (Vertex[x][y][z + 1].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y, z + 1);
		glVertex3f(x + 1, y + 1, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 9 ===============
	if ((x < 14) && (Vertex[x + 1][y][z].getActive() == 1) && (Vertex[x + 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((y > 0) && (Vertex[x][y - 1][z].getActive() == 1) && (Vertex[x][y - 1][z].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y, z);
		glVertex3f(x + 1, y, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 10 ===============
	if ((x < 14) && (Vertex[x + 1][y][z].getActive() == 1) && (Vertex[x + 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((y < 14) && (Vertex[x][y + 1][z].getActive() == 1) && (Vertex[x][y + 1][z].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x + 1, y + 1, z);
		glVertex3f(x + 1, y + 1, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 11 ===============
	if ((x > 0) && (Vertex[x - 1][y][z].getActive() == 1) && (Vertex[x - 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((y < 14) && (Vertex[x][y + 1][z].getActive() == 1) && (Vertex[x][y + 1][z].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x, y + 1, z);
		glVertex3f(x, y + 1, z + 1);
	} else {
		edgeFlag = 0;
	}

	// ============= 12 ===============
	if ((x < 0) && (Vertex[x - 1][y][z].getActive() == 1) && (Vertex[x - 1][y][z].getColour() == c)) {
		edgeFlag = 1;
	}
	if ((y < 0) && (Vertex[x][y - 1][z].getActive() == 1) && (Vertex[x][y - 1][z].getColour() == c)) {
		edgeFlag = 1;
	}

	if (edgeFlag == 0) {
		glVertex3f(x, y, z);
		glVertex3f(x, y, z + 1);
	} else {
		edgeFlag = 0;
	}
	glEnd();
	if ((c == 4) && (displayCount == 0)) {
		glutPostRedisplay();
		displayCount = 1;
	}
	glLineWidth(1);
	glFlush();
}

/*==============================================================================
Displays all the cubes in the field
==============================================================================*/
void displayAll() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 1) {
					if (Vertex[i][j][k].getLoaded() == 1) {
						displayCube(i, j, k, 4);
					} else {
						displayCube(i, j, k, Vertex[i][j][k].getColour());
					}
				}
			}
		}
	}
}

/*==============================================================================
Display Grid
==============================================================================*/
void displayGrid() {
	int n = 15;        // grid length

	/* white grid */
	glBegin(GL_LINES);
	for (int i = 0; i <= n; i++) {
		// set colour
		glColor3f(1, 0, 0);

		// x-z axis
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, n);

		glVertex3f(0, 0, i);
		glVertex3f(n, 0, i);

		glColor3f(0, 1, 0);
		// y-z axis
		glVertex3f(0, i, 0);
		glVertex3f(0, i, n);

		glVertex3f(0, 0, i);
		glVertex3f(0, n, i);

		glColor3f(0, 1, 1);
		// x-y axis
		glVertex3f(i, 0, 0);
		glVertex3f(i, n, 0);

		glVertex3f(0, i, 0);
		glVertex3f(n, i, 0);
	}
	glEnd();
}

/*==============================================================================
Find neighbours please
==============================================================================*/
void loadNeighbours(int x, int y, int z, int c) {
	if ((x < 14) && (Vertex[x + 1][y][z].getActive() == 1) && (Vertex[x + 1][y][z].getLoaded() == 0) &&
		(Vertex[x + 1][y][z].getColour() == c)) {
		myL.push_back(Vertex[x + 1][y][z]);
		Vertex[x + 1][y][z].setLoaded(1);
		Vertex[x + 1][y][z].setScored(1);
	}
	if ((y < 14) && (Vertex[x][y + 1][z].getActive() == 1) && (Vertex[x][y + 1][z].getLoaded() == 0) &&
		(Vertex[x][y + 1][z].getColour() == c)) {
		myL.push_back(Vertex[x][y + 1][z]);
		Vertex[x][y + 1][z].setLoaded(1);
		Vertex[x][y + 1][z].setScored(1);
	}
	if ((x > 0) && (Vertex[x - 1][y][z].getActive() == 1) && (Vertex[x - 1][y][z].getLoaded() == 0) &&
		(Vertex[x - 1][y][z].getColour() == c)) {
		myL.push_back(Vertex[x - 1][y][z]);
		Vertex[x - 1][y][z].setLoaded(1);
		Vertex[x - 1][y][z].setScored(1);
	}
	if ((y > 0) && (Vertex[x][y - 1][z].getActive() == 1) && (Vertex[x][y - 1][z].getLoaded() == 0) &&
		(Vertex[x][y - 1][z].getColour() == c)) {
		myL.push_back(Vertex[x][y - 1][z]);
		Vertex[x][y - 1][z].setLoaded(1);
		Vertex[x][y - 1][z].setScored(1);
	}
	if ((z < 14) && (Vertex[x][y][z + 1].getActive() == 1) && (Vertex[x][y][z + 1].getLoaded() == 0) &&
		(Vertex[x][y][z + 1].getColour() == c)) {
		myL.push_back(Vertex[x][y][z + 1]);
		Vertex[x][y][z + 1].setLoaded(1);
		Vertex[x][y][z + 1].setScored(1);
	}
	if ((z > 0) && (Vertex[x][y][z - 1].getActive() == 1) && (Vertex[x][y][z - 1].getLoaded() == 0) &&
		(Vertex[x][y][z - 1].getColour() == c)) {
		myL.push_back(Vertex[x][y][z - 1]);
		Vertex[x][y][z - 1].setLoaded(1);
		Vertex[x][y][z - 1].setScored(1);
	}
}

/*==============================================================================
Move the selected cube to the according position
==============================================================================*/
void moveCube() {
	int axisChoice;
	int farChoice;
	int mX, mY, mZ;
	int pX, pY, pZ;
	int moveFlag = 0;
	cout << "Welcome to the move cube function" << endl;
	cout << "Type 1 for move at X axis" << endl << "Type 2 for move at Y axis" << endl << "Type 3 for move at Z axis"
		 << endl;
	cin >> axisChoice;
	cout << "How far you wnat to move the bloody cube?" << endl;
	cin >> farChoice;

	list<Cube>::iterator it;
	for (it = myL.begin(); it != myL.end(); ++it) {
		mX = (*it).getPosX();
		mY = (*it).getPosY();
		mZ = (*it).getPosZ();
		switch (axisChoice) {
			case 1:
				mX = mX + farChoice;
				if ((mX < 15) && (mX >= 0)) {
					if (Vertex[mX][mY][mZ].getActive() == 1) {
						moveFlag = 1;
					}
				}
				break;
			case 2:
				mY = mY + farChoice;
				if ((mY < 15) && (mY >= 0)) {
					if (Vertex[mX][mY][mZ].getActive() == 1) {
						moveFlag = 1;
					}
				}
				break;
			case 3:
				mZ = mZ + farChoice;
				if ((mZ < 15) && (mZ >= 0)) {
					if (Vertex[mX][mY][mZ].getActive() == 1) {
						moveFlag = 1;
					}
				}
				break;
			default:
				break;
		}
	}

	if (moveFlag == 0) {
		alreadyMoved = 1;
		cout << "Moving..." << endl;

		/* Run accross the list to make the moves to all the cubes */
		for (it = myL.begin(); it != myL.end(); ++it) {
			mX = (*it).getPosX();
			mY = (*it).getPosY();
			mZ = (*it).getPosZ();

			pX = (*it).getPosX();
			pY = (*it).getPosY();
			pZ = (*it).getPosZ();
			switch (axisChoice) {
				case 1:
					mX = mX + farChoice;
					break;
				case 2:
					mY = mY + farChoice;
					break;
				case 3:
					mZ = mZ + farChoice;
					break;
				default:
					break;
			}
			if ((mX >= 0) && (mX < 15) && (mY >= 0) && (mY < 15) && (mZ >= 0) && (mZ < 15)) {
				Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
				Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
				Vertex[mX][mY][mZ].setActive(1);
				Vertex[pX][pY][pZ].setActive(0);
			} else {
				Vertex[pX][pY][pZ].setActive(0);
			}
		}
	} else {
		cout << "move failed!" << endl;
	}
}

/*==============================================================================
Rotates the selected cube to the acording axis
==============================================================================*/
void rotateCube() {
	int axisChoice;
	int mX, mY, mZ;
	int pX, pY, pZ;
	int moveFlag = 0;
	int rotX = 0, rotY = 0, rotZ = 0;
	int rotType;
	list<Cube>::iterator it;
	cout << "Welcome to the rotate cube function" << endl;
	cout << "Type 1 for rotate at X axis" << endl << "Type 2 for rotate at Y axis" << endl
		 << "Type 3 for rotate at Z axis" << endl;
	cin >> axisChoice;
	switch (axisChoice) {
		case 1:        // x axis
			cout << "X axis rotation..." << endl;
			cout << "Type y: " << endl;
			cin >> rotY;
			cout << "Type z: " << endl;
			cin >> rotZ;

			break;
		case 2:        // y axis
			cout << "Y axis rotation..." << endl;
			cout << "Type X: " << endl;
			cin >> rotX;
			cout << "Type z: " << endl;
			cin >> rotZ;
			break;
		case 3:        // z axis
			cout << "Z axis rotation..." << endl;
			cout << "Type x: " << endl;
			cin >> rotX;
			cout << "Type y: " << endl;
			cin >> rotY;
			break;
		default:
			break;
	}

	/* Selected axis is inside the grid */
	if ((rotX >= 0) && (rotX <= 15) && (rotY >= 0) && (rotY <= 15) && (rotZ >= 0) && (rotZ <= 15)) {
		cout << "Type 1 for p/2 rotation or 2 for -p/2 rotation" << endl;
		cin >> rotType;
		for (it = myL.begin(); it != myL.end(); ++it) {
			mX = (*it).getPosX();
			mY = (*it).getPosY();
			mZ = (*it).getPosZ();

			pX = (*it).getPosX();
			pY = (*it).getPosY();
			pZ = (*it).getPosZ();

			switch (axisChoice) {
				case 1:        // x axis rotation
					if (rotZ < pZ) {
						if (rotY < pY) {
							mZ = pY - rotY;
							mY = pZ - rotZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mZ = rotY - pY;
							mY = pZ - rotZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}

						}
					} else {
						if (rotY < pY) {
							mZ = pY - rotY;
							mY = rotZ - pZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mZ = rotY - pY;
							mY = rotZ - pZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						}
					}
					break;
				case 2:        // y axis rotation
					if (rotX < pX) {
						if (rotZ < pZ) {
							mX = pZ - rotZ;
							mZ = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mX = rotZ - pZ;
							mZ = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}

						}
					} else {
						if (rotY < pY) {
							mX = pZ - rotZ;
							mZ = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mX = rotZ - pZ;
							mZ = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						}
					}
					break;
				case 3:        // z axis rotation
					if (rotX < pX) {
						if (rotY < pY) {
							mX = pY - rotY;
							mY = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mX = rotY - pY;
							mY = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}

						}
					} else {
						if (rotY < pY) {
							mX = pY - rotY;
							mY = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						} else {
							mX = rotY - pY;
							mY = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									moveFlag = 1;
								}
							}
						}
					}
					break;
				default:
					break;
			}
		}
	}

	if (moveFlag == 0) {
		alreadyMoved = 1;
		cout << "Rotating..." << endl;

		/* Run accross the list to make the moves to all the cubes */
		for (it = myL.begin(); it != myL.end(); ++it) {
			mX = (*it).getPosX();
			mY = (*it).getPosY();
			mZ = (*it).getPosZ();

			pX = (*it).getPosX();
			pY = (*it).getPosY();
			pZ = (*it).getPosZ();
			switch (axisChoice) {
				case 1:        // x axis rotation
					if (rotZ < pZ) {
						if (rotY < pY) {
							mZ = pY - rotY;
							mY = pZ - rotZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mZ = rotY - pY;
							mY = pZ - rotZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}

						}
					} else {
						if (rotY < pY) {
							mZ = pY - rotY;
							mY = rotZ - pZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mZ = rotY - pY;
							mY = rotZ - pZ;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						}
					}
					break;
				case 2:        // y axis rotation
					if (rotX < pX) {
						if (rotZ < pZ) {
							mX = pZ - rotZ;
							mZ = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mX = rotZ - pZ;
							mZ = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}

						}
					} else {
						if (rotY < pY) {
							mX = pZ - rotZ;
							mZ = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mX = rotZ - pZ;
							mZ = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						}
					}
					break;
				case 3:        // z axis rotation
					if (rotX < pX) {
						if (rotY < pY) {
							mX = pY - rotY;
							mY = pX - rotX;
							cout << "" << mX << "," << mY << "," << mZ << endl;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 0) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mX = rotY - pY;
							mY = pX - rotX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}

						}
					} else {
						if (rotY < pY) {
							mX = pY - rotY;
							mY = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						} else {
							mX = rotY - pY;
							mY = rotX - pX;
							if ((mX >= 0) && (mX <= 14) && (mY >= 0) && (mY <= 14) && (mZ >= 0) && (mZ <= 14)) {
								if (Vertex[mX][mY][mZ].getActive() == 1) {
									Vertex[mX][mY][mZ].movePos(mX, mY, mZ);
									Vertex[mX][mY][mZ].moveColour(Vertex[pX][pY][pZ].getColour());
									Vertex[mX][mY][mZ].setActive(1);
									Vertex[pX][pY][pZ].setActive(0);
								} else {
									Vertex[pX][pY][pZ].setActive(0);
								}
							}
						}
					}
					break;
				default:
					break;
			}
		}
	} else {
		cout << "Rotation failed!" << endl;
	}
}

/*==============================================================================
Displays to the terminal some choices for the selected cube
==============================================================================*/
void bloodyCode() {
	int choice;
	cout << "Type 1 to move" << endl << "Type 2 to rotate" << endl << "\tType 3 to exit" << endl;
	cin >> choice;
	switch (choice) {
		case 1:        // move
			moveCube();
			break;
		case 2:        // rotate
			rotateCube();
			break;
		case 3:        // exit
			cout << "Continue..." << endl;
			break;
		default:
			break;
	}
}

/*==============================================================================
Move the cube
==============================================================================*/
void func() {
	/* In case you come back another time to select the object */
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 1) {
					Vertex[i][j][k].setLoaded(0);
				}
			}
		}
	}

	myL.clear();

	/* add first element at the list */
	if (Vertex[selectX][selectY][selectZ].getActive() == 1) {
		myL.push_front(Vertex[selectX][selectY][selectZ]);
		Vertex[selectX][selectY][selectZ].setLoaded(1);
	}

	if (!myL.empty()) {
		list<Cube>::iterator it;
		/* Load neighbours and display them */
		for (it = myL.begin(); it != myL.end(); ++it) {
			cubeNum++;
			loadNeighbours((*it).getPosX(), (*it).getPosY(), (*it).getPosZ(), (*it).getColour());
			displayCount = 0;
			displayCube((*it).getPosX(), (*it).getPosY(), (*it).getPosZ(), 4);

		}
		cout << "AM : " << alreadyMoved << " - lD: " << listDisplayed << endl;
		if ((alreadyMoved == 0) && (listDisplayed == 2)) {
			bloodyCode();
		}
		listDisplayed++;
		cubeNum = 0;
	}
}



/*==============================================================================
Move the cube
==============================================================================*/
void moveDown(int value) {
	if (PAUSE == 0) {
		if ((indexZ > 0) && (Vertex[indexX][indexY][indexZ - 1].getActive() == 0)) {
			indexZ--;
		} else {
			storeCube();
			eat();
			indexZ = 15;
			indexX = Generator::randPosX();
			indexY = Generator::randPosY();
			randNum = Generator::generateNum();
		}
		glutPostRedisplay();
	}

	glFlush();
	glutTimerFunc(500, moveDown, 0);
}

/*==============================================================================
Initialization
==============================================================================*/
void init() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 1, 1000);

	gluLookAt(30, 30, 30, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sourceLight);

	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
}

/*==============================================================================
Main display functions
==============================================================================*/
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	displayGrid();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	displayCube(indexX, indexY, indexZ, randNum);
	displayAll();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	if ((PAUSE == 1) && (START == 0)) {
		func();
		displaySelectedCube();
	}

	glutSwapBuffers();
	glFlush();
}


void computeScore() {
	cubeNum = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 1) {
					Vertex[i][j][k].setLoaded(0);
					Vertex[i][j][k].setScored(0);
				}
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if ((Vertex[i][j][k].getActive() == 1) && (Vertex[i][j][k].getScored() == 0)) {
					myL.push_front(Vertex[i][j][k]);
					Vertex[i][j][k].setLoaded(1);
					Vertex[i][j][k].setScored(1);
				}
				if (!myL.empty()) {
					list<Cube>::iterator it;
					for (it = myL.begin(); it != myL.end(); ++it) {
						cubeNum++;
						//cout << "cubeNum :" << cubeNum << endl;
						loadNeighbours((*it).getPosX(), (*it).getPosY(), (*it).getPosZ(), (*it).getColour());
					}
					SCORE = SCORE + cubeNum * cubeNum;
					cubeNum = 0;
					myL.clear();
				}

			}
		}
	}
	cout << "SCORE : " << SCORE << endl;
}

//TODO aplopoihsh
void ComputeScoreKoiloZ() {
	int OphFlag;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 0) {
					if ((i > 0) && (j > 0) && (i < 14) && (j < 14)) {
						if ((Vertex[i - 1][j - 1][k].getActive() == 1) && (Vertex[i - 1][j][k].getActive() == 1) &&
							(Vertex[i - 1][j + 1][k].getActive() == 1) && (Vertex[i][j - 1][k].getActive() == 1) &&
							(Vertex[i][j + 1][k].getActive() == 1) && (Vertex[i + 1][j - 1][k].getActive() == 1) &&
							(Vertex[i + 1][j][k].getActive() == 1) && (Vertex[i + 1][j + 1][k].getActive() == 1)) {
							if ((Vertex[i - 1][j][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i - 1][j + 1][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i][j - 1][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i][j + 1][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i + 1][j - 1][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i + 1][j][k].getColour() == Vertex[i - 1][j - 1][k].getColour()) &&
								(Vertex[i + 1][j + 1][k].getColour() == Vertex[i - 1][j - 1][k].getColour())) {
								Vertex[i][j][k].setScored(1);
								int myk = k;
								while (myk >= 0) {
									if ((Vertex[i][j][myk].getActive() == 0) && (Vertex[i][j][myk].getScored() == 1)) {
										myk = 0;
										OphFlag = 1;
									}
									if (Vertex[i][j][myk].getActive() == 1) {
										if (Vertex[i - 1][j - 1][k].getColour() == Vertex[i][j][myk].getColour()) {
											myk = 0;
											SCORE = SCORE + 100;
											OphFlag = 0;
										} else {
											myk = 0;
											OphFlag = 0;
											SCORE = SCORE + 1000;
										}
									}
									myk--;
								}
								if (OphFlag == 1) {
									SCORE = SCORE + 1000;
									OphFlag = 0;
								}
							}

						}
					}
				}
			}
		}
	}
}
//TODO aplopoihsh
void ComputeScoreKoiloX() {
	int OphFlag;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 0) {
					if ((k > 0) && (j > 0) && (k < 14) && (j < 14)) {
						if ((Vertex[i][j - 1][k - 1].getActive() == 1) && (Vertex[i][j][k - 1].getActive() == 1) &&
							(Vertex[i][j + 1][k - 1].getActive() == 1) && (Vertex[i][j - 1][k].getActive() == 1) &&
							(Vertex[i][j + 1][k].getActive() == 1) && (Vertex[i][j - 1][k + 1].getActive() == 1) &&
							(Vertex[i][j][k + 1].getActive() == 1) && (Vertex[i][j + 1][k + 1].getActive() == 1)) {
							if ((Vertex[i][j][k - 1].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j + 1][k - 1].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j - 1][k].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j + 1][k].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j - 1][k + 1].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j][k + 1].getColour() == Vertex[i][j - 1][k - 1].getColour()) &&
								(Vertex[i][j + 1][k + 1].getColour() == Vertex[i][j - 1][k - 1].getColour())) {
								Vertex[i][j][k].setScored(1);
								int myi = i;
								while (myi >= 0) {
									if ((Vertex[myi][j][k].getActive() == 0) && (Vertex[myi][j][k].getScored() == 1)) {
										myi = 0;
										OphFlag = 1;
									}
									if (Vertex[myi][j][k].getActive() == 1) {
										if (Vertex[i][j - 1][k - 1].getColour() == Vertex[myi][j][k].getColour()) {
											myi = 0;
											SCORE = SCORE + 100;
											OphFlag = 0;
										} else {
											myi = 0;
											OphFlag = 0;
											SCORE = SCORE + 1000;
										}
									}
									myi--;
								}
								if (OphFlag == 1) {
									SCORE = SCORE + 1000;
									OphFlag = 0;
								}
							}

						}
					}
				}
			}
		}
	}
}
//TODO aplopoihsh
void ComputeScoreKoiloY() {
	int OphFlag;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 15; k++) {
				if (Vertex[i][j][k].getActive() == 0) {
					if ((i > 0) && (k > 0) && (i < 14) && (j < 14)) {
						if ((Vertex[i - 1][j][k - 1].getActive() == 1) && (Vertex[i - 1][j][k].getActive() == 1) &&
							(Vertex[i - 1][j][k + 1].getActive() == 1) && (Vertex[i][j][k - 1].getActive() == 1) &&
							(Vertex[i][j][k + 1].getActive() == 1) && (Vertex[i + 1][j][k - 1].getActive() == 1) &&
							(Vertex[i + 1][j][k].getActive() == 1) && (Vertex[i + 1][j][k + 1].getActive() == 1)) {
							if ((Vertex[i - 1][j][k].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i - 1][j][k + 1].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i][j][k - 1].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i][j][k + 1].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i + 1][j][k - 1].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i + 1][j][k].getColour() == Vertex[i - 1][j][k - 1].getColour()) &&
								(Vertex[i + 1][j][k + 1].getColour() == Vertex[i - 1][j][k - 1].getColour())) {
								Vertex[i][j][k].setScored(1);
								int myj = j;
								while (myj >= 0) {
									if ((Vertex[i][myj][k].getActive() == 0) && (Vertex[i][myj][k].getScored() == 1)) {
										myj = 0;
										OphFlag = 1;
									}
									if (Vertex[i][myj][k].getActive() == 1) {
										if (Vertex[i - 1][j][k - 1].getColour() == Vertex[i][myj][k].getColour()) {
											myj = 0;
											SCORE = SCORE + 100;
											OphFlag = 0;
										} else {
											myj = 0;
											OphFlag = 0;
											SCORE = SCORE + 1000;
										}
									}
									myj--;
								}
								if (OphFlag == 1) {
									SCORE = SCORE + 1000;
									OphFlag = 0;
								}
							}

						}
					}
				}
			}
		}
	}
}

/*==============================================================================
Keyboard combinations
==============================================================================*/
//TODO na mpoyn se pinaka deikton se methodoys




void keyboardFunc(GLubyte key, GLint xMouse, GLint yMouse) {
    KeyboardCommands a;
    if (key == 27) {
        exit(EXIT_SUCCESS);
    } else {
        a.findCommand(key);
    }
	glutPostRedisplay();
}
void specialFunc(int key, int x= NULL, int y= NULL) {
	switch (key) {
		case GLUT_KEY_RIGHT:
			if ((indexX > 0) && (Vertex[indexX - 1][indexY][indexZ].getActive() == 0) && (PAUSE == 0)) {
				indexX--;
			}
			break;
		case GLUT_KEY_LEFT:
			if ((indexX < 14) && (Vertex[indexX + 1][indexY][indexZ].getActive() == 0) && (PAUSE == 0)) {
				indexX++;
			}
			break;
		case GLUT_KEY_UP:
			if ((indexY > 0) && (Vertex[indexX][indexY - 1][indexZ].getActive() == 0) && (PAUSE == 0)) {
				indexY--;
			}
			break;
		case GLUT_KEY_DOWN:
			if ((indexY < 14) && (Vertex[indexX][indexY + 1][indexZ].getActive() == 0) && (PAUSE == 0)) {
				indexY++;
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void run(int &argc,char **argv);

int main(int argc, char **argv) {
	run(argc, argv);
	return 0;
}
void run(int &argc,char **argv) {
    KeyboardCommands aaa;
    glutInit(&argc, argv);                                                    // GLUT initialization
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);                    // Display Mode
    glutInitWindowPosition(100, 250);
    glutInitWindowSize(600, 600);                                                // set window size
    glutCreateWindow("Cube Constructor - 3D");                                    // create Window

    init();
    glutDisplayFunc(display);                                                    // register Display Function
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    //glutFullScreen();                                                             //Fullscreen Display
    glutMainLoop();                                                                // run GLUT mainloop
}




