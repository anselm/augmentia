/*

[ EULA: Revision date: 2009/03/22 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Free Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for any purpose, including
free or commercial applications, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim
that you wrote the original software. 

If you are using the "Free Edition" of this software in a product (either free
or commercial), you are required to display a full-screen "Powered by SIO2 engine"
splash screen logo in the start up sequence of any product created and released
with the SIO2 Engine.

This screen shall be visible for no less than two (2) seconds, using one (1) of
the two (2) files provided with the SIO2 SDK:

(a) "/SIO2_SDK/src/poweredby_p.jpg" for portrait

(b) "/SIO2_SDK/src/poweredby_l.jpg" for landscape.

2. Altered source versions must be plainly marked as such (even for internal use),
and must not be misrepresented as being the original software. You are also invited
to post any modifications done to the SIO2 source, at the following email
address: sio2interactive@gmail.com, for review and possible addition to the SIO2
source tree to make them available to the community and to make SIO2 a better
software. But it is not required to do so.

3. This notice may not be removed or altered from any source distribution.

4. If your product using SIO2 Engine "Free Edition" is made available to the
public ( either in a free or commercial form ) you are required to let us know
by email (sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.




[ EULA: Revision date: 2009/03/23 ]

SIO2 Engine 3D Game for iPhone & iPod Touch :: Indie Edition

Copyright (C) 2009 SIO2 Interactive http://sio2interactive.com

This software is provided 'as-is', without any express or implied warranty.

In no event will the authors be held liable for any damages arising from the use
of this software.

Permission is granted to anyone to use this software for free or commercial applications,
subject to the following restrictions:

1. By using the "SIO2 Indie Edition" you are required to use and include the "sio2.cert"
certificate within your application on a game basis. The certificate will be send to you to
the email that you provide within the purchase form in the next two (2) working days. Certificate
is restricted on a per application basis, you CANNOT reuse the certificate for multiple game
production.

2. By using the "SIO2 Indie Edition" you are entitled of a life time free upgrade to any
subsequent SIO2 versions on a game basis prior to the initial purchase date. Every time
a new version is made available you will receive notification by email within two (2) 
working days after its official release.

3. You must use an independent certificate for every game that you release, either free or
commercial.

4. By using the "SIO2 Indie Edition" you are NOT required to use any splash screen, or
mention of any kind of SIO2 Engine or SIO2 Interactive within your application.

5. By using the "SIO2 Indie Edition" you are entitled to receive customer support and
customer service within working hours (either on IM or by email at sio2interactive@gmail.com).
Every requests will be answered within 48 hours or two (2) working days.

6. You are required to NOT clear the console output and do not override the system log in
order to display at any time on the console prompt the information that your "sio2.cert"
hold, such as your "Game Studio" and "Game Title" as well as your unique certificate key
bundle within your ".app".

7. If your product using SIO2 Engine "Indie Edition" is made available to the public
( either in a free or commercial form ) you are invited to let us know by email
(sio2interactive@gmail.com) the following information:

- The title of your product

- A short description of your product

- A valid URL and screenshot(s) of the product in order for us to put it on our
website (http://sio2interactive.com/GAMES.html) in order to help you promote
your creation(s) as well as promoting the SIO2 project.

But it is NOT required to do so.

If you have any questions or want more information concerning this agreement
please send us an email at: sio2interactive@gmail.com

SIO2 Engine is using other external library and source packages and their
respective license(s), as well as this one, can be found in the 
"/SIO2_SDK/src/LICENSE/" directory, please review all the licenses before
making your product available.

*/

#include "sio2.h"


