#pragma once

#include <Aspect_RenderingContext.hxx>
#include <Aspect_Window.hxx>

struct GLFWwindow;

class OcctWindow : public Aspect_Window
{
    DEFINE_STANDARD_RTTI_INLINE(OcctWindow, Aspect_Window)
public:
    OcctWindow(GLFWwindow* theWin, int theWidth, int theHeight);
    virtual ~OcctWindow() {}

    void updateSize(int w, int h);
    Aspect_RenderingContext NativeGlContext() const;

    virtual Aspect_Drawable NativeHandle() const Standard_OVERRIDE;
    virtual Aspect_Drawable NativeParentHandle() const Standard_OVERRIDE { return 0; }
    virtual Aspect_TypeOfResize DoResize() Standard_OVERRIDE;
    virtual Standard_Boolean IsMapped() const Standard_OVERRIDE { return Standard_True; }
    virtual Standard_Boolean DoMapping() const Standard_OVERRIDE { return Standard_True; }
    virtual void Map() const Standard_OVERRIDE {}
    virtual void Unmap() const Standard_OVERRIDE {}

    void Position(Standard_Integer& theX1, Standard_Integer& theY1,
                  Standard_Integer& theX2, Standard_Integer& theY2) const
    {
        theX1 = myXLeft; theX2 = myXRight; theY1 = myYTop; theY2 = myYBottom;
    }
    virtual Standard_Real Ratio() const
    {
        return Standard_Real(myXRight - myXLeft) / Standard_Real(myYBottom - myYTop);
    }
    virtual void Size(Standard_Integer& theWidth, Standard_Integer& theHeight) const
    {
        theWidth = myXRight - myXLeft; theHeight = myYBottom - myYTop;
    }
    virtual Aspect_FBConfig NativeFBConfig() const { return nullptr; }

private:
    GLFWwindow* myWindow;
    Standard_Integer myXLeft = 0, myYTop = 0;
    Standard_Integer myXRight = 0, myYBottom = 0;
};
