#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <GL/glext.h> //FOR GL_LIGHT_MODEL_COLOR_CONTROL & GL_SEPARATE_SPECULAR_COLOR
#include <vector>
#include "param.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif



// Initialization function for multiple textures
void initializeBackgroundTextures()
{
    int backgroundNumbers = (int)(sizeof(background_name) / sizeof(background_name[0]));
    textures.resize(backgroundNumbers);
    widths.resize(backgroundNumbers);
    heights.resize(backgroundNumbers);
    channels.resize(backgroundNumbers);

    for (int i = 0; i < 4; i++)
    {
        const char* filename = background_name[i];
        stbi_uc* image = stbi_load(filename, &widths[i], &heights[i], &channels[i], 3);

        if (!image)
        {
            std::cout << "CAN'T LOAD BACKGROUND TEXTURE: " << filename << std::endl;
            continue;
        }

        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widths[i], heights[i], 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}





void AutoRotation(){

    if(!rotationPaused)
    {
    auto_rotate_angle += 1;
    if(auto_rotate_angle > 360) auto_rotate_angle = 0;
    //sleep(20);

    if(scanLight)
    {
        if(scanLightYLevel<=0.0)
            scanLightFlag = 0;
        else if(scanLightYLevel>=40.0)
            scanLightFlag = 1;


        if(!scanLightFlag)
            scanLightYLevel+=0.1;

        else
            scanLightYLevel-=0.1;
    }

    glutPostRedisplay();
    }
}

//This is just to change to RAD
float deg2rad(float deg) {
  return deg * M_PI / 180.0f;
}

////////////
//TO GET RID OF LATER
void drawControlPoints(GLfloat(*point)[5][3])
{
    glPointSize(2.5);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    for( int i=0;i<3;i++)
        for( int j=0;j<5;j++)
            glVertex3fv(point[i][j]);
    glEnd();

}

void drawBufferPoints(GLfloat (*point)[3][3])
{
    glPointSize(2.5);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    for( int i=0;i<3;i++)
        for( int j=0;j<3;j++)
            glVertex3fv(point[i][j]);
    glEnd();

}

void drawSoftSurfacePoints(GLfloat (*point)[5][3])
{
    glPointSize(4);
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
    for( int i=0;i<3;i++)
        for( int j=0;j<5;j++)
            glVertex3fv(point[i][j]);
    glEnd();
}


void init(void)
{
    glClearColor(0, 0, 0, 0);
    glColor3f(1.0, 1.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    initializeBackgroundTextures();

}

void menuFunction(int value)
{
    switch(value)
    {
    case 0:
        rotationPaused = true;
        break;
    case 1:
        rotationPaused = false;
        break;
    case 2:
        scanLight = true;
        break;
    case 3:
        scanLight = false;
        break;
    }
}


void menu()
{
    glutCreateMenu(menuFunction);

    //ADD MENU ITEMS
    glutAddMenuEntry("STOP ROATION", 0);
    glutAddMenuEntry("START ROTATION", 1);
    glutAddMenuEntry("SCAN LIGHT ON", 2);
    glutAddMenuEntry("SCAN LIGHT OFF", 3);

    //Attach the menu to the right mouse button
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}



void drawScanLight()
{
    GLfloat p1_x_unit = 0.070375, p1_y_unit=0.035; //((Y_TOP=2.5) - (Y_Bottom=-1))/(NUMBER OF RAYS=40)
    GLfloat p2_x_unit = 0.1025, p2_y_unit=0.0875; //((Y_TOP=1.5) - (Y_Bottom=0))/(NUMBER OF RAYS=40)
    //LEFT EYE
    glPushMatrix();
        glColor3f(1,1,1);
        glBegin(GL_LINES);
            for( int i=0; i<40; i++)
            {
                glVertex3f(2.36 + (p1_x_unit * i), p1_y_unit * scanLightYLevel, 0.5);
                glVertex3f(1.7 +(p2_x_unit*i), -1 + (p2_y_unit* scanLightYLevel), -1.3);
            }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1,1,1);
        glBegin(GL_LINES);
            for( int i=0; i<40; i++)
            {
                glVertex3f(-(2.36 + (p1_x_unit * i)), p1_y_unit * scanLightYLevel, 0);
                glVertex3f(-(1.7 +(p2_x_unit*i)), -1 + (p2_y_unit* scanLightYLevel), -1.3);
            }
        glEnd();
    glPopMatrix();
}

void surface(const GLfloat* points, GLfloat color[], GLint u_val[], GLint v_val[]){
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 5, 0, 1, 15, 3, points);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(color[0], color[1], color[2]);
    glEvalMesh2(GL_FILL, u_val[0], u_val[1], v_val[0], v_val[1]);
    glEnd();
}

