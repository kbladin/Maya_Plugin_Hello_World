#include "../include/PushDeformerNode.h"

MTypeId PushDeformerNode::id(0x00000002);
MObject PushDeformerNode::inflation_attr;
 
void* PushDeformerNode::creator() { return new PushDeformerNode; }

MStatus PushDeformerNode::deform(MDataBlock& data, MItGeometry& it_geo,
                          const MMatrix &local_to_world_matrix, unsigned int m_index) {
  MStatus status;
  
  // Fetch the envelope and the inflation input value
  float env = data.inputValue(envelope).asFloat();
  double inflation = data.inputValue(inflation_attr).asDouble();

  // Get the input mesh (fn_input_mesh)
  MArrayDataHandle h_input = data.outputArrayValue( input, &status );
  CHECK_MSTATUS_AND_RETURN_IT( status )
  status = h_input.jumpToElement( m_index );
  CHECK_MSTATUS_AND_RETURN_IT( status )
  MObject o_input_geom = h_input.outputValue().child( inputGeom ).asMesh();
  MFnMesh fn_input_mesh( o_input_geom );

  // Get the normal array from the input mesh
  MFloatVectorArray normals = MFloatVectorArray();
  fn_input_mesh.getVertexNormals(true, normals, MSpace::kTransform);

  // Loop through the geometry and set vertex positions
  for (; !it_geo.isDone(); it_geo.next())
  {
    int idx = it_geo.index();
    MVector nrm = MVector(normals[idx]);
    MPoint pos = it_geo.position();
    MPoint new_pos = pos + (nrm * inflation * env);
    it_geo.setPosition(new_pos);
  }

  return MS::kSuccess;
}
 
MStatus PushDeformerNode::initialize() {
  MFnTypedAttribute tAttr;
  MFnNumericAttribute nAttr;

  // Create a numeric attribute "inflation"
  inflation_attr = nAttr.create("inflation", "in", MFnNumericData::kDouble, 0.0);
  nAttr.setMin(0.0);
  nAttr.setMax(10.0);
  nAttr.setChannelBox(true);

  // Add the attribute
  addAttribute(inflation_attr);
  attributeAffects(inflation_attr, outputGeom);

  // Make the deformer weights paintable (maybe wait with this)
  // MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer PushDeformerNode weights;");
 
  return MS::kSuccess;
}