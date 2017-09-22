#include <cnoid/Plugin> //declare a plug-in
#include <boost/bind.hpp>

using namespace cnoid;
using namespace boost;

Class ProtoPlugin() : public Plugin 
{
public: 
	ProtoPlugin() : Plugin("ProtoypePlugin")
	{
	
	}
	
	/* virtual functions can have their behavior overridden
	by derived functions */
	virtual bool initialize() 
	{
		// create functionality here
	}

private:

	void onProtoTriggered()
	{
		// functionality here
	}
};

//link to a cnoid file
CNOID_IMPLEMENT_PLUGIN_ENTRY(ProtoPlugin)





