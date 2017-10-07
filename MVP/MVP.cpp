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
  public:
	bool leftLeg;
	BipedalMovement() : Plugin("InMoov Bipedal Kinematics")
	{
		/* define that Body files will be implemented */
		require("Body");
	}

	virtual bool initialize()
	{
		leftLeg = true;
		ToolBar* TB = new ToolBar("InMoov Kinematics");
		TB->addButton("Walk")
			->sigClicked()
			.connect(bind(&BipedalMovement::onButtonClicked, this, +0.02));
		/* From here, add buttons and functionality to the TB.
		ToolBar class has member functions for adding buttons
		and defining how the joint sliders react when clicked.
		It is a self-bound function. Look around at the other
		predefined functions for guidance. */

		TB->addButton("SwingLegs")
			->sigClicked()
			.connect(bind(&BipedalMovement::swingLegs, this, 0.04));

		/* Note that this virtual function must return true.
		It may be a good idea to use this restriction as a
		testing parameter */
    addToolBar(TB);
		return true;
	}

	void onButtonClicked(double dq)
	{
		/* vector of type BodyItem */
		ItemList<BodyItem> bodyItems =
		    ItemTreeView::mainInstance()->selectedItems<BodyItem>();

		/* size_t is defined as unsigned long long - to be used for large iterative values > 0 */
		/* for loop: for each body item, assign a pointer to it, same with joints internal loop */
		for(size_t i=0; i < bodyItems.size(); ++i){
		    BodyPtr body = bodyItems[i]->body();
		    for(int j=0; j < body->numJoints(); ++j){
		        body->joint(j)->q() += dq;
		    }
		    bodyItems[i]->notifyKinematicStateChange(true);
		}
	}

	void swingLegs(double dq)
    	{
		ItemList<BodyItem> bodyItems =
		    ItemTreeView::mainInstance()->selectedItems<BodyItem>();

		for(size_t i=0; i < bodyItems.size(); ++i){
		    BodyPtr body = bodyItems[i]->body();
		    int lleg_hip_p = body->link("LLEG_HIP_P")->jointId();
		    int rleg_hip_p = body->link("RLEG_HIP_P")->jointId();
		    int lleg_knee = body->link("LLEG_KNEE")->jointId();
		    int rleg_knee = body->link("RLEG_KNEE")->jointId();

		    if(body->joint(lleg_hip_p)->q() < -1) {
		        this->leftLeg = true;
		    } else if(body->joint(lleg_hip_p)->q() > 1) {
		        this->leftLeg = false;
		    }

		    if(this->leftLeg) {
		        body->joint(lleg_hip_p)->q() += dq;
		        if(body->joint(lleg_knee)->q() > 0)
		            body->joint(lleg_knee)->q() -= dq;
		        body->joint(rleg_hip_p)->q() -= dq;
		        body->joint(rleg_knee)->q() += dq;
		    } else {
		        body->joint(lleg_hip_p)->q() -= dq;
		        body->joint(lleg_knee)->q() += dq;
		        body->joint(rleg_hip_p)->q() += dq;
		        if(body->joint(rleg_knee)->q() > 0)
		            body->joint(rleg_knee)->q() -= dq;

		    }
		    bodyItems[i]->notifyKinematicStateChange(true);
		}
    	}

};


CNOID_IMPLEMENT_PLUGIN_ENTRY(BipedalMovement)