SIO2physic *sio2PhysicInit( char *_name )
{
	SIO2physic *_SIO2physic = ( SIO2physic * ) calloc( 1, sizeof( SIO2physic ) );
	
	sio2StringCpy( _SIO2physic->name, _name );

	_SIO2physic->_btSoftBodyRigidBodyCollisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();
	_SIO2physic->_btCollisionDispatcher						= new btCollisionDispatcher( _SIO2physic->_btSoftBodyRigidBodyCollisionConfiguration );	
	_SIO2physic->_btBroadphaseInterface						= new btDbvtBroadphase();
	_SIO2physic->_btConstraintSolver						= new btSequentialImpulseConstraintSolver();
	
	_SIO2physic->_btSoftBodyWorldInfo.m_dispatcher			= _SIO2physic->_btCollisionDispatcher;
	_SIO2physic->_btSoftBodyWorldInfo.m_broadphase			= _SIO2physic->_btBroadphaseInterface;
	
	_SIO2physic->_btSoftRigidDynamicsWorld = new btSoftRigidDynamicsWorld( _SIO2physic->_btCollisionDispatcher,	
																		   _SIO2physic->_btBroadphaseInterface,
																		   _SIO2physic->_btConstraintSolver,
																		   _SIO2physic->_btSoftBodyRigidBodyCollisionConfiguration );
	gContactAddedCallback = sio2PhysicCollisionCallback;

	_SIO2physic->_btSoftBodyWorldInfo.m_sparsesdf.Initialize();

	sio2ResourceAdd( sio2->_SIO2resource,
					 SIO2_PHYSIC,
					 ( void * )_SIO2physic );

	return _SIO2physic;
}


SIO2physic *sio2PhysicFree( SIO2physic *_SIO2physic )
{
	sio2PhysicRemoveAllObjects( _SIO2physic );

	delete _SIO2physic->_btSoftBodyRigidBodyCollisionConfiguration;
	delete _SIO2physic->_btCollisionDispatcher;
	delete _SIO2physic->_btBroadphaseInterface;
	delete _SIO2physic->_btConstraintSolver;
	delete _SIO2physic->_btSoftRigidDynamicsWorld;

	_SIO2physic->_btSoftBodyRigidBodyCollisionConfiguration = NULL;
	_SIO2physic->_btCollisionDispatcher						= NULL;
	_SIO2physic->_btBroadphaseInterface						= NULL;
	_SIO2physic->_btConstraintSolver						= NULL;
	_SIO2physic->_btSoftRigidDynamicsWorld					= NULL;


	sio2ResourceDel( sio2->_SIO2resource,
					 SIO2_PHYSIC,
					 (void *)_SIO2physic );

	_SIO2physic->_btSoftBodyWorldInfo.m_sparsesdf.Reset();
	_SIO2physic->_btSoftBodyWorldInfo.m_sparsesdf.cells.clear();

	free( _SIO2physic );

	return NULL;
}


void sio2PhysicAddObject( SIO2physic *_SIO2physic,
						  SIO2object *_SIO2object )
{
	if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_SOFTBODY ) )
	{ sio2PhysicAddSoftBody( _SIO2physic, _SIO2object ); }
	
	else
	{ sio2PhysicAddRigidBody( _SIO2physic, _SIO2object ); }
}


