#include "Plane.h"

short Plane::indices [] = {
		0, 1, 2,
		2, 3, 0
};
float Plane::vertices []= {
		10.0f, 0.0f, 10.0f,
		-10.0f, 0.0f, 10.0f,
		-10.0f, 0.0f, -10.0f,
		10.0f, 0.0f, -10.0f,
};


Plane::Plane(btDiscreteDynamicsWorld* dynamicsWorld){
	shape = new btStaticPlaneShape(btVector3(0,1,0),0.0f);
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,motionState,shape,btVector3(0,0,0));
	body = new btRigidBody(groundRigidBodyCI);
	this->world = dynamicsWorld;
	world->addRigidBody(body);
}

Plane::~Plane(){
	world->removeRigidBody(body);
	delete motionState;
	delete body;
	delete shape;
}

void Plane::draw(){

	glPushMatrix();
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	float matrix[16] ;
	trans.getOpenGLMatrix(matrix);
	glMultMatrixf (matrix);
	glFrontFace(GL_CW);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor4f(255.0f,0.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();


}
