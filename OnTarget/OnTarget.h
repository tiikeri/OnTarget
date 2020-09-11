#pragma comment(lib, "BakkesMod.lib")
using namespace std;
#include <fstream>
#include <sstream>

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

#include "imgui/imgui.h"

#define RED ImColor(255, 0, 0)
#define LIGHTRED ImColor(170, 0, 0)
#define GREEN ImColor(0, 255, 0)
#define LIGHTGREEN ImColor(0, 170, 0)
#define GREY ImColor(170, 170, 170)
#define DARKGREY ImColor(85, 85, 85)
#define WHITE ImColor(255, 255, 255)

using namespace placeholders;

struct Shot {
	ImVec2 location;
	bool goal;
	bool multiTouch;
	float speed;
};

class OnTarget : public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginWindow
{
public:
	void onLoad();
	void onUnload();

	void writeCfg();

	ImColor colorScale(float Val);
	ImColor stringToImColor(string colorString);
	string ImColorToString(ImColor color);

	void onNewAttempt(string eventName);
	void onDestroyBall(string eventName);
	void onStartNewRound(string eventName);
	void clearShotsResetCounts(string eventName);

	void onHitGoal(BallWrapper ball, void* params, string eventName);
	void onHitWorld(BallWrapper ball, void* params, string eventName);

	ImVec2 flattenToPlane(Vector vector);

	void Render();
	void RenderImGui();
	string GetMenuName();
	string GetMenuTitle();
	void SetImGuiContext(uintptr_t ctx);
	bool ShouldBlockInput();
	bool IsActiveOverlay();
	void OnOpen();
	void OnClose();

	bool renderShotChart = false;
	bool renderSettings = false;
	bool gotEnd = false;

	string configurationFilePath = "./bakkesmod/cfg/ontarget.cfg";

	string	shotHistorySetting = "onTargetShotHistory",
		titleBarSetting = "onTargetTitleBar",
		transparencySetting = "onTargetTransparency",
		toggleResetCountsAsMiss = "onTargetResetMiss",
		goalHitColorSetting = "onTargetGoalHitColorRGB",
		multiTouchColorSetting = "onTargetMultiTouchColorRGB",
		wallHitColorSetting = "onTargetWallHitColorRGB";

		

	int shotHistory;
	int counter;
	bool titleBar, doesResetCountAsMiss, useColorScale;
	float transparency;

	ImColor goalHitColor, wallHitColor, multiTouchColor;

	vector<float> goalSpeeds;

	float avgGoalSpeed, lastGoalSpeed, averageBuffer;

	uint64_t ballHit = 0, ballDestroyed = 0, ballResets = 0;


	vector<Shot> shots;
};
