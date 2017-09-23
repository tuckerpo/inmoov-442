#include <cnoid/Plugin>
#include <boost/bind.hpp>

using namespace cnoid;
using namespace boost;

class ProtoPlugin : public Plugin
{
public:

    ProtoPlugin() : Plugin("ProtoPlugin")
    {
	
    }

	/* virtual functions can be overridden by child functions */ 		
    virtual bool initialize()
    {
	// make things happen
    }

private:

    void onProtoTriggered()
    {
       	// make things binded to ProtoPlugin() happen
	
    }
};


/* generate associated .cnoid file ( i think ) */
CNOID_IMPLEMENT_PLUGIN_ENTRY(ProtoPlugin)

