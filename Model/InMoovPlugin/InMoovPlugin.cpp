/* Pull in cnoid functionality suite. There's a lot more if you need. */
#include <cnoid/Plugin>
#include <cnoid/ItemTreeView>
#include <cnoid/BodyItem>
#include <cnoid/ToolBar>

/* Begin namespace(s) to not have to fully qualify every line of code */
using namespace std;
using namespace cnoid;

/* define our MVP logic class, declare plugin function */
class InMoovPlugin : public Plugin
{
	public:
		/* Boolean for completion of single step */
		bool stepDone;

		InMoovPlugin() : Plugin("InMoovPlugin")
		{
			/* define that Body files will be implemented */
			require("Body");
		}
	    
	virtual bool initialize()
	{
		/* Initialize stepDone boolean */
		stepDone = true;

		/* Defines toolbar for plugin */
		ToolBar* TB = new ToolBar("InMoov Plugin");

		/* From here, add buttons and functionality to the TB.
		ToolBar class has member functions for adding buttons
		and defining how the joint sliders react when clicked.
		It is a self-bound function. Look around at the other
		predefined functions for guidance. */

		/* Adds Walk button to toolbar */
		TB->addButton("Walk")->sigClicked().connect(bind(&InMoovPlugin::walk, this, 0.04));
		/* Adds Reset button to toolbar */
		TB->addButton("Reset")->sigClicked().connect(bind(&InMoovPlugin::reset, this));

		/* Adds toolbar to choreonoid toolbar tab*/
		addToolBar(TB);

		/* Note that this virtual function must return true.
		It may be a good idea to use this restriction as a
		testing parameter */
		return true;
	}