void sio2PhysicAddRigidBody( SIO2physic *_SIO2physic,
							 SIO2object *_SIO2object )
{
	unsigned int i = 0;
	
	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;
	
	btCollisionShape *_btCollisionShape;
	btDefaultMotionState *_btDefaultMotionState;

	btTransform _btTransform;
	btVector3 _btVector3( 0.0f, 0.0f, 0.0f );
	
	if( _SIO2object->_SIO2objectphysic->_btRigidBody )
	{ return; }	
	
	switch( _SIO2object->_SIO2objectphysic->bounds )
	{
		case SIO2_PHYSIC_BOX:
		{
			_btCollisionShape = new btBoxShape( btVector3( _SIO2object->dim->x * _SIO2object->_SIO2transform->scl->x,
														   _SIO2object->dim->y * _SIO2object->_SIO2transform->scl->y,
														   _SIO2object->dim->z * _SIO2object->_SIO2transform->scl->z ) );
			break;
		}
		
		case SIO2_PHYSIC_SPHERE:
		{
			_btCollisionShape = new btSphereShape( _SIO2object->rad * 0.575f );
			break;
		}
		
		case SIO2_PHYSIC_CYLINDER:
		{
			_btCollisionShape = new btCylinderShapeZ( btVector3( _SIO2object->dim->x * _SIO2object->_SIO2transform->scl->x,
																 _SIO2object->dim->y * _SIO2object->_SIO2transform->scl->y,
																 _SIO2object->dim->z * _SIO2object->_SIO2transform->scl->z ) );
			break;
		}
		
		case SIO2_PHYSIC_CONE:
		{
			_btCollisionShape = new btConeShapeZ(   _SIO2object->dim->x * _SIO2object->_SIO2transform->scl->x,
												  ( _SIO2object->dim->z * 2.0f ) * _SIO2object->_SIO2transform->scl->z );
			break;
		}
		
		case SIO2_PHYSIC_TRIANGLEMESH:
		{
			unsigned int j;
		
			btVector3 tri[ 3 ];
			
			_SIO2object->_SIO2objectphysic->_btTriangleMesh = new btTriangleMesh();

			while( i != tmp->n_vgroup )
			{
				if( tmp->_SIO2vertexgroup[ i ]->mode == GL_TRIANGLES )
				{
					j = 0;
					while( j != tmp->_SIO2vertexgroup[ i ]->n_ind )
					{
						memcpy( &tri[ 0 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j     ] * 12 ], 12 );
						memcpy( &tri[ 1 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j + 1 ] * 12 ], 12 );
						memcpy( &tri[ 2 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j + 2 ] * 12 ], 12 );
						
						_SIO2object->_SIO2objectphysic->_btTriangleMesh->addTriangle( tri[ 0 ], tri[ 1 ], tri[ 2 ], 1 );
						j += 3;
					}
				}
				
				else if( tmp->_SIO2vertexgroup[ i ]->mode == GL_TRIANGLE_STRIP )
				{
					j = 2;
					while( j != tmp->_SIO2vertexgroup[ i ]->n_ind )
					{
						memcpy( &tri[ 0 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j - 2 ] * 12 ], 12 );
						memcpy( &tri[ 1 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j - 1 ] * 12 ], 12 );
						memcpy( &tri[ 2 ][ 0 ], &tmp->buf[ tmp->_SIO2vertexgroup[ i ]->ind[ j     ] * 12 ], 12 );
						
						_SIO2object->_SIO2objectphysic->_btTriangleMesh->addTriangle( tri[ 0 ], tri[ 1 ], tri[ 2 ], 1 );
						++j;
					}				
				}
			
				++i;
			}
			
			_btCollisionShape = new btBvhTriangleMeshShape( _SIO2object->_SIO2objectphysic->_btTriangleMesh, 1, 1 );

			break;
		}
		
		case SIO2_PHYSIC_CONVEXHULL:
		{
			unsigned int n_vert = sio2ObjectGetNumVert( tmp );
				
			btVector3 vert;
		
			_SIO2object->_SIO2objectphysic->_btConvexHullShape = new btConvexHullShape();
			
			_SIO2object->_SIO2objectphysic->_btConvexHullShape->setMargin( 0.25f );
			
			while( i != n_vert )
			{
				memcpy( &vert[ 0 ], &tmp->buf[ i * 12 ], 12 );
				
				_SIO2object->_SIO2objectphysic->_btConvexHullShape->addPoint( vert );
			
				++i;
			}
	
			_btCollisionShape = _SIO2object->_SIO2objectphysic->_btConvexHullShape;

			break;
		}
	}
	
	_btTransform.setIdentity();

	_btTransform.setFromOpenGLMatrix( _SIO2object->_SIO2transform->mat );

	_btDefaultMotionState = new btDefaultMotionState( _btTransform );
	
	
	if( _SIO2object->_SIO2objectphysic->mass )
	{			
		_btCollisionShape->calculateLocalInertia( _SIO2object->_SIO2objectphysic->mass,
												  _btVector3 );
	}


	if( _SIO2object->_SIO2objectphysic->margin )
	{
		_btCollisionShape->setMargin( _SIO2object->_SIO2objectphysic->margin );
	}


	_SIO2object->_SIO2objectphysic->_btRigidBody = new btRigidBody( _SIO2object->_SIO2objectphysic->mass,
												 _btDefaultMotionState,
												 _btCollisionShape,
												 _btVector3 );


	if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_DYNAMIC ) )
	{
		if( !sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_RIGIDBODY ) )
		{ _SIO2object->_SIO2objectphysic->_btRigidBody->setAngularFactor( 0.0f ); }
		
		_SIO2object->_SIO2objectphysic->_btRigidBody->setDamping( _SIO2object->_SIO2objectphysic->damp,
											   _SIO2object->_SIO2objectphysic->rotdamp );
	}
	
	
	if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_NOSLEEPING ) )
	{ _SIO2object->_SIO2objectphysic->_btRigidBody->setActivationState( DISABLE_DEACTIVATION ); }


	if( sio2IsStateEnabled( _SIO2object->flags, SIO2_OBJECT_GHOST ) )
	{
		_SIO2object->_SIO2objectphysic->_btRigidBody->setCollisionFlags( _SIO2object->_SIO2objectphysic->_btRigidBody->getCollisionFlags() |
													  btCollisionObject::CF_NO_CONTACT_RESPONSE );
	}
	
	
	if( tmp->n_vgroup )
	{
		i = 0;
		while( i != tmp->n_vgroup )
		{
			if( tmp->_SIO2vertexgroup[ i ]->_SIO2material )
			{
				_SIO2object->_SIO2objectphysic->_btRigidBody->setFriction( tmp->_SIO2vertexgroup[ i ]->_SIO2material->friction );
				_SIO2object->_SIO2objectphysic->_btRigidBody->setRestitution( tmp->_SIO2vertexgroup[ i ]->_SIO2material->restitution );
				break;
			}
			
			++i;
		}
	}

	_SIO2object->_SIO2objectphysic->_btRigidBody->setUserPointer( _SIO2object );
	
	_SIO2physic->_btSoftRigidDynamicsWorld->addRigidBody( _SIO2object->_SIO2objectphysic->_btRigidBody );
}


