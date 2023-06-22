#ifndef param_h
#define param_h

//metal outfit(front)
int background_option = 0;
const GLfloat DEG2RAD = (GLfloat)(3.14159/180);

GLint auto_rotate_angle = 0;
GLint control_rotate_angle[4] = {0, 0, 0, 0};

GLfloat scanLightYLevel = 0;
GLboolean scanLightFlag = true;
GLboolean scanLight = false;
GLboolean rotationPaused = false;


const char *roundRectangleTexTure = "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/sponge.png";
const char *softTexturePath = "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/smooth.png";
const char* background_name[4] = {
    "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/1.2.png", //PATH TO be altered based on the picture's path in the system
    "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/2.2.png",
    "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/3.2.png",
    "C:/Users/benal/OneDrive/Desktop/04-23/Computer graphics/GRP PROJECT/pics/4.2.png"
};


std::vector<GLuint> textures;  // Vector to store texture IDs
std::vector<int> widths;       // Vector to store texture widths
std::vector<int> heights;      // Vector to store texture heights
std::vector<int> channels;     // Vector to store texture channels

//text to be printed
std::string text0  = "HOW TO USE?";
std::string text1  = "RIGHT-CLICK: Open MENU";
std::string text2  = "ROTATION";
std::string text3  = "   D/d : Clockwise Rotation on Z-axis";
std::string text4  = "   A/a : Counter-clockwise Rotation on Z-axis";
std::string text5  = "   S/s : Clockwise Rotation on X-axis";
std::string text6  = "   W/w : Counter-clockwise Rotation on X-axis";
std::string text7  = "COLOR";
std::string text8  = "   B/b : Blue Color";
std::string text9  = "   P/p : Pink Color";
std::string text10 = "   G/g : Green Color";
std::string text11 = "CAMERA MOVEMENT";
std::string text12 = "X-axis:";
std::string text13 = "    1  : Move Camera RIGHT";
std::string text14 = "    4  : Move Camera LEFT";
std::string text15 = "Y-axis:";
std::string text16 = "    2  : Move Camera DOWN";
std::string text17 = "    5  : Move Camera UP";
std::string text18 = "Z-axis:";
std::string text19 = "    3  : Move Camera AWAY";
std::string text20 = "    6  : Move Camera FORTH";
std::string text21 = "ESC: QUIT APPLICATION";

GLint u_val[2][2] ={
    {0, 40},
    {1, 17}
};
GLint v_val[2][2] ={
    {0, 40},
    {5, 25}
};

GLdouble thickness = 0.5;
GLdouble x_direction = 0, y_direction = 0, z_direction = 5;

