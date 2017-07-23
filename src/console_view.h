class ConsoleView {
public :
  bool isClosed() const;

  void openGameWindow(int width, int height, const char* title);

  void beginRenderLoop();
  void render();
  void endRenderLoop();
};