void sio2PhysicAddSoftBody( SIO2physic *_SIO2physic,
							SIO2object *_SIO2object )
{
	unsigned int i = 0,
				 j;

	btTransform _btTransform;

	SIO2object *tmp = _SIO2object->_SIO2instance ? ( SIO2object * )_SIO2object->_SIO2instance : _SIO2object;

	unsigned int n_vert = sio2ObjectGetNumVert( tmp );
	
	btVector3 *buf = ( btVector3 * )malloc( n_vert * sizeof( btVector3 ) );


	if( _SIO2object->_SIO2objectphysic->_btSoftBody )
	{ return; }
	

	while( i != n_vert )
	{
		memcpy( &buf[ i ], &tmp->buf[ i * 12 ], 12 );
		++i;
	}
	
	_SIO2object->_SIO2objectphysic->_btSoftBody = new btSoftBody( &_SIO2physic->_btSoftBodyWorldInfo,
																  n_vert,
																  buf,
																  NULL );
	
	i = 0;
	while( i != tmp->n_vgroup )
	{
		j = 0;
		while( j != tmp->_SIO2vertexgroup[ i ]->n_ind )
		{
			_SIO2object->_SIO2objectphysic->_btSoftBody->appendFace( tmp->_SIO2vertexgroup[ i ]->ind[ j     ],
																	 tmp->_SIO2vertexgroup[ i ]->ind[ j + 1 ],
																	 tmp->_SIO2vertexgroup[ i ]->ind[ j + 2 ] );
			j += 3;
		}
	
		++i;
	}
	free( buf );
	buf = NULL;


	if( _SIO2object->_SIO2objectphysic->margin )
	{ _SIO2object->_SIO2objectphysic->_btSoftBody->getCollisionShape()->setMargin( _SIO2object->_SIO2objectphysic->margin ); }

	_btTransform.setIdentity();
	
	_btTransform.setFromOpenGLMatrix( _SIO2object->_SIO2transform->mat );
	
	_SIO2object->_SIO2objectphysic->_btSoftBody->transform( _btTransform );
	
	btSoftBody::Material *_Material = _SIO2object->_SIO2objectphysic->_btSoftBody->m_materials[ 0 ];	

	
	if( _SIO2object->_SIO2objectphysic-> linstiff )
	{ _Material->m_kLST = _SIO2object->_SIO2objectphysic-> linstiff; }	

	
	_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.piterations = _SIO2object->_SIO2objectphysic->piteration;
	
	_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.citerations = _SIO2object->_SIO2objectphysic->citeration;
	
	if( _SIO2object->_SIO2objectphysic->shapematch )
	{
		_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kMT  = _SIO2object->_SIO2objectphysic->shapematch;
		_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kDP  = 0.0f;
		_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kCHR = 1.0f;
		_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kKHR = 0.8f;
		_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kSHR = 1.0f;		
		
		_SIO2object->_SIO2objectphysic->_btSoftBody->setPose( false, true );
	}
	else
	{ _SIO2object->_SIO2objectphysic->_btSoftBody->setPose( true, false ); }

	
	if( tmp->n_vgroup )
	{
		i = 0;
		while( i != tmp->n_vgroup )
		{
			if( tmp->_SIO2vertexgroup[ i ]->_SIO2material )
			{
				_SIO2object->_SIO2objectphysic->_btSoftBody->m_cfg.kDF = tmp->_SIO2vertexgroup[ i ]->_SIO2material->friction * 0.01f;
				break;
			}
			
			++i;
		}
	}

	_SIO2object->_SIO2objectphysic->_btSoftBody->prepareClusters( 16 );

	_SIO2object->_SIO2objectphysic->_btSoftBody->setTotalMass( _SIO2object->_SIO2objectphysic->mass, true );

	_SIO2object->_SIO2objectphysic->_btSoftBody->randomizeConstraints();
	
	_SIO2object->_SIO2objectphysic->_btSoftBody->setUserPointer( _SIO2object );	
	
	_SIO2physic->_btSoftRigidDynamicsWorld->addSoftBody( _SIO2object->_SIO2objectphysic->_btSoftBody );
}


