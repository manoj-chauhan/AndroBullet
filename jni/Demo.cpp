

#include <jni.h>
#include <android/log.h>

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <btBulletDynamicsCommon.h>
#include "Sphere.h"
#include "Plane.h"

#define  LOG_TAG    "BulletDemo"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


///Physics variables

btDiscreteDynamicsWorld* dynamicsWorld;
btBroadphaseInterface* broadphase;
btDefaultCollisionConfiguration* collisionConfiguration;
btCollisionDispatcher* dispatcher;
btSequentialImpulseConstraintSolver* solver;

Plane *plane;
Sphere *sphere;
Sphere *sphere2;
Sphere *sphere3;
Sphere *sphere4;

GLfloat xrot; /* X Rotation ( NEW ) */
GLfloat yrot; /* Y Rotation ( NEW ) */
GLfloat zrot; /* Z Rotation ( NEW ) */


void init_physics();


extern "C" {
JNIEXPORT void JNICALL Java_com_bullet_demo_DemoLib_init(JNIEnv * env, jobject obj,  jint width, jint height);
JNIEXPORT void JNICALL Java_com_bullet_demo_DemoLib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_bullet_demo_DemoLib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	LOGI("OpenGL Init finished");

	glViewport( 0, 0, ( GLint )width, ( GLint )height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	float w = width;
	float h = height;
	glFrustumf(-1.0f, 1.0f, -1*h/w, h/w, 5.0f, 1000.0f);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	LOGI("View Port and frustrum set.");

	init_physics();
	LOGI("Physics initialized");

}



JNIEXPORT void JNICALL Java_com_bullet_demo_DemoLib_step(JNIEnv * env, jobject obj)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	dynamicsWorld->stepSimulation(1/60.f,10);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -40.0f);
	glRotatef( 10, 1.0f, 0.0f, 0.0f); /* Rotate On The X Axis */
	glRotatef( yrot, 0.0f, 1.0f, 0.0f); /* Rotate On The Y Axis */
//	glRotatef( 30, 0.0f, 0.0f, 1.0f); /* Rotate On The Z Axis */

	plane->draw();
	sphere->draw();
	sphere2->draw();
	sphere3->draw();
	sphere4->draw();

	xrot += 0.3f; /* X Axis Rotation */
	yrot += 0.2f; /* Y Axis Rotation */
	zrot += 0.4f; /* Z Axis Rotation */
}



//////////////////////Bullet Physics code////////////////////////////////
void init_physics(){
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));

	plane = new Plane(dynamicsWorld);
	sphere = new Sphere(dynamicsWorld, 0, 20, 0);
	sphere2 = new Sphere(dynamicsWorld, 0.5f, 30, -0.5f);
	sphere3 = new Sphere(dynamicsWorld, -0.5f, 40, 0.5f);
	sphere4 = new Sphere(dynamicsWorld, -0.5f, 50, 0.5f);

}

void remove_physics(){
	delete plane;
	delete sphere;
	delete sphere2;
	delete sphere3;
	delete sphere4;

	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}


