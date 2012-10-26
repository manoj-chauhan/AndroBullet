/*
 * Triangle.h
 *
 *  Created on: 27-Mar-2011
 *      Author: manoj
 */


#include <GLES/gl.h>
#include <GLES/glext.h>

#include <btBulletDynamicsCommon.h>

class Plane{

private:

	static short indices [];
	static float vertices [];

	btDiscreteDynamicsWorld* world;
	btCollisionShape* shape;
	btDefaultMotionState* motionState;
	btRigidBody* body;

public:
	Plane(btDiscreteDynamicsWorld* dynamicsWorld);
	~Plane();
	void draw();
};