//metal outfit(front)
GLfloat outfit_ctrl_point_front[3][5][3] = {
    {
        {-7.0, 2, 0},{-5.5, 3, 1.5},
        {0.0, 4, 0},{5.5, 3, 1.5},{7.0, 2, 0}
    },
    {
        {-10.0, 0.0, 3.0},{-5.5, 0.0, 4.5},
        {0.0, 0.0, 3.0},{5.5, 0.0, 4.5},{10.0, 0.0, 3.0}
    },
    {
        {-7.0, -2, 0},{-5.5, -3, 1.5},
        {0.0, 4, 0},{5.5, -3, 1.5},{7.0, -2, -0}
    }
};
//metal outfit(back)
GLfloat outfit_ctrl_point_back[3][5][3] = {
    {
        {-7.0, 2, (GLfloat)(0 - thickness)},{-5.5, 3, (GLfloat)(1.5-thickness)},
        {0.0, 4, (GLfloat)(0-thickness)},{5.5, 3, (GLfloat)(1.5-thickness)},
        {7.0, 2, (GLfloat)(0-thickness)}
    },
    {
        {-10.0, 0.0, (GLfloat)(3.0-thickness)},{-5.5, 0.0, (GLfloat)(4.5-thickness)},
        {0.0, 0.0, (GLfloat)(3.0-thickness)},{5.5, 0.0, (GLfloat)(4.5-thickness)},
        {10.0, 0.0, (GLfloat)(3.0-thickness)}
    },
    {
        {-7.0, -2, (GLfloat)(0 - thickness)},{-5.5, -3, (GLfloat)(1.5-thickness)},
        {0.0, 4, (GLfloat)(0 - thickness)},{5.5, -3, (GLfloat)(1.5-thickness)},
        {7.0, -2, (GLfloat)(0 - thickness)}
    }
};
// metal outfit(side1)
GLfloat outfit_ctrl_point_side1[3][5][3] = {
    {
        {-7.0, 2, 0},{-7.0, 2, (GLfloat)(0 - thickness/4)},
        {-7.0, 2, (GLfloat)(0 - thickness/2)},
        {-7.0, 2, (GLfloat)(0 - 3 * thickness/4)},{-7.0, 2, (GLfloat)(0 - thickness)}
    },
    {
        {-10.0, 0, 3.0},{-10.0, 0, (GLfloat)(3.0 - thickness/4)},
        {-10.0, 0, (GLfloat)(3.0 - thickness/2)},
        {-10.0, 0, (GLfloat)(3.0 - 3 * thickness/4)},{-10.0, 0, (GLfloat)(3.0 - thickness)}
    },
    {
        {-7.0, -2, 0},{-7.0, -2, (GLfloat)(0 - thickness/4)},
        {-7.0, -2, (GLfloat)(0 - thickness/2)},
        {-7.0, -2, (GLfloat)(0 - 3*thickness/4)},{-7.0, -2, (GLfloat)(0 - thickness)}
    }
};
// metal outfit(side2)
GLfloat outfit_ctrl_point_side2[3][5][3] = {
    {
        {-7.0, 2, 0},{-5.5, 2, 1.5},
        {0.0, 2, 0},{5.5, 2, 1.5},{7.0, 2, 0}
    },
    {
        {10.0, 0, 3.0},{10.0, 0, (GLfloat)(3.0 - thickness/4)},
        {10.0, 0, (GLfloat)(3.0 - thickness/2)},
        {10.0, 0, (GLfloat)(3.0 - 3 * thickness/4)},{10.0, 0, (GLfloat)(3.0 - thickness)}
    },
    {
        {7.0, -2, 0},{7.0, -2, (GLfloat)(0 - thickness/4)},
        {7.0, -2, (GLfloat)(0 - thickness/2)},
        {7.0, -2, (GLfloat)(0 - 3*thickness/4)},{7.0, -2, (GLfloat)(0 - thickness)}
    }
};
// metal outfit(upper)
GLfloat outfit_ctrl_point_upper[3][5][3] = {
    {
        {-7.0, 2, 0},{-5.5, 3, 1.5},
        {0.0, 4, 0},{5.5, 3, 1.5},{7.0, 2, 0}
    },
    {
        {-7.0, 2, (GLfloat)(0 - thickness/2)},{-5.5, 3, (GLfloat)(1.5-thickness/2)},
        {0.0, 4, (GLfloat)(0-thickness/2)},{5.5, 3, (GLfloat)(1.5-thickness/2)},
        {7.0, 2, (GLfloat)(0-thickness/2)}
    },
    {
        {-7.0, 2, (GLfloat)(0 - thickness)},{-5.5, 3, (GLfloat)(1.5-thickness)},
        {0.0, 4, (GLfloat)(0-thickness)},{5.5, 3, (GLfloat)(1.5-thickness)},
        {7.0, 2, (GLfloat)(0-thickness)}
    }
};
// metal outfit(lower)
GLfloat outfit_ctrl_point_lower[3][5][3] = {
    {
        {-7.0, -2, 0},{-5.5, -3, 1.5},
        {0.0, 4, 0},{5.5, -3, 1.5},{7.0, -2, -0}
    },
    {
        {-7.0, -2, (GLfloat)(0 - thickness/2)},{-5.5, -3, (GLfloat)(1.5-thickness/2)},
        {0.0, 4, (GLfloat)(0 - thickness/2)},{5.5, -3, (GLfloat)(1.5-thickness/2)},
        {7.0, -2, (GLfloat)(0 - thickness/2)}
    },
    {
        {-7.0, -2, (GLfloat)(0 - thickness)},{-5.5, -3, (GLfloat)(1.5-thickness)},
        {0.0, 4, (GLfloat)(0 - thickness)},{5.5, -3, (GLfloat)(1.5-thickness)},
        {7.0, -2, (GLfloat)(0 - thickness)}
    }
};

//SOFT SURFACE
GLfloat soft_surface_ctrl_point[3][5][3] = {
    {
        {-7.0, 2, (GLfloat)(0 - thickness)},{-5.5, 3, (GLfloat)(2-thickness)},
        {0.0, 4, (GLfloat)(-0.5-thickness)},{5.5, 3, (GLfloat)(2-thickness)},
        {7.0, 2, (GLfloat)(0-thickness)}
    },
    {
        {-7.0, 0.0, (GLfloat)(0-thickness)},{-5.5, 0.0, (GLfloat)(9-thickness)},
        {0.0, 0.0, (GLfloat)(-9-thickness)},{5.5, 0.0, (GLfloat)(9-thickness)},
        {7.0, 0.0, (GLfloat)(0-thickness)}
    },
    {
        {-7.0, -2, (GLfloat)(0 - thickness)},{-5.5, -3, (GLfloat)(2-thickness)},
        {0.0, 4, (GLfloat)(-0.5 - thickness)},{5.5, -3, (GLfloat)(2-thickness)},
        {7.0, -2, (GLfloat)(0 - thickness)}
    }
};

