#pragma once

#include "Scene.h"

class CBossWillPase2 :
    public CScene
{
	friend class CSceneManager;

private:
	CBossWillPase2();
	virtual ~CBossWillPase2();

private:
	bool m_UpLegActive;
	bool m_DownLegActive;
	bool m_CrackActive;

private:
	float m_Time;

	std::vector<float> m_vecLeg;

public:
	void SetUpLegActive(bool UpLegActive)
	{
		m_UpLegActive = UpLegActive;
	}

	void SetDownLegActive(bool DownLegActive)
	{
		m_DownLegActive = DownLegActive;
	}

	void SetCrackActive(bool CrackActive)
	{
		m_CrackActive = CrackActive;
	}

	void SetTime(float Time)
	{
		m_Time = Time;
	}

public:
	bool GetUpLegActive() const
	{
		return m_UpLegActive;
	}

	bool GetDownLegActive() const
	{
		return m_DownLegActive;
	}

	bool GetCrackActive() const
	{
		return m_CrackActive;
	}

	float GetTime() const
	{
		return m_Time;
	}

public:
	virtual bool Init();
	virtual bool Update(float DeltaTime);
	virtual bool PostUpdate(float DeltaTime);
	virtual bool Collision(float DeltaTime);
	virtual bool Render(HDC hDC);

private:
	void LoadAnimationSequence();
	void LoadSound();
};