void sio2PhysicAddCamera( SIO2physic *_SIO2physic,
						  SIO2camera *_SIO2camera )
{
	btCollisionShape		*_btCollisionShape;
	btDefaultMotionState	*_btDefaultMotionState;
	btTransform				 _btTransform;
	btMatrix3x3				 _btMatrix3x3;
		
	btVector3				 _btVector3( 0.0f, 0.0f, 0.0f );

	
	_btCollisionShape = new btCylinderShapeZ( btVector3( _SIO2camera->rad,
														 0.0f,
														 _SIO2camera->height ) );
	
	_btTransform.setIdentity();
	
	_btTransform.setOrigin( btVector3( _SIO2camera->_SIO2transform->loc->x,
									   _SIO2camera->_SIO2transform->loc->y,
									   _SIO2camera->_SIO2transform->loc->z ) );
	
	_btDefaultMotionState = new btDefaultMotionState( _btTransform );
	
	_btCollisionShape->calculateLocalInertia( _SIO2camera->mass,
											  _btVector3 );
	
	_SIO2camera->_btRigidBody = new btRigidBody( _SIO2camera->mass,
												 _btDefaultMotionState,
												 _btCollisionShape,
												 _btVector3 );

	_SIO2camera->_btRigidBody->setAngularFactor( 0.0f );
	
	_SIO2camera->_btRigidBody->setFriction( _SIO2camera->friction );
	
	_SIO2camera->_btRigidBody->setRestitution( _SIO2camera->restitution );
	
	_SIO2physic->_btSoftRigidDynamicsWorld->addRigidBody( _SIO2camera->_btRigidBody );
	
	_SIO2camera->_btRigidBody->setUserPointer( _SIO2camera );
}


