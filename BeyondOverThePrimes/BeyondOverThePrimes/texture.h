#pragma once
/*  --- テクスチャファイルを読み込むための設定 ---  */
#define imageWidth 128
#define imageHeight 128
#define NumOfTextureFiles 2

static const char *images[] = {
	"t16cs042_yozora.ppm",
	"t16cs042_sosu.ppm"
};

GLubyte image[imageHeight][imageWidth][3];
GLint texID[NumOfTextureFiles];

char* get_word(void);
void LoadASCIIPPMImage(const char* filename);

static FILE* texturefile;
static char readbuf[256];
static char word[256];
static char* ptr = readbuf;
static char* ptr2 = word;

//描画する
void Yozora(void)
{
	float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	//glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);

	glBindTexture(GL_TEXTURE_2D, texID[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(10, 20, -5);
	glTexCoord2f(0.0, 10.0); glVertex3f(10, -20, -5);
	glTexCoord2f(10.0, 10.0); glVertex3f(-10, -20, -5);
	glTexCoord2f(10.0, 0.0); glVertex3f(-10, 20, -5);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
}//描画する
void Sosu(void)
{
	float diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float ambient[] = { 0.1, 0.1, 0.1, 1.0 };

	//glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
	double x = -5;
	double y = -8.5;
	double size = 2;
	glBindTexture(GL_TEXTURE_2D, texID[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(size + x, size + y, 5);
	glTexCoord2f(1.0, 0.0); glVertex3f(size + x, -size + y, 5);
	glTexCoord2f(0.0, 0.0); glVertex3f(-size + x, -size + y, 5);
	glTexCoord2f(0.0, 1.0); glVertex3f(-size + x, size + y, 5);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
}

//テクスチャデータを初期化する
void initTexturePPM(void)
{
	glGenTextures(NumOfTextureFiles, (unsigned int *)texID);

	//  テクスチャデータを読み込む関数を実行する 
	int i;
	for (i = 0; i<NumOfTextureFiles; i++) {
		LoadASCIIPPMImage(images[i]);

		glBindTexture(GL_TEXTURE_2D, texID[i]);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imageWidth, imageHeight, 0,
			GL_RGB, GL_UNSIGNED_BYTE, &image);
	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}
/*  --- 以降，テクスチャファイルを読み込むために必要な関数 ---  */
char* get_word(void)
{
	while (1)
	{
		if (*ptr == '\0')
		{
			fgets(readbuf, 256, texturefile);
			while (*readbuf == '#')
			{
				fgets(readbuf, 256, texturefile);
			}
			ptr = readbuf;
			continue;
		}
		else if (isspace(*ptr))
		{
			ptr++;
			continue;
		}
		else
		{
			break;
		}
	}

	ptr2 = word;
	while (!isspace(*ptr))
	{
		*ptr2++ = *ptr++;
	}
	*ptr2 = '\0';
	return word;
}


void LoadASCIIPPMImage(const char* filename)
{
	int i, j;

	fopen_s(&texturefile,filename, "r");

	get_word();

	for (i = imageHeight - 1; i >= 0; i--)
	{
		for (j = 0; j < imageWidth; j++)
		{
			image[i][j][0] = (GLubyte)atoi(get_word());
			image[i][j][1] = (GLubyte)atoi(get_word());
			image[i][j][2] = (GLubyte)atoi(get_word());
		}
	}
	fclose(texturefile);
}
