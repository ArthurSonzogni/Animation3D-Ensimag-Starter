// created by Arthur Sonzogni

#ifndef INPUT_QHZPGW1N
#define INPUT_QHZPGW1N


struct GLFWwindow;

class Input
{
    public:
        // update state
        static void update(GLFWwindow* window);
        // keyboard
        static bool isKeyPressed(int key);
        static bool isKeyReleased(int key);
        static bool isKeyHold(int key);
        // mouse
        static bool isMousePressed(int key);
        static bool isMouseReleased(int key);
        static bool isMouseHold(int key);
        static double mouseX();
        static double mouseY();
        static double deltaX();
        static double deltaY();
        static void setMousePos(double x, double y); // relative

        static void fixMouse();
        static void unfixMouse();
        static bool isMouseFixed();

        static float getHorAngle();
        static float getVerAngle();
};

#endif /* end of include guard: INPUT_QHZPGW1N */
