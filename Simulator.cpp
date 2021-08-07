#include "Simulator.h"
#include "ModelController.h"

void Simulator::createGroundNode()
{
	osg::ref_ptr<osg::MatrixTransform> groundNode = new osg::MatrixTransform;
	groundNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\lz.osg"));
	groundNode->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -200.0f));
	_groundNode = groundNode;
	_root->addChild(_groundNode.get());
}

void Simulator::createCessnaNode()
{
	osg::ref_ptr<osg::MatrixTransform> cessnaNode = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform> cessnaFiredNode = new osg::MatrixTransform;
	cessnaNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\cessna.osg.0,0,90.rot"));
	cessnaFiredNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\cessnafire.osg"));
	_cessnaNode = cessnaNode;
	_cessnaFiredNode = cessnaFiredNode;
	_root->addChild(_cessnaNode.get(), true);
	_root->addChild(_cessnaFiredNode.get(), false);
}

void Simulator::createTruckNode()
{
	osg::ref_ptr<osg::MatrixTransform> truckNode = new osg::MatrixTransform;
	truckNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\dumptruck.osg"));
	truckNode->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -100.0f));
	_truckNode = truckNode;
	_root->addChild(_truckNode.get());
}

void Simulator::loadViewer()
{
	osg::ref_ptr<ModelController> ctrler = new ModelController(_cessnaNode);
	_viewer.addEventHandler(ctrler.get());
	_viewer.setSceneData(_root.get());
	_viewer.realize();

	while (!_viewer.done()) {
		_viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3(100.f, -100.f, 0.f), _cessnaNode->getBound().center(), osg::Z_AXIS);
		if (_cessnaNode->getBound().intersects(_truckNode->getBound())) {
			_root->setChildValue(_cessnaNode.get(), false);
			_root->setChildValue(_cessnaFiredNode.get(), true);
			_cessnaFiredNode->setMatrix(_cessnaNode->getMatrix());
		}
		_viewer.frame();
	}
}

osg::AnimationPath* Simulator::createAnimationPath(float radius, float time)
{
	osg::ref_ptr<osg::AnimationPath> path =	new osg::AnimationPath;
	path->setLoopMode(osg::AnimationPath::LOOP);
	unsigned int numSamples = 32;
	float delta_yaw = 2.0f * osg::PI / ((float)numSamples - 1.0f);
	float delta_time = time / (float)numSamples;
	for (unsigned int i = 0; i < numSamples; ++i)
	{
		float yaw = delta_yaw * (float)i;
		osg::Vec3 pos(sinf(yaw) * radius, cosf(yaw) * radius, 0.0f);
		osg::Quat rot(-yaw, osg::Z_AXIS);
		path->insert(i,	osg::AnimationPath::ControlPoint(pos, rot)
		);
	}
	return path.release();
}

