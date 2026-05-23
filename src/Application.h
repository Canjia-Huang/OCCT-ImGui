#pragma once

#include <memory>

#include <GLFW/glfw3.h>

#include "imgui.h"

class OcctViewer;

class Application {
public:
    Application();
    virtual ~Application();

    int run();

protected:
    virtual void init();
    virtual void drawGui();
    virtual void drawMenuBar();
    virtual void drawStatusBar();
    virtual void drawRubberBand();
    virtual void onImport();
    virtual void onExport();
    virtual void onImportFile(const char* path);
    virtual void postFrame();
    virtual void shutdown();

    GLFWwindow* window() const { return window_; }
    OcctViewer*  viewer() const { return viewer_.get(); }
    int  width()  const { return width_; }
    int  height() const { return height_; }
    float pixelRatio() const { return pixelRatio_; }

    bool showViewerPanel_ = true;
    bool showObjectPanel_ = true;
    bool showTool_        = false;
    bool guiWantsMouse_   = false;
    bool firstFrame_      = true;
    bool panning_         = false;   // left-drag → pan
    bool selecting_       = false;   // Shift+left-drag → rect-select
    bool selectShift_     = false;   // true if currently in shift-rect-select
    int  selStartX_       = 0, selStartY_ = 0;
    int  selEndX_         = 0, selEndY_   = 0;
    int  clickStartX_     = 0, clickStartY_ = 0;
    int  lastMouseX_      = 0;
    int  lastMouseY_      = 0;

    // Deferred rectangle selection (processed in postFrame)
    bool pendingRectSelect_  = false;
    bool pendingRectShift_   = false;
    int  rectX1_ = 0, rectY1_ = 0, rectX2_ = 0, rectY2_ = 0;

private:
    void initWindow();
    void initImGui();
    void applyStyle();
    void mainLoop();
    void beginFrame();
    void endFrame();
    void drawDockSpace();
    void setupDockLayout(ImGuiID dockspaceId);

    static void glfwErrorCallback(int error, const char* description);
    static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void glfwDropCallback(GLFWwindow* window, int count, const char** paths);

    GLFWwindow* window_ = nullptr;
    std::unique_ptr<OcctViewer> viewer_;
    int width_  = 1400;
    int height_ = 900;
    float fontScale_   = 1.0f;
    float pixelRatio_  = 1.0f;
    bool  docksInitialized_ = false;
};