void softSurface(const GLfloat* points, GLfloat color[], GLint u_val[], GLint v_val[])
{
    GLuint textureName = 0;
    int width = 0, height = 0, channels = 0;
    stbi_uc * image = stbi_load(softTexturePath, &width, &height, &channels, 3);

    if(!image)
    {
        std::cout<<"CAN't LOAD BACKGROUND";
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);

    // Set the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      // Create the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Map the texture
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,&textureControlPoints[0][0][0]);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 5, 0, 1, 15, 3, points);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(color[0], color[1], color[2]);
    glEvalMesh2(GL_FILL, u_val[0], u_val[1], v_val[0], v_val[1]);

    //Free the image and unbind the texture
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);


    glEnd();

}



void metal_outfit(GLfloat (*color)[3]){
    surface(&outfit_ctrl_point_front[0][0][0], color[0], u_val[0], v_val[0]);
//    drawControlPoints(outfit_ctrl_point_front);

    softSurface(&soft_surface_ctrl_point[0][0][0], color[0], u_val[0], v_val[0]);
//    drawSoftSurfacePoints(soft_surface_ctrl_point);
    surface(&outfit_ctrl_point_back[0][0][0], color[1], u_val[0], v_val[0]);
    surface(&outfit_ctrl_point_side1[0][0][0], color[2], u_val[0], v_val[0]);
    surface(&outfit_ctrl_point_side2[0][0][0], color[2], u_val[0], v_val[0]);
    surface(&outfit_ctrl_point_upper[0][0][0], color[2], u_val[0], v_val[0]);
    surface(&outfit_ctrl_point_lower[0][0][0], color[2], u_val[0], v_val[0]);
//    drawControlPoints(outfit_ctrl_point_lower);
    GLfloat black[3] = {0, 0, 0};
    surface(&outfit_ctrl_point_front[0][0][0], black , u_val[1], v_val[1]);
}


void leftEyeBorder()
{
     //Left eye rectangle border
        // Left eye bottom border
    glPushMatrix();
        glTranslatef(0.5*7+0.25,0,0.5);
        glScalef(1,0.05,0.1);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(3);
    glPopMatrix();

        //Left eye left border
    glPushMatrix();
        glTranslatef(0.5*10+0.25, 0.75, 0.5);
        glScalef(0.05,1,0.2);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(1.5);
    glPopMatrix();

        //Left eye right border
    glPushMatrix();
        glTranslatef(0.5*4+0.25, 0.75, 0.5);
        glScalef(0.05,1,0.2);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(1.5);
    glPopMatrix();

        // Left eye top border
    glPushMatrix();
        glTranslatef(0.5*7+0.25,1.5,0.5);
        glScalef(1,0.05,0.1);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(3);
    glPopMatrix();
}

void rightEyeBorder()
{
    //Right eye rectangle border
        // Right eye bottom border
    glPushMatrix();
        glTranslatef(-0.5*7-0.25,0,0.5);
        glScalef(1,0.05,0.1);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(3);
    glPopMatrix();

        //Right eye left border
    glPushMatrix();
        glTranslatef(-0.5*10-0.25, 0.75, 0.5);
        glScalef(0.05,1,0.2);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(1.5);
    glPopMatrix();

        //Right eye right border
    glPushMatrix();
        glTranslatef(-0.5*4-0.25, 0.75, 0.5);
        glScalef(0.05,1,0.2);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(1.5);
    glPopMatrix();

        // Right eye top border
    glPushMatrix();
        glTranslatef(-0.5*7-0.25,1.5,0.5);
        glScalef(1,0.05,0.1);
        glColor3f(0.5, 0.5, 0.5);
        glutSolidCube(3);
    glPopMatrix();
}

