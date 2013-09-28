static char *tlist_id = 
	"@(#)Copyright (C) H.Shirouzu 1996-2005   tlist.cpp	Ver0.95";
/* ========================================================================
	Project  Name			: Win32 Lightweight  Class Library Test
	Module Name				: List Class
	Create					: 1996-06-01(Sat)
	Update					: 2005-05-03(Tue)
	Copyright				: H.Shirouzu
	Reference				: 
	======================================================================== */

#include "tlib.h"

/*
	TList class
*/
TList::TList(void)
{
	Init();
}

void TList::Init(void)
{
	top.prior = top.next = &top;
}

void TList::AddObj(TListObj * obj)
{
	obj->prior = top.prior;
	top.prior->next = obj;
	obj->next = &top;
	top.prior = obj;
}

void TList::DelObj(TListObj * obj)
{
	if (obj->next)
		obj->next->prior = obj->prior;
	if (obj->prior)
		obj->prior->next = obj->next;
	obj->next = obj->prior = NULL;
}

TListObj* TList::TopObj(void)
{
	return	top.next == &top ? NULL : top.next;
}

TListObj* TList::NextObj(TListObj *obj)
{
	return	obj->next == &top ? NULL : obj->next;
}

void TList::MoveList(TList *from_list)
{
	if (from_list->top.next != &from_list->top) {	// from_list is not empty
		if (top.next == &top) {	// empty
			top = from_list->top;
			top.next->prior = top.prior->next = &top;
		}
		else {
			top.prior->next = from_list->top.next;
			from_list->top.next->prior = top.prior;
			from_list->top.prior->next = &top;
			top.prior = from_list->top.prior;
		}
		from_list->Init();
	}
}

/*
	TRecycleList class
*/
TRecycleList::TRecycleList(int init_cnt, int size)
{
	data = new char [init_cnt * size];
	memset(data, 0, init_cnt * size);

	for (int cnt=0; cnt < init_cnt; cnt++) {
		TListObj *obj = (TListObj *)(data + cnt * size);
		list[FREE_LIST].AddObj(obj);
	}
}

TRecycleList::~TRecycleList()
{
	delete [] data;
}

TListObj *TRecycleList::GetObj(int list_type)
{
	TListObj	*obj = list[list_type].TopObj();

	if (obj)
		list[list_type].DelObj(obj);

	return	obj;
}

void TRecycleList::PutObj(int list_type, TListObj *obj)
{
	list[list_type].AddObj(obj);
}

