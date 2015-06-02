
class Application
{
protected:
	int height;
	int width;

	//time interval for the timer
	float timeinterval;
public:
	virtual void initGraphics(void);
	virtual void display(void);
	virtual void update(void);
	virtual void resize(int width, int height);
	float getTimeinterval(void);
	void setTimeinterval(float timeint);
};