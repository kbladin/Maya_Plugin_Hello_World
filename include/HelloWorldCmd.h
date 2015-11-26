#ifndef HELLOWORLD_H
#define HELLOWORLD_H
 
#include <maya/MArgList.h>
#include <maya/MObject.h>
#include <maya/MGlobal.h>
#include <maya/MPxCommand.h>
 
class HelloWorld : public MPxCommand {
 public:
  HelloWorld() {};
  virtual MStatus doIt(const MArgList& argList);
  static void* creator();
};
#endif


/*
#ifndef BLENDNODE_H
#define BLENDNODE_H
 
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MGlobal.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MPointArray.h>
#include <maya/MStatus.h>
 
#include <maya/MFnMesh.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
 
#include <maya/MPxDeformerNode.h>
 
class BlendNode : public MPxDeformerNode {
 public:
  BlendNode() {};
  virtual MStatus deform(MDataBlock& data, MItGeometry& itGeo,
                         const MMatrix &localToWorldMatrix, unsigned int mIndex);
  static void* creator();
  static MStatus initialize();
 
  static MTypeId id;
  static MObject aBlendMesh;
  static MObject aBlendWeight;
};
#endif
*/