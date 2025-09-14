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

	, mannequinLiteAttack01{ U"assets/models/mannequin/mannequin_liteAttack01.obj" }
	, mannequinLiteAttack02{ U"assets/models/mannequin/mannequin_liteAttack02.obj" }
	, mannequinLiteAttack03{ U"assets/models/mannequin/mannequin_liteAttack03.obj" }
	, mannequinLiteAttack04{ U"assets/models/mannequin/mannequin_liteAttack04.obj" }

	, mannequinLiteAttack05{ U"assets/models/mannequin/mannequin_liteAttack05.obj" }
	, mannequinLiteAttack06{ U"assets/models/mannequin/mannequin_liteAttack06.obj" }
	, mannequinLiteAttack07{ U"assets/models/mannequin/mannequin_liteAttack07.obj" }

	, mannequinLiteAttack08{ U"assets/models/mannequin/mannequin_liteAttack08.obj" }
	, mannequinLiteAttack09{ U"assets/models/mannequin/mannequin_liteAttack09.obj" }
	, mannequinLiteAttack10{ U"assets/models/mannequin/mannequin_liteAttack10.obj" }

	, mannequinHeavyAttack01{ U"assets/models/mannequin/mannequin_heavyAttack01.obj" }
	, mannequinHeavyAttack02{ U"assets/models/mannequin/mannequin_heavyAttack02.obj" }
	, mannequinHeavyAttack03{ U"assets/models/mannequin/mannequin_heavyAttack03.obj" }
	, mannequinHeavyAttack04{ U"assets/models/mannequin/mannequin_heavyAttack04.obj" }

	, mannequinHeavyAttack05{ U"assets/models/mannequin/mannequin_heavyAttack05.obj" }
	, mannequinHeavyAttack06{ U"assets/models/mannequin/mannequin_heavyAttack06.obj" }
	, mannequinHeavyAttack07{ U"assets/models/mannequin/mannequin_heavyAttack07.obj" }
	, mannequinHeavyAttack08{ U"assets/models/mannequin/mannequin_heavyAttack08.obj" }
	, mannequinHeavyAttack09{ U"assets/models/mannequin/mannequin_heavyAttack09.obj" }

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

	, liteAttackAnimationArray01{
		mannequinLiteAttack01,
		mannequinLiteAttack02,
		mannequinLiteAttack03,
		mannequinLiteAttack04
	}

	, liteAttackAnimationArray02{
		mannequinLiteAttack05,
		mannequinLiteAttack06,
		mannequinLiteAttack07
	}

	, liteAttackAnimationArray03{
		mannequinLiteAttack08,
		mannequinLiteAttack09,
		mannequinLiteAttack10,
		mannequinLiteAttack10,
		mannequinLiteAttack10,
	}

	, heavyAttackAnimationArray01{
		mannequinHeavyAttack01,
		mannequinHeavyAttack02,
		mannequinHeavyAttack03,
		mannequinHeavyAttack04,
		mannequinHeavyAttack04,
		mannequinHeavyAttack04
	}

	, heavyAttackAnimationArray02{
		mannequinHeavyAttack05,
		mannequinHeavyAttack06,
		mannequinHeavyAttack07,
		mannequinHeavyAttack08,
		mannequinHeavyAttack09,
		mannequinHeavyAttack09,
		mannequinHeavyAttack09
	}

	, guardAnimationArray{
		mannequinGuard
	}
{

}
