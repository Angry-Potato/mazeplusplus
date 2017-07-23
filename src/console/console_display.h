class ConsoleDisplay {
public :
  bool isClosed() const;

  void openGameWindow(int width, int height, const char* title);

  void beginRenderLoop();
  void render(int id, int x, int y);
  void endRenderLoop();
};
