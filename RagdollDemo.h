/*
Bullet Continuous Collision Detection and Physics Library
RagdollDemo
Copyright (c) 2007 Starbreeze Studios

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Written by: Marten Svanfeldt
*/

#ifndef RAGDOLLDEMO_H
#define RAGDOLLDEMO_H

#include "GlutDemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "BulletDynamics/ConstraintSolver/btHingeConstraint.h"

class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;

class RagdollDemo : public GlutDemoApplication
{

	btAlignedObjectArray<class RagDoll*> m_ragdolls;

	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btBroadphaseInterface*	m_broadphase;

	btCollisionDispatcher*	m_dispatcher;

	btConstraintSolver*	m_solver;

	btDefaultCollisionConfiguration* m_collisionConfiguration;
    
    btRigidBody*         body[9]; // one main body, 4x2 leg segments
    btCollisionShape* geom[9];
    bool pause = false;
    
    btHingeConstraint* joints[8];
    bool oneStep;


public:
	void initPhysics();

	void exitPhysics();

	virtual ~RagdollDemo()
	{
		exitPhysics();
	}
    
    btVector3 PointWorldToLocal(int index, btVector3 &p) {
        btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
        return local1 * p;
    }
    
    btVector3 AxisWorldToLocal(int index, btVector3 &a) {
        btTransform local1 = body[index]->getCenterOfMassTransform().inverse();
        btVector3 zero(0,0,0);
        local1.setOrigin(zero);
        return local1 * a;
    }
    
    void CreateBox( int index,
                   double x, double y, double z,
                   double length, double width, double height);
    
    void CreateCylinder( int index,
                   double x, double y, double z,
                   double diameter, double sideLength,
                   int i_x, int i_y, int i_z, double angle);
    
    void CreateHinge(int index, int body1, int body2, double x, double y, double z, double ax, double ay, double az);
    
    
	void spawnRagdoll(const btVector3& startOffset);

	virtual void clientMoveAndDisplay();

	virtual void displayCallback();

	virtual void keyboardCallback(unsigned char key, int x, int y);

	static DemoApplication* Create()
	{
		RagdollDemo* demo = new RagdollDemo();
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
	
};


#endif
