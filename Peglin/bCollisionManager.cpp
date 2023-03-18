#include "bCollisionManager.h"
#include "bScene.h"
#include "bSceneManager.h"

namespace b
{
	WORD CollisionManager::mMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::End; row++)
		{
			for (UINT col = 0; col < (UINT)eLayerType::End; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (auto leftObject : lefts)
		{
			Collider* leftCollider = leftObject->GetComponent<Collider>();

			if (leftCollider == nullptr)
				continue;

			for (auto rightObject : rights)
			{
				Collider* rightCollider = rightObject->GetComponent<Collider>();

				if (rightCollider == nullptr)
					continue;

				if (leftObject == rightObject)
					continue;

				ColliderCollision(leftCollider, rightCollider, left, right);
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPos();
		Vector2 rightPos = right->GetPos();

		// �� �浹ü ���� �Ÿ��� �� ������ ���ݳ����� ���� ���ؼ� �Ÿ��� �� ��ٸ� �浹x, �Ÿ��� �� ª�ٸ� �浹 o
		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		if (fabs(leftPos.x - rightPos.x) < (leftSize.x / 2.0f) + (rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < (leftSize.y / 2.0f) + (rightSize.y / 2.0f))
		{
			return true;
		}

		return false;
	}

	void CollisionManager::ColliderCollision(Collider* leftCol, Collider* rightCol, eLayerType left, eLayerType right)
	{
		ColliderID colliderID = {};
		colliderID.left = (UINT)leftCol->GetID();
		colliderID.right = (UINT)rightCol->GetID();

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(leftCol, rightCol))
		{
			if (iter->second == false)
			{
				// ���� �浹 �������� �� enter
				leftCol->OnCollisionEnter(rightCol);
				rightCol->OnCollisionEnter(leftCol);

				iter->second = true;
			}
			else
			{
				// �浹 ���� ���� stay
				leftCol->OnCollisionStay(rightCol);
				rightCol->OnCollisionStay(leftCol);
			}
		}
		else
		{
			if (iter->second == true)
			{
				// �浹�� ���� ���� exit
				leftCol->OnCollisionExit(rightCol);
				rightCol->OnCollisionExit(leftCol);

				iter->second = false;
			}
		}
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool value)
	{
		UINT row = 0;
		UINT col = 0;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (left <= right)
		{
			row = iRight;
			col = iLeft;
		}
		else
		{
			row = iLeft;
			col = iRight;
		}

		if (value == true)
			mMatrix[row] |= (1 << col);
		else
			mMatrix[row] &= ~(1 << col);
	}

	void CollisionManager::Clear()
	{
		memset(mMatrix, 0, sizeof(WORD) * (UINT)eLayerType::End);
		mCollisionMap.clear();
	}
}