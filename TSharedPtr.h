#pragma once

// =====================================================================
/**	@class		SharedPtr
	@brief		���� ī��Ʈ ����� �ִ� ���� ������ Ŭ����
	
*/// ===================================================================
template<class T> class SharedPtr
{
public:
	/// if(ptr) �� ���� �˻縦 �����ϰ� �ϱ�����
	class TestProxy{};

	// ===================================================================
	// ��� ����
	// ===================================================================
protected:
	T*				pRep;
	unsigned int*	pUseCount;

	// ===================================================================
	// ��� �Լ�
	// ===================================================================
public:
	// ===================================================================
	inline T& operator*() const		{ return *get(); }
	inline T* operator->() const	{ return  get(); }
	inline bool operator!() const	{ return !get(); }
	// -------------------------------------------------------------------
	/// if(ptr) �� ���� �˻縦 �����ϰ� �ϱ�����
	operator TestProxy*() const
	{
		if(!(*this) || !get() ) 
			return(0);

		static TestProxy testProxy;
		return(&testProxy);
	}
	// ===================================================================
	/// ���������Ͱ� ������ �ִ� �� �����͸� ��´�.
	virtual T* get() const					
	{
		return pRep; 
	}
	/// ���������Ͱ� ������ �ִ� �� �����͸� static_cast �� ��´�.
	template <typename RET>	inline RET* staticGet() const					
	{
		return static_cast<RET*>(get()); 
	}
	/// ���������Ͱ� ������ �ִ� �� �����͸� const_cast �� ��´�.
	template <typename RET>	inline RET* constGet() const					
	{
		return const_cast<RET*>(get()); 
	}
	/// ���������Ͱ� ������ �ִ� �� �����͸� reinterpret_cast �� ��´�.
	template <typename RET>	inline RET* reinterpretGet() const					
	{
		return reinterpret_cast<RET*>(get()); 
	}
	// ===================================================================
	/// �� ���� �����͸� static_cast �� ���� �����͸� ��´�.
	template <typename RET>	inline SharedPtr<RET> staticCast() const
	{
		SharedPtr<RET> sptr(static_cast<RET*>(pRep), pUseCount);
		return sptr;
	}
	/// �� ���� �����͸� const_cast �� ���� �����͸� ��´�.
	template <typename RET>	inline SharedPtr<RET> constCast() const
	{
		SharedPtr<RET> sptr(const_cast<RET*>(pRep), pUseCount);
		return sptr;
	}
	/// �� ���� �����͸� reinterpret_cast �� ���� �����͸� ��´�.
	template <typename RET>	inline SharedPtr<RET> reinterpretCast() const
	{
		SharedPtr<RET> sptr(reinterpret_cast<RET*>(pRep), pUseCount);
		return sptr;
	}
	// ===================================================================
	/// �� ���� �������� ������ �� �ϳ����� �˾ƿ´�.
	inline bool unique() const				
	{ 
		bool res = false;
		if(pUseCount)
			res = static_cast<bool>(*pUseCount==1); 
			
		return res;
	}
	/// �� �����Ͱ� �������� ������ ��´�.
	inline unsigned int useCount() const	
	{ 
		unsigned int res = 0;
		if(pUseCount)
			res = *pUseCount; 

		return res;
	}
	// ===================================================================
	/// �� �������ΰ�?
	inline bool isNull(void) const			
	{ return static_cast<bool>(get()==NULL); }
	/// �� �����͸� �η� �����.
	inline void setNull(void) 
	{ 
		release();

		pRep = NULL;
		pUseCount = NULL;
	}
	// ===================================================================
	// �� �����ڵ�..
	//
	friend inline bool operator==(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() == l.get()); }

	friend inline bool operator!=(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() != l.get()); }

	friend inline bool operator>(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() > l.get()); }

	friend inline bool operator<(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() < l.get()); }

	friend inline bool operator<=(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() <= l.get()); }

	friend inline bool operator>=(SharedPtr<T>& r,SharedPtr<T>& l)
	{ return (r.get() >= l.get()); }

	// ===================================================================
	// ����/�Ҹ�
	// ===================================================================
protected:
	virtual void release(void) 
	{
		bool del = false;

		if (pUseCount)
		{
			if (--(*pUseCount) == 0) 
				del = true;
		}

		if(del)
			destroy();
	}

	virtual void destroy(void)
	{
        delete pRep;
		delete pUseCount;
	}

public:
	// -------------------------------------------------------------------
	SharedPtr() : pRep(NULL), pUseCount(NULL) 
	{
	}
	// -------------------------------------------------------------------
	explicit SharedPtr(T* rep) : pRep(rep)
	{
		if(pRep)
			pUseCount = new unsigned int(1);
		else
			pUseCount = NULL;
	}
	// -------------------------------------------------------------------
	SharedPtr(const SharedPtr& r) 
	{ 
		pRep = r.pRep;
		pUseCount = r.pUseCount;
		if(pUseCount)
			++(*pUseCount); 
	}
	// -------------------------------------------------------------------
	SharedPtr(T* rep, unsigned int* usecnt)
	{
		pRep = rep;
		pUseCount = usecnt;
		if (pUseCount)
			++(*pUseCount);
	}
	// -------------------------------------------------------------------
	SharedPtr& operator=(const SharedPtr& r) 
	{
		if (pRep == r.pRep)
			return *this;
		release();

		pRep = r.pRep;
		pUseCount = r.pUseCount;
		if (pUseCount)
			++(*pUseCount);
	
		return *this;
	}
	// -------------------------------------------------------------------
	virtual ~SharedPtr() 
	{
		release();
	}
	// -------------------------------------------------------------------
};










