/* Pull in cnoid functionality suite. There's a lot more if you need. */
#include <cnoid/Plugin>
#include <cnoid/ItemTreeView>
#include <cnoid/BodyItem>
#include <cnoid/ToolBar>

/* Begin namespace(s) to not have to fully qualify every line of code */
using namespace cnoid;
using namespace std;


/* Preprocessor macro for defining a weighted constant */
#define GRAVITY 9.8

/* define our MVP logic class, declare plugin function */ 
class BipedalMovement : public Plugin 
{
	
	BipedalMovement() : Plugin("InMoov Bipedal Kinematics")
	{
		/* define that Body files will be implemented */
		require("Body");
	}

	virtual bool initialize() 
	{
		ToolBar* TB = new ToolBar("InMoov Kinematics");
		/* From here, add buttons and functionality to the TB.
		ToolBar class has member functions for adding buttons 
		and defining how the joint sliders react when clicked.
		It is a self-bound function. Look around at the other
		predefined functions for guidance. */

		/* Note that this virtual function must return true. 
		It may be a good idea to use this restriction as a 
		testing parameter */
	}

}