	void walk(double dq)
    	{
		/* vector of type BodyItem */
		ItemList<BodyItem> bodyItems = ItemTreeView::mainInstance()->selectedItems<BodyItem>();

		/* size_t is defined as unsigned long long - to be used for large iterative values > 0 */
		/* for loop: for each body item, assign a pointer to it, same with joints internal loop */
		for(size_t i=0; i < bodyItems.size(); ++i)
		{
			/* Obtain joint ids from model */
			BodyPtr body = bodyItems[i]->body();
			int hip_right = body->link("HIP_RIGHT")->jointId();
			int hip_left = body->link("HIP_LEFT")->jointId();
			int knee_right = body->link("KNEE_RIGHT")->jointId();
			int knee_left = body->link("KNEE_LEFT")->jointId();
			int ankle_right = body->link("ANKLE_RIGHT")->jointId();
			int ankle_left = body->link("ANKLE_LEFT")->jointId();

			/* Left leg moves forward first */
			if(this->stepDone)
			{
				/* When left leg back and right leg forward */
				if(body->joint(hip_left)->q() < -0.01)
				{
					// Left leg moves forward
					body->joint(hip_left)->q() += dq;
					if(body->joint(hip_left)->q() > -0.19)
					{
						body->joint(knee_left)->q() += dq * 2.5;
						if(body->joint(hip_left)->q() > -0.07)
						{
							body->joint(ankle_left)->q() += dq / 2;
						}
					}

					// Right leg moves back
					if(body->joint(hip_left)->q() < -0.19)
					{
						body->joint(knee_right)->q() -= dq * 2.5;
					}
					else if(body->joint(hip_left)->q() >= -0.19 && body->joint(knee_right)->q() < -0.01)
					{
						body->joint(knee_right)->q() += dq * 2.5;
					}

					if(body->joint(hip_right)->q() > 0.17)
					{
						body->joint(hip_right)->q() -= dq / 0.625;
					}
					else if(body->joint(hip_right)->q() <= 0.17)
					{
						body->joint(hip_right)->q() -= dq;
					}
					
				}
				/* When both legs in neutral/straight position */			
				else if(body->joint(hip_left)->q() >= -0.01 && body->joint(hip_left)->q() < 0.15)
				{
					// Left leg continues to move forward
					body->joint(hip_left)->q() += dq;
					if(body->joint(knee_left)->q() > -0.39)
					{
						body->joint(knee_left)->q() -= dq * 2.5;
					}

					// Right leg continues to move back
					body->joint(hip_right)->q() -= dq;
					body->joint(ankle_right)->q() += dq;
				}
				/* Left leg halfway forwards and right leg halfway backwards */
				else if(body->joint(hip_left)->q() >= 0.15 && body->joint(hip_left)->q() < 0.47)
				{
					// Right leg moving fully backwards
					if(body->joint(hip_left)->q() < 0.35)
					{
						body->joint(knee_right)->q() -= dq * 2.5;
						body->joint(ankle_right)->q() -= dq;
					}
					body->joint(hip_right)->q() -= dq * 0.625;

					// Left leg extending fully forwards
					if(body->joint(hip_left)->q() >= 0.3)
					{
						body->joint(knee_left)->q() += dq * 2.5;
					}
					body->joint(hip_left)->q() += dq;
				}
				/* Left leg front and right leg back complete.
				   Switching to right leg front and left leg back. */
				else if(body->joint(hip_left)->q() >= 0.47)
				{
					this->stepDone = false;
				}
			}

			else
			{
				/* Left leg starts moving backwards and right leg starts moving forward */
				if(body->joint(hip_left)->q() <= 0.49 && body->joint(hip_left)->q() >= 0.33)
				{
					// Left leg moves backward
					if(body->joint(knee_left)->q() > -0.4)
					{
						body->joint(knee_left)->q() -= dq * 2.5;
					}
					body->joint(hip_left)->q() -= dq;

					// Right leg moves forward
					body->joint(hip_right)->q() += dq;
				}
				/* Moving both legs back to neutral/standing position */
				else if(body->joint(hip_left)->q() < 0.33 && body->joint(hip_left)->q() >= 0.01)
				{
					// Left leg moves backward
					body->joint(knee_left)->q() += dq * 1.25;
					body->joint(hip_left)->q() -= dq;

					// Right leg moves forward
					body->joint(hip_right)->q() += dq * 0.625;
					if(body->joint(hip_left)->q() < 0.29 && body->joint(hip_left)->q() > 0.11)
					{
						body->joint(knee_right)->q() += dq * 2.5;
						if(body->joint(hip_left)->q() < 0.19)
						{
							body->joint(ankle_right)->q() += dq / 2;
						}
					}
				}
				/* Both legs back to neutral/standing position.
				   Begin moving left leg further back and right leg forwards*/
				else if(body->joint(hip_left)->q() < 0.01 && body->joint(hip_left)->q() >= -0.35)
				{
					// Left leg steps backward
					body->joint(hip_left)->q() -= dq;
					body->joint(ankle_left)->q() += dq;
					if(body->joint(hip_left)->q() <= -0.19)
					{
						body->joint(knee_left)->q() -= dq * 2.5;
						body->joint(ankle_left)->q() -= dq * 2;
					}

					// Right leg extends forward
					if(body->joint(knee_right)->q() > -0.39 && body->joint(hip_right)->q() < 0.25)
					{
						body->joint(knee_right)->q() -= dq * 2.5;
					}
					if(body->joint(hip_right)->q() >= 0.25)
					{
						body->joint(knee_right)->q() += dq * 2.5;
					}
					body->joint(hip_right)->q() += dq * 1.33333;
				}
				/* Right leg front and left leg back complete.
				   Switching back to right leg back and left leg front. */
				else if(body->joint(hip_left)->q() < -0.35)
				{
					this->stepDone = true;
				}
			}

			/* Update model's joint positions */
			bodyItems[i]->notifyKinematicStateChange(true);
		}
    	}

	/* Resets position of model back to default */
	void reset()
    	{
		this->stepDone = true;

		ItemList<BodyItem> bodyItems = ItemTreeView::mainInstance()->selectedItems<BodyItem>();
		for(size_t i=0; i < bodyItems.size(); ++i)
		{
			BodyPtr body = bodyItems[i]->body();
			int hip_right = body->link("HIP_RIGHT")->jointId();
			int hip_left = body->link("HIP_LEFT")->jointId();
			int knee_right = body->link("KNEE_RIGHT")->jointId();
			int knee_left = body->link("KNEE_LEFT")->jointId();
			int ankle_right = body->link("ANKLE_RIGHT")->jointId();
			int ankle_left = body->link("ANKLE_LEFT")->jointId();

			body->joint(hip_right)->q() = 0;
			body->joint(hip_left)->q() = 0;
			body->joint(knee_right)->q() = 0;
			body->joint(knee_left)->q() = 0;
			body->joint(ankle_right)->q() = 0;
			body->joint(ankle_left)->q() = 0;

			bodyItems[i]->notifyKinematicStateChange(true);
		}
	}
};


CNOID_IMPLEMENT_PLUGIN_ENTRY(InMoovPlugin)
