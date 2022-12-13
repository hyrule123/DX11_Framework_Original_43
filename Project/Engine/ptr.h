#pragma once

template<typename T>
class Ptr
{
private:
	T*		m_Res;


public:
	T* Get() { return m_Res; }

	T* operator -> ()
	{
		return m_Res;
	}

	void operator = (T* _Res)
	{
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	void operator = (const Ptr<T>& _Res)
	{
		if (nullptr != m_Res)
			m_Res->Release();

		m_Res = _Res.m_Res;

		if (nullptr != m_Res)
			m_Res->AddRef();
	}


public:
	Ptr()
		: m_Res(nullptr)
	{

	}

	Ptr(T* _Res)
		: m_Res(_Res)
	{
		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	Ptr(const Ptr<T>& _Res)
		: m_Res(_Res.m_Res)
	{
		if (nullptr != m_Res)
			m_Res->AddRef();
	}

	~Ptr()
	{
		if (nullptr != m_Res)
		{
			m_Res->Release();
		}
	}
};
