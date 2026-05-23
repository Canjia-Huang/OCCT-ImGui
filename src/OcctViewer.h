#pragma once

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TopoDS_Shape.hxx>
#include <NCollection_List.hxx>
#include <Aspect_Window.hxx>

struct GLFWwindow;

class OcctViewer {
public:
    OcctViewer(GLFWwindow* glfwWindow);
    ~OcctViewer();

    void redraw();
    void updateViewer();
    void resize(int width, int height);

    // Camera
    void startRotation(int x, int y);
    void rotation(int x, int y);
    void zoom(int deltaY);
    void pan(int x, int y);
    void fitAll();

    // Scene
    void displayShape(const Handle(AIS_Shape)& shape, bool update = true);
    void removeShape(const Handle(AIS_Shape)& shape, bool update = true);

    // Display mode
    void setShadedWithEdges();

    // Import / export
    TopoDS_Shape importShape(const char* path);
    bool exportShape(const TopoDS_Shape& shape, const char* path);
    void getSelectedShapes(NCollection_List<TopoDS_Shape>& outList);

    // File dialogs
    static bool openFileDialog(char* outPath, int maxLen);
    static bool saveFileDialog(char* outPath, int maxLen);

    // Selection & hover
    void moveTo(int x, int y);
    void deselectOrClear();
    bool shiftSelect(int x, int y);
    void selectRectangle(int x1, int y1, int x2, int y2);
    void shiftSelectRectangle(int x1, int y1, int x2, int y2);
    void clearSelection();

    Handle(V3d_View) view() const { return view_; }
    Handle(V3d_Viewer) viewer() const { return viewer_; }
    Handle(AIS_InteractiveContext) context() const { return context_; }

private:
    GLFWwindow* glfwWindow_ = nullptr;
    Handle(Aspect_Window) nativeWin_;
    Handle(V3d_Viewer) viewer_;
    Handle(V3d_View) view_;
    Handle(AIS_InteractiveContext) context_;
};
