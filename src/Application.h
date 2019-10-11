#pragma once

#include <vector>

#include "btBulletDynamicsCommon.h"
#include "CommonInterfaces/CommonExampleInterface.h"
#include "CommonInterfaces/CommonRigidBodyBase.h"

struct Application : public CommonRigidBodyBase
{
public:
	const btVector3 OBJECT_SIZE = btVector3(0.25, 0.05, 0.05);

	Application(GUIHelperInterface* gui);

	// Simulation event handlers
	virtual void initPhysics();
	virtual void stepSimulation(float deltaTime);
	virtual void renderScene();

	// Initialisation
	void initialise();
	void initialise_temporary_objects();

	void generate_graphics_objects();

	// Temporary: create sample simulation objects
	btRigidBody* create_ground();
	std::vector<btRigidBody*> create_objects(size_t count);
	std::vector<btTypedConstraint*> create_constraints(const std::vector<btRigidBody*>& objects);
	btTypedConstraint* create_slider_constraint(btRigidBody* const objA, btRigidBody* const objB);
	btGeneric6DofSpring2Constraint* create_spring_constraint(btRigidBody* const objA, btRigidBody* const objB);
	
	void reset_camera();

	virtual ~Application();

private:
	btGeneric6DofSpring2Constraint* m_spring_constraint;
};
