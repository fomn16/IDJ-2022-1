class Sprite{
    Sprite();
};
class Music{
    Music();
};

class State{
    public:
    State();
    bool QuitRequested();
    void LoidAssets();
    void Update(float dt);
    void Render();

    private:
    Sprite bg;
    Music music;
    bool quitRequested;
};  