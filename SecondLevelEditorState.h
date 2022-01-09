#ifndef _SECOND_LEVEL_EDITOR_STATE_H_
#define _SECOND_LEVEL_EDITOR_STATE_H_
#include "MapEditorState.h"

class SecondLevelEditorState :
    public MapEditorState
{
public:
    SecondLevelEditorState(Editor* editor);
    virtual ~SecondLevelEditorState();

    virtual void initWindow() override;

    virtual void update(Camera& camera, float delta_time) override;
    virtual void render() override;
    void updateFile();
private: 
    bool delete_state;
    float time_after_click;
};
#endif