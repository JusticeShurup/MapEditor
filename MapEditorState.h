#ifndef _MAP_EDITOR_STATE_H_
#define _MAP_EDITOR_STATE_H_

class Editor;
class Camera;
class MapEditorState
{
protected: 
	Editor* editor;

public: 
	MapEditorState(Editor* editor);
	virtual ~MapEditorState();
	virtual void update(Camera& camera, float delta_time) = 0;
	virtual void render() = 0;

	virtual void initWindow() = 0;
};
#endif 