void sio2PhysicRemoveObject( SIO2physic *_SIO2physic,
						     SIO2object *_SIO2object )
{
	int i = 0;

	if( !_SIO2object->_SIO2objectphysic->_btRigidBody && !_SIO2object->_SIO2objectphysic->_btSoftBody )
	{ return; }

	while( i != _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ i ];
		
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );
		
		btSoftBody *_btSoftBody  = btSoftBody::upcast( _btCollisionObject );
		
		
		if( _btRigidBody && _btRigidBody == _SIO2object->_SIO2objectphysic->_btRigidBody )
		{
			delete _btRigidBody->getCollisionShape();
			
			delete _btRigidBody->getMotionState();
			
			_SIO2physic->_btSoftRigidDynamicsWorld->removeRigidBody( _btRigidBody );
			_SIO2physic->_btSoftRigidDynamicsWorld->removeCollisionObject( _btCollisionObject );
			
			delete _btRigidBody;

			_SIO2object->_SIO2objectphysic->_btRigidBody = NULL;
			
			break;
		}
		
		else if( _btSoftBody && _btSoftBody == _SIO2object->_SIO2objectphysic->_btSoftBody )
		{
			_SIO2physic->_btSoftRigidDynamicsWorld->removeSoftBody( _btSoftBody );
			_SIO2physic->_btSoftRigidDynamicsWorld->removeCollisionObject( _btCollisionObject );
			
			delete _btSoftBody;

			_SIO2object->_SIO2objectphysic->_btSoftBody = NULL;
			
			break;
		}
		
		++i;
	}
}


void sio2PhysicRemoveAllObjects( SIO2physic *_SIO2physic )
{
	while( _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ 0 ];
		
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );

		if( _btRigidBody )
		{
			delete _btRigidBody->getCollisionShape();
			
			delete _btRigidBody->getMotionState();
			
			_SIO2physic->_btSoftRigidDynamicsWorld->removeRigidBody( _btRigidBody );
			
			_SIO2physic->_btSoftRigidDynamicsWorld->removeCollisionObject( _btCollisionObject );
			
			delete _btRigidBody;
		}
		else
		{
			btSoftBody *_btSoftBody = btSoftBody::upcast( _btCollisionObject );
			
			_SIO2physic->_btSoftRigidDynamicsWorld->removeSoftBody( _btSoftBody );
			_SIO2physic->_btSoftRigidDynamicsWorld->removeCollisionObject( _btCollisionObject );
			
			delete _btSoftBody;
		}
	}
	

	while( _SIO2physic->_btSoftRigidDynamicsWorld->getNumConstraints() )
	{
		btTypedConstraint *_btTypedConstraint = _SIO2physic->_btSoftRigidDynamicsWorld->getConstraint( 0 );
		
		_SIO2physic->_btSoftRigidDynamicsWorld->removeConstraint( _btTypedConstraint );
		
		delete _btTypedConstraint;
	}
}


void sio2PhysicRemoveCamera( SIO2physic *_SIO2physic,
						     SIO2camera *_SIO2camera )
{
	int i = 0;

	if( !_SIO2camera->_btRigidBody )
	{ return; }


	while( i != _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ i ];
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );
		
		if( _btRigidBody == _SIO2camera->_btRigidBody )
		{
			delete _btRigidBody->getCollisionShape();
			
			delete _btRigidBody->getMotionState();
		
			_SIO2physic->_btSoftRigidDynamicsWorld->removeRigidBody( _btRigidBody );
			
			_SIO2physic->_btSoftRigidDynamicsWorld->removeCollisionObject( _btCollisionObject );
		
			delete _SIO2camera->_btRigidBody;
			_SIO2camera->_btRigidBody = NULL;
			
			delete _btCollisionObject;
						
			break;
		}
		
		++i;
	}
}


void sio2PhysicSetGravity( SIO2physic *_SIO2physic,
						   vec3		  *_grav )
{
	_SIO2physic->_btSoftRigidDynamicsWorld->setGravity( btVector3( _grav->x,
																   _grav->y,
																   _grav->z ) );

	_SIO2physic->_btSoftBodyWorldInfo.m_gravity.setValue( _grav->x,
													      _grav->y,
														  _grav->z );
														   
	_SIO2physic->_btSoftBodyWorldInfo.air_density   = 1.2f;
	_SIO2physic->_btSoftBodyWorldInfo.water_density = 0.0f;
	_SIO2physic->_btSoftBodyWorldInfo.water_offset  = 0.0f;
	_SIO2physic->_btSoftBodyWorldInfo.water_normal  = btVector3( 0.0f, 0.0f, 1.0f );
}


