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
	private:
		osgViewer::Viewer* _viewer;
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

	//setters and getters for internal use
	private:
		osgViewer::Viewer* getViewer() {	return _viewer;	}
		osg::ref_ptr<osg::MatrixTransform> getGroundNode() { return _groundNode; }
		osg::ref_ptr<osg::MatrixTransform> getCessnaNode() { return _cessnaNode; }
		osg::ref_ptr<osg::MatrixTransform> getCessnaFiredNode() { return _cessnaFiredNode; }
		osg::ref_ptr<osg::MatrixTransform> getTruckNode() { return _truckNode; }

		void setViewer(osgViewer::Viewer* viewer) { _viewer = viewer; }
		void setGroundNode(osg::ref_ptr<osg::MatrixTransform> node) { _groundNode = node; }
		void setCessnaNode(osg::ref_ptr<osg::MatrixTransform> node) { _cessnaNode = node; }
		void setCessnaFiredNode(osg::ref_ptr<osg::MatrixTransform> node) { _cessnaFiredNode = node; }
		void setTruckNode(osg::ref_ptr<osg::MatrixTransform> node) { _truckNode = node; }
};