#include"Sphere.h"

short Sphere::indices [] = {
		14, 12, 1,
		12, 14, 13,
		2, 13, 14,
		13, 0, 12,
		16, 1, 12,
		12, 15, 16,
		5, 16, 15,
		12, 0, 15,
		18, 13, 2,
		13, 18, 17,
		3, 17, 18,
		17, 0, 13,
		20, 17, 3,
		17, 20, 19,
		4, 19, 20,
		19, 0, 17,
		21, 19, 4,
		19, 21, 15,
		5, 15, 21,
		15, 0, 19,
		23, 1, 16,
		16, 22, 23,
		10, 23, 22,
		22, 16, 5,
		25, 2, 14,
		14, 24, 25,
		6, 25, 24,
		24, 14, 1,
		27, 3, 18,
		18, 26, 27,
		7, 27, 26,
		26, 18, 2,
		29, 4, 20,
		20, 28, 29,
		8, 29, 28,
		28, 20, 3,
		31, 5, 21,
		21, 30, 31,
		9, 31, 30,
		30, 21, 4,
		32, 23, 10,
		23, 32, 24,
		6, 24, 32,
		24, 1, 23,
		33, 25, 6,
		25, 33, 26,
		7, 26, 33,
		26, 2, 25,
		34, 27, 7,
		27, 34, 28,
		8, 28, 34,
		28, 3, 27,
		35, 29, 8,
		29, 35, 30,
		9, 30, 35,
		30, 4, 29,
		36, 31, 9,
		31, 36, 22,
		10, 22, 36,
		22, 5, 31,
		38, 6, 32,
		32, 37, 38,
		11, 38, 37,
		37, 32, 10,
		39, 7, 33,
		33, 38, 39,
		11, 39, 38,
		38, 33, 6,
		40, 8, 34,
		34, 39, 40,
		11, 40, 39,
		39, 34, 7,
		41, 9, 35,
		35, 40, 41,
		11, 41, 40,
		40, 35, 8,
		37, 10, 36,
		36, 41, 37,
		11, 37, 41,
		41, 36, 9
};
float Sphere::vertices []= {
		0.027778, -1.000000, 0.001226,
		0.751378, -0.447215, 0.526946,
		-0.248607, -0.447215, 0.851866,
		-0.866647, -0.447215, 0.001226,
		-0.248607, -0.447215, -0.849414,
		0.751378, -0.447215, -0.524494,
		0.304163, 0.447215, 0.851866,
		-0.695822, 0.447215, 0.526946,
		-0.695822, 0.447215, -0.524494,
		0.304163, 0.447215, -0.849414,
		0.922203, 0.447215, 0.001226,
		0.027778, 1.000000, 0.001226,
		0.453101, -0.850654, 0.310237,
		-0.134677, -0.850654, 0.501221,
		0.290647, -0.525738, 0.810237,
		0.453101, -0.850654, -0.307786,
		0.878426, -0.525736, 0.001226,
		-0.497952, -0.850652, 0.001226,
		-0.660411, -0.525736, 0.501223,
		-0.134677, -0.850654, -0.498770,
		-0.660411, -0.525736, -0.498771,
		0.290647, -0.525738, -0.807786,
		0.978836, -0.000000, -0.307787,
		0.978836, 0.000000, 0.310238,
		0.615564, 0.000000, 0.810242,
		0.027778, 0.000000, 1.001226,
		-0.560008, 0.000000, 0.810242,
		-0.923280, 0.000000, 0.310238,
		-0.923280, -0.000000, -0.307787,
		-0.560008, -0.000000, -0.807791,
		0.027778, -0.000000, -0.998774,
		0.615564, -0.000000, -0.807791,
		0.715967, 0.525736, 0.501223,
		-0.235091, 0.525738, 0.810237,
		-0.822870, 0.525736, 0.001226,
		-0.235091, 0.525738, -0.807786,
		0.715967, 0.525736, -0.498771,
		0.553508, 0.850652, 0.001226,
		0.190234, 0.850654, 0.501221,
		-0.397545, 0.850654, 0.310237,
		-0.397545, 0.850654, -0.307786,
		0.190234, 0.850654, -0.498770
};


Sphere::Sphere(btDiscreteDynamicsWorld* dynamicsWorld, float x, float y ,float z){
	fallShape = new btSphereShape(1.0f);
	fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(x,y,z)));
	btScalar mass = 1;
	btVector3 fallInertia(0,0,0);
	fallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	this->world = dynamicsWorld;
	dynamicsWorld->addRigidBody(fallRigidBody);
}

Sphere::~Sphere(){
	world->removeRigidBody(fallRigidBody);
	delete fallMotionState;
	delete fallRigidBody;
	delete fallShape;
}

void Sphere::draw(){

	glPushMatrix();
	btTransform trans;
	fallRigidBody->getMotionState()->getWorldTransform(trans);
	float matrix[16] ;
	trans.getOpenGLMatrix(matrix);
	glMultMatrixf (matrix);
	glFrontFace(GL_CW);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);

	glColor4f(255.0f,0.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[0]);
	glColor4f(255.0f,255.0f,0.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[24]);
	glColor4f(0.0f,255.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[48]);
	glColor4f(255.0f,0.0f,0.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[72]);
	glColor4f(0.0f,0.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[96]);
	glColor4f(0.0f,255.0f,0.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[120]);
	glColor4f(255.0f,0.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[144]);
	glColor4f(255.0f,255.0f,0.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[168]);
	glColor4f(0.0f,255.0f,255.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[192]);
	glColor4f(255.0f,0.0f,0.0f,255.0f);
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, &indices[216]);

	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();


}
