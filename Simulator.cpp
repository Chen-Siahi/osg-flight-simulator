#include "Simulator.h"
#include "ModelController.h"

void Simulator::createGroundNode()
{
	osg::ref_ptr<osg::MatrixTransform> groundNode = new osg::MatrixTransform;
	groundNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\lz.osg"));
	groundNode->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -200.0f));
	setGroundNode(groundNode);
}

void Simulator::createCessnaNode()
{
	osg::ref_ptr<osg::MatrixTransform> cessnaNode = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform> cessnaFiredNode = new osg::MatrixTransform;
	cessnaNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\cessna.osg.0,0,90.rot"));
	cessnaFiredNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\cessnafire.osg"));
	setCessnaNode(cessnaNode);
	setCessnaFiredNode(cessnaFiredNode);
}

void Simulator::createTruckNode()
{
	osg::ref_ptr<osg::MatrixTransform> truckNode = new osg::MatrixTransform;
	truckNode->addChild(osgDB::readNodeFile("C:\\Users\\Chen\\Desktop\\Simulator projet\\OpenSceneGraph-Data\\dumptruck.osg"));
	truckNode->setMatrix(osg::Matrix::translate(0.0f, 0.0f, -100.0f));
	setTruckNode(truckNode);
}

void Simulator::loadViewer()
{
	_root->addChild(getGroundNode().get());
	_root->addChild(getCessnaNode().get(), true);
	_root->addChild(getCessnaFiredNode().get(), false); //invisible
	_root->addChild(getTruckNode().get());

	osg::ref_ptr<ModelController> ctrler = new ModelController(getCessnaNode());

	osgViewer::Viewer* viewer = new osgViewer::Viewer();
	viewer->addEventHandler(ctrler.get());
	viewer->setSceneData(_root.get());
	viewer->realize();
	setViewer(viewer);

	while (!getViewer()->done()) {
		//camera follows the cessna
		getViewer()->getCamera()->setViewMatrixAsLookAt(osg::Vec3(100.f, -100.f, 0.f), getCessnaNode()->getBound().center(), osg::Z_AXIS);
		//collision between cessna and truck
		if (getCessnaNode()->getBound().intersects(getTruckNode()->getBound())) {
			_root->setChildValue(getCessnaNode().get(), false);
			_root->setChildValue(getCessnaFiredNode().get(), true);
			getCessnaFiredNode()->setMatrix(getCessnaNode()->getMatrix());
		}
		getViewer()->frame();
	}
}