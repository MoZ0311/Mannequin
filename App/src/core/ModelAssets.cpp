// ModelAssets class

# include "ModelAssets.hpp"

using namespace Assets;

ModelAssets& ModelAssets::GetInstance()
{
	static ModelAssets instance;
	return instance;
}

ModelAssets::ModelAssets()
	: mannequinRest{ U"assets/models/mannequin/mannequin_rest.obj" }

	, m_mannequinIdle01{ U"assets/models/mannequin/mannequin_idle01.obj" }
	, m_mannequinIdle02{ U"assets/models/mannequin/mannequin_idle02.obj" }
	, m_mannequinIdle03{ U"assets/models/mannequin/mannequin_idle03.obj" }

	, m_mannequinWalk01{ U"assets/models/mannequin/mannequin_walk01.obj" }
	, m_mannequinWalk02{ U"assets/models/mannequin/mannequin_walk02.obj" }
	, m_mannequinWalk03{ U"assets/models/mannequin/mannequin_walk03.obj" }
	, m_mannequinWalk04{ U"assets/models/mannequin/mannequin_walk04.obj" }
	, m_mannequinWalk05{ U"assets/models/mannequin/mannequin_walk05.obj" }
	, m_mannequinWalk06{ U"assets/models/mannequin/mannequin_walk06.obj" }
	, m_mannequinWalk07{ U"assets/models/mannequin/mannequin_walk07.obj" }
	, m_mannequinWalk08{ U"assets/models/mannequin/mannequin_walk08.obj" }

	, m_mannequinLiteAttack01{ U"assets/models/mannequin/mannequin_liteAttack01.obj" }
	, m_mannequinLiteAttack02{ U"assets/models/mannequin/mannequin_liteAttack02.obj" }
	, m_mannequinLiteAttack03{ U"assets/models/mannequin/mannequin_liteAttack03.obj" }
	, m_mannequinLiteAttack04{ U"assets/models/mannequin/mannequin_liteAttack04.obj" }

	, m_mannequinLiteAttack05{ U"assets/models/mannequin/mannequin_liteAttack05.obj" }
	, m_mannequinLiteAttack06{ U"assets/models/mannequin/mannequin_liteAttack06.obj" }
	, m_mannequinLiteAttack07{ U"assets/models/mannequin/mannequin_liteAttack07.obj" }

	, m_mannequinLiteAttack08{ U"assets/models/mannequin/mannequin_liteAttack08.obj" }
	, m_mannequinLiteAttack09{ U"assets/models/mannequin/mannequin_liteAttack09.obj" }
	, m_mannequinLiteAttack10{ U"assets/models/mannequin/mannequin_liteAttack10.obj" }

	, m_mannequinHeavyAttack01{ U"assets/models/mannequin/mannequin_heavyAttack01.obj" }
	, m_mannequinHeavyAttack02{ U"assets/models/mannequin/mannequin_heavyAttack02.obj" }
	, m_mannequinHeavyAttack03{ U"assets/models/mannequin/mannequin_heavyAttack03.obj" }
	, m_mannequinHeavyAttack04{ U"assets/models/mannequin/mannequin_heavyAttack04.obj" }

	, m_mannequinHeavyAttack05{ U"assets/models/mannequin/mannequin_heavyAttack05.obj" }
	, m_mannequinHeavyAttack06{ U"assets/models/mannequin/mannequin_heavyAttack06.obj" }
	, m_mannequinHeavyAttack07{ U"assets/models/mannequin/mannequin_heavyAttack07.obj" }
	, m_mannequinHeavyAttack08{ U"assets/models/mannequin/mannequin_heavyAttack08.obj" }
	, m_mannequinHeavyAttack09{ U"assets/models/mannequin/mannequin_heavyAttack09.obj" }

	, m_mannequinGuard{ U"assets/models/mannequin/mannequin_guard.obj" }

	, qpKowa{ U"assets/models/kowa.obj" }

	, mannequinInsideCollider{
		mannequinRest.boundingBox().scaled(Models::MannequinColliderScale)
	}

	, mannequinOutsideCollider{
		mannequinRest.boundingBox().scaled(Models::MannequinBoundingBoxScale)
	}

	, idleAnimationArray{
		m_mannequinIdle01,
		m_mannequinIdle02,
		m_mannequinIdle01,
		m_mannequinIdle03,
	}
	, walkAnimationArray{
		m_mannequinWalk01,
		m_mannequinWalk02,
		m_mannequinWalk03,
		m_mannequinWalk04,
		m_mannequinWalk05,
		m_mannequinWalk06,
		m_mannequinWalk07,
		m_mannequinWalk08
	}

	, liteAttackAnimationArray01{
		m_mannequinLiteAttack01,
		m_mannequinLiteAttack02,
		m_mannequinLiteAttack03,
		m_mannequinLiteAttack04
	}

	, liteAttackAnimationArray02{
		m_mannequinLiteAttack05,
		m_mannequinLiteAttack06,
		m_mannequinLiteAttack07
	}

	, liteAttackAnimationArray03{
		m_mannequinLiteAttack08,
		m_mannequinLiteAttack09,
		m_mannequinLiteAttack10,
		m_mannequinLiteAttack10,
		m_mannequinLiteAttack10,
	}

	, heavyAttackAnimationArray01{
		m_mannequinHeavyAttack01,
		m_mannequinHeavyAttack02,
		m_mannequinHeavyAttack03,
		m_mannequinHeavyAttack04,
		m_mannequinHeavyAttack04,
		m_mannequinHeavyAttack04
	}

	, heavyAttackAnimationArray02{
		m_mannequinHeavyAttack05,
		m_mannequinHeavyAttack06,
		m_mannequinHeavyAttack07,
		m_mannequinHeavyAttack08,
		m_mannequinHeavyAttack09,
		m_mannequinHeavyAttack09,
		m_mannequinHeavyAttack09
	}

	, guardAnimationArray{
		m_mannequinGuard
	}
{

}
