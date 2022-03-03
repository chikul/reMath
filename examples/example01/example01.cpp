#define SDL_MAIN_HANDLED
#include <cstdio>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <reMath/reMath.h>
#include <vector>
#include <cmath>


struct Quad
{
	int v1, v2, v3, v4;
};


const short WIDTH = 800;
const short HEIGHT = 600;
auto lookAtMatrix = re::lookAt(re::Vec3d(0.0f, 0.0f, 6.0f), re::Vec3d(0.0f, 0.0f, 0.0f), re::Vec3d(0.0f, 1.0f, 0.0f));
auto perspectiveMatrix = re::perspective(45.0f, static_cast<float>(WIDTH) / HEIGHT, 0.3f, 100.0f);

std::vector<re::Vec3d> vertices;
std::vector<re::Vec3d> normals;
std::vector<Quad> faces;

float ambient_[] = { .02f, .02f, .02f, 1.f };
float diffuse_[] = { 0, .5f, 0, 1.f };
float specular_[] = { .15f, .15f, 0, 1.f };
float emissive_[] = { 0, 0, 0, 1 };
float shininess_ = 38.4f;


void createTorus(int sliceCount, int loopCount)
{
	const float slicesDelta = 2 * re::PI / sliceCount;
	const float loopsDelta = 2 * re::PI / loopCount;
	const float outerRadius = 1.5f;
	const float innerRadius = 0.7f;

	float slicesAngle = 0;
	float loopsAngle = 0;

	for (auto i = 0; i < sliceCount; i++)
	{
		const auto sliceAngle = static_cast<float>(i) / sliceCount * 2 * re::PI;
		const auto slicesCos = cos(sliceAngle);
		const auto slicesSin = sin(sliceAngle);
		auto slice_rad = outerRadius + innerRadius * slicesCos;

		for (auto j = 0; j < loopCount; j++)
		{
			const auto loopAngle = static_cast<float>(j) / loopCount * 2 * re::PI;
			const auto loopsCos = cos(loopAngle);
			const auto loopsSin = sin(loopAngle);

			vertices.emplace_back(
				(outerRadius + innerRadius * slicesCos) * loopsCos,
				(outerRadius + innerRadius * slicesCos) * loopsSin,
				innerRadius * slicesSin
				);
			
			loopsAngle += loopsDelta;
		}

		slicesAngle += slicesDelta;
	}

	for (auto i = 0; i < sliceCount; i++)
	{
		for (auto j = 0; j < loopCount; j++)
		{
			const bool iOverlapped = i + 1 == sliceCount;
			const int index2 = iOverlapped ? j : i * loopCount + j + loopCount;
			int index3, index4;

			if (j + 1 == loopCount)
			{
				index3 = iOverlapped ? 0 : i * loopCount + loopCount;
				index4 = i * loopCount;
			}
			else
			{
				index3 = iOverlapped ? j + 1 : i * loopCount + j + loopCount + 1;
				index4 = i * loopCount + j + 1;
			}
			
			faces.push_back({ i * loopCount + j, index2, index3, index4 });
		}
	}

	std::vector<re::Vec3d> faceNormals;
	for (auto & face : faces)
	{
		const auto a = vertices[face.v1] - vertices[face.v2];
		const auto b = vertices[face.v1] - vertices[face.v3];
		auto normal = a.cross(b);
		normal.normalize();
		faceNormals.emplace_back(normal);
	}

	for (auto i = 0; i < vertices.size(); i++)
	{
		re::Vec3d v;

		int j = 0;
		for (auto k = 0; k < faces.size(); k++)
		{
			if ((faces[k].v1 == i) ||
				(faces[k].v2 == i) ||
				(faces[k].v3 == i) ||
				(faces[k].v4 == i))
			{
				v += faceNormals[k];
				j++;
			}
		}

		if (j != 0)
		{
			v /= static_cast<float>(j);
			v.normalize();
			normals.emplace_back(v);
		}
	}
}


SDL_Window* createSdlWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	return SDL_CreateWindow("reMath - Example 1", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
}


void setUpOpenGl()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glViewport(0, 0, WIDTH, HEIGHT);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissive_);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess_);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void render(float angle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(static_cast<float*>(perspectiveMatrix * lookAtMatrix));
	
	re::Matrix4 rotation;
	rotation.setRotation(re::toRadians(angle), re::toRadians(angle), 0);

	glBegin(GL_QUADS);
	for (auto & face : faces)
	{
		glNormal3fv(static_cast<float*>(normals[face.v1] * rotation));
		glVertex3fv(static_cast<float*>(vertices[face.v1] * rotation));
		glNormal3fv(static_cast<float*>(normals[face.v2] * rotation));
		glVertex3fv(static_cast<float*>(vertices[face.v2] * rotation));
		glNormal3fv(static_cast<float*>(normals[face.v3] * rotation));
		glVertex3fv(static_cast<float*>(vertices[face.v3] * rotation));
		glNormal3fv(static_cast<float*>(normals[face.v4] * rotation));
		glVertex3fv(static_cast<float*>(vertices[face.v4] * rotation));
	}
	glEnd();
}


void main()
{
	SDL_Window* window = createSdlWindow();
	const SDL_GLContext context = SDL_GL_CreateContext(window);

	std::cout << "GL_VERSION  : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL_VENDOR   : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL_RENDERER : " << glGetString(GL_RENDERER) << std::endl;

	setUpOpenGl();
	createTorus(16, 30);

	SDL_Event windowEvent;
	float angle = 0;

	while(true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				break;
			}
		}

		angle += 0.4;
		while (angle > 360)
			angle -= 360;

		render(angle);

		SDL_GL_SwapWindow(window);
		SDL_Delay(10);
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
