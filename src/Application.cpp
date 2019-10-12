#include "Application.h"

#include <iostream>
#include <vector>

#include "CommonInterfaces/CommonRigidBodyBase.h"
#include "CommonInterfaces/CommonParameterInterface.h"

#include "Genetics/Dna.h"
#include "Genetics/DnaWriter.h"
#include "Entity/Entity.h"


Application::Application(GUIHelperInterface *gui)
	: 
	CommonRigidBodyBase(gui),
	m_spring_constraint(nullptr)
{
}


void Application::initialise()
{
	initPhysics();		// Simulation interface
	
	initialise_temporary_objects();

	reset_camera();
	generate_graphics_objects();
}

void Application::initialise_temporary_objects()
{
	// Create simulation objects
	auto ground = create_ground();
	auto objects = create_objects(5);
	auto constraints = create_constraints(objects);
	//auto slider = create_slider_constraint(objects[0], objects.back());
	m_spring_constraint = create_spring_constraint(objects[0], objects.back());
}


void Application::initPhysics()
{
	// Set up empty world and debug drawing
	m_guiHelper->setUpAxis(1);

	createEmptyDynamicsWorld();
	m_guiHelper->createPhysicsDebugDrawer(m_dynamicsWorld);

	if (m_dynamicsWorld->getDebugDrawer())
		m_dynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe + btIDebugDraw::DBG_DrawConstraints + btIDebugDraw::DBG_DrawConstraintLimits);
}

void Application::generate_graphics_objects()
{
	// TODO: need to reset first?
	m_guiHelper->autogenerateGraphicsObjects(m_dynamicsWorld);
}

void Application::stepSimulation(float deltaTime)
{
	static float timer = 0.0f;
	timer += deltaTime;

	CommonRigidBodyBase::stepSimulation(deltaTime);

	if (timer > 2.0f)
	{
		timer -= 2.0f;
		if (m_spring_constraint)
			m_spring_constraint->getTranslationalLimitMotor()->m_targetVelocity[0] *= -1;
	}

	if (m_spring_constraint)
		std::cout << "Step; dt = " << deltaTime << ", target_vel = " << m_spring_constraint->getTranslationalLimitMotor()->m_targetVelocity[0] << "\n";
}

btRigidBody *Application::create_ground()
{
	btBoxShape *groundShape = createBoxShape(btVector3(50.0, 50.0, 50.0));

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0.0, -50.0, 0.0));

	m_collisionShapes.push_back(groundShape);

	return createRigidBody(0.0f, groundTransform, groundShape, btVector4(0, 1, 0, 1));
}

std::vector<btRigidBody *> Application::create_objects(size_t count)
{
	std::vector<btRigidBody *> objects;

	btBoxShape *objectShape = createBoxShape(OBJECT_SIZE);
	m_collisionShapes.push_back(objectShape);

	btTransform transform;
	transform.setIdentity();

	float offset = static_cast<float>(count) * objectShape->getHalfExtentsWithMargin().x() * -1.0f;  //0.5f;

	for (auto i = 0; i < count; ++i)
	{
		bool isDynamic = (i != 0);
		float mass = (isDynamic ? 1.0f : 0.0f);

		btVector3 localInertia;
		if (isDynamic)
			objectShape->calculateLocalInertia(mass, localInertia);

		btVector3 pos(offset + (static_cast<float>(i) * objectShape->getHalfExtentsWithMargin().x() * 2.0f), 1.0f, 0.0f);
		transform.setOrigin(pos);

		objects.push_back(createRigidBody(mass, transform, objectShape));
	}
	
	return objects;
}

std::vector<btTypedConstraint *> Application::create_constraints(const std::vector<btRigidBody *> &objects)
{
	std::vector<btTypedConstraint *> constraints;

	btVector3 axis(0.0f, 0.0f, 1.0);
	btVector3 pivot(OBJECT_SIZE.x() * 1.1f, 0.0f, 0.0f);

	for (auto i = 0; i < objects.size() - 1; ++i)
	{
		auto constraint = new btHingeConstraint(*objects[i], *objects[i + 1], -pivot, pivot, axis, axis);

		m_dynamicsWorld->addConstraint(constraint);
		constraints.push_back(constraint);
	}

	return constraints;
}

btTypedConstraint *Application::create_slider_constraint(btRigidBody *const objA, btRigidBody *const objB)
{
	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(SIMD_PI, 0.0f, 0.0f));

	auto slider = new btSliderConstraint(*objA, *objB, transform, transform, true);
	slider->setUpperLinLimit(10000.0f);
	slider->setUpperAngLimit(SIMD_2_PI);
	slider->setDbgDrawSize(5.0f);

	m_dynamicsWorld->addConstraint(slider);
	return slider;
}

btGeneric6DofSpring2Constraint *Application::create_spring_constraint(btRigidBody *const objA, btRigidBody *const objB)
{
	static int index = -1;
	index += 1;

	btTransform transform;
	transform.setIdentity();
	transform.setRotation(btQuaternion(SIMD_PI, 0.0f, 0.0f));

	auto spring = new btGeneric6DofSpring2Constraint(*objA, *objB, transform, transform);
	spring->setLinearUpperLimit(btVector3(1000.0f, 0.5f, 0.5f));
	spring->setLinearLowerLimit(btVector3(0.5f, 0.0f, 0.0f));
	spring->setAngularUpperLimit(btVector3(SIMD_2_PI, SIMD_PI/180.0f * 5.0f, 0.0f));
	spring->setMaxMotorForce(0, 20.0f);
	spring->enableMotor(0, true);
	
	auto motor = spring->getTranslationalLimitMotor();
	motor->m_enableMotor[0] = true;
	motor->m_targetVelocity = btVector3(20.0f, 0.0f, 0.0f);
	motor->m_upperLimit = btVector3(1000.0f, 1.0f, 1.0f);

	spring->setDbgDrawSize(5.0f);

	m_dynamicsWorld->addConstraint(spring);
	return spring;
}

void Application::renderScene()
{
	CommonRigidBodyBase::renderScene();
}

void Application::reset_camera()
{
	m_guiHelper->resetCamera(4.0f, 52.0f, -35.0f, 0.0f, 0.0f, 0.0f);
}

Application::~Application()
{
}
