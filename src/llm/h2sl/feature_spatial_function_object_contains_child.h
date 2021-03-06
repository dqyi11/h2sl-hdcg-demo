#ifndef H2SL_FEATURE_SPATIAL_FUNCTION_OBJECT_CONTAINS_CHILD_H
#define H2SL_FEATURE_SPATIAL_FUNCTION_OBJECT_CONTAINS_CHILD_H

#include <iostream>

#include <h2sl/feature.h>

namespace h2sl {

  class Feature_Spatial_Function_Object_Contains_Child : public Feature {
  public:
    Feature_Spatial_Function_Object_Contains_Child( const bool& invert = false );
    virtual ~Feature_Spatial_Function_Object_Contains_Child();

    Feature_Spatial_Function_Object_Contains_Child( const Feature_Spatial_Function_Object_Contains_Child& other );
    Feature_Spatial_Function_Object_Contains_Child& operator=( const Feature_Spatial_Function_Object_Contains_Child& other );

    virtual bool value( const unsigned int& cv, const Grounding* grounding, const std::vector< std::pair< const Phrase*, std::vector< Grounding* > > >& children, const Phrase* phrase, const World* world );

    virtual void to_xml( xmlDocPtr doc, xmlNodePtr root )const;
    virtual void from_xml( xmlNodePtr root );
 
    virtual inline const feature_type_t type( void )const { return FEATURE_TYPE_GROUNDING; };
 
  protected:

  private:

  };

  std::ostream& operator<<( std::ostream& out, const Feature_Spatial_Function_Object_Contains_Child& other );
}

#endif // H2SL_FEATURE_SPATIAL_FUNCTION_OBJECT_CONTAINS_CHILD_H
