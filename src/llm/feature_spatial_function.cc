#include <sstream>

#include "h2sl/spatial_function.h"
#include "h2sl/feature_spatial_function.h"

using namespace std;
using namespace h2sl;

Feature_Spatial_Function::
Feature_Spatial_Function( const bool& invert,
                const unsigned int& spatialFunctionType ) : Feature( invert ),
                                                    _spatial_function_type( spatialFunctionType ) {

}

Feature_Spatial_Function::
~Feature_Spatial_Function() {

}

Feature_Spatial_Function::
Feature_Spatial_Function( const Feature_Spatial_Function& other ) : Feature( other ),
                                                _spatial_function_type( other._spatial_function_type ){

}

Feature_Spatial_Function&
Feature_Spatial_Function::
operator=( const Feature_Spatial_Function& other ) {
  _invert = other._invert;
  _spatial_function_type = other._spatial_function_type;
  return (*this);
}

bool
Feature_Spatial_Function::
value( const unsigned int& cv,
        const Grounding* grounding,
        const vector< pair< const Phrase*, vector< h2sl::Grounding* > > >& children,
        const Phrase* phrase,
        const World* world ){
  const Spatial_Function * spatial_function = dynamic_cast< const Spatial_Function* >( grounding );
  if( spatial_function != NULL ){
    if( spatial_function->type() == _spatial_function_type ){
      return !_invert;
    }
  }
  return false;
}

void
Feature_Spatial_Function::
to_xml( xmlDocPtr doc, xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_spatial_function" ), NULL );
  stringstream invert_string;
  invert_string << _invert;
  xmlNewProp( node, ( const xmlChar* )( "invert" ), ( const xmlChar* )( invert_string.str().c_str() ) );
  stringstream spatial_function_type_string;
  spatial_function_type_string << _spatial_function_type;
  xmlNewProp( node, ( const xmlChar* )( "spatial_function_type" ), ( const xmlChar* )( spatial_function_type_string.str().c_str() ) );
  xmlAddChild( root, node );
  return;
}

void
Feature_Spatial_Function::
from_xml( xmlNodePtr root ){
  _invert = false;
  _spatial_function_type = 0;
  if( root->type == XML_ELEMENT_NODE ){
    xmlChar * tmp = xmlGetProp( root, ( const xmlChar* )( "invert" ) );
    if( tmp != NULL ){
      string invert_string = ( char* )( tmp );
      _invert = ( bool )( strtol( invert_string.c_str(), NULL, 10 ) );
      xmlFree( tmp );
    }
    tmp = xmlGetProp( root, ( const xmlChar* )( "spatial_function_type" ) );
    if( tmp != NULL ){
      string spatial_function_type_string = ( char* )( tmp );
      _spatial_function_type = strtol( spatial_function_type_string.c_str(), NULL, 10 );
      xmlFree( tmp );
    }
  }
  return;
}

namespace h2sl {
  ostream&
  operator<<( ostream& out,
              const Feature_Spatial_Function& other ) {
    out << "Feature_Spatial_Function:(invert:(" << other.invert() << ") spatial_function_type:(" << Spatial_Function::type_to_std_string( other.spatial_function_type() ) << "))";
    return out;
  }

}
