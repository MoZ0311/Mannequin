// ModelAssets class

# include "ModelAssets.hpp"
# include "../core/Config.hpp"

using namespace Assets;

ModelAssets& ModelAssets::GetInstance()
{
	static ModelAssets instance;
	return instance;
}

ModelAssets::ModelAssets()
	: mannequinRest{ U"assets/models/mannequin/mannequin_rest.obj" }

	, mannequinIdle01{ U"assets/models/mannequin/mannequin_idle01.obj" }
	, mannequinIdle02{ U"assets/models/mannequin/mannequin_idle02.obj" }
	, mannequinIdle03{ U"assets/models/mannequin/mannequin_idle03.obj" }

	, mannequinWalk01{ U"assets/models/mannequin/mannequin_walk01.obj" }
	, mannequinWalk02{ U"assets/models/mannequin/mannequin_walk02.obj" }
	, mannequinWalk03{ U"assets/models/mannequin/mannequin_walk03.obj" }
	, mannequinWalk04{ U"assets/models/mannequin/mannequin_walk04.obj" }
	, mannequinWalk05{ U"assets/models/mannequin/mannequin_walk05.obj" }
	, mannequinWalk06{ U"assets/models/mannequin/mannequin_walk06.obj" }
	, mannequinWalk07{ U"assets/models/mannequin/mannequin_walk07.obj" }
	, mannequinWalk08{ U"assets/models/mannequin/mannequin_walk08.obj" }

	, mannequinGuard{ U"assets/models/mannequin/mannequin_guard.obj" }

	, mannequinCollider{
		mannequinRest.boundingBox().scaled(Models::MannequinColliderScale)
	}

	, idleAnimationArray{
		mannequinIdle01,
		mannequinIdle02,
		mannequinIdle01,
		mannequinIdle03,
	}
	, walkAnimationArray{
		mannequinWalk01,
		mannequinWalk02,
		mannequinWalk03,
		mannequinWalk04,
		mannequinWalk05,
		mannequinWalk06,
		mannequinWalk07,
		mannequinWalk08
	}

	, guardAnimationArray{
		mannequinGuard
	}
{

}
