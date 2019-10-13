#pragma once

#include <vector>

#include "btBulletDynamicsCommon.h"
#include "CommonInterfaces/CommonExampleInterface.h"
#include "CommonInterfaces/CommonRigidBodyBase.h"

struct Application : public CommonRigidBodyBase
{
public:
	const btVector3 OBJECT_SIZE = btVector3(0.25f, 0.05f, 0.05f);

	Application(GUIHelperInterface* gui);

	// Simulation event handlers
	virtual auto initPhysics() -> void;
	virtual auto stepSimulation(float deltaTime) -> void;
	virtual auto renderScene() -> void;

	// Initialisation
	auto initialise() -> void;
	auto initialise_temporary_objects() -> void;

	auto generate_graphics_objects() -> void;

	// Temporary: create sample simulation objects
	auto create_ground() -> btRigidBody* ;
	auto create_objects(size_t count) -> std::vector<btRigidBody*> ;
	auto create_constraints(const std::vector<btRigidBody*>& objects) -> std::vector<btTypedConstraint*> ;
	auto create_slider_constraint(btRigidBody* const objA, btRigidBody* const objB) -> btTypedConstraint* ;
	auto create_spring_constraint(btRigidBody* const objA, btRigidBody* const objB) -> btGeneric6DofSpring2Constraint* ;
	
	auto reset_camera() -> void;

	virtual ~Application();

private:
	btGeneric6DofSpring2Constraint* m_spring_constraint;
};