void lens()
{
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &lenCtrlPointsLeft[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40 , 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(0.8,0.94,0.956);
    glEvalMesh2(GL_LINE, 0, 40, 0, 40);
//    drawBufferPoints(lenCtrlPointsLeft);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &lenCtrlPointsRight[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40 , 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(0.8,0.94,0.956);
    glEvalMesh2(GL_LINE, 0, 40, 0, 40);
//    drawBufferPoints(lenCtrlPointsRight);
}

void rounded_rectangle(GLdouble r, GLfloat (*color)[3]){

    GLuint textureName2 = 0;
    int width = 0, height = 0, channels = 0;
    stbi_uc * image = stbi_load(roundRectangleTexTure, &width, &height, &channels, 3);

    if(!image)
    {
        std::cout<<"CAN't LOAD BACKGROUND";
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureName2);
    glBindTexture(GL_TEXTURE_2D, textureName2);

    // Set the parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      // Create the texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    // Map the texture
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,&textureControlPoints[0][0][0]);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &buffer_ctrl_point_side1[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(color[2][0], color[2][1], color[2][2]);
    glEvalMesh2(GL_FILL, 0, 40, 0, 40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(color[0][0], color[0][1], color[0][2]);
    for(int i = 0; i < 360; i ++){
        glVertex3f(-7.0, 0.0 + r * sin(deg2rad(i)), -3.0+ r * cos(deg2rad(i)));
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(color[0][0], color[0][1], color[0][2]);
    for(int i = 0; i < 360; i ++){
        glVertex3f(7.0, 0.0 + r * sin(deg2rad(i)), -3.0+ r * cos(deg2rad(i)));
    }
    glEnd();

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &buffer_ctrl_point_side2[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(color[2][0], color[2][1], color[2][2]);
    glEvalMesh2(GL_FILL, 0, 40, 0, 40);
    glEnd();

    //Free the image and unbind the texture
    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_TEXTURE_2D);
//
//    drawBufferPoints(buffer_ctrl_point_side1);
//    drawBufferPoints(buffer_ctrl_point_side2);
}

void ribbon(){
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 2, &ribbon_ctrl_point[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(40, 0.0, 1.0, 40, 0.0, 1.0);
    glColor3f(1, 1, 1);
    glEvalMesh2(GL_FILL, 0, 40, 0, 40);
    glEnd();
}

void mouseFunction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Left mouse button is pressed, resume rotation
        rotationPaused = false;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // Right mouse button is pressed, pause rotation
        rotationPaused = true;
    }

}
void drawText(const char *text, int length, float x, float y)
{
    glPushMatrix();
        glColor3f(0, 0, 0);

        glMatrixMode(GL_PROJECTION);
        double *matrix = new double[16];
        glGetDoublev(GL_PROJECTION_MATRIX, matrix);
        glLoadIdentity();
        glOrtho(0,800,0,600,-5,5);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRasterPos2f(x,y);
        for (int i=0; i < length;i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
        }
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    delete[] matrix; //FREE THE DYNAMIC ALLOCATED MEMORY
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();
}


void displayText()
{

    int x = 20;
    int y = -20;

    drawText(text1.data(), text1.length(), x, 580+y);

    //Rotation
    drawText(text2.data(),  text2.length(), x, 560+y);
    drawText(text3.data(),  text3.length(), x, 545+y);
    drawText(text4.data(),  text4.length(), x, 530+y);
    drawText(text5.data(),  text5.length(), x, 515+y);
    drawText(text6.data(),  text6.length(), x, 500+y);

    //Color
    drawText(text7.data(),  text7.length(), x, 470+y);
    drawText(text8.data(),  text8.length(), x, 455+y);
    drawText(text9.data(),  text9.length(), x, 440+y);
    drawText(text10.data(), text10.length(), x, 425+y);

    //CAMERA MOVEMENT
    drawText(text11.data(), text11.length(), x, 395+y);

    //X-axis
    drawText(text12.data(), text12.length(), x, 375+y);
    drawText(text13.data(), text13.length(), x, 355+y);
    drawText(text14.data(), text14.length(), x, 340+y);
    //Y-axis
    drawText(text15.data(), text15.length(), x, 320+y);
    drawText(text16.data(), text16.length(), x, 305+y);
    drawText(text17.data(), text17.length(), x, 290+y);
    //Z-axis
    drawText(text18.data(), text18.length(), x, 270+y);
    drawText(text19.data(), text19.length(), x, 255+y);
    drawText(text20.data(), text20.length(), x, 240+y);

    //ESC
    drawText(text21.data(), text21.length(), x, 200+y);

    drawText(text0.data(), text0.length(), 4*x, 580);
}


//ORIGINAL BACKGROUND FUNCTION
//void background(int i){
//
//    glDisable(GL_DEPTH_TEST);
//
//    const char *filename = background_name[i];
//    GLuint texture = 0;
//    int width = 0, height = 0, channels = 0;
//    stbi_uc * image = stbi_load(filename, &width, &height, &channels, 3);
//
//    if(!image)
//    {
//        std::cout<<"CAN't LOAD BACKGROUND";
//        return;
//    }
//
//    glEnable(GL_TEXTURE_2D);
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, width, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
////    glGenerateMipmap(GL_TEXTURE_2D);
//
//    glLoadIdentity();
//    glBegin(GL_QUADS);
//    glRotatef(45, 0, 0, 0);
//    glColor3f(1.0, 1.0, 1.0);
//    glTexCoord2f(1.0f, 0.0f); glVertex3f( 22.5, 12, -12);
//    glTexCoord2f(1.0f, 1.0f); glVertex3f( 22.5,-12, -12);
//    glTexCoord2f(0.0f, 1.0f); glVertex3f(-22.5,-12, -12);
//    glTexCoord2f(0.0f, 0.0f); glVertex3f(-22.5, 12, -12);
//    glEnd();
//
//    //Free image
//    stbi_image_free(image);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glDisable(GL_TEXTURE_2D);
//
//    glEnable(GL_DEPTH_TEST);
//    glLoadIdentity();
//}


void background(int i)
{
    glDisable(GL_DEPTH_TEST);

    glBindTexture(GL_TEXTURE_2D, textures[i]);

    glLoadIdentity();
    glBegin(GL_QUADS);
        glRotatef(45, 0.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 1.0); //WHITE
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 22.5,  12, -12);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 22.5, -12, -12);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-22.5, -12, -12);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-22.5,  12, -12);
    glEnd();


    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        background(background_option);
        displayText();
    glPopMatrix();

    glLoadIdentity();

    gluLookAt(x_direction, y_direction, z_direction, 0, 0, 0, 0, 1, 0);

    //ROTATION
    glRotatef(auto_rotate_angle, 0.0, 1.0, 0.0);
    glRotatef(control_rotate_angle[0], -1.0, 0.0, 0.0);
    glRotatef(control_rotate_angle[1], 0.0, 0.0, -1.0);
    glRotatef(control_rotate_angle[2], 1.0, 0.0, 0.0);
    glRotatef(control_rotate_angle[3], 0.0, 0.0, 1.0);

    glPushMatrix();
        metal_outfit(color_ptr);
        rounded_rectangle(1.0, color_ptr);
        ribbon();
    glPopMatrix();

    glPushMatrix();
        lens();
        leftEyeBorder();
        rightEyeBorder();
        if(scanLight)
            drawScanLight();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
    if(w==0)
        w=1;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h)
        glOrtho(-12.0, 12.0, -12.0*(GLfloat)h / (GLfloat)w, 12.0*(GLfloat)h / (GLfloat)w, -24.0, 24.0);
    else
        glOrtho(-12.0*(GLfloat)w / (GLfloat)h, 12.0*(GLfloat)w / (GLfloat)h, -12.0, 12.0, -24.0, 24.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'a':
            control_rotate_angle[1] += 15;
            glutPostRedisplay();
            break;
        case 'b':
            color_ptr = outfit_color_blue;
            background_option = 1;
            glutPostRedisplay();
            break;
        case 'd':
            control_rotate_angle[3] += 15;
            glutPostRedisplay();
            break;
        case 'g':
            color_ptr = outfit_color_green;
            background_option = 3;
            glutPostRedisplay();
            break;
        case 'w':
            control_rotate_angle[0] += 15;
            glutPostRedisplay();
            break;
        case 's':
            control_rotate_angle[2] += 15;
            glutPostRedisplay();
            break;
        case 'p':
            color_ptr = outfit_color_pink;
            background_option = 2;
            glutPostRedisplay();
            break;
        case '1':
            x_direction -= 0.5;
            glutPostRedisplay();
            break;
        case '2':
            y_direction -= 0.5;
            glutPostRedisplay();
            break;
        case '3':
            z_direction -= 0.5;
            glutPostRedisplay();
            break;
        case '4':
            x_direction += 0.5;
            glutPostRedisplay();
            break;
        case '5':
            y_direction += 0.5;
            glutPostRedisplay();
            break;
        case '6':
            z_direction += 0.5;
            glutPostRedisplay();
            break;
        case 27:   //ESC
            exit(0);
            break;
        default:
            break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Bezier");
    init();
    menu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunction);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(AutoRotation);
    glutMainLoop();
    return 0;
}
