namespace VisionControl {
    void TargetFind();
    void DriverCam();
    struct Target {bool found; double horiz ; double vert;};
    Target GetTarget();
}