#ifndef H2SL_FEATURE_SPATIAL_FUNCTION_H
#define H2SL_FEATURE_SPATIAL_FUNCTION_H

#include <iostream>

#include "h2sl/feature.h"

namespace h2sl {
  class Feature_Spatial_Function: public Feature {
  public:
    Feature_Spatial_Function( const bool& invert = false, const unsigned int& spatialFunctionType = 0 );
    virtual ~Feature_Spatial_Function();
    Feature_Spatial_Function( const Feature_Spatial_Function& other );
    Feature_Spatial_Function& operator=( const Feature_Spatial_Function& other );

    virtual bool value( const unsigned int& cv, const Grounding* grounding, const std::vector< std::pair< const Phrase*, std::vector< Grounding* > > >& children, const Phrase* phrase, const World* world );

    virtual void to_xml( xmlDocPtr doc, xmlNodePtr root )const;

    virtual void from_xml( xmlNodePtr root );

    inline unsigned int& spatial_function_type( void ){ return _spatial_function_type; };
    inline const unsigned int& spatial_function_type( void )const{ return _spatial_function_type; };
    inline const feature_type_t type( void )const{ return h2sl::FEATURE_TYPE_GROUNDING; };

  protected:
    unsigned int _spatial_function_type;
      
  private:

  };
  std::ostream& operator<<( std::ostream& out, const Feature_Spatial_Function& other );
}

#endif /* H2SL_FEATURE_SPATIAL_FUNCTIONSTRAINT_H */
