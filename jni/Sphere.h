/*
 * Triangle.h
 *
 *  Created on: 27-Mar-2011
 *      Author: manoj
 */

#include <GLES/gl.h>
#include <GLES/glext.h>

#include <btBulletDynamicsCommon.h>

class Sphere{

private:

	static short indices [];
	static float vertices [];

	btDiscreteDynamicsWorld* world;
	btCollisionShape* fallShape;
	btDefaultMotionState* fallMotionState;
	btRigidBody* fallRigidBody;

public:
	Sphere(btDiscreteDynamicsWorld* dynamicsWorld, float x, float y ,float z);
	~Sphere();
	void draw();
};

