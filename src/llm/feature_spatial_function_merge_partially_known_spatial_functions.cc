/**
 * @file    feature_spatial_function_merge_partially_known_spatial_functions.cc
 * @author  Thomas M. Howard (tmhoward@csail.mit.edu)
 *          Matthew R. Walter (mwalter@csail.mit.edu)
 * @version 1.0
 *
 * @section LICENSE
 *
 * This file is part of h2sl.
 *
 * Copyright (C) 2014 by the Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html> or write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @section DESCRIPTION
 *
 * The implementation of a class used to check for a match with a spatial_function's type
 */

#include <sstream>

#include "h2sl/spatial_function.h"
#include "h2sl/feature_spatial_function_merge_partially_known_spatial_functions.h"

using namespace std;
using namespace h2sl;

Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions( const bool& invert ) : Feature( invert ) {

}

Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
~Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions() {

}

Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions( const Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions& other ) : Feature( other ) {

}

Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions&
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
operator=( const Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions& other ) {
  _invert = other._invert;
  return (*this);
}

bool
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
value( const unsigned int& cv,
        const Grounding* grounding,
        const vector< pair< const Phrase*, vector< Grounding* > > >& children,
        const Phrase* phrase,
        const World* world ){
  const Spatial_Function * spatial_function = dynamic_cast< const Spatial_Function* >( grounding );
  if( ( spatial_function != NULL ) && ( children.size() > 1 ) ){
    std::vector< const Spatial_Function* > known_spatial_function_type_and_unknown_object_type;
    std::vector< const Spatial_Function* > known_object_type_and_unknown_spatial_function_type;
    for( unsigned int i = 0; i < children.size(); i++ ){
      for( unsigned int j = 0; j < children[ i ].second.size(); j++ ){
        const Spatial_Function * child = dynamic_cast< const Spatial_Function* >( children[ i ].second[ j ] );
        if( child != NULL ){
          if( ( !child->contains_object_type( OBJECT_TYPE_UNKNOWN ) ) && ( child->type() == SPATIAL_FUNC_TYPE_UNKNOWN ) ){
            known_object_type_and_unknown_spatial_function_type.push_back( child );
          } else if( ( true == child->contains_object_type( OBJECT_TYPE_UNKNOWN ) ) && ( child->type() != SPATIAL_FUNC_TYPE_UNKNOWN ) ){
            known_spatial_function_type_and_unknown_object_type.push_back( child );
          }
        }
      }
    }
    if( !known_spatial_function_type_and_unknown_object_type.empty() && !known_object_type_and_unknown_spatial_function_type.empty() ){ 
      for( unsigned int i = 0; i < known_spatial_function_type_and_unknown_object_type.size(); i++ ){
        for( unsigned int j = 0; j < known_object_type_and_unknown_spatial_function_type.size(); j++ ){
          if( spatial_function->type() == known_spatial_function_type_and_unknown_object_type[ i ]->type() ) {
            bool identical = true;
            for( unsigned int k = 0; k < known_object_type_and_unknown_spatial_function_type[ j ]->objects().size(); k++ ) {
              if( false == spatial_function->contains_object_type( known_object_type_and_unknown_spatial_function_type[ j ]->objects()[ k ].type() ) ){
                identical = false;
              }
            }
            if( identical ) {
              return !_invert;
            }
          }
        }
      }   
       
      return _invert;
    }
  }
  return false;
}

void
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
to_xml( xmlDocPtr doc, xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_spatial_function_merge_partially_known_spatial_functions" ), NULL );
  stringstream invert_string;
  invert_string << _invert;
  xmlNewProp( node, ( const xmlChar* )( "invert" ), ( const xmlChar* )( invert_string.str().c_str() ) );
  xmlAddChild( root, node );
  return;
}

void
Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions::
from_xml( xmlNodePtr root ){
  _invert = false;
  if( root->type == XML_ELEMENT_NODE ){
    xmlChar * tmp = xmlGetProp( root, ( const xmlChar* )( "invert" ) );
    if( tmp != NULL ){
      string invert_string = ( char* )( tmp );
      _invert = ( bool )( strtol( invert_string.c_str(), NULL, 10 ) );
      xmlFree( tmp );
    }
  }
  return;
}

namespace h2sl {
  ostream&
  operator<<( ostream& out,
              const Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions& other ) {
    out << "Feature_Spatial_Function_Merge_Partially_Known_Spatial_Functions:(invert:(" << other.invert() << "))";
    return out;
  }

}