//buffer area
GLfloat buffer_len = 2.5;
GLfloat buffer_ctrl_point_side1[3][3][3] = {
    {
        {-7.01, 2.0, 0.0},{-10.01, 0.0, 3.0},
        {-7.01, -2.0, 0.0}
    },
    {
        {-6.75, 1.5, (GLfloat)(-1.25-thickness)},
        {-9.5, 0.0, (GLfloat)(-1.25-thickness)},
        {-6.75, -1.5, (GLfloat)(-1.25-thickness)}
    },
    {
        {-6.5, 1.0, (GLfloat)(-2.5-thickness)},{-8.0, 0.0, (GLfloat)(-2.5-thickness)},
        {-6.5, -1.0, (GLfloat)(-2.5-thickness)}
    }
};

GLfloat buffer_ctrl_point_side2[3][3][3] = {
    {
        {7.01, 2.0, 0.0},{10.01, 0.0, 3.0},
        {7.01, -2.0, 0.0}
    },
    {
        {6.75, 1.5, (GLfloat)(-1.25-thickness)},
        {9.5, 0.0, (GLfloat)(-1.25-thickness)},
        {6.75, -1.5, (GLfloat)(-1.25-thickness)}
    },
    {
        {6.5, 1.0, (GLfloat)(-2.5-thickness)},{8.0, 0.0, (GLfloat)(-2.5-thickness)},
        {6.5, -1.0, (GLfloat)(-2.5-thickness)}
    }
};

GLfloat lenCtrlPointsLeft[3][3][3] = {
    {
        {2.36, 0, 0.35},{2.36, 0.75, 0.35},
        {2.36, 1.5, 0.35}
    },
    {
        {4.25, 0, 1},
        {4.25, 0.75, 2.24},
        {4.25, 1.5, 1}
    },
    {
        {5.175, 0, 0.35},{5.175, 0.75, 0.35},
        {5.175, 1.5, 0.35}
    }
};

GLfloat lenCtrlPointsRight[3][3][3] = {
    {
        {-2.36, 0, 0.35},{-2.36, 0.75, 0.35},
        {-2.36, 1.5, 0.35}
    },
    {
        {-4.25, 0, 1},
        {-4.25, 0.75, 2.24},
        {-4.25, 1.5, 1}
    },
    {
        {-5.17, 0, 0.35},{-5.17, 0.75, 0.35},
        {-5.17, 1.5, 0.35}
    }
};

GLfloat ribbon_ctrl_point[2][3][3] = {
    {
        {7,  0.8, -2.95}, {0.0,  0.1, -15.0}, {-7,  0.8, -2.95}
    },
    {
        {7, -0.8, -2.95}, {0.0, -0.1, -15.0}, {-7, -0.8, -2.95}
    }
};

GLfloat textureControlPoints[2][2][2] = {
    {
        {0.0, 0.0}, {0.0, 1.0}
    },
    {
        {1.0, 0.0}, {1.0, 1.0}
    }
};

GLfloat outfit_color_white[3][3] = {
    {1.0, 0.98, 0.98},
    {0.9, 0.9, 0.9},
    {0.75, 0.75, 0.75}
};
GLfloat outfit_color_pink[3][3] = {
    {0.964, 0.745, 0.784},
    {0.576, 0.329, 0.33},
    {0.474, 0.239, 0.337}
};
GLfloat outfit_color_blue[3][3] = {
    {0.82, 0.9, 0.94},
    {0.24, 0.35, 0.67},
    {0.69, 0.87, 0.90}
};
GLfloat outfit_color_green[3][3] = {
    {0.752, 0.839, 0.584},
    {0.188, 0.501, 0.078},
    {0.298, 0.501, 0.270}
};
GLfloat (*color_ptr)[3] = outfit_color_white;

GLfloat ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
GLfloat position[] = { -2.0, 1.0, 2.0, 0.7 };
GLfloat mat_diffuse[] = { 0.19225, 0.19225, 0.19225, 1.0 };
//GLfloat mat_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
//GLfloat mat_specular[] = { 0.673911, 0.673911, 0.673911, 1.0 };
GLfloat mat_specular[] = { 0.373911, 0.373911, 0.373911, 1.0 };
GLfloat mat_shininess[] = { 50 };


#endif /* param_h */
