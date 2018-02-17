#pragma once
// I got this on stack overflow and I am in the process of modifying it
template<typename Type>
class uiManager{
private:
	virtual void render() {};
	virtual bool setValue(float mx, float my, bool bCheckBounds) { return false; };

	int index;
	vector<Type> items;
	ofParameter<Type> value;
public:
	void addItem(Type item) {
		items.push_back(item);
	}
	operator const Type & () {
		return value;
	}
	virtual bool mouseMoved(ofMouseEventArgs & args) { return false; }
	virtual bool mousePressed(ofMouseEventArgs & args) { return false; }
	virtual bool mouseDragged(ofMouseEventArgs & args) { return false; }
	virtual bool mouseReleased(ofMouseEventArgs & args) { return false; }
	virtual vector<Type> & getItems() { return items; }

	ofAbstractParameter & getParameter() { return value; }
};