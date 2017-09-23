
#include <cnoid/Plugin>
#include <cnoid/ItemTreeView>
#include <cnoid/BodyItem>
#include <cnoid/ToolBar>

using namespace std;
using namespace cnoid;

class PrototypePlugin : public Plugin
{
public:
    
    PrototypePlugin() : Plugin("PrototypePlugin")
    {
        require("Body");
    }
    
    virtual bool initialize()
    {
        ToolBar* toolbar = new ToolBar("PrototypeToolbar");
        bar->addButton("Movement++")
            ->sigClicked().connect(bind(&Sample1Plugin::onButtonClicked, this, +0.04));
        bar->addButton("Movement--")
                ->sigClicked().connect(bind(&Sample1Plugin::onButtonClicked, this, -0.04));
        addToolBar(toolbar);

        return true;
    }

    void onButtonClicked(double dq)
    {
        ItemList<BodyItem> bodyItems =
            ItemTreeView::mainInstance()->selectedItems<BodyItem>();
        
        for(size_t i=0; i < bodyItems.size(); ++i){
            BodyPtr body = bodyItems[i]->body();
            for(int j=0; j < body->numJoints(); ++j){
                body->joint(j)->q() += dq;
            }
            bodyItems[i]->notifyKinematicStateChange(true);
        }
    }
};


CNOID_IMPLEMENT_PLUGIN_ENTRY(PrototypePlugin)
