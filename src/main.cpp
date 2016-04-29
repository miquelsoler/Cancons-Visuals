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
    ofGLFWWindowSettings mainSettings;
    mainSettings.width = int(DEFAULT_WINDOW_WIDTH);
    mainSettings.height = int(DEFAULT_WINDOW_HEIGHT);
    mainSettings.windowMode = DEFAULT_WINDOW_MODE;
    mainSettings.resizable = false;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(mainSettings);
    
    ofGLFWWindowSettings guiSettings;
    guiSettings.width = 1000;
    guiSettings.height = 900;
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
