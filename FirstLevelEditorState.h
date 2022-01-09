#ifndef _FIRST_LEVEL_EDITOR_STATE_H_
#define _FIRST_LEVEL_EDITOR_STATE_H_
#include "MapEditorState.h"

class FirstLevelEditorState :
    public MapEditorState
{
public: 
    FirstLevelEditorState(Editor* editor);
    virtual ~FirstLevelEditorState();

    virtual void initWindow() override;
    virtual void update(Camera& camera, float delta_time) override;
    virtual void render() override;
    void updateFile();

};
#endif
