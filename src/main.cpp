//#include "ofMain.h"
//#include "ofApp.h"
//
//#include "Defaults.h"
//
////========================================================================
//int main( )
//{
//	ofSetupOpenGL(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_MODE);
//
//    ofRunAppWithAppUtils(new ofApp());
//}


#include "ofMain.h"
#include "ofApp.h"
#include "GUIApp.h"
#include "Defaults.h"

int main()
{
	glfwInit();
	int count_monitors;
	glfwGetMonitors(&count_monitors);
    ofGLFWWindowSettings mainSettings;
    mainSettings.width = int(DEFAULT_WINDOW_WIDTH);
    mainSettings.height = int(DEFAULT_WINDOW_HEIGHT);
    mainSettings.windowMode = (count_monitors == 1) ? OF_WINDOW : DEFAULT_WINDOW_MODE;
	mainSettings.multiMonitorFullScreen = false;
	mainSettings.monitor = (count_monitors == 1) ? 0 : 1;
    mainSettings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSettings);
    
    ofGLFWWindowSettings guiSettings;
	guiSettings.monitor = 0;
    guiSettings.width = 1500;
    guiSettings.height = 1500;
    guiSettings.windowMode = OF_WINDOW;
    guiSettings.resizable = true;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(guiSettings);
    
    shared_ptr<GUIApp> guiApp(new GUIApp);
    shared_ptr<ofApp> mainApp(new ofApp);
    
    guiApp->setMainApp(mainApp);
    mainApp->setGuiApp(guiApp);
    
    //guiApp->setSceneManager(mainApp->getSceneManager());
    
//    ofRunApp(guiWindow, guiApp);
//    ofRunApp(mainWindow, mainApp);
    
    ofRunAppWithAppUtils(guiWindow, &*guiApp);
    ofRunAppWithAppUtils(mainWindow, &*mainApp);

    
    ofRunMainLoop();
}
