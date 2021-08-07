#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgViewer/Viewer>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>

class Simulator {
public:
	osgViewer::Viewer _viewer;
	osg::ref_ptr<osg::MatrixTransform> _groundNode;
	osg::ref_ptr<osg::MatrixTransform> _cessnaNode;
	osg::ref_ptr<osg::MatrixTransform> _cessnaFiredNode;
	osg::ref_ptr<osg::MatrixTransform> _truckNode;
	osg::ref_ptr<osg::Switch> _root = new osg::Switch;
	public:
		void createGroundNode();
		void createCessnaNode();
		void createTruckNode();
		void loadViewer();
};