void sio2PhysicResetObject( SIO2physic *_SIO2physic,
							SIO2object *_SIO2object )
{
	int i = 0;
	
	if( !_SIO2object->_SIO2objectphysic->_btRigidBody && !_SIO2object->_SIO2objectphysic->_btSoftBody )
	{ return; }
	
	while( i != _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ i ];
		
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );


		if( !_btRigidBody )
		{
			++i;
			continue;
		}


		if( _SIO2object->_SIO2objectphysic->_btRigidBody == _btRigidBody )
		{
			sio2PhysicResetRigidBody( _SIO2physic,
									  _btRigidBody,
									  _btCollisionObject );	
			break;
		}
		
		// TODO: Reset soft bodies...
		++i;
	}
}


void sio2PhysicResetCamera( SIO2physic *_SIO2physic,
							SIO2camera *_SIO2camera )
{
	int i = 0;
	
	if( !_SIO2camera->_btRigidBody )
	{ return; }
	
	while( i != _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ i ];
		
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );

		if( !_btRigidBody )
		{
			++i;
			continue;
		}

		if( _SIO2camera->_btRigidBody == _btRigidBody )
		{
			sio2PhysicResetRigidBody( _SIO2physic,
									  _btRigidBody,
									  _btCollisionObject );		
			break;
		}
		
		++i;
	}
}


void sio2PhysicResetRigidBody( SIO2physic		 *_SIO2physic,
							   btRigidBody		 *_btRigidBody,
							   btCollisionObject *_btCollisionObject )
{
	if( _btRigidBody->getMotionState() )
	{
		btDefaultMotionState *_btDefaultMotionState = ( btDefaultMotionState * )_btRigidBody->getMotionState();
		_btDefaultMotionState->m_graphicsWorldTrans = _btDefaultMotionState->m_startWorldTrans;
		
		_btCollisionObject->setWorldTransform( _btDefaultMotionState->m_graphicsWorldTrans );
		_btCollisionObject->setInterpolationWorldTransform( _btDefaultMotionState->m_startWorldTrans );
		_btCollisionObject->activate();
	}
				
	_SIO2physic->_btSoftRigidDynamicsWorld->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs( _btCollisionObject->getBroadphaseHandle(),
																											 _SIO2physic->_btSoftRigidDynamicsWorld->getDispatcher() );
	
	if( !_btRigidBody->isStaticObject() )
	{
		btRigidBody::upcast( _btCollisionObject )->setLinearVelocity ( btVector3( 0, 0, 0 ) );
		btRigidBody::upcast( _btCollisionObject )->setAngularVelocity( btVector3( 0, 0, 0 ) );
	}
}


void sio2PhysicResetAll( SIO2physic *_SIO2physic )
{ 
	int i = 0;
	
	while( i != _SIO2physic->_btSoftRigidDynamicsWorld->getNumCollisionObjects() )
	{
		btCollisionObject *_btCollisionObject = _SIO2physic->_btSoftRigidDynamicsWorld->getCollisionObjectArray()[ i ];
		
		btRigidBody *_btRigidBody = btRigidBody::upcast( _btCollisionObject );

		if( !_btRigidBody )
		{
			++i;
			continue;
		}

		sio2PhysicResetRigidBody( _SIO2physic,
								  _btRigidBody,
								  _btCollisionObject );
		++i;
	}
}


void sio2PhysicPlay( SIO2physic *_SIO2physic )
{ _SIO2physic->state = SIO2_PLAY; }


void sio2PhysicPause( SIO2physic *_SIO2physic )
{ _SIO2physic->state = SIO2_PAUSE; }


void sio2PhysicStop( SIO2physic *_SIO2physic )
{ _SIO2physic->state = SIO2_STOP; }


void sio2PhysicRender( SIO2physic *_SIO2physic,
					   float	   _timestep,
					   int		   _pass )
{
	unsigned int i = 0;
	
	if( _SIO2physic->state == SIO2_PLAY )
	{
		float sub = _timestep / ( float )_pass;

		while( i != _pass )
		{
			_SIO2physic->_btSoftRigidDynamicsWorld->stepSimulation( sub, 0 );
			++i;
		}
	}
}
